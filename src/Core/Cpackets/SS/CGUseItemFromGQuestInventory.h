//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUseItemFromGQuestInventory.h 
// Written By  : excel96
// Description : 
// 인벤토리 안의 아이템을 사용할 때, 클라이언트가 X, Y 및 ObjectID를
// 보내면 아이템 클래스에 따라서, 서버가 이에 맞는 코드를 처리한다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_USE_ITEM_FROM_GQUEST_INVENTORY_H__
#define __CG_USE_ITEM_FROM_GQUEST_INVENTORY_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGUseItemFromGQuestInventory;
//////////////////////////////////////////////////////////////////////////////

class CGUseItemFromGQuestInventory : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_CG_USE_ITEM_FROM_GQUEST_INVENTORY; }
	PacketSize_t getPacketSize()  { return szBYTE; }
	string getPacketName()  { return "CGUseItemFromGQuestInventory"; }
	string toString() ;
	
public:
	BYTE getIndex()  { return m_Index; }
	void setIndex(BYTE Index) throw() { m_Index = Index; }

private:
	BYTE   m_Index; // 아이템의 index
};


//////////////////////////////////////////////////////////////////////////////
// class CGUseItemFromGQuestInventoryFactory;
//////////////////////////////////////////////////////////////////////////////

class CGUseItemFromGQuestInventoryFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGUseItemFromGQuestInventory(); }
	string getPacketName()  { return "CGUseItemFromGQuestInventory"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_USE_ITEM_FROM_GQUEST_INVENTORY; }
	PacketSize_t getPacketMaxSize()  { return szBYTE; }
};


//////////////////////////////////////////////////////////////////////////////
// class CGUseItemFromGQuestInventoryHandler;
//////////////////////////////////////////////////////////////////////////////

class GQuestInventory;
class Item;

class CGUseItemFromGQuestInventoryHandler 
{
public:
	static void execute(CGUseItemFromGQuestInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
