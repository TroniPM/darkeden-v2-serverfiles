////////////////////////////////////////////////////////////////////////////////
// 
// Filename    : GCStashSell.cpp 
// Written By  : �輺��
// Description : 
// 
////////////////////////////////////////////////////////////////////////////////

// include files
#include "GCStashSell.h"

////////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void GCStashSell::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	iStream.read(m_Price);

	__END_DEBUG
	__END_CATCH
}

		    
////////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
////////////////////////////////////////////////////////////////////////////////
void GCStashSell::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	oStream.write(m_Price);
	
	__END_DEBUG
	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// execute packet's handler
////////////////////////////////////////////////////////////////////////////////
void GCStashSell::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	GCStashSellHandler::execute( this , pPlayer );

	__END_DEBUG
	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
string GCStashSell::toString () const
       throw ()
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	StringStream msg;
	
	msg << "GCStashSell("
		<< "Price:" << (int)m_Price
		<< ")";

	return msg.toString();
		
	__END_DEBUG
	__END_CATCH
}


