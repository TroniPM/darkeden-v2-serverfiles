//////////////////////////////////////////////////////////////////////////////
// Filename    : GCBloodBibleSignInfo.cpp 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "GCBloodBibleSignInfo.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
GCBloodBibleSignInfo::~GCBloodBibleSignInfo() 
	
{
	__BEGIN_TRY 

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////////////
void GCBloodBibleSignInfo::read ( SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY

	m_pInfo = new BloodBibleSignInfo;
	m_pInfo->read( iStream );

	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////////////
void GCBloodBibleSignInfo::write ( SocketOutputStream & oStream ) const 
     
{
	__BEGIN_TRY

	m_pInfo->write( oStream );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCBloodBibleSignInfo::execute ( Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCBloodBibleSignInfoHandler::execute( this , pPlayer );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
string GCBloodBibleSignInfo::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCBloodBibleSignInfo(";
	msg << ")";

	return msg.toString();
		
	__END_CATCH
}

