//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUseItemFromGQuestInventory.h 
// Written By  : excel96
// Description : 
// �κ��丮 ���� �������� ����� ��, Ŭ���̾�Ʈ�� X, Y �� ObjectID��
// ������ ������ Ŭ������ ����, ������ �̿� �´� �ڵ带 ó���Ѵ�.
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
	BYTE   m_Index; // �������� index
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
