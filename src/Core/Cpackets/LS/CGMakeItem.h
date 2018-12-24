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
	CGMakeItem() throw();

	// destructor
	~CGMakeItem() throw();

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_MAKE_ITEM; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGMakeItemPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize() const throw() { return szItemClass + szItemType; }

	// get packet name
	string getPacketName() const throw() { return "CGMakeItem"; }
	
	// get packet's debug string
	string toString() const throw();
	
public:
	ItemType_t getItemType() const throw() { return m_ItemType;}
	void setItemType(ItemType_t c) throw() { m_ItemType = c;}

	ItemClass_t getItemClass() const throw() { return m_ItemClass;}
	void setItemClass(ItemClass_t c) throw() { m_ItemClass = c;}

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
	Packet* createPacket() throw() { return new CGMakeItem(); }

	// get packet name
	string getPacketName() const throw() { return "CGMakeItem"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_MAKE_ITEM; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGMakeItemPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize() const throw() { return szItemClass + szItemType; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGMakeItemHandler;
//
//////////////////////////////////////////////////////////////////////

class CGMakeItemHandler {
	
public:

	// execute packet's handler
	static void execute(CGMakeItem* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
