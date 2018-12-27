//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSay.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCSay.h"


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCSay::read ( SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );
	iStream.read( m_Color );

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
void GCSay::write ( SocketOutputStream & oStream ) const 
     
{
	__BEGIN_TRY
		
	oStream.write( m_ObjectID );
	oStream.write( m_Color );

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
void GCSay::execute ( Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCSayHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
string GCSay::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCSay("
		<< "ObjectID:" << m_ObjectID 
		<< ",Color:" << m_Color
		<< ",Message:" << m_Message 
		<< ")" ;
	return msg.toString();
		
	__END_CATCH
}


