//--------------------------------------------------------------------------------
// 
// Filename    : GCShopSellOK.h 
// Written By  : �輺��
// Description : �÷��̾ ���� NPC���� ���� ������ ��û���� ��, �����
//               ������ �Ǹ� �� ��Ŷ�� �÷��̾�� ���ư���.
//               Ŭ���̾�Ʈ�� �� ��Ŷ�� �޾Ƽ� ���� ������ ������Ʈ�ϰ�,
//               ������Ʈ ID�� ������ ������ üũ�� ����, ������ �̿���
//               �÷��̾��� ���� ������Ʈ�Ѵ�.
// 
//--------------------------------------------------------------------------------

#ifndef __GC_SHOP_SELL_OK_H__
#define __GC_SHOP_SELL_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//--------------------------------------------------------------------------------
//
// class GCShopSellOK;
//
//--------------------------------------------------------------------------------

class GCShopSellOK : public Packet 
{

public :

	GCShopSellOK() throw();
	virtual ~GCShopSellOK() throw();
	
	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_SHOP_SELL_OK; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szObjectID + szShopVersion + szObjectID + szPrice;
	}

	// get packet name
	string getPacketName() const throw() { return "GCShopSellOK"; }
	
	// get packet's debug string
	string toString() const throw();


public :

	// get/set NPC's object id
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID) throw() { m_ObjectID = creatureID; }

	// get/set shop version	
	ShopVersion_t getShopVersion(void) const throw() { return m_Version;}
	void setShopVersion(const ShopVersion_t ver) throw() { m_Version = ver;}

	// get/set item object id
	ObjectID_t getItemObjectID() const throw() { return m_ItemObjectID;}
	void setItemObjectID(ObjectID_t id) throw() { m_ItemObjectID = id;}

	// get/set price
	Price_t getPrice() const throw() { return m_Price;}
	void setPrice(Price_t price) { m_Price = price;}

private :
	

	// NPC's object id
	ObjectID_t m_ObjectID;
	
	// ���� ����
	ShopVersion_t m_Version;
	
	// ������ ����
	ObjectID_t    m_ItemObjectID;

	// ����
	Price_t       m_Price;

};


//////////////////////////////////////////////////////////////////////
//
// class GCShopSellOKFactory;
//
// Factory for GCShopSellOK
//
//////////////////////////////////////////////////////////////////////

class GCShopSellOKFactory : public PacketFactory 
{

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCShopSellOK(); }

	// get packet name
	string getPacketName() const throw() { return "GCShopSellOK"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SHOP_SELL_OK; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szObjectID + szShopVersion + szObjectID + szPrice;
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCShopSellOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GCShopSellOKHandler 
{
	
public :
	
	// execute packet's handler
	static void execute(GCShopSellOK* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
