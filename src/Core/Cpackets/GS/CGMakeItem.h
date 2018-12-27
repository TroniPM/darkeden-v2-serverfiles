//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGMakeItem.h 
// Written By  : 
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_MAKE_ITEM_H__
#define __CG_MAKE_ITEM_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGMakeItem;
//
//////////////////////////////////////////////////////////////////////

class CGMakeItem : public Packet {
public:

	// constructor
	CGMakeItem() ;

	// destructor
	~CGMakeItem() ;

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_MAKE_ITEM; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGMakeItemPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize()  { return szItemClass + szItemType; }

	// get packet name
	string getPacketName()  { return "CGMakeItem"; }
	
	// get packet's debug string
	string toString() ;
	
public:
	ItemType_t getItemType()  { return m_ItemType;}
	void setItemType(ItemType_t c)  { m_ItemType = c;}

	ItemClass_t getItemClass()  { return m_ItemClass;}
	void setItemClass(ItemClass_t c)  { m_ItemClass = c;}

private :

	ItemClass_t m_ItemClass;
	ItemType_t m_ItemType;	
};


//////////////////////////////////////////////////////////////////////
//
// class CGMakeItemFactory;
//
// Factory for CGMakeItem
//
//////////////////////////////////////////////////////////////////////

class CGMakeItemFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CGMakeItem(); }

	// get packet name
	string getPacketName()  { return "CGMakeItem"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_MAKE_ITEM; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGMakeItemPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize()  { return szItemClass + szItemType; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGMakeItemHandler;
//
//////////////////////////////////////////////////////////////////////

class CGMakeItemHandler {
	
public:

	// execute packet's handler
	static void execute(CGMakeItem* pPacket, Player* player) ;
};

#endif
