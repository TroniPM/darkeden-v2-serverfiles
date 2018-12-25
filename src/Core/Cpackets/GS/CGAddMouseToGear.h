//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddMouseToGear.h 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_ADD_MOUSE_TO_GEAR_H__
#define __CG_ADD_MOUSE_TO_GEAR_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGAddMouseToGear;
//////////////////////////////////////////////////////////////////////////////

class CGAddMouseToGear : public Packet 
{
public:
	CGAddMouseToGear() throw();
	~CGAddMouseToGear() throw();

public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_CG_ADD_MOUSE_TO_GEAR; }
	PacketSize_t getPacketSize()  { return szObjectID + szSlotID; }
	string getPacketName()  { return "CGAddMouseToGear"; }
	string toString() ;
	
public:
	ObjectID_t getObjectID() throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	SlotID_t getSlotID()  { return m_SlotID; }
	void setSlotID(SlotID_t SlotID) throw() { m_SlotID = SlotID; }

private:
	ObjectID_t m_ObjectID;
	SlotID_t   m_SlotID;

};

//////////////////////////////////////////////////////////////////////////////
// class CGAddMouseToGearFactory;
//////////////////////////////////////////////////////////////////////////////

class CGAddMouseToGearFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGAddMouseToGear(); }
	string getPacketName()  { return "CGAddMouseToGear"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_ADD_MOUSE_TO_GEAR; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + szSlotID; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddMouseToGearHandler;
//////////////////////////////////////////////////////////////////////////////

class CGAddMouseToGearHandler 
{
public:
	static void execute(CGAddMouseToGear* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
