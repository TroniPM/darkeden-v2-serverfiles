//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAddEffect.cpp 
// Written By  : elca@ewestsoft.com
// Description : 자신에게 쓰는 기술의 성공을 알리기 위한 패킷 클래스의
//               멤버 정의.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCLoadInventory.h"
#include "Assert.h"



//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCLoadInventory::GCLoadInventory () 
     
: m_pInventoryInfo(NULL)
{
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCLoadInventory::~GCLoadInventory () 
    
{
	SAFE_DELETE(m_pInventoryInfo);
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCLoadInventory::read ( SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY
	m_pInventoryInfo = new InventoryInfo();
	m_pInventoryInfo->read( iStream );
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCLoadInventory::write ( SocketOutputStream & oStream ) 
     
{
	__BEGIN_TRY
	m_pInventoryInfo->write( oStream );
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCLoadInventory::execute ( Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCLoadInventoryHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCLoadInventory::toString () 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCLoadInventory("
		<< ")";
	return msg.toString();

	__END_CATCH
}

