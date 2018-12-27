//////////////////////////////////////////////////////////////////////////////
// Filename    : GCShopBuyFail.cpp 
// Written By  : excel96
// Description :
// �÷��̾ �������� �������� �����Ϸ��� �ߴµ�,
// �������� ���Ű� �������� ��쿡 �÷��̾�� ������ ��Ŷ.
//////////////////////////////////////////////////////////////////////////////

#include "GCShopBuyFail.h"
#include "Assert.h"

GCShopBuyFail::GCShopBuyFail()
{
	m_ObjectID = 0;
	m_Code     = GC_SHOP_BUY_FAIL_MAX;
	m_Amount   = 0;
}

GCShopBuyFail::~GCShopBuyFail()
{
}

void GCShopBuyFail::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_Code);
	iStream.read(m_Amount);

	__END_CATCH
}
		    
void GCShopBuyFail::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
		
	oStream.write(m_ObjectID);
	oStream.write(m_Code);
	oStream.write(m_Amount);

	__END_CATCH
}

void GCShopBuyFail::execute (Player * pPlayer) 
	 
{
	__BEGIN_TRY
		
	GCShopBuyFailHandler::execute(this , pPlayer);

	__END_CATCH
}

string GCShopBuyFail::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCShopBuyFail(" 
		<< "ObjectID:" << m_ObjectID 
		<< ",CODE:" << GCShopBuyFailCode2String[m_Code]
		<< ",Amount:" << m_Amount
		<< ")";
	return msg.toString();
		
	__END_CATCH
}


