////////////////////////////////////////////////////////////////////////////////
// Filename    : CGShopRequestSell.h 
// Written By  : �輺��
// Description : 
// �÷��̾�� �ڽ��� ������ �ִ� �������� ���� NPC����
// �ȱ⸦ ��û�� �� ���̴� ��Ŷ�̴�.
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_SHOP_REQUEST_SELL_H__
#define __CG_SHOP_REQUEST_SELL_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// CGShopRequestSell operation code
////////////////////////////////////////////////////////////////////////////////
enum
{
	SHOP_REQUEST_SELL_NORMAL = 0,
	SHOP_REQUEST_SELL_ALL_SKULL,
	SHOP_REQUEST_SWAP_ADVANCEMENT_ITEM,

	SHOP_REQUEST_SELL_MAX
};

////////////////////////////////////////////////////////////////////////////////
//
// class CGShopRequestSell;
//
////////////////////////////////////////////////////////////////////////////////

class CGShopRequestSell : public Packet 
{
public:
	CGShopRequestSell() { m_ObjectID = 0; m_ItemObjectID = 0; m_OpCode = SHOP_REQUEST_SELL_NORMAL; }


public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_CG_SHOP_REQUEST_SELL; }
	PacketSize_t getPacketSize()  { return szObjectID+szObjectID+szBYTE; }
	string getPacketName()  { return "CGShopRequestSell"; }
	string toString() ;
	
public:
	ObjectID_t getObjectID() throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	ObjectID_t getItemObjectID() throw() { return m_ItemObjectID;}
	void setItemObjectID(ObjectID_t oid) { m_ItemObjectID = oid;}

	BYTE getOpCode(void) const { return m_OpCode; }
	void setOpCode(BYTE code) { m_OpCode = code; }

private:
	ObjectID_t m_ObjectID;     // NPC ID
	ObjectID_t m_ItemObjectID; // Item Object ID
	BYTE       m_OpCode;       // operation code

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGShopRequestSellFactory;
//
////////////////////////////////////////////////////////////////////////////////

class CGShopRequestSellFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGShopRequestSell(); }
	string getPacketName()  { return "CGShopRequestSell"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_SHOP_REQUEST_SELL; }
	PacketSize_t getPacketMaxSize()  { return szObjectID+szObjectID+szBYTE; }

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGShopRequestSellHandler;
//
////////////////////////////////////////////////////////////////////////////////

class CGShopRequestSellHandler 
{
public:
	static void execute(CGShopRequestSell* pPacket, Player* player) throw(ProtocolException, Error);

	static void executeNormal(CGShopRequestSell* pPacket, Player* player) throw(ProtocolException, Error);
	static void executeMotorcycle(CGShopRequestSell* pPacket, Player* player) throw(ProtocolException, Error);
	static void executeOpAllSkull(CGShopRequestSell* pPacket, Player* player) throw(ProtocolException, Error);
	static void executeOpSwapAdvancementItem(CGShopRequestSell* pPacket, Player* player) throw(ProtocolException, Error);

	static void sendFailPacket(CGShopRequestSell* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
