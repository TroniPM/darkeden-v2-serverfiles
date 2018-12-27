//////////////////////////////////////////////////////////////////////////////
// Filename    : GCShopListMysterious.cpp 
// Written By  : �輺��
// Description :
// �÷��̾ ���� ���� ������ ������ �ִ� �Ͱ� �ٸ� ���,
// �÷��̾�� ������ ������ �ִ� ��ǰ ����� �䱸�ϰ� �ȴ�.
// �� ��Ŷ�� �� �� �÷��̾�� �����ϰ� �Ǵ� ��Ŷ�̴�.
//////////////////////////////////////////////////////////////////////////////

#include "GCShopListMysterious.h"
#include "Assert.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
GCShopListMysterious::GCShopListMysterious() 
	
{
	__BEGIN_TRY 

	for (int i=0; i<SHOP_RACK_INDEX_MAX; i++)
		m_pBuffer[i].bExist = false;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
GCShopListMysterious::~GCShopListMysterious() 
	
{
	__BEGIN_TRY 
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void GCShopListMysterious::read ( SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY

	BYTE i      = 0;
	BYTE nTotal = 0;
	BYTE index  = 0;
	
	// read NPC id & version & rack type & number of item
	iStream.read(m_ObjectID);
	iStream.read(m_Version);
	iStream.read(m_RackType);
	iStream.read(nTotal);

	// read each item info
	for (i=0; i<nTotal; i++)
	{
		iStream.read(index);
		iStream.read(m_pBuffer[index].itemClass);
		iStream.read(m_pBuffer[index].itemType);

		m_pBuffer[index].bExist = true;
	}

	// read market condition
	iStream.read(m_MarketCondBuy);
	iStream.read(m_MarketCondSell);

	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////////////
void GCShopListMysterious::write ( SocketOutputStream & oStream ) const 
     
{
	__BEGIN_TRY
		
	BYTE i      = 0;
	BYTE nTotal = 0;
	
	// calculate total number of items
	for (i=0; i<SHOP_RACK_INDEX_MAX; i++)
		if (m_pBuffer[i].bExist) nTotal++;
		
	// write NPC id & version & rack type & number of item
	oStream.write(m_ObjectID);
	oStream.write(m_Version);
	oStream.write(m_RackType);
	oStream.write(nTotal);

	// write each item info
	for (i=0; i<SHOP_RACK_INDEX_MAX; i++)
	{
		if (m_pBuffer[i].bExist)
		{
			oStream.write(i);
			oStream.write(m_pBuffer[i].itemClass);
			oStream.write(m_pBuffer[i].itemType);
		}
	}

	oStream.write(m_MarketCondBuy);
	oStream.write(m_MarketCondSell);
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCShopListMysterious::execute ( Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCShopListMysteriousHandler::execute( this , pPlayer );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
PacketSize_t GCShopListMysterious::getPacketSize () const 
	
{ 
	PacketSize_t unit_size = szBYTE + szItemType;
	PacketSize_t rValue    = 0;

	rValue += szObjectID;     // NPC id
	rValue += szShopVersion;  // shop version
	rValue += szShopRackType; // rack type
	rValue += szBYTE;         // total number of item

	for (int i=0; i<SHOP_RACK_INDEX_MAX; i++)
	{
		if (m_pBuffer[i].bExist) 
		{
			rValue += szBYTE;    // Item index in shop rack
			rValue += unit_size; // actual item info
		}
	}

	rValue += szMarketCond*2; // market condition

	return rValue;
}

//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
string GCShopListMysterious::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCShopListMysterious(" << "ObjectID:" << m_ObjectID << ","
	    << "ShopVersion:" << m_Version << ","
	    << "RackType:" << m_RackType << ",";
	
	for (int i=0; i<SHOP_RACK_INDEX_MAX; i++)
	{
		msg << "(Item" << i << ":";
		if (m_pBuffer[i].bExist)
		{
			msg << "ItemClass:" << (int)(m_pBuffer[i].itemClass) 
			    << "ItemType:"  << (int)(m_pBuffer[i].itemType);
		}
		msg << ")";
	}

	msg << "MarketCondBuy:"  << (int)m_MarketCondBuy
	    << "MarketCondSell:" << (int)m_MarketCondSell;

	msg << ")";

	return msg.toString();
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
SHOPLISTITEM_MYSTERIOUS GCShopListMysterious::getShopItem(BYTE index) const
	
{
	// check bound
	if (index >= SHOP_RACK_INDEX_MAX) throw ("GCShopListMysterious::getShopItem() : Out of Bound!");

	// return shop item info
	return m_pBuffer[index];
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void GCShopListMysterious::setShopItem(BYTE index, const Item* pItem) 
	
{
	// check bound
	if (index >= SHOP_RACK_INDEX_MAX) throw ("GCShopListMysterious::setShopItem() : Out of Bound!");

	// check pointer 
	Assert(pItem != NULL);

	// set shop item info
	m_pBuffer[index].bExist     = true;
	m_pBuffer[index].itemClass  = pItem->getItemClass();
	m_pBuffer[index].itemType   = pItem->getItemType();
}
