//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGThrowItem.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_THROW_ITEM_H__
#define __CG_THROW_ITEM_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGThrowItem;
//
//////////////////////////////////////////////////////////////////////

class CGThrowItem : public Packet {

public:
	
	// constructor
	CGThrowItem() ;
	
	// destructor
	~CGThrowItem() ;

	
public:
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_THROW_ITEM; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szObjectID + szObjectID + szCoordInven + szCoordInven; }

	// get packet name
	string getPacketName()  { return "CGThrowItem"; }

	// get/set ItemObjectID
	ObjectID_t getObjectID()   { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	// get / set TargetObjectID
	ObjectID_t getTargetObjectID()   { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t TargetObjectID) throw() { m_TargetObjectID = TargetObjectID; }

	// get/set InvenX
	CoordInven_t getX()  { return m_InvenX; }
	void setX(CoordInven_t InvenX) throw() { m_InvenX = InvenX; }

	// get/set InvenY
	CoordInven_t getY()  { return m_InvenY; }
	void setY(CoordInven_t InvenY) throw() { m_InvenY = InvenY; }

	// get packet's debug string
	string toString() ;

private :

	// Item Object ID
	ObjectID_t m_ObjectID;

	// TargetObjectID
	ObjectID_t m_TargetObjectID;

	// InvenX / Y
	CoordInven_t m_InvenX;
	CoordInven_t m_InvenY;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGThrowItemFactory;
//
// Factory for CGThrowItem
//
//////////////////////////////////////////////////////////////////////

class CGThrowItemFactory : public PacketFactory {

public:
	
	// constructor
	CGThrowItemFactory() throw() {}
	
	// destructor
	virtual ~CGThrowItemFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGThrowItem(); }

	// get packet name
	string getPacketName()  { return "CGThrowItem"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_THROW_ITEM; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szObjectID + szObjectID + szCoordInven + szCoordInven; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGThrowItemHandler;
//
//////////////////////////////////////////////////////////////////////

class CGThrowItemHandler {

public:

	// execute packet's handler
	static void execute(CGThrowItem* pCGThrowItem, Player* pPlayer);

};

#endif
