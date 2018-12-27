//----------------------------------------------------------------------
//
// Filename    : GameServerInfo.h
// Written By  : Reiot
// Description : �α��� �������� ���� �ִ� �� ���� ������ ���� ����
//
//----------------------------------------------------------------------

#ifndef __GAME_SERVER_INFO_H__
#define __GAME_SERVER_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "StringStream.h"


//----------------------------------------------------------------------
//
// class GameServerInfo;
//
// GAME DB�� GameServerInfo ���̺��� �о���� �� ���� ������ ������
// ���� Ŭ�����̴�.
//
//----------------------------------------------------------------------

class GameServerInfo {

public :

	// get/set GameServerID
	ServerID_t getServerID()  { return m_ServerID; }
	void setServerID( ServerID_t ServerID )  { m_ServerID = ServerID; }

	// get/set host name
	string getNickname ()  { return m_Nickname; }
	void setNickname ( string nickname )  { m_Nickname = nickname; }
	
	// get/set ip address
	string getIP ()  { return m_IP; }
	void setIP ( string ip )  { m_IP = ip; }

	// get/set port
	uint getTCPPort ()  { return m_TCPPort; }
	void setTCPPort ( uint port )  { m_TCPPort = port; }

	// get/set UDP port
	uint getUDPPort ()  { return m_UDPPort; }
	void setUDPPort ( uint port )  { m_UDPPort = port; }

	// get/set GameServerGroupID
	ServerGroupID_t getGroupID()  { return m_GroupID; }
	void setGroupID( ServerGroupID_t GroupID ) { m_GroupID = GroupID; }

	// get/set GameWorldID
	WorldID_t getWorldID()  { return m_WorldID; }
	void setWorldID( WorldID_t WorldID ) { m_WorldID= WorldID; }

	// get/set ServerStat
	ServerStatus getServerStat()  { return m_ServerStat; }
	void setServerStat( ServerStatus Stat )  { m_ServerStat = Stat; }

	// get debug string
	string toString ()  
	{
		StringStream msg;
		msg << "GameServerInfo("
			<< "ServerID: " << (int)m_ServerID
			<< ",Nickname:" << m_Nickname 
			<< ",IP: " << m_IP
			<< ",TCPPort:" << m_TCPPort
			<< ",UDPPort:" << m_UDPPort
			<< ",GroupID:" << (int)m_GroupID
			<< ",WorldID:" << (int)m_WorldID
			<< ",ServerStat:" << (int)m_GroupID
			<< ")";
		return msg.toString();
	}

private :

	// GameServer ID
	ServerID_t m_ServerID;

	// GameServer Process's nick name
	string m_Nickname;

	// Host's IP address
	string m_IP;

	// GameServer's port
	uint m_TCPPort;
	uint m_UDPPort;

	// GameServerGroupID
	ServerGroupID_t m_GroupID;

	// GameServerWorld
	WorldID_t m_WorldID;

	// Server Stat
	ServerStatus m_ServerStat;

};

#endif
