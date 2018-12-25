//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUseItemFromInventory.h 
// Written By  : excel96
// Description : 
// �κ��丮 ���� �������� ����� ��, Ŭ���̾�Ʈ�� X, Y �� ObjectID��
// ������ ������ Ŭ������ ����, ������ �̿� �´� �ڵ带 ó���Ѵ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_USE_ITEM_FROM_INVENTORY_H__
#define __CG_USE_ITEM_FROM_INVENTORY_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGUseItemFromInventory;
//////////////////////////////////////////////////////////////////////////////

class CGUseItemFromInventory : public Packet 
{
public:
	CGUseItemFromInventory () throw ();
	~CGUseItemFromInventory () throw ();
	
   	 void read(SocketInputStream & iStream) throw(ProtocolException, Error);
   	 void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_CG_USE_ITEM_FROM_INVENTORY; }
	PacketSize_t getPacketSize()  { return szObjectID + szObjectID + szCoordInven + szCoordInven; }
	string getPacketName()  { return "CGUseItemFromInventory"; }
	string toString() ;
	
public:
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	ObjectID_t getInventoryItemObjectID() throw() { return m_InventoryItemObjectID; }
	void setInventoryItemObjectID(ObjectID_t InventoryItemObjectID) throw() { m_InventoryItemObjectID = InventoryItemObjectID; }

	CoordInven_t getX()  { return m_InvenX; }
	void setX(CoordInven_t InvenX) throw() { m_InvenX = InvenX; }

	CoordInven_t getY()  { return m_InvenY; }
	void setY(CoordInven_t InvenY) throw() { m_InvenY = InvenY; }

private:
	ObjectID_t   m_ObjectID; // �������� object id 
	CoordInven_t m_InvenX;   // �������� �κ��丮 ��ǥ X
	CoordInven_t m_InvenY;   // �������� �κ��丮 ��ǥ Y
	ObjectID_t	 m_InventoryItemObjectID;
};


//////////////////////////////////////////////////////////////////////////////
// class CGUseItemFromInventoryFactory;
//////////////////////////////////////////////////////////////////////////////

class CGUseItemFromInventoryFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGUseItemFromInventory(); }
	string getPacketName()  { return "CGUseItemFromInventory"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_USE_ITEM_FROM_INVENTORY; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + szObjectID + szCoordInven + szCoordInven; }
};


//////////////////////////////////////////////////////////////////////////////
// class CGUseItemFromInventoryHandler;
//////////////////////////////////////////////////////////////////////////////

class Inventory;
class Item;

class CGUseItemFromInventoryHandler 
{
public:
	static void execute(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error);

protected:
	static void executePotion(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeMagazine(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeETC(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeSerum(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeVampireETC(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeSlayerPortalItem(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeOustersSummonItem(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeKeyItem(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeFirecraker(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeDyePotion(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeResurrectItem(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeTranslator(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeEffectItem(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executePetItem(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executePetFood(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeEventGiftBox(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeTrapItem(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeSubInventory(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeSkillBook(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeOustersWingItem(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
