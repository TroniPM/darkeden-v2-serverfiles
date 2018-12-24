//--------------------------------------------------------------------------------
// 
// Filename    : GCShopMarketCondition.h 
// Written By  : �輺��
// Description : �÷��̾�� ���� ���� ���� ������ �˷��� �� ���̴� ��Ŷ�̴�.
// 
//--------------------------------------------------------------------------------

#ifndef __GC_SHOP_MARKET_CONDITION_H__
#define __GC_SHOP_MARKET_CONDITION_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//--------------------------------------------------------------------------------
//
// class GCShopMarketCondition;
//
//--------------------------------------------------------------------------------

class GCShopMarketCondition : public Packet 
{

public :

	GCShopMarketCondition() throw();
	virtual ~GCShopMarketCondition() throw();
	
	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_SHOP_MARKET_CONDITION; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szObjectID + szMarketCond*2; }

	// get packet name
	string getPacketName() const throw() { return "GCShopMarketCondition"; }
	
	// get packet's debug string
	string toString() const throw();


public :

	// get/set NPC's object id
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID) throw() { m_ObjectID = creatureID; }

	// get/set market condition buy
	MarketCond_t getMarketCondBuy(void) const throw() { return m_MarketCondBuy;}
	void setMarketCondBuy(MarketCond_t cond) throw() { m_MarketCondBuy = cond;}

	// get/set market condition sell
	MarketCond_t getMarketCondSell(void) const throw() { return m_MarketCondSell;}
	void setMarketCondSell(MarketCond_t cond) throw() { m_MarketCondSell = cond;}

private :
	
	// NPC's object id
	ObjectID_t m_ObjectID;

	// shop version
	MarketCond_t m_MarketCondBuy;
	MarketCond_t m_MarketCondSell;

};


//////////////////////////////////////////////////////////////////////
//
// class GCShopMarketConditionFactory;
//
// Factory for GCShopMarketCondition
//
//////////////////////////////////////////////////////////////////////

class GCShopMarketConditionFactory : public PacketFactory 
{

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCShopMarketCondition(); }

	// get packet name
	string getPacketName() const throw() { return "GCShopMarketCondition"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SHOP_MARKET_CONDITION; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCShopMarketConditionPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szMarketCond*2; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCShopMarketConditionHandler;
//
//////////////////////////////////////////////////////////////////////

class GCShopMarketConditionHandler 
{
	
public :
	
	// execute packet's handler
	static void execute(GCShopMarketCondition* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
