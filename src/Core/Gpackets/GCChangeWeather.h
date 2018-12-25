//--------------------------------------------------------------------------------
// 
// Filename    : GCChangeWeather.h 
// Written By  : reiot
// 
//--------------------------------------------------------------------------------

#ifndef __GC_CHANGE_WEATHER_H__
#define __GC_CHANGE_WEATHER_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//--------------------------------------------------------------------------------
//
// class GCChangeWeather;
//
//--------------------------------------------------------------------------------

class GCChangeWeather : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_CHANGE_WEATHER; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCChangeWeatherPacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize()  { return szWeather + szWeatherLevel; }

	// get packet's name
	string getPacketName()  { return "GCChangeWeather"; }
	
	// get packet's debug string
	string toString() ;

public :

	Weather getWeather()  { return m_Weather; }
	void setWeather(Weather weather) throw() { m_Weather = weather; }

	WeatherLevel_t getWeatherLevel()  { return m_WeatherLevel; }
	void setWeatherLevel(WeatherLevel_t weatherLevel) throw() { m_WeatherLevel = weatherLevel; }

public :

	Weather m_Weather;

	WeatherLevel_t m_WeatherLevel;

};


//--------------------------------------------------------------------------------
//
// class GCChangeWeatherFactory;
//
// Factory for GCChangeWeather
//
//--------------------------------------------------------------------------------

class GCChangeWeatherFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCChangeWeather(); }

	// get packet name
	string getPacketName()  { return "GCChangeWeather"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_CHANGE_WEATHER; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCChangeWeatherPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  { return szWeather + szWeatherLevel; }

};


//--------------------------------------------------------------------------------
//
// class GCChangeWeatherHandler;
//
//--------------------------------------------------------------------------------

class GCChangeWeatherHandler {

public :

	// execute packet's handler
	static void execute(GCChangeWeather* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
