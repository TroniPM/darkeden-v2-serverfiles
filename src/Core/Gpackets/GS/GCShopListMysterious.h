//////////////////////////////////////////////////////////////////////////////
// Filename    : GCShopListMysterious.h 
// Written By  : �輺��
// Description : 
// �÷��̾ ���� ���� ������ ������ �ִ� �Ͱ� �ٸ� ���,
// �÷��̾�� ������ ������ �ִ� ��ǰ ����� �䱸�ϰ� �ȴ�.
// �� ��Ŷ�� �� �� �÷��̾�� �����ϰ� �Ǵ� ��Ŷ�̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_SHOP_LIST_MYSTERIOUS_H__
#define __GC_SHOP_LIST_MYSTERIOUS_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// buffer structure
//////////////////////////////////////////////////////////////////////////////
typedef struct 
{
	bool       bExist;
	BYTE       itemClass;
	ItemType_t itemType;

} SHOPLISTITEM_MYSTERIOUS;


//////////////////////////////////////////////////////////////////////////////
// class GCShopListMysterious;
//////////////////////////////////////////////////////////////////////////////

class Item;

class GCShopListMysterious : public Packet 
{
public:
	GCShopListMysterious() throw();
	virtual ~GCShopListMysterious() throw();

public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_SHOP_LIST_MYSTERIOUS; }
	PacketSize_t getPacketSize() ;
	string getPacketName()  { return "GCShopListMysterious"; }
	string toString() ;

public:
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID) throw() { m_ObjectID = creatureID; }

	ShopVersion_t getShopVersion(void)  { return m_Version;}
	void setShopVersion(ShopVersion_t ver) throw() { m_Version = ver;}
	
	ShopRackType_t getShopType(void)  { return m_RackType;}
	void setShopType(const ShopRackType_t type) { m_RackType = type;}
	
	SHOPLISTITEM_MYSTERIOUS getShopItem(BYTE index) ;
	void setShopItem(BYTE index, const Item* pItem) throw();

	MarketCond_t getMarketCondBuy(void)  { return m_MarketCondBuy;}
	MarketCond_t getMarketCondSell(void)  { return m_MarketCondSell;}
	void setMarketCondBuy(MarketCond_t cond) throw() { m_MarketCondBuy = cond;}
	void setMarketCondSell(MarketCond_t cond) throw() { m_MarketCondSell = cond;}
	
private:
	ObjectID_t              m_ObjectID;                     // NPC's object id
	ShopVersion_t           m_Version;                      // Shop version
	ShopRackType_t          m_RackType;                     // rack type
	SHOPLISTITEM_MYSTERIOUS m_pBuffer[SHOP_RACK_INDEX_MAX]; // buffer for i/o
	MarketCond_t            m_MarketCondBuy;                // ���� �ü�
	MarketCond_t            m_MarketCondSell;

};

//////////////////////////////////////////////////////////////////////////////
// class GCShopListMysteriousFactory;
//////////////////////////////////////////////////////////////////////////////

class GCShopListMysteriousFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCShopListMysterious(); }
	string getPacketName()  { return "GCShopListMysterious"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SHOP_LIST_MYSTERIOUS; }
	PacketSize_t getPacketMaxSize()  
	{ 
		PacketSize_t unit_size = szBYTE + szItemType;
		PacketSize_t rValue    = 0; 

		rValue += szObjectID;                    // NPC ID
		rValue += szShopVersion;                 // shop version
		rValue += szShopRackType;                // shop rack type
		rValue += szBYTE;                        // total number of item
		rValue += unit_size*SHOP_RACK_INDEX_MAX; // actual item info
		rValue += szMarketCond*2;                // market condition

		return rValue;
	}
};


//////////////////////////////////////////////////////////////////////
//
// class GCShopListMysteriousHandler;
//
//////////////////////////////////////////////////////////////////////

class GCShopListMysteriousHandler 
{
public:
	static void execute(GCShopListMysterious* pPacket, Player* pPlayer) ;
};

#endif
