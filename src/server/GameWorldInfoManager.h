//----------------------------------------------------------------------
//
// Filename    : GameWorldInfoManager.h
// Written By  : reiot@ewestsoft.com
// Description :
//
//----------------------------------------------------------------------

#ifndef __GAME_WORLD_INFO_MANAGER_H__
#define __GAME_WORLD_INFO_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "GameWorldInfo.h"
#include <hash_map>

typedef hash_map< WorldID_t , GameWorldInfo* > HashMapGameWorldInfo;

//----------------------------------------------------------------------
//
// class GameWorldInfoManager;
//
// ���� ������ ID �� Ű������ �ϴ� GameWorldInfo�� hash_map �� 
// ���ο� ������ �ִ�.
//
//----------------------------------------------------------------------

class GameWorldInfoManager {
	
public :
	
	// constructor
	GameWorldInfoManager ();
	
	// destructor
	~GameWorldInfoManager ();

	// initialize manager
	void init ();

	// load from database
	void load ();

	// clear GameWorldInfo objects
	void clear();
	
	// add info
	void addGameWorldInfo ( GameWorldInfo * pGameWorldInfo ) throw ( DuplicatedException );
	
	// delete info
	void deleteGameWorldInfo ( const WorldID_t WorldID ) throw ( NoSuchElementException );
	
	// get GameWorldInfo by WorldID
	GameWorldInfo * getGameWorldInfo ( const WorldID_t WorldID ) ;

	// get count of info
	uint getSize ()  { return m_GameWorldInfos.size(); }

	// get debug string
	string toString () ;

private :
	
	// hash map of GameWorldInfo
	// key   : WorldID_t
	// value : GameWorldInfo *
	HashMapGameWorldInfo m_GameWorldInfos;

};


// global variable declaration
extern GameWorldInfoManager * g_pGameWorldInfoManager;

#endif
