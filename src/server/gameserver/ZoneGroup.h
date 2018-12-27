//////////////////////////////////////////////////////////////////////
//
// Filename    : ZoneGroup.h
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

#ifndef __ZONE_GROUP_H__
#define __ZONE_GROUP_H__

// include files
#include "Types.h"
#include "Exception.h"
#include <hash_map>
#include "Zone.h"
#include "GameTime.h"
#include "Gpackets/GMServerInfo.h"

// forward declaration
class ZoneThread;
class ZonePlayerManager;

// type redefinition
//typedef hash_map<ZoneID_t,Zone*> ZONE_HASHMAP;

//////////////////////////////////////////////////////////////////////
//
// class ZoneGroup;
//
//////////////////////////////////////////////////////////////////////
class ZoneGroup {
	
	// friend declaration
	friend class ZoneThread;

public:
	
	// constructor
	ZoneGroup(ZoneGroupID_t zoneGroupID) ;
	
	// destructor
	~ZoneGroup() ;
	

public:
	
	// initialize zone group
	void init();
	
	// load sub zones from database
	void load();
	
	// save sub zones to database
	void save();

	//
	void processPlayers();
	void heartbeat();	
	
public:

	// add zone to zone group
	void addZone(Zone* pZone);
	
	// delete zone from zone group
	void deleteZone(ZoneID_t zoneID) ;
	Zone* removeZone(ZoneID_t zoneID) ;
	
	// get zone from zone group
	Zone* getZone(ZoneID_t zoneID) ;

//#ifdef __NO_COMBAT__
	Zone* getCombatZone(ZoneID_t zoneID) ; // getZone�� ���� ���� �����ϳ� NULL�� �����ϴ� ���� ����, ��漮
//#endif

//--------------------------------------------------
// get/set methods
//--------------------------------------------------
public:

	// get/set zone group id
	ZoneGroupID_t getZoneGroupID()  { return m_ZoneGroupID; }
	void setZoneGroupID(ZoneGroupID_t zoneGroupID)  { m_ZoneGroupID = zoneGroupID; }

	// get zone player manager
	ZonePlayerManager* getZonePlayerManager()  { return m_pZonePlayerManager; }
	void setZonePlayerManager(ZonePlayerManager* pZonePlayerManager)  { m_pZonePlayerManager = pZonePlayerManager; }

	// get/set game time
	GameTime getGameTime()  { return m_GameTime; }
	void setGameTime(const GameTime & gameTime)  { m_GameTime = gameTime; }

	void makeZoneUserInfo ( GMServerInfo & gmServerInfo );

	const hash_map< ZoneID_t, Zone* >& getZones() const { return m_Zones; }

	// get debug string
	string toString() ;

public :
	void 	lock() 		{ m_Mutex.lock(); }
	void 	unlock() 		{ m_Mutex.unlock(); }

	  void   initLoadValue();
      DWORD  getLoadValue() const;


//--------------------------------------------------
// data members
//--------------------------------------------------
private:

	// zone group id
	ZoneGroupID_t m_ZoneGroupID;
	
	// zone �� �ؽ���
	hash_map< ZoneID_t, Zone* > m_Zones;

	// zone player manager
	ZonePlayerManager* m_pZonePlayerManager;

	// game time
	GameTime m_GameTime;

	// Tick Time
	Timeval m_TickTime;

	DWORD	m_LoadValue;

	mutable Mutex  m_Mutex;
};

#endif
