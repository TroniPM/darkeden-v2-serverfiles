//////////////////////////////////////////////////////////////////////////////
// Filename    : DarkLightInfo.h
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __DARK_LIGHT_INFO_H__
#define __DARK_LIGHT_INFO_H__

#include "Types.h"
#include "Exception.h"

class Zone;

//////////////////////////////////////////////////////////////////////////////
// class DarkLightInfo
//////////////////////////////////////////////////////////////////////////////

class DarkLightInfo 
{
public:
	DarkLightInfo() throw();
	DarkLightInfo(const DarkLightInfo & dli) throw();

public:
	DarkLevel_t getDarkLevel() const throw() { return m_DarkLevel; }
	void setDarkLevel(DarkLevel_t darkLevel) throw() { m_DarkLevel = darkLevel; }

	LightLevel_t getLightLevel() const throw() { return m_LightLevel; }
	void setLightLevel(LightLevel_t lightLevel) throw() { m_LightLevel = lightLevel; }

	string toString() const throw();

private:

	// ��ӱ� ���� 
	// 0 - 15 ������ ������, ���� ���� ȭ���� ��ο�����.
	DarkLevel_t m_DarkLevel;

	// ���� ũ��
	// 1 - 13 ������ ������, ���� ���� ���� ������ Ŀ����.
	LightLevel_t m_LightLevel;

};


////////////////////////////////////////////////////////////////////////////////
// DLIM �� ���� DLI �� �迭�� ũ��
////////////////////////////////////////////////////////////////////////////////
const uint nDarkLightInfos = 12* 24* 6;


////////////////////////////////////////////////////////////////////////////////
// class DarkLightInfoManager
////////////////////////////////////////////////////////////////////////////////

class DarkLightInfoManager 
{
public:
	DarkLightInfoManager() throw();
	~DarkLightInfoManager() throw();

public:
	void init() throw(Error);
	void load() throw(Error);

	DarkLightInfo* getDarkLightInfo(BYTE month, BYTE hour, BYTE minute) throw(OutOfBoundException, Error);
	const DarkLightInfo* getDarkLightInfo(BYTE month, BYTE hour, BYTE minute) const throw(OutOfBoundException, Error);

	DarkLightInfo* getCurrentDarkLightInfo( Zone* pZone ) throw(Error);
	const DarkLightInfo* getCurrentDarkLightInfo( Zone* pZone ) const throw(Error);

	string toString() const throw();

private:
	DarkLightInfo* m_DarkLightInfos[nDarkLightInfos];

};


// global variable declaration
extern DarkLightInfoManager* g_pDarkLightInfoManager;

#endif
