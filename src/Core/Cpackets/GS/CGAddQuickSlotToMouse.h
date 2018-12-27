//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddQuickSlotToMouse.h 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_ADD_QUICKSLOT_TO_MOUSE_H__
#define __CG_ADD_QUICKSLOT_TO_MOUSE_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGAddQuickSlotToMouse;
//////////////////////////////////////////////////////////////////////////////

class CGAddQuickSlotToMouse : public Packet 
{
public:
	CGAddQuickSlotToMouse() ;
	~CGAddQuickSlotToMouse() ;

public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_CG_ADD_QUICKSLOT_TO_MOUSE; }
	PacketSize_t getPacketSize()  { return szObjectID + szSlotID; }
	string getPacketName()  { return "CGAddQuickSlotToMouse"; }
	string toString() ;
	
public:
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	SlotID_t getSlotID()  { return m_SlotID; }
	void setSlotID(SlotID_t SlotID)  { m_SlotID = SlotID; }

private:
	ObjectID_t m_ObjectID;
	SlotID_t m_SlotID;
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddQuickSlotToMouseFactory;
//////////////////////////////////////////////////////////////////////////////

class CGAddQuickSlotToMouseFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGAddQuickSlotToMouse(); }
	string getPacketName()  { return "CGAddQuickSlotToMouse"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_ADD_QUICKSLOT_TO_MOUSE; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + szSlotID; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddQuickSlotToMouseHandler;
//////////////////////////////////////////////////////////////////////////////

class CGAddQuickSlotToMouseHandler 
{
public:
	static void execute(CGAddQuickSlotToMouse* pPacket, Player* player) ;
};

#endif
