//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCKickMessage.cpp 
// Written By  : reiot@ewestsoft.com
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCKickMessage.h"


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCKickMessage::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE t;
	iStream.read( t );
	m_Type = (KickMessageType)t;

	iStream.read( m_Seconds );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCKickMessage::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE t = (BYTE)m_Type;
	oStream.write( t );

	oStream.write( m_Seconds );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCKickMessage::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCKickMessageHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
string GCKickMessage::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCKickMessage("
		<< "Type:" << (int)m_Type 
		<< "Seconds:" << (int)m_Seconds
		<< ")" ;
	
	return msg.toString();
		
	__END_CATCH
}


