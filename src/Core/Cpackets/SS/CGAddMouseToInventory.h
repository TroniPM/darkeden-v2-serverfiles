//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddMouseToInventory.h 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_ADD_MOUSE_TO_INVENTORY_H__
#define __CG_ADD_MOUSE_TO_INVENTORY_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGAddMouseToInventory;
//////////////////////////////////////////////////////////////////////////////

class CGAddMouseToInventory : public Packet 
{
public:
	CGAddMouseToInventory() ;
	~CGAddMouseToInventory() ;

public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_CG_ADD_MOUSE_TO_INVENTORY; }
	PacketSize_t getPacketSize()  { return szObjectID + szObjectID + szCoordInven + szCoordInven; }
	string getPacketName()  { return "CGAddMouseToInventory"; }
	string toString() ;
	
public:
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	ObjectID_t getInventoryItemObjectID()  { return m_InventoryItemObjectID; }
	void setInventoryItemObjectID(ObjectID_t InventoryItemObjectID)  { m_InventoryItemObjectID = InventoryItemObjectID; }

	CoordInven_t getInvenX()  { return m_InvenX; }
	void setInvenX(CoordInven_t InvenX)  { m_InvenX = InvenX; }

	CoordInven_t getInvenY()  { return m_InvenY; }
	void setInvenY(CoordInven_t InvenY) { m_InvenY = InvenY; }

private:
	ObjectID_t m_ObjectID;

	// ���� �κ��丮 �������� ������Ʈ ���̵�. 0�̸� ���� �κ��丮���� ����
	ObjectID_t m_InventoryItemObjectID;

	CoordInven_t m_InvenX;
	CoordInven_t m_InvenY;
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddMouseToInventoryFactory;
//////////////////////////////////////////////////////////////////////////////

class CGAddMouseToInventoryFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGAddMouseToInventory(); }
	string getPacketName()  { return "CGAddMouseToInventory"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_ADD_MOUSE_TO_INVENTORY; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + szObjectID + szCoordInven + szCoordInven; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddMouseToInventoryHandler;
//////////////////////////////////////////////////////////////////////////////

class CGAddMouseToInventoryHandler 
{
public:
	static void execute(CGAddMouseToInventory* pPacket, Player* player) ;
};

#endif
