//--------------------------------------------------------------------------------
// 
// Filename    : GCShopVersion.h 
// Written By  : �輺��
// Description : �÷��̾�� ���� ���� ���� ������ �˷��� �� ���̴� ��Ŷ�̴�.
// 
//--------------------------------------------------------------------------------

#ifndef __GC_SHOP_VERSION_H__
#define __GC_SHOP_VERSION_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//--------------------------------------------------------------------------------
//
// class GCShopVersion;
//
//--------------------------------------------------------------------------------

class GCShopVersion : public Packet 
{

public :

	GCShopVersion() ;
	virtual ~GCShopVersion() ;
	
	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read(SocketInputStream & iStream) ;
		    
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_SHOP_VERSION; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szObjectID + szShopVersion*3 + szMarketCond; }

	// get packet name
	string getPacketName()  { return "GCShopVersion"; }
	
	// get packet's debug string
	string toString() ;


public :

	// get/set NPC's object id
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID) throw() { m_ObjectID = creatureID; }

	// get/set shop version
	ShopVersion_t getVersion(ShopRackType_t type) 
	{
		if(type >= SHOP_RACK_TYPE_MAX) throw("GCShopVersion::getVersion() : Out of Bound!");
		return m_Version[type];
	}
	
	void setVersion(ShopRackType_t type, ShopVersion_t ver) throw()
	{
		if(type >= SHOP_RACK_TYPE_MAX) throw("GCShopVersion::setVersion() : Out of Bound!");
		m_Version[type] = ver;
	}

	// get/set market condition sell
	MarketCond_t getMarketCondSell(void)  { return m_MarketCondSell;}
	void setMarketCondSell(MarketCond_t cond) throw() { m_MarketCondSell = cond;}

private :

	// NPC's object id
	ObjectID_t m_ObjectID;

	// shop version
	ShopVersion_t m_Version[SHOP_RACK_TYPE_MAX];

	MarketCond_t m_MarketCondSell;
};


//////////////////////////////////////////////////////////////////////
//
// class GCShopVersionFactory;
//
// Factory for GCShopVersion
//
//////////////////////////////////////////////////////////////////////

class GCShopVersionFactory : public PacketFactory 
{

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCShopVersion(); }

	// get packet name
	string getPacketName()  { return "GCShopVersion"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SHOP_VERSION; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCShopVersionPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  { return szObjectID + szShopVersion*3 + szMarketCond; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCShopVersionHandler;
//
//////////////////////////////////////////////////////////////////////

class GCShopVersionHandler 
{
	
public :
	
	// execute packet's handler
	static void execute(GCShopVersion* pPacket, Player* pPlayer) ;

};

#endif
