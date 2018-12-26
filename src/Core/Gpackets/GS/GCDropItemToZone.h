//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCDropItemToZone.h 
// Written By  : elca
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_DROP_ITEM_TO_ZONE_H__
#define __GC_DROP_ITEM_TO_ZONE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "SubItemInfo.h"
#include "GCAddItemToZone.h"


//////////////////////////////////////////////////////////////////////
//
// class GCDropItemToZone;
//
////////////////////////////////////////////////////////////////////

class GCDropItemToZone : public GCAddItemToZone {

public :

	GCDropItemToZone() ;
	~GCDropItemToZone() ;
	
	PacketSize_t getPacketSize()  { return GCAddItemToZone::getPacketSize() + szObjectID; }

    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_DROP_ITEM_TO_ZONE; }
	
	// get packet's name
	string getPacketName()  { return "GCDropItemToZone"; }

	// get packet's debug string
	string toString() ;

public:
	ObjectID_t getDropPetOID() const { return m_DropPetOID; }
	void setDropPetOID( ObjectID_t PetOID ) { m_DropPetOID = PetOID; }

private:
	ObjectID_t	m_DropPetOID;
};


//////////////////////////////////////////////////////////////////////
//
// class GCDropItemToZoneFactory;
//
// Factory for GCDropItemToZone
//
//////////////////////////////////////////////////////////////////////

class GCDropItemToZoneFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCDropItemToZone(); }

	// get packet name
	string getPacketName()  { return "GCDropItemToZone"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_DROP_ITEM_TO_ZONE; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCDropItemToZonePacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize()  { return szObjectID + szCoord + szCoord + szBYTE + szItemType + szBYTE + 255 + szBYTE + 255  + szDurability + szItemNum + szBYTE +(szObjectID + szBYTE + szItemType + szItemNum + szSlotID)* 12 + szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCDropItemToZoneHandler;
//
//////////////////////////////////////////////////////////////////////

class GCDropItemToZoneHandler {

public :

	// execute packet's handler
	static void execute(GCDropItemToZone* pPacket, Player* pPlayer);

};

#endif
