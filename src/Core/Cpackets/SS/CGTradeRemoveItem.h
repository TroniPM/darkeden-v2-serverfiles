////////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradeRemoveItem.h 
// Written By  : 김성민
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_TRADE_REMOVE_ITEM_H__
#define __CG_TRADE_REMOVE_ITEM_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeRemoveItem;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradeRemoveItem : public Packet 
{
public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_CG_TRADE_REMOVE_ITEM; }
	PacketSize_t getPacketSize()  { return szObjectID*2; }
	string getPacketName()  { return "CGTradeRemoveItem"; }
	string toString() ;
	
public:
	ObjectID_t getTargetObjectID()  { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id)  { m_TargetObjectID = id; }

	ObjectID_t getItemObjectID()  { return m_ItemObjectID; }
	void setItemObjectID(ObjectID_t id)  { m_ItemObjectID = id; }

private:
	ObjectID_t m_TargetObjectID; // 교환을 원하는 상대방의 ObjectID
	ObjectID_t m_ItemObjectID;   // 교환 리스트에 추가할 아이템의 OID

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeRemoveItemFactory;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradeRemoveItemFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGTradeRemoveItem(); }
	string getPacketName()  { return "CGTradeRemoveItem"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_TRADE_REMOVE_ITEM; }
	PacketSize_t getPacketMaxSize()  { return szObjectID*2; }
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeRemoveItemHandler;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradeRemoveItemHandler 
{
public:
	static void execute(CGTradeRemoveItem* pPacket, Player* player) ;
	static void executeSlayer(CGTradeRemoveItem* pPacket, Player* player) ;
	static void executeVampire(CGTradeRemoveItem* pPacket, Player* player) ;
	static void executeOusters(CGTradeRemoveItem* pPacket, Player* player) ;
	static void executeError(CGTradeRemoveItem* pPacket, Player* player, BYTE ErrorCode) ;
};

#endif
