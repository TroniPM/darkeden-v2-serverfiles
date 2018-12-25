//--------------------------------------------------------------------------------
// 
// Filename    : GCDeleteInventoryItem.h 
// Written By  : Reiot
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __GC_DELETE_INVENTORY_ITEM_H__
#define __GC_DELETE_INVENTORY_ITEM_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class GCDeleteInventoryItem;
//
//--------------------------------------------------------------------------------

class GCDeleteInventoryItem : public Packet {

public :

	// constructor
	GCDeleteInventoryItem() throw()
	{
	}

	GCDeleteInventoryItem(ObjectID_t objectID) throw()
		: m_ObjectID(objectID)
	{
	}


public :
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_DELETE_INVENTORY_ITEM; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  
	{ 
		return szObjectID; 
	}

	// get packet name
	string getPacketName()  { return "GCDeleteInventoryItem"; }
	
	// get packet's debug string
	string toString() ;

public :

	// get/set object id
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t objectID) throw() { m_ObjectID = objectID; }

private :

	// object id
	ObjectID_t m_ObjectID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCDeleteInventoryItemFactory;
//
// Factory for GCDeleteInventoryItem
//
//////////////////////////////////////////////////////////////////////

class GCDeleteInventoryItemFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCDeleteInventoryItem(); }

	// get packet name
	string getPacketName()  { return "GCDeleteInventoryItem"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_DELETE_INVENTORY_ITEM; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize()  
	{ 
		return szObjectID; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCDeleteInventoryItemHandler;
//
//////////////////////////////////////////////////////////////////////

class GCDeleteInventoryItemHandler {

public :

	// execute packet's handler
	static void execute(GCDeleteInventoryItem* pPacket, Player* player) throw(ProtocolException, Error);

};

#endif
