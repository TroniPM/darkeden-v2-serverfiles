//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGPortCheck.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "CGPortCheck.h"


//////////////////////////////////////////////////////////////////////
// Datagram ��ü�κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void CGPortCheck::read ( Datagram & iDatagram ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// read creature's name
	//--------------------------------------------------
	BYTE szPCName;

	iDatagram.read( szPCName );

	if ( szPCName == 0 )
		throw InvalidProtocolException("szPCName == 0");

	if ( szPCName > 20 )
		throw InvalidProtocolException("too long name length");

	iDatagram.read( m_PCName , szPCName );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void CGPortCheck::write ( Datagram & oDatagram ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// write PC name
	//--------------------------------------------------
	BYTE szPCName = m_PCName.size();

	if ( szPCName == 0 )
		throw InvalidProtocolException("szPCName == 0");

	if ( szPCName > 20 )
		throw InvalidProtocolException("too long name length");

	oDatagram.write( szPCName );

	oDatagram.write( m_PCName );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void CGPortCheck::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	CGPortCheckHandler::execute( this );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
string CGPortCheck::toString () const
    throw ()
{
	StringStream msg;

	msg << "CGPortCheck("
		<< ",PCName:" << m_PCName 
		<< ")";

	return msg.toString();
}

