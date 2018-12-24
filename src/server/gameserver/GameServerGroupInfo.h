//----------------------------------------------------------------------
//
// Filename    : GameServerGroupInfo.h
// Written By  : Reiot
// Description : �α��� �������� ���� �ִ� �� ���� ������ ���� ����
//
//----------------------------------------------------------------------

#ifndef __GAME_SERVER_GROUP_INFO_H__
#define __GAME_SERVER_GROUP_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "StringStream.h"


//----------------------------------------------------------------------
//
// class GameServerGroupInfo;
//
// GAME DB�� GameServerGroupInfo ���̺��� �о���� �� ���� ������ ������
// ���� Ŭ�����̴�.
//
//----------------------------------------------------------------------

class GameServerGroupInfo {

public :

	// get/set GameWorldID
	WorldID_t getWorldID() const throw() { return m_WorldID; }
	void setWorldID( WorldID_t WorldID ) throw() { m_WorldID = WorldID; }

	// get/set GameServerGroupID
	ServerGroupID_t getGroupID() const throw() { return m_GroupID; }
	void setGroupID( ServerGroupID_t GroupID ) throw() { m_GroupID = GroupID; }

	// get/set host name
	string getGroupName() const throw () { return m_GroupName; }
	void setGroupName( string GroupName ) throw () { m_GroupName = GroupName; }
	
	// get/set host name
	BYTE getStat() const throw () { return m_Stat; }
	void setStat( BYTE stat ) throw () { m_Stat = stat; }

	// get debug string
	string toString () const throw () 
	{
		StringStream msg;
		msg << "GameServerGroupInfo("
			<< "WorldID : " << (int)m_WorldID
			<< "ServerGroupID: " << (int)m_GroupID
			<< ",GroupName:" << m_GroupName
			<< ")";
		return msg.toString();
	}

private :

	// WorldID
	WorldID_t	m_WorldID;

	// GameServerGroup ID
	ServerGroupID_t m_GroupID;

	// GameServerGroup Process's nick name
	string m_GroupName;

	BYTE	m_Stat;
};

#endif
