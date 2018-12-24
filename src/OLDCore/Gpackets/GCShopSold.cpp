//--------------------------------------------------------------------------------
// 
// Filename    : GCShopSold.cpp 
// Written By  : �輺��
// Description : �� �÷��̾ ���� NPC���� ������ �����ߴµ�,
//               �ٸ� �÷��̾ ���� ���� NPC�� ��ȭ ���̾��ٸ�,
//               �� �÷��̾�� ������ ����� ����ȭ�����־�� �Ѵ�.
//               �� ��Ŷ�� �׸� ���� ��Ŷ�̴�.
// 
//--------------------------------------------------------------------------------

// include files
#include "GCShopSold.h"
#include "Assert.h"

//--------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------

GCShopSold::GCShopSold() 
	throw ()
{
	__BEGIN_TRY 
	
	__END_CATCH;
}

//--------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------
GCShopSold::~GCShopSold() 
	throw ()
{
	__BEGIN_TRY 
	
	__END_CATCH;
}

//--------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//--------------------------------------------------------------------
void GCShopSold::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );
	iStream.read( m_Version );
	iStream.read( m_RackType );
	iStream.read( m_RackIndex );	

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void GCShopSold::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( m_ObjectID );
	oStream.write( m_Version );
	oStream.write( m_RackType );
	oStream.write( m_RackIndex );	
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCShopSold::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCShopSoldHandler::execute( this , pPlayer );

	__END_CATCH
}

//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
string GCShopSold::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCShopSold("     
		<< "ObjectID:"        << (int)m_ObjectID
		<< ",ShopVersion: "   << (int)m_Version
		<< ",ShopRackType: "  << (int)m_RackType
		<< ",ShopRackIndex: " << (int)m_RackIndex
		<< ")";
	return msg.toString();
		
	__END_CATCH
}


