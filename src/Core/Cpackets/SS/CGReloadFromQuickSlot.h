//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGReloadFromQuickSlot.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_RELOAD_FROM_QUICKSLOT_H__
#define __CG_RELOAD_FROM_QUICKSLOT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGReloadFromQuickSlot;
//
//////////////////////////////////////////////////////////////////////

class CGReloadFromQuickSlot : public Packet {
public:

	// constructor
	CGReloadFromQuickSlot() throw();

	// destructor
	~CGReloadFromQuickSlot() throw();

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_RELOAD_FROM_QUICKSLOT; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGReloadFromQuickSlotPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize() const throw() { return szObjectID + szSlotID; }

	// get packet name
	string getPacketName() const throw() { return "CGReloadFromQuickSlot"; }
	
	// get packet's debug string
	string toString() const throw();
	
public:

	// get / set ObjectID
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	// get / set QuickSlotID
	SlotID_t getSlotID() const throw() { return m_SlotID; }
	void setSlotID(SlotID_t SlotID) throw() { m_SlotID = SlotID; }


private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// QuickSlot�� ID
	SlotID_t m_SlotID;

};


//////////////////////////////////////////////////////////////////////
//
// class CGReloadFromQuickSlotFactory;
//
// Factory for CGReloadFromQuickSlot
//
//////////////////////////////////////////////////////////////////////

class CGReloadFromQuickSlotFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CGReloadFromQuickSlot(); }

	// get packet name
	string getPacketName() const throw() { return "CGReloadFromQuickSlot"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_RELOAD_FROM_QUICKSLOT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGReloadFromQuickSlotPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szSlotID; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGReloadFromQuickSlotHandler;
//
//////////////////////////////////////////////////////////////////////

class CGReloadFromQuickSlotHandler {
	
public:

	// execute packet's handler
	static void execute(CGReloadFromQuickSlot* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
