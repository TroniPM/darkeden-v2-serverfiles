//-------------------------------------------------------------------------------- // 
// Filename    : GCRequestPowerPointResult.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//--------------------------------------------------------------------------------

// include files
#include "GCRequestPowerPointResult.h"


//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
GCRequestPowerPointResult::GCRequestPowerPointResult ()
	
	: m_ErrorCode(0), m_SumPowerPoint(0), m_RequestPowerPoint(0)
{
}

//--------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------
GCRequestPowerPointResult::~GCRequestPowerPointResult ()
	
{
}

//--------------------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//--------------------------------------------------------------------------------
void GCRequestPowerPointResult::read ( SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY

	// Error code
	iStream.read( m_ErrorCode );

	// ���� ������ �Ŀ�¯ ����Ʈ
	iStream.read( m_SumPowerPoint );

	// ��û���� ������ �Ŀ�¯ ����Ʈ
	iStream.read( m_RequestPowerPoint );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void GCRequestPowerPointResult::write ( SocketOutputStream & oStream ) const 
     
{
	__BEGIN_TRY

	// Error code
	oStream.write( m_ErrorCode );

	// ���� ������ �Ŀ�¯ ����Ʈ
	oStream.write( m_SumPowerPoint );

	// ��û���� ������ �Ŀ�¯ ����Ʈ
	oStream.write( m_RequestPowerPoint );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCRequestPowerPointResult::execute ( Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCRequestPowerPointResultHandler::execute( this , pPlayer );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
string GCRequestPowerPointResult::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCRequestPowerPointResult("
		<< "ErrorCode:" << (int)m_ErrorCode
		<< ",SumPowerPoint:" << m_SumPowerPoint
		<< ",RequestPowerPoint:" << m_RequestPowerPoint
		<< ")";

	return msg.toString();

	__END_CATCH
}

