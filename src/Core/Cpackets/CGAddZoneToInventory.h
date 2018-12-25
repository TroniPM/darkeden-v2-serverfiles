//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddZoneToInventory.h 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_ADD_ZONE_TO_INVENTORY_H__
#define __CG_ADD_ZONE_TO_INVENTORY_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGAddZoneToInventory;
//////////////////////////////////////////////////////////////////////////////

class CGAddZoneToInventory : public Packet 
{
public:
	CGAddZoneToInventory() throw();
	~CGAddZoneToInventory() throw();

public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_CG_ADD_ZONE_TO_INVENTORY; }
	PacketSize_t getPacketSize()  { return szObjectID + szCoord + szCoord + szCoordInven + szCoordInven; }
	string getPacketName()  { return "CGAddZoneToInventory"; }
	string toString() ;
	
public:
	ObjectID_t getObjectID() throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	Coord_t getZoneX()  { return m_ZoneX; }
	void setZoneX(Coord_t ZoneX) throw() { m_ZoneX = ZoneX; }

	Coord_t getZoneY()  { return m_ZoneY; }
	void setZoneY(Coord_t ZoneY) throw() { m_ZoneY = ZoneY; }

	CoordInven_t getInvenX()  { return m_InvenX; }
	void setInvenX(CoordInven_t InvenX) throw() { m_InvenX = InvenX; }

	CoordInven_t getInvenY()  { return m_InvenY; }
	void setInvenY(CoordInven_t InvenY) { m_InvenY = InvenY; }

private:
	ObjectID_t   m_ObjectID;
	Coord_t      m_ZoneX;
	Coord_t      m_ZoneY;
	CoordInven_t m_InvenX;
	CoordInven_t m_InvenY;
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddZoneToInventoryFactory;
//////////////////////////////////////////////////////////////////////////////

class CGAddZoneToInventoryFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGAddZoneToInventory(); }
	string getPacketName()  { return "CGAddZoneToInventory"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_ADD_ZONE_TO_INVENTORY; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + szCoord + szCoord + szCoordInven + szCoordInven; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddZoneToInventoryHandler;
//////////////////////////////////////////////////////////////////////////////

class CGAddZoneToInventoryHandler 
{
public:
	static void execute(CGAddZoneToInventory* pPacket, Player* player) ;
};

#endif
