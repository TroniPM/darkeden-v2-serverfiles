//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectVampireRelic.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectVampireRelic.h"
#include "ZoneGroupManager.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "MonsterCorpse.h"
#include "Player.h"
#include "StringPool.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCSystemMessage.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectVampireRelic::EffectVampireRelic(Creature* pCreature)
	
{
	__BEGIN_TRY

	m_HPRecovery = 1;

	setTarget(pCreature);

	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectVampireRelic::EffectVampireRelic(Item* pItem)
	
{
	__BEGIN_TRY

	m_HPRecovery = 1;

	setTarget(pItem);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectVampireRelic::affect(Creature* pCreature)
	
{
	__BEGIN_TRY
																															    	
	//Timeval      nextTime   = getNextTime();
	//Timeval      deadLine   = getDeadline();
	//Turn_t       RemainTime = deadLine.tv_sec - nextTime.tv_sec;

/*
	StringStream msg;

	if (pCreature->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

		msg << pSlayer->getName();
	}
	else
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

		msg << pVampire->getName();
	}

	msg << " ���� �����̾� ������ �������ϴ�.";
*/

    char msg[50];
    sprintf( msg, g_pStringPool->c_str( STRID_TAKE_VAMPIRE_RELIC ),
                    pCreature->getName().c_str() );

    string sMsg( msg );

	GCSystemMessage gcSystemMessage;

	gcSystemMessage.setType(SYSTEM_MESSAGE_COMBAT);
	gcSystemMessage.setMessage(sMsg);

	g_pZoneGroupManager->broadcast( &gcSystemMessage );


	// Effect���δ�.
	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID( pCreature->getObjectID() );
	gcAddEffect.setEffectID( getSendEffectClass() );
	gcAddEffect.setDuration( 65000 );
	pCreature->getZone()->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcAddEffect);

	setNextTime(m_Tick);

	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectVampireRelic::affect(Item* pItem)
	
{
	__BEGIN_TRY
																															    	
		/*
	//Timeval      nextTime   = getNextTime();
	//Timeval      deadLine   = getDeadline();
	//Turn_t       RemainTime = deadLine.tv_sec - nextTime.tv_sec;
	StringStream msg;

	if (pCreature->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

		msg << pSlayer->getName() << " ���� ";
	}
	else
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

		msg << pVampire->getName() << " ���� ";
	}

	msg << " �����̾� ������ ������ �ֽ��ϴ�." << endl;

	GCSystemMessage gcSystemMessage;
	gcSystemMessage.setMessage(msg.toString());

	g_pZoneGroupManager->broadcast( &gcSystemMessage );

	setNextTime(m_Tick);
	*/

	__END_CATCH
}

void EffectVampireRelic::unaffect() 
	
{
	__BEGIN_TRY	

	
	switch (m_pTarget->getObjectClass())
	{
		case OBJECT_CLASS_CREATURE :
		{
			Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
			unaffect(pCreature);
		}
		break;

		case OBJECT_CLASS_ITEM :
		{
			Item* pItem = dynamic_cast<Item *>(m_pTarget);
			unaffect(pItem);
		}
		break;

		default :
			throw Error("Wrong Object Class");
	}


	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectVampireRelic::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectVampireRelic" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	// �ɷ�ġ�� ���������� �ǵ����� ���ؼ��� �÷��׸� ����,
	// initAllStat�� �ҷ��� �Ѵ�.
	pCreature->removeFlag(Effect::EFFECT_CLASS_VAMPIRE_RELIC);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_VAMPIRE_RELIC);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectVampireRelic" << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectVampireRelic::unaffect(Item* pItem)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectVampireRelic" << "unaffect BEGIN" << endl;

	Assert(pItem != NULL);

	Assert(pItem->getItemClass()==Item::ITEM_CLASS_CORPSE);
	Assert(pItem->getItemType()==MONSTER_CORPSE);

	MonsterCorpse* pCorpse = dynamic_cast<MonsterCorpse*>(pItem);

	pCorpse->removeFlag(Effect::EFFECT_CLASS_VAMPIRE_RELIC);

	Zone* pZone = pCorpse->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pItem->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_VAMPIRE_RELIC);
	pZone->broadcastPacket(pCorpse->getX(), pCorpse->getY(), &gcRemoveEffect);

	//cout << "EffectVampireRelic" << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectVampireRelic::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectVampireRelic("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
