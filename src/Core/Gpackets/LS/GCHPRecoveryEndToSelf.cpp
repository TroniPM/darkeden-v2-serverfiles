//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCHPRecoveryEndToSelf.cpp 
// Written By  : Reiot
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCHPRecoveryEndToSelf.h"

//--------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------
GCHPRecoveryEndToSelf::GCHPRecoveryEndToSelf()
	
{
	__BEGIN_TRY
	m_CurrentHP = 0;
	__END_CATCH
}

//--------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------
GCHPRecoveryEndToSelf::~GCHPRecoveryEndToSelf()
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCHPRecoveryEndToSelf::read ( SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY
		
	iStream.read( m_CurrentHP );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCHPRecoveryEndToSelf::write ( SocketOutputStream & oStream ) const 
     
{
	__BEGIN_TRY
		
	oStream.write( m_CurrentHP );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCHPRecoveryEndToSelf::execute ( Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCHPRecoveryEndToSelfHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCHPRecoveryEndToSelf::toString () const
       
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCHPRecoveryEndToSelf("
		<< ",CurrentHP:" << (int)m_CurrentHP
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
