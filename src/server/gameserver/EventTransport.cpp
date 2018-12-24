//////////////////////////////////////////////////////////////////////////////
// Filename    : EventTransport.cpp
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EventTransport.h"
#include "GamePlayer.h"
#include "Zone.h"
#include "PlayerStatus.h"
#include "ZoneGroup.h"
#include "ZonePlayerManager.h"
#include "PlayerStatus.h"
#include "ZoneUtil.h"
#include "PlayerCreature.h"
#include "RelicUtil.h"
#include "CreatureUtil.h"
#include "StringPool.h"
	
#include "Gpackets/GCSystemMessage.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////////////
// class EventTransport member methods
//////////////////////////////////////////////////////////////////////////////

EventTransport::EventTransport(GamePlayer* pGamePlayer) 
	throw()
: Event(pGamePlayer)
{
//	m_pTransportZone = NULL;
//	m_X = m_Y = 0;
}

EventTransport::~EventTransport() 
	throw()
{
}

//----------------------------------------------------------------------
// affect
//----------------------------------------------------------------------
void EventTransport::sendMessage()
	throw(Error)
{
	__BEGIN_TRY

	Assert(m_pGamePlayer != NULL);
	Creature * pCreature = m_pGamePlayer->getCreature();

	Timeval currentTime;
	getCurrentTime(currentTime);

	Turn_t       RemainTime = max(0, (int)(m_Deadline.tv_sec-currentTime.tv_sec));

//	StringStream msg;
//	msg << (int)RemainTime << "�� �Ŀ� " << m_ZoneName << "�� �̵��˴ϴ�.";

    char msg[50];
    sprintf( msg, g_pStringPool->c_str( STRID_TRANSPORT_CREATURE ),
                    (int)RemainTime,
                    m_ZoneName.c_str() );

    string sMsg( msg );

	GCSystemMessage gcSystemMessage;
	gcSystemMessage.setMessage(sMsg);
	pCreature->getPlayer()->sendPacket( &gcSystemMessage );

	//setNextTime( m_MessageTick );

	__END_CATCH
}


void EventTransport::activate () 
	throw (Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG


	Assert(m_pGamePlayer != NULL);

	Creature * pCreature = m_pGamePlayer->getCreature();

	Zone* pOldZone = pCreature->getZone();
	Assert(pOldZone != NULL);

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert(pPC!=NULL);

	bool bSendPacket = true;
	dropRelicToZone( pPC, bSendPacket );
	dropFlagToZone( pPC, bSendPacket );
	dropSweeperToZone( pPC, bSendPacket );

	// Zone���� �����Ѵ�.
	pOldZone->deleteCreature( pCreature, pCreature->getX(), pCreature->getY() );

	// �̵��ؾ��� Zone�� �����Ѵ�.
	pCreature->setNewZone( getZoneByZoneID(m_ZoneID) );
	pCreature->setNewXY( m_X, m_Y );

	try 
	{
		// ���׷��� ZPM���� �÷��̾ �����Ѵ�.
		pOldZone->getZoneGroup()->getZonePlayerManager()->deletePlayer(m_pGamePlayer->getSocket()->getSOCKET());

		// ���⼭ ������������� Save �̺�Ʈ�� IPM���� �������� �ʴ´�.
		m_pGamePlayer->setPlayerStatus(GPS_WAITING_FOR_CG_READY);

		// IPM���� �÷��̾ �ű��.
		//g_pIncomingPlayerManager->pushPlayer(m_pGamePlayer);
		pOldZone->getZoneGroup()->getZonePlayerManager()->pushOutPlayer(m_pGamePlayer);

	} 
	catch (NoSuchElementException& t) 
	{
		filelog("eventTransport.txt", "%s", t.toString().c_str());
		cerr << "EventTransport::activate() : NoSuchElementException" << endl;
		throw Error("���� �÷��̾ �������� �ʽ��ϴ�.");
	}


	__END_DEBUG
	__END_CATCH
}

string EventTransport::toString () const 
	throw ()
{
	StringStream msg;
	msg << "EventTransport("
		<< ")";
	return msg.toString();
}
