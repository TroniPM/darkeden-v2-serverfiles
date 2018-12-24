//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRingOfFlare.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectDeadlyGland.h"
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
EffectDeadlyGland::EffectDeadlyGland(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

void EffectDeadlyGland::affect()
	throw(Error)
{
	__BEGIN_TRY


	Creature* pCastCreature = dynamic_cast<Creature*>(m_pTarget);
	Assert( pCastCreature != NULL );

	Zone* pZone = pCastCreature->getZone();
	Assert( pZone != NULL );

	Creature* pAttacker = pZone->getCreature( m_UserObjectID );
	Assert( pAttacker != NULL );
cout << "���⼭ ���ϵǳ�?"<<endl;
	if ( pCastCreature == NULL || !pAttacker->isVampire() ) return;

	Vampire* pVampire = dynamic_cast<Vampire*>(pAttacker);
	Assert( pVampire != NULL );

	Player* pPlayer = dynamic_cast<Player*>(pAttacker->getPlayer());
	Assert( pPlayer != NULL );
cout << "���⼭ ���ϵǳ�? 2"<<endl;
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

			// Ÿ�Ͼȿ� ����?ϴ?������Ʈ�� �����´�.
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
				  || pCreature->isVampire()
				  || !checkZoneLevelToHitTarget(pCreature)
				)
				{
					continue;
				}

				if ( pCreature->isPC() )
				{
cout << "���⼭ ���ϵǳ�? 3"<<endl;
					//cout << pCreature->getName() << "�� RingOfFlare�� " << m_Damage << "��ŭ�� �������� ����ϴ�." << endl;
					GCModifyInformation gcMI;
					::setDamage( pCreature, m_Damage, pCastCreature, SKILL_SUMMON_DEADLY_GLAND, &gcMI, &gcAttackerMI, false );

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
cout << "���⼭ ���ϵǳ�? 4"<<endl;
					Monster* pMonster = dynamic_cast<Monster*>(pCreature);

					::setDamage( pMonster, m_Damage, pCastCreature, SKILL_SUMMON_DEADLY_GLAND, NULL, &gcAttackerMI, false );

					pMonster->addEnemy( pCastCreature );
				}

				GCSkillToObjectOK4 gcSkillToObjectOK4;
				gcSkillToObjectOK4.setSkillType( SKILL_ATTACK_MELEE );
				gcSkillToObjectOK4.setTargetObjectID( pCreature->getObjectID() );
				gcSkillToObjectOK4.setDuration(0);

				pZone->broadcastPacket( X, Y, &gcSkillToObjectOK4, pCreature );

				// �׾����� ����ġ�ش�. ��.....
				if ( pAttacker != NULL )
				{
					if (pCreature->isDead() && pAttacker->isVampire())
					{
						Vampire* pCastOusters = dynamic_cast<Vampire*>( pAttacker);
						Assert( pCastOusters != NULL );

						int exp = computeCreatureExp(pCreature, 100);
						shareVampExp(pCastOusters, exp, gcAttackerMI);

					}
				}

				if ( gcAttackerMI.getShortCount() != 0 || gcAttackerMI.getLongCount() != 0 ) pAttacker->getPlayer()->sendPacket(&gcAttackerMI);
			}
		}
	}

	setNextTime( 10 );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDeadlyGland::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectDeadlyGland" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isMonster());

	// �÷��׸� ����.
	pCreature->removeFlag(Effect::EFFECT_CLASS_DEADLY_GLAND);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// ����Ʈ�� �����϶�� �˷��ش�.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(getSendEffectClass());
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectDeadlyGland" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDeadlyGland::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectDeadlyGland::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectDeadlyGland("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH

}

