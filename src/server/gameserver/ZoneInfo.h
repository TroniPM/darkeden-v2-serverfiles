//////////////////////////////////////////////////////////////////////////////
// Filename    : ZoneInfo.h
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ZONEINFO_H__
#define __ZONEINFO_H__

#include "Types.h"
#include "Exception.h"
#include "Zone.h"

//////////////////////////////////////////////////////////////////////////////
// class ZoneInfo;
//////////////////////////////////////////////////////////////////////////////

class ZoneInfo 
{
public:
	ZoneInfo();
	~ZoneInfo();

	void load( ZoneID_t zoneID ) throw(Error);

public:
	ZoneID_t getZoneID()  { return m_ZoneID; }
	void setZoneID(ZoneID_t zoneID) throw() { m_ZoneID = zoneID; }

	ZoneGroupID_t getZoneGroupID()  { return m_ZoneGroupID; }
	void setZoneGroupID(ZoneGroupID_t zoneGroupID) throw() { m_ZoneGroupID = zoneGroupID; }

	ZoneType getZoneType()  { return m_ZoneType; }
	void setZoneType(ZoneType zoneType) throw() { m_ZoneType = zoneType; }
	void setZoneType(const string & zoneType) throw(Error);

	ZoneLevel_t getZoneLevel()  { return m_ZoneLevel; }
	void setZoneLevel(ZoneLevel_t zoneLevel) throw() { m_ZoneLevel = zoneLevel; }

	ZoneAccessMode getZoneAccessMode()  { return m_ZoneAccessMode; }
	void setZoneAccessMode(ZoneAccessMode zoneAccessMode) throw() { m_ZoneAccessMode = zoneAccessMode; }
	void setZoneAccessMode(const string & zoneAccessMode) throw(Error);

	bool isPayPlay()  { return m_bPayPlay; }
	void setPayPlay(bool bPayPlay=true) throw() { m_bPayPlay = bPayPlay; }

	bool isPremiumZone()  { return m_bPremiumZone; }
	void setPremiumZone(bool bPremiumZone=true) throw() { m_bPremiumZone = bPremiumZone; }

	string getZoneOwnerID()  { return m_OwnerID; }
	void setZoneOwnerID(const string & ownerID) throw() { m_OwnerID = ownerID; }

	string getSMPFilename(void)  { return m_SMPFilename; }
	void setSMPFilename(const string& name) throw() { m_SMPFilename = name; }

	string getSSIFilename(void)  { return m_SSIFilename; }
	void setSSIFilename(const string& name) throw() { m_SSIFilename = name; }

	string getFullName(void)  { return m_FullName; }
	void setFullName(const string& name) throw() { m_FullName = name; }

	string getShortName(void)  { return m_ShortName; }
	void setShortName(const string& name) throw() { m_ShortName = name; }

	bool isPKZone()  { return m_bPKZone; }
	void setPKZone(bool bPKZone=true) throw() { m_bPKZone = bPKZone; }

	bool isNoPortalZone()  { return m_bNoPortalZone; }
	void setNoPortalZone(bool bNoPortalZone=true) throw() { m_bNoPortalZone = bNoPortalZone; }

	bool isMasterLair()  { return m_bMasterLair; }
	void setMasterLair(bool bMasterLair=true) throw() { m_bMasterLair = bMasterLair; }

	bool isCastle()  { return m_bCastle; }
	void setCastle(bool bCastle=true) throw() { m_bCastle = bCastle; }

	bool isHolyLand()  { return m_bHolyLand; }
	void setHolyLand(bool bHolyLand=true) throw() { m_bHolyLand = bHolyLand; }

	bool isLevelWarZone() const
	{
		switch ( m_ZoneID )
		{
			case 1131:
			case 1132:
			case 1133:
			case 1134:
				{
					return true;
				}
				break;
			default:
				{
					return false;
				}
				break;
		}
	}

	bool isAvailable()  { return m_bAvailable; }
	void setAvailable(bool bAvailable=true) throw() { m_bAvailable = bAvailable; }

	int getOpenLevel()  { return m_OpenLevel; }
	void setOpenLevel(int OpenLevel) throw() { m_OpenLevel = OpenLevel; }

	string toString() ;

private:
	ZoneID_t       m_ZoneID;         // �� ���̵�
	ZoneGroupID_t  m_ZoneGroupID;    // �� �׷� ���̵�
	ZoneType       m_ZoneType;       // �� Ÿ��
	ZoneLevel_t    m_ZoneLevel;      // �� ����(0 - 10)
	ZoneAccessMode m_ZoneAccessMode; // �� ���� ���
	bool           m_bPayPlay;		 // ����ȭ ��? = �� ���� �� �� �ִ� ��
	bool           m_bPremiumZone;	 // �����̾� ���񽺰� �Ǵ� �� 
	string         m_OwnerID;        // �� ������ ���̵�
	string         m_SMPFilename;    // SMP ���� �̸�
	string         m_SSIFilename;    // SSI ���� �̸�
	string         m_FullName;       // �� �̸�
	string         m_ShortName;      // ª�� �̸�

	bool           m_bPKZone;        // ���� �� �������� ��
	bool           m_bNoPortalZone;  // portal�� �̵��� �Ұ����� ��
	bool           m_bMasterLair;  	 // ������ �����ΰ�?
	bool           m_bCastle;  	 		// Castle�ΰ�?
	bool           m_bHolyLand;  	 	// �ƴ��� �����ΰ�?
	bool           m_bAvailable;        // ���;� �Ǵ� ���ΰ�?

	int            m_OpenLevel;         // ���� ���� ����. OpenDegree�� ���� ���� �������� ���ƾ� ���´�.

};

#endif
