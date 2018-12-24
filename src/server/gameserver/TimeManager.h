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

	GameTime getGameTime() const throw();	

	time_t getgametime() const throw();

	time_t getBaseGameTime() const throw() { return m_BaseGameTime; }
	time_t getBaseRealTime() const throw() { return m_BaseRealTime; }

	bool isDawnTime(void) const throw();
	bool isDayTime(void) const throw();
	bool isDuskTime(void) const throw();
	bool isNightTime(void) const throw();
	uint getTimeband(void) const throw();

	// get debug string
	string toString() const throw();

private:
	time_t m_BaseGameTime;
	time_t m_BaseRealTime;
	
};

// global variable declaration
extern TimeManager* g_pTimeManager;

#endif
