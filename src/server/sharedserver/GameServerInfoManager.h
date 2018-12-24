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
typedef HashMapGameServerInfo::iterator HashMapGameServerInfoItor;

//////////////////////////////////////////////////////////////////////////////
// class GameServerInfoManager;
// ���� ������ ID �� Ű������ �ϴ� GameServerInfo�� hash_map �� 
// ���ο� ������ �ִ�.
// World �ϳ��� GameServerInfo�� ������.
//////////////////////////////////////////////////////////////////////////////

class GameServerInfoManager 
{
public:
	GameServerInfoManager () throw ();
	~GameServerInfoManager () throw ();

public:
	void init () throw ( Error );
	void load () throw ( Error );
	
	void addGameServerInfo ( GameServerInfo * pGameServerInfo, const ServerGroupID_t ServerGroupID ) throw ( DuplicatedException );
	void deleteGameServerInfo ( const ServerID_t ServerID, const ServerGroupID_t ServerGroupID ) throw ( NoSuchElementException );
	GameServerInfo * getGameServerInfo ( const ServerID_t ServerID, const ServerGroupID_t ServerGroupID ) const throw( NoSuchElementException );
	uint getSize ( const ServerGroupID_t ServerGroupID ) const throw () { return m_pGameServerInfos[ServerGroupID].size(); }
	string toString () const throw ();
	
	// get MaxServerGroupID
	int getMaxServerGroupID() const throw() { return m_MaxServerGroupID; }

private:
	// hash map of GameServerInfo
	// key   : GameServerID_t
	// value : GameServerInfo *
	HashMapGameServerInfo* m_pGameServerInfos;
	int m_MaxServerGroupID;

};

// global variable declaration
extern GameServerInfoManager * g_pGameServerInfoManager;

#endif
