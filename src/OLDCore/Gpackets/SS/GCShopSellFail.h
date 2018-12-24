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

	GCShopSellFail() throw();
	virtual ~GCShopSellFail() throw();
	
	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_SHOP_SELL_FAIL; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szObjectID;}

	// get packet name
	string getPacketName() const throw() { return "GCShopSellFail"; }
	
	// get packet's debug string
	string toString() const throw();


public :

	// get/set NPC's object id
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID) throw() { m_ObjectID = creatureID; }


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
	Packet* createPacket() throw() { return new GCShopSellFail(); }

	// get packet name
	string getPacketName() const throw() { return "GCShopSellFail"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SHOP_SELL_FAIL; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCShopSellFailPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID; }

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
	static void execute(GCShopSellFail* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
