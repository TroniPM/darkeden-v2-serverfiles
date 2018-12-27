//////////////////////////////////////////////////////////////////////
// 
// Filename    : WarInfo.cpp 
// Written By  : 
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "WarInfo.h"

//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void WarInfo::read ( SocketInputStream & iStream ) 
	 //
{
	__BEGIN_TRY

	iStream.read( m_RemainTime );
	iStream.read( m_StartTime );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void WarInfo::write ( SocketOutputStream & oStream ) //const 
     //
{
	__BEGIN_TRY

//	cout << "WarInfo : " << m_StartTime << endl;

	oStream.write( m_RemainTime );
	oStream.write( m_StartTime );

	__END_CATCH
}

