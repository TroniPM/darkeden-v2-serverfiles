//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCStatusCurrentHP.cpp 
// Written By  : Reiot
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCStatusCurrentHP.h"

//--------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------
GCStatusCurrentHP::GCStatusCurrentHP()
	
{
	__BEGIN_TRY
	m_CurrentHP = 0;
	m_ObjectID = 0;
	__END_CATCH
}

//--------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------
GCStatusCurrentHP::~GCStatusCurrentHP()
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCStatusCurrentHP::read ( SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );
	iStream.read( m_CurrentHP );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCStatusCurrentHP::write ( SocketOutputStream & oStream ) const 
     
{
	__BEGIN_TRY
		
	oStream.write( m_ObjectID );
	oStream.write( m_CurrentHP );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCStatusCurrentHP::execute ( Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCStatusCurrentHPHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCStatusCurrentHP::toString () const
       
{
	__BEGIN_TRY

	StringStream msg;

	msg << "GCStatusCurrentHP("
		<< "ObjectID:" << m_ObjectID
		<< ",CurrentHP:" << (int)m_CurrentHP
		<< ")" ;

	return msg.toString();

	__END_CATCH
}
