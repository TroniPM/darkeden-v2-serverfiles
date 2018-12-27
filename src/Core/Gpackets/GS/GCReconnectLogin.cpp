//----------------------------------------------------------------------
// 
// Filename    : GCReconnectLogin.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//----------------------------------------------------------------------

// include files
#include "GCReconnectLogin.h"


//----------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//----------------------------------------------------------------------
void GCReconnectLogin::read ( SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY
		
	//--------------------------------------------------
	// read game server's ip
	//--------------------------------------------------
	BYTE szLoginServerIP;

	iStream.read( szLoginServerIP );

	if ( szLoginServerIP == 0 )
		throw InvalidProtocolException("szLoginServerIP == 0");

	if ( szLoginServerIP > 15 )
		throw InvalidProtocolException("too long IP length");

	iStream.read( m_LoginServerIP , szLoginServerIP );

	//--------------------------------------------------
	// read game server's port
	//--------------------------------------------------
	iStream.read( m_LoginServerPort );

	//--------------------------------------------------
	// read auth-key
	//--------------------------------------------------
	iStream.read( m_Key );

	__END_CATCH
}

		    
//----------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//----------------------------------------------------------------------
void GCReconnectLogin::write ( SocketOutputStream & oStream ) const 
     
{
	__BEGIN_TRY
		
	//--------------------------------------------------
	// write game server's ip
	//--------------------------------------------------
	BYTE szLoginServerIP = m_LoginServerIP.size();

	if ( szLoginServerIP == 0 )
		throw InvalidProtocolException("szLoginServerIP == 0");

	if ( szLoginServerIP > 15 )
		throw InvalidProtocolException("too long IP length");

	oStream.write( szLoginServerIP );

	oStream.write( m_LoginServerIP );

	//--------------------------------------------------
	// write game server's port
	//--------------------------------------------------
	oStream.write( m_LoginServerPort );

	//--------------------------------------------------
	// write auth-key
	//--------------------------------------------------
	oStream.write( m_Key );

	__END_CATCH
}


//----------------------------------------------------------------------
// execute packet's handler
//----------------------------------------------------------------------
void GCReconnectLogin::execute ( Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCReconnectLoginHandler::execute( this , pPlayer );

	__END_CATCH
}


//----------------------------------------------------------------------
// get packet's debug string
//----------------------------------------------------------------------
string GCReconnectLogin::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCReconnectLogin("
		<< "LoginServerIP:" << m_LoginServerIP 
		<< ",LoginServerPort:" << m_LoginServerPort 
		<< ",KEY:" << m_Key << ")" ;
	return msg.toString();

	__END_CATCH
}


