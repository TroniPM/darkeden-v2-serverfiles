//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddMouseToQuickSlot.h 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_ADD_MOUSE_TO_QUICKSLOT_H__
#define __CG_ADD_MOUSE_TO_QUICKSLOT_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGAddMouseToQuickSlot;
//////////////////////////////////////////////////////////////////////////////

class CGAddMouseToQuickSlot : public Packet 
{
public:
	CGAddMouseToQuickSlot() throw();
	~CGAddMouseToQuickSlot() throw();

public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_CG_ADD_MOUSE_TO_QUICKSLOT; }
	PacketSize_t getPacketSize()  { return szObjectID + szSlotID; }
	string getPacketName()  { return "CGAddMouseToQuickSlot"; }
	string toString() ;
	
public:
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	SlotID_t getSlotID()  { return m_SlotID; }
	void setSlotID(SlotID_t SlotID) throw() { m_SlotID = SlotID; }

private:
	ObjectID_t m_ObjectID;
	SlotID_t m_SlotID;
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddMouseToQuickSlotFactory;
//////////////////////////////////////////////////////////////////////////////

class CGAddMouseToQuickSlotFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGAddMouseToQuickSlot(); }
	string getPacketName()  { return "CGAddMouseToQuickSlot"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_ADD_MOUSE_TO_QUICKSLOT; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + szSlotID; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddMouseToQuickSlotHandler;
//////////////////////////////////////////////////////////////////////////////

class CGAddMouseToQuickSlotHandler 
{
public:
	static void execute(CGAddMouseToQuickSlot* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
