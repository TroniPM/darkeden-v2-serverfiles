//----------------------------------------------------------------------
//
// Filename    : GameWorldInfo.h
// Written By  : Reiot
// Description : �α��� �������� ���� �ִ� �� ���� ������ ���� ����
//
//----------------------------------------------------------------------

#ifndef __GAME_WORLD_INFO_H__
#define __GAME_WORLD_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "StringStream.h"


//----------------------------------------------------------------------
//
// class GameWorldInfo;
//
// GAME DB�� GameWorldInfo ���̺��� �о���� �� ���� ������ ������
// ���� Ŭ�����̴�.
//
//----------------------------------------------------------------------

class GameWorldInfo {

public :

	// get/set GameWorldID
	WorldID_t getID()  { return m_ID; }
	void setID( WorldID_t ID )  { m_ID = ID; }

	// get/set host name
	string getName()  { return m_Name; }
	void setName( string Name )  { m_Name = Name; }
	
	// get/set World Status
	WorldStatus getStatus()  { return m_Status; }
	void setStatus( WorldStatus status )  { m_Status = status; } 
	
	// get debug string
	string toString ()  
	{
		StringStream msg;
		msg << "GameWorldInfo("
			<< "WorldID: " << (int)m_ID
			<< ",Name:" << m_Name
			<< ")";
		return msg.toString();
	}

private :

	// GameWorld ID
	WorldID_t m_ID;

	// GameWorld Process's nick name
	string m_Name;

	// GameWorld status
	WorldStatus m_Status;

};

#endif
