//////////////////////////////////////////////////////////////////////////////
// Filename    : EventAuth.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EventAuth.h"
#include "GamePlayer.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Item.h"

#include "Gpackets/GCAuthKey.h"
#include "Gpackets/GCSystemMessage.h"
#include "EventKick.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
EventAuth::EventAuth (GamePlayer* pGamePlayer) 
	throw (Error)
: Event(pGamePlayer)
{
	// 1��
	setDeadline(600);
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
EventAuth::~EventAuth () 
	throw ()
{
}

//////////////////////////////////////////////////////////////////////////////
// activate
//////////////////////////////////////////////////////////////////////////////
void EventAuth::activate () 
	throw (Error)
{
	__BEGIN_TRY

	if (m_pGamePlayer->getPlayerStatus() == GPS_NORMAL) 
	{
		Assert(m_pGamePlayer != NULL);

		if ( !m_pGamePlayer->getCSAuth().IsAuth() )
		{
			filelog("CSAuth.log", "[%s] ���� �ð� ������ �ʰ��߽��ϴ�.", m_pGamePlayer->getID().c_str() );

			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage("nProtect GameGuard ��֤ʧ��.ִ���ļ������GameGuard�ļ���.");
			m_pGamePlayer->sendPacket( &gcSystemMessage );

			EventKick* pKick = new EventKick( m_pGamePlayer );
			pKick->setDeadline(100);
//			pKick->setMessage("GameGuard ���� ���� �ð��� �ʰ��߽��ϴ�.. 10�� �ڿ� ������ ����˴ϴ�.");
			pKick->sendMessage();

			m_pGamePlayer->addEvent( pKick );
		}
		else
		{
			DWORD key = m_pGamePlayer->getCSAuth().GetAuthDword();
			GCAuthKey gcKey;
			gcKey.setKey(key);
			m_pGamePlayer->sendPacket(&gcKey);
		}
	}

	// 5�п� �ѹ�
	Timeval delay;
	delay.tv_sec = 300;
	delay.tv_usec = 0;

	m_Deadline = m_Deadline + delay;
	
	__END_CATCH
}
