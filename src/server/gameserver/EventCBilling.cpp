//////////////////////////////////////////////////////////////////////////////
// Filename    : EventCBilling.cpp
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EventCBilling.h"
#include "GamePlayer.h"
#include "chinabilling/CBillingPlayerManager.h"
#include "Assert.h"


//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
EventCBilling::EventCBilling (GamePlayer* pGamePlayer) 
	
: Event(pGamePlayer),
  m_TrySendLoginCount(0)
{
}


//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
EventCBilling::~EventCBilling () 
	
{
}

			
//////////////////////////////////////////////////////////////////////////////
// activate
//////////////////////////////////////////////////////////////////////////////
void EventCBilling::activate () 
	
{
	__BEGIN_TRY

	Assert(m_pGamePlayer != NULL);

	if ( !m_pGamePlayer->isCBillingVerified() )
	{
		// ���� Login ��Ŷ�� ������ ���ߴٸ� �ٽ� ������. ( ������ ���� �־ ������ ���� �����̴�. )
		m_pGamePlayer->setCBillingVerified( g_pCBillingPlayerManager->sendLogin( m_pGamePlayer ) );
		m_TrySendLoginCount++;
	}

	// Login ��Ŷ�� ���´ٸ� minus point packet �� ������, �ƴ϶�� �׾� �д�.
	if ( m_pGamePlayer->isCBillingVerified() )
	{
		// ���� ��Ŷ�� ������. minus point/minute
		if ( !g_pCBillingPlayerManager->sendMinusPoint( m_pGamePlayer ) )
		{
			m_pGamePlayer->increaseMissedMinusPointPacket();
		}

		// send missed minus point packet
		while ( m_pGamePlayer->hasMissedMinusPointPacket() )
		{
			if ( g_pCBillingPlayerManager->sendMinusPoint( m_pGamePlayer ) )
			{
				m_pGamePlayer->decreaseMissedMinusPointPacket();
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		// Login packet �� ������ ���� �����̴�. minus packet �� �������ɷ� �ϰ� �׾Ƶд�.
		m_pGamePlayer->increaseMissedMinusPointPacket();
	}

	// ������ ���� �ð� �����Ѵ�. �� ����
	static int interval = g_pCBillingPlayerManager->getMinusIntervalInt();

	Timeval delay;
	delay.tv_sec = interval * 60;
	delay.tv_usec = 0;

	m_Deadline = m_Deadline + delay;
	
	__END_CATCH
}
