//////////////////////////////////////////////////////////////////////////////
// Filename   : TimeManager.h
// Written By : Reiot
//////////////////////////////////////////////////////////////////////////////

#ifndef __TIME_MANAGER_H__
#define __TIME_MANAGER_H__

#include "Types.h"
#include "GameTime.h"


#define DAWN_START_HOUR    4
#define DAWN_END_HOUR      8

#define DAY_START_HOUR     8
#define DAY_END_HOUR      16

#define DUSK_START_HOUR   16
#define DUSK_END_HOUR     20

#define NIGHT_START_HOUR  20
#define NIGHT_END_HOUR     4

enum Timeband
{
	TIME_DAWN = 0, // ����
	TIME_DAY,      // ��
	TIME_DUSK,     // ����
	TIME_NIGHT,    // ��

	TIME_MAX
};

//////////////////////////////////////////////////////////////////////////////
// class TimeManager;
//
// ���� ���� �ð��� ������ִ� �Ŵ��� Ŭ�����̴�.(��� �Ŵ������ �� �͵� ����.
// �� �ܿ��� ���� �ٸ� ������ �� �͵� ����...
//////////////////////////////////////////////////////////////////////////////

class TimeManager 
{
public:
	void init() throw(Error);

	GameTime getGameTime() ;	

	time_t getgametime() ;

	time_t getBaseGameTime()  { return m_BaseGameTime; }
	time_t getBaseRealTime()  { return m_BaseRealTime; }

	bool isDawnTime(void) ;
	bool isDayTime(void) ;
	bool isDuskTime(void) ;
	bool isNightTime(void) ;
	uint getTimeband(void) ;

	// get debug string
	string toString() ;

private:
	time_t m_BaseGameTime;
	time_t m_BaseRealTime;
	
};

// global variable declaration
extern TimeManager* g_pTimeManager;

#endif
