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
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_RELOAD_FROM_QUICKSLOT; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGReloadFromQuickSlotPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketSize()  { return szObjectID + szSlotID; }

	// get packet name
	string getPacketName()  { return "CGReloadFromQuickSlot"; }
	
	// get packet's debug string
	string toString() ;
	
public:

	// get / set ObjectID
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	// get / set QuickSlotID
	SlotID_t getSlotID()  { return m_SlotID; }
	void setSlotID(SlotID_t SlotID) throw() { m_SlotID = SlotID; }


private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// QuickSlot의 ID
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
	string getPacketName()  { return "CGReloadFromQuickSlot"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_RELOAD_FROM_QUICKSLOT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGReloadFromQuickSlotPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketMaxSize()  { return szObjectID + szSlotID; }

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
