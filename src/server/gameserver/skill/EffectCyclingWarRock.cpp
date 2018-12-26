//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRingOfFlare.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectCyclingWarRock.h"
#include "Ousters.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "PCFinder.h"
#include "ZoneUtil.h"
#include "ZoneInfoManager.h"
#include "SkillUtil.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectCyclingWarRock::EffectCyclingWarRock(Creature* pCreature)
	
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	Assert(pCreature->isOusters());

	setTarget(pCreature);

	__END_CATCH
}

void EffectCyclingWarRock::affect()
	
{
	__BEGIN_TRY

	Creature* pCastCreature = dynamic_cast<Creature*>(m_pTarget);

	if ( pCastCreature == NULL || !pCastCreature->isOusters() ) return;

	Ousters* pOusters = dynamic_cast<Ousters*>(pCastCreature);
	Assert( pOusters != NULL );

	Item* pWeapon = pOusters->getWearItem(Ousters::WEAR_RIGHTHAND);
	if (pWeapon == NULL || pWeapon->getItemClass() != Item::ITEM_CLASS_OUSTERS_WRISTLET || !pOusters->isRealWearingEx(Ousters::WEAR_RIGHTHAND))
	{
		// �߰��� ����Ʋ���� �������� ����Ʈ�� �������.
		setDeadline(0);
		return;
	}

	Player* pPlayer = dynamic_cast<Player*>(pCastCreature->getPlayer());
	Assert( pPlayer != NULL );

	Zone* pZone = pCastCreature->getZone();
	Assert( pZone != NULL );

	VSRect rect( 0, 0, pZone->getWidth()-1, pZone->getHeight()-1 );

	ZoneCoord_t Cx = pCastCreature->getX();
	ZoneCoord_t Cy = pCastCreature->getY();

	for ( int x=-2; x<=2; x++ )
	{
		for ( int y=-2; y<=2; y++ )
		{
			if ( x == 0 && y == 0 ) continue;

			int X = Cx + x;
			int Y = Cy + y;

			if ( !rect.ptInRect( X, Y ) ) continue;

			// Ÿ�Ͼȿ� �����ϴ� ������Ʈ�� �����´�.
			Tile& tile = pZone->getTile( X, Y );

			if( tile.hasCreature(Creature::MOVE_MODE_WALKING) )
			{
				Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
				Assert( pCreature != NULL );
				
				GCModifyInformation gcAttackerMI;

				// �ڽ��� ���� �ʴ´�. ������ �� �´´�. �����̾ �� �´���.
				// �������� üũ
				// 2003.1.10 by bezz, Sequoia
				if ( pCreature == m_pTarget
				  || !canAttack( pCastCreature, pCreature )
				  || pCreature->isFlag( Effect::EFFECT_CLASS_COMA )
				  || pCreature->isOusters()
				  || !checkZoneLevelToHitTarget(pCreature)
				)
				{
					continue;
				}

				if ( pCreature->isPC() )
				{
					//cout << pCreature->getName() << "�� CyclingWarRock�� " << m_Damage << "��ŭ�� �������� ����ϴ�." << endl;
					GCModifyInformation gcMI;
					::setDamage( pCreature, m_Damage, pCastCreature, SKILL_CYCLING_WAR_ROCK, &gcMI, &gcAttackerMI );

					pCreature->getPlayer()->sendPacket( &gcMI );

					// �´� ������ �����ش�.
					GCSkillToObjectOK2 gcSkillToObjectOK2;
					gcSkillToObjectOK2.setObjectID( 1 );    // �ǹ� ����.
					gcSkillToObjectOK2.setSkillType( SKILL_ATTACK_MELEE );
					gcSkillToObjectOK2.setDuration(0);
					pCreature->getPlayer()->sendPacket(&gcSkillToObjectOK2);

				}
				else if ( pCreature->isMonster() )
				{
					Monster* pMonster = dynamic_cast<Monster*>(pCreature);

					::setDamage( pMonster, m_Damage, pCastCreature, SKILL_CYCLING_WAR_ROCK, NULL, &gcAttackerMI );

					pMonster->addEnemy( pCastCreature );
				}

				GCSkillToObjectOK4 gcSkillToObjectOK4;
				gcSkillToObjectOK4.setSkillType( SKILL_ATTACK_MELEE );
				gcSkillToObjectOK4.setTargetObjectID( pCreature->getObjectID() );
				gcSkillToObjectOK4.setDuration(0);

				pZone->broadcastPacket( X, Y, &gcSkillToObjectOK4, pCreature );

				// �׾����� ����ġ�ش�. ��.....
				if ( pCastCreature != NULL )
				{
					if (pCreature->isDead() && pCastCreature->isOusters())
					{
						Ousters* pCastOusters = dynamic_cast<Ousters*>( pCastCreature );
						Assert( pCastOusters != NULL );

						int exp = computeCreatureExp(pCreature, 100, pCastOusters);
						shareOustersExp(pCastOusters, exp, gcAttackerMI);

					}
				}

				if ( gcAttackerMI.getShortCount() != 0 || gcAttackerMI.getLongCount() != 0 ) pCastCreature->getPlayer()->sendPacket(&gcAttackerMI);
			}
		}
	}

	setNextTime( 10 );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectCyclingWarRock::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY

	//cout << "EffectCyclingWarRock" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isOusters());

	// �÷��׸� ����.
	pCreature->removeFlag(Effect::EFFECT_CLASS_CYCLING_WAR_ROCK);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	Ousters* pTargetOusters = dynamic_cast<Ousters*>(pCreature);
	Assert( pTargetOusters != NULL );

	// ����Ʈ�� �����϶�� �˷��ش�.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(getSendEffectClass());
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectCyclingWarRock" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectCyclingWarRock::unaffect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectCyclingWarRock::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectCyclingWarRock("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH

}

