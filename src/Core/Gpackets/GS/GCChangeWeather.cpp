//--------------------------------------------------------------------------------
// 
// Filename    : GCChangeWeather.cpp 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

// include files
#include "GCChangeWeather.h"


//--------------------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//--------------------------------------------------------------------------------
void GCChangeWeather::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE weather;
	iStream.read( weather );
	m_Weather = (Weather)weather;

	iStream.read( m_WeatherLevel );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void GCChangeWeather::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( (BYTE)m_Weather );
	oStream.write( m_WeatherLevel );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCChangeWeather::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCChangeWeatherHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
string GCChangeWeather::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCChangeWeather("
		<< "Weather:" << Weather2String[m_Weather]
		<< ",WeatherLevel:" << (int)m_WeatherLevel 
		<< ")";
	return msg.toString();

	__END_CATCH
}
