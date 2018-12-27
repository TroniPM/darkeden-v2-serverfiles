//--------------------------------------------------------------------------------
// 
// Filename    : GCShopSellFail.h 
// Written By  : �輺��
// Description : �÷��̾ NPC���� ������ �ȷ��� �ߴµ�, � ������ 
//               �������� ��쿡�� �� ��Ŷ�� �÷��̾�� �����ش�.
// 
//--------------------------------------------------------------------------------

#ifndef __GC_SHOP_SELL_FAIL_H__
#define __GC_SHOP_SELL_FAIL_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//--------------------------------------------------------------------------------
//
// class GCShopSellFail;
//
//--------------------------------------------------------------------------------

class GCShopSellFail : public Packet 
{

public :

	GCShopSellFail() ;
	virtual ~GCShopSellFail() ;
	
	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read(SocketInputStream & iStream) ;
		    
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_SHOP_SELL_FAIL; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szObjectID;}

	// get packet name
	string getPacketName()  { return "GCShopSellFail"; }
	
	// get packet's debug string
	string toString() ;


public :

	// get/set NPC's object id
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID)  { m_ObjectID = creatureID; }


private :
	
	// NPC's object id
	ObjectID_t m_ObjectID;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCShopSellFailFactory;
//
// Factory for GCShopSellFail
//
//////////////////////////////////////////////////////////////////////

class GCShopSellFailFactory : public PacketFactory 
{

public :
	
	// create packet
	Packet* createPacket()  { return new GCShopSellFail(); }

	// get packet name
	string getPacketName()  { return "GCShopSellFail"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SHOP_SELL_FAIL; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCShopSellFailPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  { return szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCShopSellFailHandler;
//
//////////////////////////////////////////////////////////////////////

class GCShopSellFailHandler 
{
	
public :
	
	// execute packet's handler
	static void execute(GCShopSellFail* pPacket, Player* pPlayer) ;

};

#endif
