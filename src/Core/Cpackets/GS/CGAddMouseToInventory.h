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
	CGAddMouseToInventory() throw();
	~CGAddMouseToInventory() throw();

public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_CG_ADD_MOUSE_TO_INVENTORY; }
	PacketSize_t getPacketSize()  { return szObjectID + szObjectID + szCoordInven + szCoordInven; }
	string getPacketName()  { return "CGAddMouseToInventory"; }
	string toString() ;
	
public:
	ObjectID_t getObjectID() throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	ObjectID_t getInventoryItemObjectID() throw() { return m_InventoryItemObjectID; }
	void setInventoryItemObjectID(ObjectID_t InventoryItemObjectID) throw() { m_InventoryItemObjectID = InventoryItemObjectID; }

	CoordInven_t getInvenX()  { return m_InvenX; }
	void setInvenX(CoordInven_t InvenX) throw() { m_InvenX = InvenX; }

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
	Packet* createPacket() throw() { return new CGAddMouseToInventory(); }
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
	static void execute(CGAddMouseToInventory* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
