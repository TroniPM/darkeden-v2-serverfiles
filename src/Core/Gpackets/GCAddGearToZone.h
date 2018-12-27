//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddGearToZone.h 
// Written By  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_GEAR_TO_ZONE_H__
#define __GC_ADD_GEAR_TO_ZONE_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddGearToZone;
//////////////////////////////////////////////////////////////////////////////

class GCAddGearToZone : public Packet 
{
public:
	GCAddGearToZone() ;
	~GCAddGearToZone() ;

public :
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_ADD_GEAR_TO_ZONE; }
	PacketSize_t getPacketSize()  { return szSlotID; }
	string getPacketName()  { return "GCAddGearToZone"; }
	string toString() ;
	
public:
	SlotID_t getSlotID()  { return m_SlotID; }
	void setSlotID(SlotID_t SlotID)  { m_SlotID = SlotID; }

private:
	SlotID_t m_SlotID; // SlotID
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddGearToZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddGearToZoneFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCAddGearToZone(); }
	string getPacketName()  { return "GCAddGearToZone"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_ADD_GEAR_TO_ZONE; }
	PacketSize_t getPacketMaxSize()  { return szSlotID; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddGearToZoneHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddGearToZoneHandler 
{
public:
	static void execute(GCAddGearToZone* pPacket, Player* player) ;
};

#endif
