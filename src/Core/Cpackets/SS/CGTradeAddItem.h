////////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradeAddItem.h 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_TRADE_ADD_ITEM_H__
#define __CG_TRADE_ADD_ITEM_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeAddItem;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradeAddItem : public Packet 
{
public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_CG_TRADE_ADD_ITEM; }
	PacketSize_t getPacketSize()  { return szObjectID*2; }
	string getPacketName()  { return "CGTradeAddItem"; }
	string toString() ;
	
public:
	ObjectID_t getTargetObjectID()  { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id)  { m_TargetObjectID = id; }

	ObjectID_t getItemObjectID()  { return m_ItemObjectID; }
	void setItemObjectID(ObjectID_t id)  { m_ItemObjectID = id; }

private:
	ObjectID_t m_TargetObjectID; // ��ȯ�� ���ϴ� ������ ObjectID
	ObjectID_t m_ItemObjectID;   // ��ȯ ����Ʈ�� �߰��� �������� OID

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeAddItemFactory;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradeAddItemFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGTradeAddItem(); }
	string getPacketName()  { return "CGTradeAddItem"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_TRADE_ADD_ITEM; }
	PacketSize_t getPacketMaxSize()  { return szObjectID*2; }
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeAddItemHandler;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeAddItem;
class Item;

class CGTradeAddItemHandler 
{
public:
	static void execute(CGTradeAddItem* pPacket, Player* player) ;
	static void executeSlayer(CGTradeAddItem* pPacket, Player* player) ;
	static void executeVampire(CGTradeAddItem* pPacket, Player* player) ;
	static void executeOusters(CGTradeAddItem* pPacket, Player* player) ;
	static void makeGCTradeAddItemPacket(GCTradeAddItem* pPacket, ObjectID_t Sender, Item* pItem, CoordInven_t X, CoordInven_t Y) ;
	static void executeError(CGTradeAddItem* pPacket, Player* player, BYTE ErrorCode) ;
};

#endif
