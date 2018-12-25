//--------------------------------------------------------------------------------
//
// Filename   : WeatherManager.h
// Written By : Reiot
//
//--------------------------------------------------------------------------------

#ifndef __WEATHER_MANAGER_H__
#define __WEATHER_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Assert.h"
#include <time.h>

class Zone;

//--------------------------------------------------------------------------------
//
// class WeatherManager;
//
// ���� ������ �����ϴ� ��ü�μ�, �� ���� �ϳ��� WeatherManager�� ������ �־�� �Ѵ�. 
//
// ���� ������ �Ϸ翡 �ѹ� ������ �ȴ�. �켱, GameTime ���� ������ ���������
// �˾Ƴ� ����, WeatherInfoManager ���� �ش�Ǵ� WeatherInfo �� �����´�. 
// ���� dice �� ������, ������ ������ �������´�. CLEAR-RAIN-SNOW �� �ϳ��� ����
// ��������, ���� �Ϸ��� �������� ������ �������´�.
//
// ������ �⺻ ������ ���� �ð� 1 �ð��̴�. 
//
// WEATHER_CLEAR : �� ���, �� ���� ������ �ʴ´�.
// WEATHER_RAINY, WEATHER_SNOWY : �Ϸ翡 �� ���� Ȯ���� �������� �� �ð�����
// ���̽��� ������ �� ������ �Ѵ�. �̶�, �� ��ĥ �ð��� ���̽��� ������ش�.
//(�� ������ �ð� ���ú ���� �ð� �ѽð��� ������ �Ѵ�.)
//
// ������ ġ�� �⺻ ������ �ǽð� 1���̸�, Ȯ����(���� ����* 5 - 30) %�̴�.
//
//--------------------------------------------------------------------------------
class WeatherManager {

public:

	// constructor
	WeatherManager(Zone* pZone) throw(Error) : m_pZone(pZone) { Assert(m_pZone != NULL); }

	// destructor
	virtual ~WeatherManager() throw(Error);

	// initialize 
	void init() throw(Error);

	// ���� �ð��� �Ǹ� ������ �˾Ƽ� �ٲ��ش�. ���� heartbeat ���� ȣ��Ǿ�� �Ѵ�.
	void heartbeat() throw(Error);

	// ������ ������ �����Ѵ�.
	Weather getTodayWeather()  { return m_TodayWeather; }

	// ���� �� ���� �� Ȯ���� �����Ѵ�.
	uint getProbability()  { return m_Probability; }

	// ������ ������ �����Ѵ�.
	Weather getCurrentWeather()  { return m_CurrentWeather; }

	// ������ ���� ������ �����Ѵ�.
	WeatherLevel_t getWeatherLevel()  { return m_WeatherLevel; }

	void resetDarkLightInfo() throw() { m_Next10Min = time(0); }

	// get debug string
	string toString() ;

private:

	// ���� �����Ǿ� �ִ� ��
	Zone* m_pZone;

	// ������ ����(CLEAR/RAINY/SNOWY)
	Weather m_TodayWeather;	

	// �� ���� �� Ȯ��(0 - 100)
	uint m_Probability;

	// ������ ����
	Weather m_CurrentWeather;

	// ���� ����(1 - 20)
	WeatherLevel_t m_WeatherLevel;


//--------------------------------------------------
// ���� XXX �� �ð�(�ʴ����� ����ϴ�)
//--------------------------------------------------
private:

	// ����
	time_t m_Tomorrow;

	// ���� ���� ���� �ð�
	time_t m_NextWeatherChangingTime;

	// ���� ���� �ð�
	time_t m_NextLightning;

	// ���� 10�д�
	time_t m_Next10Min;

};

#endif
