//--------------------------------------------------------------------------------
// 
// Filename    : CURequestLoginMode.cpp 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

// include files
#include "CURequestLoginMode.h"


//--------------------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//--------------------------------------------------------------------------------
void CURequestLoginMode::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__END_CATCH
}


//--------------------------------------------------------------------------------
// �������κ��� ���� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//--------------------------------------------------------------------------------
void CURequestLoginMode::read ( Socket * pSocket ) 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__END_CATCH
}

	    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void CURequestLoginMode::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void CURequestLoginMode::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	CURequestLoginModeHandler::execute ( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string CURequestLoginMode::toString () const
	throw ()
{

	return "CUReqeustLoginMode()";
}
