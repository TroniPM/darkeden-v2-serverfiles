//////////////////////////////////////////////////////////////////////////////
// Filename    : GameServerInfoManager.h
// Written By  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GAME_SERVER_INFO_MANAGER_H__
#define __GAME_SERVER_INFO_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "GameServerInfo.h"
#include <hash_map>

typedef hash_map<ServerID_t, GameServerInfo*> HashMapGameServerInfo;

//////////////////////////////////////////////////////////////////////////////
// class GameServerInfoManager;
// ���� ������ ID �� Ű������ �ϴ� GameServerInfo�� hash_map �� 
// ���ο� ������ �ִ�.
//////////////////////////////////////////////////////////////////////////////

class GameServerInfoManager 
{
public:
	GameServerInfoManager ();
	~GameServerInfoManager ();

public:
	void init ();
	void load ();

	// clear GameServerInfo objects
	void clear();
	
	void addGameServerInfo ( GameServerInfo * pGameServerInfo, const ServerGroupID_t ServerGroupID, WorldID_t WorldID ) throw ( DuplicatedException );
	void deleteGameServerInfo ( const ServerID_t ServerID, const ServerGroupID_t ServerGroupID, WorldID_t WorldID ) throw ( NoSuchElementException );
	//GameServerInfo * getGameServerInfo ( const string & name ) ;
	GameServerInfo * getGameServerInfo ( const ServerID_t ServerID, const ServerGroupID_t ServerGroupID, WorldID_t WorldID ) ;
	uint getSize ( WorldID_t WorldID, const ServerGroupID_t ServerGroupID )  { return m_pGameServerInfos[WorldID][ServerGroupID].size(); }
	string toString () ;

	// by sigi. 2002.5.30
	int						getMaxWorldID() const		{ return m_MaxWorldID; }
	int						getMaxServerGroupID() const		{ return m_MaxServerGroupID; }
	HashMapGameServerInfo** getGameServerInfos() const { return m_pGameServerInfos; }
private:
	// hash map of GameServerInfo
	// key   : GameServerID_t
	// value : GameServerInfo *
	HashMapGameServerInfo** m_pGameServerInfos;
	int m_MaxServerGroupID;
	int m_MaxWorldID;

};

// global variable declaration
extern GameServerInfoManager * g_pGameServerInfoManager;

#endif
