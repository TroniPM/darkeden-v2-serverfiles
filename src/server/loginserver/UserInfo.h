//----------------------------------------------------------------------
//
// Filename    : UserInfo.h
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

#ifndef __USER_INFO_H__
#define __USER_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"

//----------------------------------------------------------------------
//
// class UserInfo;
//
// �α��� ������ �� �׷� ���� ��ü�̴�.
//
// � ���׷��� � ������ ���ؼ� ó���Ǵ����� �ٷ��.
//
//----------------------------------------------------------------------

class UserInfo {

public :

	// get/set zone group id
	WorldID_t getWorldID()  { return m_WorldID; }
	void setWorldID ( WorldID_t WorldID )  { m_WorldID = WorldID ; }

	// get/set zone group id
	ZoneGroupID_t getServerGroupID()  { return m_ServerGroupID; }
	void setServerGroupID ( ZoneGroupID_t GroupID )  { m_ServerGroupID = GroupID ; }

	// get/set zone group id
	UserNum_t getUserNum()  { return m_UserNum; }
	void setUserNum ( UserNum_t UserNum )  { m_UserNum = UserNum; }


	// get debug string
	string toString () 
	{
		StringStream msg;

		msg << "UserInfo("
			<< "WorldID:" << m_WorldID
			<< "ServerGroupID:" << m_ServerGroupID
			<< ",UserNum:" << m_UserNum
			<< ")";

		return msg.toString();
	}

private :

	// ���� ID
	WorldID_t m_WorldID;

	// ���� ����
	ZoneGroupID_t m_ServerGroupID;

	// ����
	UserNum_t m_UserNum;

};

#endif
