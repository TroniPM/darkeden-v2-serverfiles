//--------------------------------------------------------------------------------
//
// Filename    : GameTime.h
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

#ifndef __GAME_TIME_H__
#define __GAME_TIME_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//--------------------------------------------------------------------------------
//
// ���� �������� �ð��� ��Ÿ����.
//
//--------------------------------------------------------------------------------

class GameTime {

public :

	// ���Ͽ� embedding �Ƿ��� ��ü�� ������ ���� �޽�带 �����ؾ� �Ѵ�.
	// ���߿��� �̰� �������̽��� �ذ��� �����̴�.

	// read from socket input stream
	void read (SocketInputStream & iStream);

	// write to socket output stream
	void write (SocketOutputStream & oStream) ;

	// get size of object
	uint getSize ()  { return szWORD + szBYTE* 5; }
	static uint getMaxSize () throw () { return szWORD + szBYTE* 5; }


public :


	// get/set year
	WORD getYear ()  { return m_Year; }
	void setYear (WORD year) throw () { m_Year = year; }

	// get/set month
	BYTE getMonth ()  { return m_Month; }
	void setMonth (BYTE month) throw () { m_Month = month; }

	// get/set day
	BYTE getDay ()  { return m_Day; }
	void setDay (BYTE day) throw () { m_Day = day; }

	// get/set hour
	BYTE getHour ()  { return m_Hour; }
	void setHour (BYTE hour) throw () { m_Hour = hour; }

	// get/set minute
	BYTE getMinute ()  { return m_Minute; }
	void setMinute (BYTE minute) throw () { m_Minute = minute; }

	// get/set second
	BYTE getSecond ()  { return m_Second; }
	void setSecond (BYTE second) throw () { m_Second = second; }

	// get english month string
	string getMonthString () 
	{
		switch (m_Month) {
			case 1 : return "JAN";
			case 2 : return "FEB";
			case 3 : return "MAR";
			case 4 : return "APR";
			case 5 : return "MAY";
			case 6 : return "JUN";
			case 7 : return "JUL";
			case 8 : return "OUG";
			case 9 : return "SEP";
			case 10 : return "OCT";
			case 11 : return "NOV";
			case 12 : return "DEC";
		}
		return "???";
	}

	// get debug string
	string toString () ;

private :

	// YYYY-MM-DD
	WORD m_Year;
	BYTE m_Month;
	BYTE m_Day;

	// HH:MM:SS
	BYTE m_Hour;
	BYTE m_Minute;
	BYTE m_Second;
	
};

#endif
