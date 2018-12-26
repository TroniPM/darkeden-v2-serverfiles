//////////////////////////////////////////////////////////////////////////////
// Filename    : EventRefreshHolyLandPlayer.cpp
// Written by  : bezz
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EventRefreshHolyLandPlayer.h"
#include "HolyLandManager.h"
//#include "BloodBibleBonusManager.h"
#include "Zone.h"
#include "ZoneGroupManager.h"
#include "ZoneGroup.h"

//#include "Gpackets/GCHolyLandBonusInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class EventRefreshHolyLandPlayer member methods
//////////////////////////////////////////////////////////////////////////////

EventRefreshHolyLandPlayer::EventRefreshHolyLandPlayer( GamePlayer* pGamePlayer )
	throw ()
	:Event(pGamePlayer)
{
}

void EventRefreshHolyLandPlayer::activate () 
	
{
	__BEGIN_TRY

	const hash_map<ZoneGroupID_t, ZoneGroup*>& zoneGroups = g_pZoneGroupManager->getZoneGroups();

	hash_map<ZoneGroupID_t, ZoneGroup*>::const_iterator itr = zoneGroups.begin();

	for ( ; itr != zoneGroups.end(); ++itr )
	{
		const hash_map< ZoneID_t, Zone* >& zones = itr->second->getZones();
		hash_map< ZoneID_t, Zone* >::const_iterator zItr = zones.begin();

		for ( ; zItr != zones.end(); ++zItr )
		{
//			cout << zItr->second->getZoneID() << " �� update" << endl;
			zItr->second->setRefreshHolyLandPlayer(true);
		}
	}

	// �ƴ��� ������ �ִ� �÷��̾���� ������ ���� ����Ѵ�.(���� ���� ���ʽ�)
//	g_pHolyLandManager->refreshHolyLandPlayers();

/*	// �ƴ��� ���� ������ ���� ���� ���ʽ� ������ �Ѹ���.
	GCHolyLandBonusInfo gcHolyLandBonusInfo;
	g_pBloodBibleBonusManager->makeHolyLandBonusInfo( gcHolyLandBonusInfo );
	g_pHolyLandManager->broadcast( &gcHolyLandBonusInfo );
*/
	__END_CATCH
}

string EventRefreshHolyLandPlayer::toString () const 
	throw ()
{
	StringStream msg;
	msg << "EventRefreshHolyLandPlayer("
		<< ")";
	return msg.toString();
}
