//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHeavenGround.cpp
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#include "EffectCurseOfBloodGround.h"
#include "Zone.h"
#include "Tile.h"

#include "EffectTrapTriggered.h"
#include "Monster.h"

#include "Gpackets/GCDeleteEffectFromTile.h"
#include "Gpackets/GCAddEffect.h"


#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "SkillUtil.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
EffectCurseOfBloodGround::EffectCurseOfBloodGround( Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y )
	throw(Error)
{
	__BEGIN_TRY

	m_pZone = pZone;
	m_X = X;
	m_Y = Y;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectCurseOfBloodGround::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Tile& tile = m_pZone->getTile( m_X, m_Y );
	tile.deleteEffect( m_ObjectID );
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectCurseOfBloodGround::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectCurseOfBloodGround("
		<< "Level:" << (int)m_Level
		<< ")";
	return msg.toString();

	__END_CATCH
}
/*
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectCurseOfBloodGround::EffectCurseOfBloodGround( Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y )
	throw(Error)
{
	__BEGIN_TRY

	m_pZone = pZone;
	m_X = X;
	m_Y = Y;
	m_UserObjectID = 0;
	m_bSlayer = false;
	m_Damage = 0;
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectCurseOfBloodGround::affect()
	throw(Error)
{
	__BEGIN_TRY

		Assert(m_pZone != NULL);
	//cout << "UserObejctID:" << (int)m_UserObjectID << endl;
	// ��ȡʹ�ü��ܵ�����
	Creature * pCastCreature = m_pZone->getCreature( m_UserObjectID );

	if ( pCastCreature == NULL  )
	{
		setNextTime(m_Tick);

		return;
	}
	//Slayer* pSlayer = dynamic_cast<Slayer*>(pSlayer);

	// ȡ����ͼ
	Tile& tile = m_pZone->getTile(m_X, m_Y);

	// ��ȡ��ͼ��Ʒ����
	const slist<Object*>& oList = tile.getObjectList();
	slist<Object*>::const_iterator itr = oList.begin();
	for (; itr != oList.end(); itr++) 
	{
		Assert(*itr != NULL);

		Object* pObject = *itr;
		Assert(pObject != NULL);

		if (pObject->getObjectClass() == Object::OBJECT_CLASS_CREATURE)
		{
			Creature* pCreature = dynamic_cast<Creature*>(pObject);
			Assert(pCreature != NULL);

			// ��⵱ǰ�����Ƿ�ɹ���
			if ( !canAttack( pCastCreature, pCreature )
				|| pCreature->isFlag(Effect::EFFECT_CLASS_IMMUNE_TO_ACID)
				|| pCreature->isFlag(Effect::EFFECT_CLASS_COMA) 
				)
			{
				continue;
			}

			// ����ͼ�ȼ�
			if( !checkZoneLevelToHitTarget( pCreature ) ) continue;
			// �����˺�
			int AcidDamage = computeMagicDamage(pCreature, m_Damage, SKILL_CURSE_OF_BLOOD2, m_bSlayer, pCastCreature);
			// ���еĲ�����
			if (pCreature->getMoveMode() != Creature::MOVE_MODE_FLYING)
			{
				GCModifyInformation gcAttackerMI;
				GCModifyInformation gcDefenderMI;
				// ���������,�򲻻�����˺�
				if (pCreature->isVampire())
				{
					continue;
				}
				else 	if (pCreature->isSlayer()) 
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

					::setDamage( pSlayer, AcidDamage, pCastCreature, SKILL_CURSE_OF_BLOOD2, &gcDefenderMI, &gcAttackerMI, false );

					Player* pPlayer = pSlayer->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(&gcDefenderMI);

					//setNextTime(m_Tick);
					//return;
				} 
				else if (pCreature->isOusters())
				{
					Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

					::setDamage( pOusters, AcidDamage, pCastCreature, SKILL_CURSE_OF_BLOOD2, &gcDefenderMI, &gcAttackerMI, false );

					Player* pPlayer = pOusters->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(&gcDefenderMI);
				}
				else if (pCreature->isMonster())
				{
					Monster* pMonster = dynamic_cast<Monster*>(pCreature);

					::setDamage( pMonster, AcidDamage, pCastCreature, SKILL_CURSE_OF_BLOOD2, NULL, &gcAttackerMI, false );
				}

				bool modifiedAttacker = false;

				// �׾����� ����ġ�ش�. ��.....
// 				if ( pCastCreature != NULL )
// 				{
// 					if (pCreature->isDead() && pCastCreature->isVampire())
// 					{
// 						//computeAlignmentChange(pCreature, AcidDamage, pSlayer, &gcDefenderMI, &gcAttackerMI);
// 						//decreaseDurability(pSlayer, pCreature, NULL, &gcAttackerMI, &gcDefenderMI);
// 
// 						// Ÿ���� �����̾ �ƴ� ��쿡�� ����ġ�� �÷��ش�.
// 						if (!pCreature->isSlayer())
// 						{
// // 							//shareAttrExp(pSlayer, AcidDamage , 1, 1, 8, _GCSkillToObjectOK1);
// // 							increaseDomainExp(pSlayer, SKILL_CURSE_OF_BLOOD2, pSkillInfo->getPoint(), gcAttackerMI, pTargetCreature->getLevel());
// // 							increaseSkillExp(pSlayer, SKILL_HEAVEN_GROUND,  pSkillSlot, pSkillInfo, gcAttackerMI);
// // 							increaseAlignment(pSlayer, pCreature, gcAttackerMI);
// 						}
// 						modifiedAttacker = true;
// 					}
// 				}

				// ���� ����ϱ�
				if ( pCastCreature != NULL
					&& pCastCreature->isPC()
					&& pCreature->isPC()
						)
					{
						computeAlignmentChange( pCreature, AcidDamage, pCastCreature, &gcDefenderMI, &gcAttackerMI );
						modifiedAttacker = true;
					}

					if (modifiedAttacker) pCastCreature->getPlayer()->sendPacket( &gcAttackerMI );
			}
		}
	}

	setNextTime(m_Tick);

	//cout << "EffectAcidSwamp" << "affect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectCurseOfBloodGround::affect(Zone* pZone, ZoneCoord_t Cx, ZoneCoord_t Cy)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectCurseOfBloodGround::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Tile& tile = m_pZone->getTile( m_X, m_Y );
	tile.deleteEffect( m_ObjectID );

	GCDeleteEffectFromTile gcDeleteEffect;
	gcDeleteEffect.setXY( m_X, m_Y );
	gcDeleteEffect.setObjectID( getObjectID() );
	gcDeleteEffect.setEffectID( getSendEffectClass() );

	m_pZone->broadcastPacket( m_X, m_Y, &gcDeleteEffect );
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectCurseOfBloodGround::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectCurseOfBloodGround("
		<< ")";
	return msg.toString();

	__END_CATCH
}
*/
