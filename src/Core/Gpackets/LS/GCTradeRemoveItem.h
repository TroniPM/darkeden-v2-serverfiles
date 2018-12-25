////////////////////////////////////////////////////////////////////////////////
// Filename    : GCTradeRemoveItem.h 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __GC_TRADE_REMOVE_ITEM_H__
#define __GC_TRADE_REMOVE_ITEM_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeRemoveItem
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeRemoveItem : public Packet 
{
public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_TRADE_REMOVE_ITEM; }
	PacketSize_t getPacketSize()  { return szObjectID*2; }
	string getPacketName()  { return "GCTradeRemoveItem"; }
	string toString() ;

public:
	ObjectID_t getTargetObjectID()  { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id) throw() { m_TargetObjectID = id; }

	ObjectID_t getItemObjectID()  { return m_ItemObjectID; }
	void setItemObjectID(ObjectID_t id) throw() { m_ItemObjectID = id; }

private:
	ObjectID_t m_TargetObjectID; // ��ȯ�� ���ϴ� ������ ObjectID
	ObjectID_t m_ItemObjectID;   // ��ȯ ����Ʈ�� �߰��� �������� OID

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeRemoveItemFactory;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeRemoveItemFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCTradeRemoveItem(); }
	string getPacketName()  { return "GCTradeRemoveItem"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_TRADE_REMOVE_ITEM; }
	PacketSize_t getPacketMaxSize()  { return szObjectID*2; }

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeRemoveItemHandler;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeRemoveItemHandler 
{
public:
	static void execute(GCTradeRemoveItem* pPacket, Player* pPlayer) ;

};

#endif
