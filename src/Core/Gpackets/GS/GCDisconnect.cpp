//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCDisconnect.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCDisconnect.h"


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCDisconnect::read ( SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY
		
	BYTE szMessage;

	iStream.read( szMessage );

	if ( szMessage == 0 )
		throw InvalidProtocolException("szMessage == 0");

	if ( szMessage > 128 )
		throw InvalidProtocolException("too large message length");

	iStream.read( m_Message , szMessage );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCDisconnect::write ( SocketOutputStream & oStream ) const 
     
{
	__BEGIN_TRY
		
	BYTE szMessage = m_Message.size();

	if ( szMessage == 0 )
		throw InvalidProtocolException("szMessage == 0");

	if ( szMessage > 128 )
		throw InvalidProtocolException("too large message length");

	oStream.write( szMessage );

	oStream.write( m_Message );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCDisconnect::execute ( Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCDisconnectHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
string GCDisconnect::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCDisconnect("
		<< "Message:" << m_Message 
		<< ")" ;
	return msg.toString();
		
	__END_CATCH
}


