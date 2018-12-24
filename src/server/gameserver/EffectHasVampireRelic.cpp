//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHasVampireRelic.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectHasVampireRelic.h"
#include "ZoneInfoManager.h"
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
EffectHasVampireRelic::EffectHasVampireRelic(Creature* pCreature)
	throw(Error)
: EffectHasRelic(pCreature)
{
	__BEGIN_TRY

	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectHasVampireRelic::EffectHasVampireRelic(Item* pItem)
	throw(Error)
: EffectHasRelic(pItem)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHasVampireRelic::affect(Creature* pCreature)
	throw(Error)
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

	GCSystemMessage gcSystemMessage;
	gcSystemMessage.setMessage(msg.toString());

	g_pZoneGroupManager->broadcast( &gcSystemMessage );
	*/
	// �� ������ ��´�.
	Zone* pZone = pCreature->getZone();
	Assert(pZone!=NULL);

	ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( pZone->getZoneID() );
	Assert( pZoneInfo != NULL );

    // ��ġ�� �˸���.
    char msg[100];

	const char* race;
	if ( pCreature->isSlayer() )
	{
		race = g_pStringPool->c_str( STRID_SLAYER );
	}
	else if ( pCreature->isVampire() )
	{
		race = g_pStringPool->c_str( STRID_VAMPIRE );
	}
	else if ( pCreature->isOusters() )
	{
		race = g_pStringPool->c_str( STRID_OUSTERS );
	}

    sprintf( msg, g_pStringPool->c_str( STRID_HAVING_VAMPIRE_RELIC ),
                pCreature->getName().c_str(),
				race,
//                ( pCreature->isSlayer() ? g_pStringPool->c_str( STRID_SLAYER ) : g_pStringPool->c_str( STRID_VAMPIRE ) ),
                (int)pCreature->getX(),
                (int)pCreature->getY()
    );

/*	// ��ġ�� �˸���.
	StringStream msg;
	msg << pCreature->getName() << " ��(" << ( pCreature->isSlayer() ? "�����̾�" : "�����̾�" ) << ")�� " 
		<< pZoneInfo->getFullName() << "(" << (int)pCreature->getX() << ", " << (int)pCreature->getY()
		<< ")���� �����̾� ������ ������ �ֽ��ϴ�."; */

	GCSystemMessage gcSystemMessage;
	gcSystemMessage.setMessage(msg);

	g_pZoneGroupManager->broadcast( &gcSystemMessage );

	setNextTime(m_Tick);

	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHasVampireRelic::affect(Item* pItem)
	throw(Error)
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

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectHasVampireRelic::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectHasVampireRelic("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
