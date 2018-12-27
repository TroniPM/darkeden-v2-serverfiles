//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGDisplayItem.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_DISPLAY_ITEM_H__
#define __CG_DISPLAY_ITEM_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGDisplayItem;
//
//////////////////////////////////////////////////////////////////////

class CGDisplayItem : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_DISPLAY_ITEM; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szCoordInven + szCoordInven + szObjectID + szGold + szBYTE; }

	// get packet name
	string getPacketName()  { return "CGDisplayItem"; }

	// get packet's debug string
	string toString() ;

	CoordInven_t	getX() const { return m_X; }
	CoordInven_t	getY() const { return m_Y; }
	void			setXY(CoordInven_t x, CoordInven_t y) { m_X = x; m_Y = y; }

	ObjectID_t		getItemObjectID() const { return m_ItemObjectID; }
	void			setItemObjectID(ObjectID_t oid) { m_ItemObjectID = oid; }

	Gold_t			getPrice() const { return m_Price; }
	void			setPrice(Gold_t price) { m_Price = price; }

	BYTE			getIndex() const { return m_Index; }
	void			setIndex(BYTE index) { m_Index = index; }
private :

	CoordInven_t	m_X, m_Y;
	ObjectID_t		m_ItemObjectID;
	Gold_t			m_Price;
	BYTE			m_Index;
};


//////////////////////////////////////////////////////////////////////
//
// class CGDisplayItemFactory;
//
// Factory for CGDisplayItem
//
//////////////////////////////////////////////////////////////////////

class CGDisplayItemFactory : public PacketFactory {

public:
	
	// constructor
	CGDisplayItemFactory()  {}
	
	// destructor
	virtual ~CGDisplayItemFactory()  {}

	
public:
	
	// create packet
	Packet* createPacket()  { return new CGDisplayItem(); }

	// get packet name
	string getPacketName()  { return "CGDisplayItem"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_DISPLAY_ITEM; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szCoordInven + szCoordInven + szObjectID + szGold + szBYTE; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGDisplayItemHandler;
//
//////////////////////////////////////////////////////////////////////

class CGDisplayItemHandler {

public:

	// execute packet's handler
	static void execute(CGDisplayItem* pCGDisplayItem, Player* pPlayer);

};

#endif
