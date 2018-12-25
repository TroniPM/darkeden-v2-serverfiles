//----------------------------------------------------------------------
//
// Filename    : ZoneInfoManager.h
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

#ifndef __ZONE_INFO_MANAGER_H__
#define __ZONE_INFO_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ZoneInfo.h"
#include <hash_map>

typedef hash_map< ZoneID_t , ZoneInfo * > HashMapZoneInfo;

//----------------------------------------------------------------------
//
// class ZoneInfoManager;
//
// �� ���̵� Ű������ �ϴ� �� ������ hash_map �� ������ �ִ�.
//
//----------------------------------------------------------------------

class ZoneInfoManager {
	
public :
	
	// constructor
	ZoneInfoManager ();
	
	// destructor
	~ZoneInfoManager ();

	// initialize manager
	void init ();

	// load from database
	void load ();
	
	// add info
	void addZoneInfo ( ZoneInfo * pZoneInfo ) throw ( DuplicatedException );
	
	// delete info
	void deleteZoneInfo ( ZoneID_t zoneID ) throw ( NoSuchElementException );
	
	// get info
	ZoneInfo * getZoneInfo ( ZoneID_t zoneID ) ;

	// get count of info
	uint getSize ()  { return m_ZoneInfos.size(); }

	// get debug string
	string toString () ;

private :
	
	// hash map of ZoneInfo
	// key   : ZoneID_t
	// value : ZoneInfo *
	HashMapZoneInfo m_ZoneInfos;

};


// global variable declaration
extern ZoneInfoManager * g_pZoneInfoManager;

#endif
