//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGUndisplayItem.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_UNDISPLAY_ITEM_H__
#define __CG_UNDISPLAY_ITEM_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGUndisplayItem;
//
//////////////////////////////////////////////////////////////////////

class CGUndisplayItem : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_UNDISPLAY_ITEM; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szCoordInven + szCoordInven + szObjectID + szBYTE; }

	// get packet name
	string getPacketName()  { return "CGUndisplayItem"; }

	// get packet's debug string
	string toString() ;

	CoordInven_t	getX() const { return m_X; }
	CoordInven_t	getY() const { return m_Y; }
	void			setXY(CoordInven_t x, CoordInven_t y) { m_X = x; m_Y = y; }

	ObjectID_t		getItemObjectID() const { return m_ItemObjectID; }
	void			setItemObjectID(ObjectID_t oid) { m_ItemObjectID = oid; }

	BYTE			getIndex() const { return m_Index; }
	void			setIndex(BYTE index) { m_Index = index; }

private :
	CoordInven_t	m_X, m_Y;
	ObjectID_t		m_ItemObjectID;
	BYTE			m_Index;
};


//////////////////////////////////////////////////////////////////////
//
// class CGUndisplayItemFactory;
//
// Factory for CGUndisplayItem
//
//////////////////////////////////////////////////////////////////////

class CGUndisplayItemFactory : public PacketFactory {

public:
	
	// constructor
	CGUndisplayItemFactory() throw() {}
	
	// destructor
	virtual ~CGUndisplayItemFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGUndisplayItem(); }

	// get packet name
	string getPacketName()  { return "CGUndisplayItem"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_UNDISPLAY_ITEM; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szCoordInven + szCoordInven + szObjectID + szBYTE; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGUndisplayItemHandler;
//
//////////////////////////////////////////////////////////////////////

class CGUndisplayItemHandler {

public:

	// execute packet's handler
	static void execute(CGUndisplayItem* pCGUndisplayItem, Player* pPlayer) throw(Error);

};

#endif
