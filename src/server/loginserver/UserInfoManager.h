//----------------------------------------------------------------------
//
// Filename    : UserInfoManager.h
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

#ifndef __USER_INFO_MANAGER_H__
#define __USER_INFO_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "UserInfo.h"
#include <hash_map>

typedef hash_map< ZoneGroupID_t , UserInfo * > HashMapUserInfo;

//----------------------------------------------------------------------
//
// class UserInfoManager;
//
// 존그룹 아이디를 키값으로 하는 존 정보의 hash_map 을 가지고 있다.
//
//----------------------------------------------------------------------

class UserInfoManager {
	
public :
	
	// constructor
	UserInfoManager ();
	
	// destructor
	~UserInfoManager ();

	// initialize manager
	void init ();

	// add info
	void addUserInfo ( UserInfo * pUserInfo ) ;
	
	// delete info
	void deleteUserInfo ( ZoneGroupID_t ServerGroupID, WorldID_t WorldID ) ;
	
	// get info
	UserInfo * getUserInfo ( ZoneGroupID_t ServerGroupID, WorldID_t WorldID ) ;

	// get count of info
	uint getSize ( WorldID_t WorldID )  { return m_UserInfos[WorldID].size(); }

	// get debug string
	string toString () ;

	// load from database
	void load ();
	
private :
	
	// hash map of UserInfo
	// key   : UserID_t
	// value : UserInfo *
	HashMapUserInfo * m_UserInfos;

	WorldID_t m_MaxWorldID;

};


// global variable declaration
extern UserInfoManager * g_pUserInfoManager;

#endif
