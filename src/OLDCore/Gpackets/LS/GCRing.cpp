//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRing.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCRing.h"




//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCRing::GCRing () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCRing::~GCRing () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCRing::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_PhoneNumber );
	iStream.read( m_SlotID );

	BYTE szName;
	iStream.read( szName );

	if ( szName == 0 )
		throw InvalidProtocolException("szName == 0");
	if ( szName > 20 )
		throw InvalidProtocolException("too long name length");

	iStream.read( m_Name , szName );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCRing::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( m_PhoneNumber );
	oStream.write( m_SlotID );

	BYTE szName = m_Name.size();

	if ( szName == 0 )
	throw InvalidProtocolException("szName == 0");

	if ( szName > 20 )
	throw InvalidProtocolException("too long name length");

	oStream.write( szName );
	oStream.write( m_Name );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCRing::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	GCRingHandler::execute ( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// toString()
//////////////////////////////////////////////////////////////////////
string GCRing::toString () const
    throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCRing("
		<< "PhoneNumber:" << (int)m_PhoneNumber
		<< ",SlotID:" << (int)m_SlotID
		<< ",Name:" << m_Name
		<< " )";
	return msg.toString();

	__END_CATCH
}

