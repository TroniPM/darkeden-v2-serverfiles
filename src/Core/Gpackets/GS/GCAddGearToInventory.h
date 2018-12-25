//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddGearToInventory.h 
// Written By  : crazydog
// Description : 
// Skill ShieldStrike에 의해 발생. shield를 장착창에서 inventory로 보낸다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_GEAR_TO_INVENTORY_H__
#define __GC_ADD_GEAR_TO_INVENTORY_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddGearToInventory;
//////////////////////////////////////////////////////////////////////////////

class GCAddGearToInventory : public Packet 
{
public:
	GCAddGearToInventory() throw();
	~GCAddGearToInventory() throw();

public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_ADD_GEAR_TO_INVENTORY; }
	PacketSize_t getPacketSize()  { return szSlotID + szCoordInven + szCoordInven; }
	string getPacketName()  { return "GCAddGearToInventory"; }
	string toString() ;
	
public:
	SlotID_t getSlotID() throw() { return m_SlotID; }
	void setSlotID(SlotID_t SlotID) throw() { m_SlotID = SlotID; }

	CoordInven_t getInvenX()  { return m_InvenX; }
	void setInvenX(CoordInven_t InvenX) throw() { m_InvenX = InvenX; }

	CoordInven_t getInvenY()  { return m_InvenY; }
	void setInvenY(CoordInven_t InvenY) { m_InvenY = InvenY; }

private:
	SlotID_t     m_SlotID; // wear part ID
	CoordInven_t m_InvenX; // Inventory의 X, Y 좌표.
	CoordInven_t m_InvenY;
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddGearToInventoryFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddGearToInventoryFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCAddGearToInventory(); }
	string getPacketName()  { return "GCAddGearToInventory"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_ADD_GEAR_TO_INVENTORY; }
	PacketSize_t getPacketMaxSize()  { return szSlotID + szCoordInven + szCoordInven; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddGearToInventoryHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddGearToInventoryHandler 
{
public:
	static void execute(GCAddGearToInventory* pPacket, Player* player) ;
};


#endif
