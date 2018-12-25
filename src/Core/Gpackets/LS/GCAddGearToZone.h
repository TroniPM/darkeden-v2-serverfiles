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
	GCAddGearToZone() throw();
	~GCAddGearToZone() throw();

public :
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_GC_ADD_GEAR_TO_ZONE; }
	PacketSize_t getPacketSize()  { return szSlotID; }
	string getPacketName()  { return "GCAddGearToZone"; }
	string toString() ;
	
public:
	SlotID_t getSlotID() throw() { return m_SlotID; }
	void setSlotID(SlotID_t SlotID) throw() { m_SlotID = SlotID; }

private:
	SlotID_t m_SlotID; // SlotID
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddGearToZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddGearToZoneFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCAddGearToZone(); }
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
	static void execute(GCAddGearToZone* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
