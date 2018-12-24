//----------------------------------------------------------------------
// 
// Filename    : GCMorphVampire2.cpp
// Written By  : crazydog
// 
//----------------------------------------------------------------------

// include files
#include "GCMorphVampire2.h"


//----------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//----------------------------------------------------------------------
void GCMorphVampire2::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	m_VampireInfo3.read( iStream );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void GCMorphVampire2::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

		
	m_VampireInfo3.write( oStream );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCMorphVampire2::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCMorphVampire2Handler::execute( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
string GCMorphVampire2::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCMorphVampire2("
		<< m_VampireInfo3.toString()
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
