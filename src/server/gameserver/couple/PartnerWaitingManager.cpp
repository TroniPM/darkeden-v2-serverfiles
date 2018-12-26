#include "PlayerCreature.h"
#include "PCFinder.h"

#include "WaitForMeet.h"
#include "WaitForApart.h"

#include "VariableManager.h"
#include "PartnerWaitingManager.h"

#include "Zone.h"
#include "PlayerCreature.h"

#include "Gpackets/GCNPCResponse.h"

PartnerWaitInfo::PartnerWaitInfo( PlayerCreature* pWaitingPC, string RequestedPCName )
{
	Assert( pWaitingPC != NULL );

	m_pZone = pWaitingPC->getZone();
	Assert( m_pZone != NULL );

	m_RequestedPCName = RequestedPCName;
	m_WaitingPCOID = pWaitingPC->getObjectID();

	// ���ѽð� 1��
	Timeval currentTime;
	getCurrentTime( currentTime );
	m_Deadline = currentTime;
	m_Deadline.tv_sec += 60;
}

PartnerWaitInfo* PartnerWaitInfo::getPartnerWaitInfo(PlayerCreature* pWaitingPC, string RequestedPCName, WaitType waitType)
	
{
	__BEGIN_TRY

	Assert( pWaitingPC != NULL );

	switch( waitType )
	{
		case WAIT_FOR_MEET:
			return new WaitForMeet( pWaitingPC, RequestedPCName );
		case WAIT_FOR_APART:
			return new WaitForApart( pWaitingPC, RequestedPCName );
		default:
			return NULL;
	}

	__END_CATCH
}

PlayerCreature*	PartnerWaitInfo::getWaitingPC() const
{
	__BEGIN_TRY

	Assert( m_pZone != NULL );

	Creature* pCreature = m_pZone->getCreature( m_WaitingPCOID );
	if ( pCreature != NULL )
	{
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
		Assert( pPC != NULL );

		return pPC;
	}

	return NULL;

	__END_CATCH
}

PartnerWaitingManager::~PartnerWaitingManager()
{
	WaitInfoHashMap::iterator itr = m_WaitInfos.begin();

	for( ; itr != m_WaitInfos.end(); itr++ )
	{
		SAFE_DELETE( itr->second );
	}

	m_WaitInfos.clear();
}

// ���ο� PartnerWaitInfo�� ����� ����Ѵ�.
uint PartnerWaitingManager::waitForPartner( PlayerCreature* pWaitingPC, string RequestedPCName )
	
{
	__BEGIN_TRY

	if ( !g_pVariableManager->isActivateCouple() ) return COUPLE_MESSAGE_NOT_EVENT_TERM;

	Assert( pWaitingPC != NULL );
	if ( isWaitForPartner( pWaitingPC ) ) return COUPLE_MESSAGE_ALREADY_WAITING;

	PlayerCreature* pTargetPC = NULL;

    __ENTER_CRITICAL_SECTION((*g_pPCFinder))

    Creature* pTargetCreature = g_pPCFinder->getCreature_LOCKED(RequestedPCName);
    if (pTargetCreature!=NULL)
    {
		if ( !pTargetCreature->isPC() )
		{
			g_pPCFinder->unlock();
			return COUPLE_MESSAGE_LOGOFF;
		}

		pTargetPC = dynamic_cast<PlayerCreature*>( pTargetCreature );
		Assert( pTargetPC != NULL );
    }

	__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

	if ( pTargetPC == NULL ) return COUPLE_MESSAGE_LOGOFF;

	// PartnerWaitInfo �� FactoryMethod �� ���ο� PartnerWaitInfo �� ��ü�� �����. WaitForMeet or WaitForApart
	PartnerWaitInfo* pPartnerWaitInfo = PartnerWaitInfo::getPartnerWaitInfo( pWaitingPC, RequestedPCName, getWaitType() );
	Assert( pPartnerWaitInfo != NULL );

	uint result = pPartnerWaitInfo->waitPartner( pTargetPC );
	if ( result != 0 )
	{
		SAFE_DELETE( pPartnerWaitInfo );
		return result;
	}

	m_WaitInfos[ RequestedPCName ] = pPartnerWaitInfo;

	return 0;

	__END_CATCH
}

// �ش��ϴ� PC�� ��ٸ��� �ִ� ��Ʈ�� ��û�� ã�Ƽ� �����.
bool PartnerWaitingManager::stopWaitForPartner( PlayerCreature* pWaitingPC )
	
{
	__BEGIN_TRY

	Assert( pWaitingPC != NULL );

	WaitInfoHashMap::iterator itr = m_WaitInfos.begin();

	for( ; itr != m_WaitInfos.end(); itr++ )
	{
		if ( pWaitingPC == itr->second->getWaitingPC() )
		{
			SAFE_DELETE( itr->second );
			m_WaitInfos.erase( itr );
			return true;
		}
	}

	return false;

	__END_CATCH
}

uint PartnerWaitingManager::acceptPartner( PlayerCreature* pRequestedPC )
	
{
	__BEGIN_TRY

	if ( !g_pVariableManager->isActivateCouple() ) return COUPLE_MESSAGE_NOT_EVENT_TERM;

	Assert( pRequestedPC != NULL );

	WaitInfoHashMap::iterator itr = m_WaitInfos.find( pRequestedPC->getName() );
	// �� ����� ��ٸ��� �ڰ� ����.
	if ( itr == m_WaitInfos.end() ) return COUPLE_MESSAGE_NO_WAITING;

	PartnerWaitInfo* pPartnerWaitInfo = itr->second;
	Assert( pPartnerWaitInfo != NULL );

	PlayerCreature* pWaitingPC = pPartnerWaitInfo->getWaitingPC();
	if ( pWaitingPC == NULL )
		return COUPLE_MESSAGE_LOGOFF;

	// ������ ������ ����� �� ����.
	if ( pWaitingPC->getSex() == pRequestedPC->getSex() ) return COUPLE_MESSAGE_SAME_SEX;

	uint result = pPartnerWaitInfo->acceptPartner( pRequestedPC );

	// ����� ���Ŀ� �����ش�.
	SAFE_DELETE( pPartnerWaitInfo );
	m_WaitInfos.erase( itr );

	return result;

	__END_CATCH
}

bool PartnerWaitingManager::isWaitForPartner( PlayerCreature* pRequestedPC )
	
{
	__BEGIN_TRY

	WaitInfoHashMap::iterator itr = m_WaitInfos.find( pRequestedPC->getName() );
	return ( itr != m_WaitInfos.end() );

	__END_CATCH
}

PlayerCreature* PartnerWaitingManager::getWaitingPartner( PlayerCreature* pRequestedPC )
	
{
	__BEGIN_TRY

	WaitInfoHashMap::iterator itr = m_WaitInfos.find( pRequestedPC->getName() );
	if ( itr == m_WaitInfos.end() ) return NULL;

	return itr->second->getWaitingPC();
	
	__END_CATCH
}

void PartnerWaitingManager::heartbeat()
	
{
	__BEGIN_TRY

	WaitInfoHashMap::iterator itr = m_WaitInfos.begin();

	for ( ; itr != m_WaitInfos.end() ; )
	{
		PartnerWaitInfo* pPartnerWaitInfo = itr->second;
		Assert( pPartnerWaitInfo != NULL );

		Timeval currentTime;
		getCurrentTime( currentTime );

		if ( pPartnerWaitInfo->getDeadline() < currentTime )
		{
			WaitInfoHashMap::iterator delitr = itr;
			itr++;

			// ��������� ������!
			pPartnerWaitInfo->timeExpired();
			SAFE_DELETE( pPartnerWaitInfo );
			m_WaitInfos.erase( delitr );
		}
		else
		{
			itr++;
		}
	}

	__END_CATCH
}

