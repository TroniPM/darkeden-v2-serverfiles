//----------------------------------------------------------------------
//
// Filename    : ZoneInfo.h
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

#ifndef __ZONE_INFO_H__
#define __ZONE_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"

//----------------------------------------------------------------------
//
// class ZoneInfo;
//
// �α��� ������ �� ���� ��ü�̴�.
//
// � ���� � �� �׷쿡 ���ϴ����� �ٷ��.
//
//----------------------------------------------------------------------

class ZoneInfo {

public :

	// get/set zone id
	ZoneID_t getZoneID ()  { return m_ZoneID; }
	void setZoneID ( ZoneID_t zoneID )  { m_ZoneID = zoneID; }

	// get/set zone group id
	ZoneGroupID_t getZoneGroupID ()  { return m_ZoneGroupID; }
	void setZoneGroupID ( ZoneGroupID_t zoneGroupID )  { m_ZoneGroupID = zoneGroupID; }

	// get debug string
	string toString () 
	{
		StringStream msg;
		msg << "ZoneInfo(ZoneID:" << m_ZoneID << ",ZoneGroupID:" << m_ZoneGroupID << ")";
		return msg.toString();
	}

private :

	// �� ���̵�
	ZoneID_t m_ZoneID;

	// �� �׷� ���̵�
	ZoneGroupID_t m_ZoneGroupID;

};

#endif
