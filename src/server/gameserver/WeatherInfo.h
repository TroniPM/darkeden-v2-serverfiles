////////////////////////////////////////////////////////////////////////////////
// Filename    : WeatherInfo.h
// Written By  : Reiot
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __WEATHER_INFO_H__
#define __WEATHER_INFO_H__

#include "Types.h"
#include "Exception.h"

////////////////////////////////////////////////////////////////////////////////
// class WeatherInfo;
////////////////////////////////////////////////////////////////////////////////

class WeatherInfo 
{
public:
	// Ȯ������ �Ķ���ͷ� �Ѱ��ָ�, ������ ������ �����Ѵ�.
	Weather getWeather(uint probability) const throw();

	// Ư�� ������ Ȯ���� �����Ѵ�.
	uint getProbability(Weather weather) const throw() { return m_Probabilities[weather]; }

	// Ư�� ������ Ȯ���� �����Ѵ�.
	void setProbability(Weather weather, uint prob) throw() { m_Probabilities[weather] = prob; }

	// get debug string
	string toString() const throw();

private:
	uint m_Probabilities[WEATHER_MAX];

};


////////////////////////////////////////////////////////////////////////////////
// class WeatherInfoManager;
//
// ���� ���� ������ �����ϴ� �Ŵ��� Ŭ�����̴�.
////////////////////////////////////////////////////////////////////////////////

class WeatherInfoManager 
{
public:
	// init vision info
	void init() throw(Error) { load(); }

	// load from database
	void load() throw(Error);

	// save to database
	void save() throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__); }

	// get vision info
	const WeatherInfo & getWeatherInfo(int month) const throw(OutOfBoundException)
	{
		if(month > 12) throw OutOfBoundException("too large month value");
		return m_WeatherInfos[ month - 1 ];
	}

	// get debug string
	string toString() const throw();

private:
	// WeatherInfo�� ������ �迭
	WeatherInfo m_WeatherInfos[12];

};

// global variable declaration
extern WeatherInfoManager* g_pWeatherInfoManager;

#endif
