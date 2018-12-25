//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddItemToCodeSheet.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_ADD_ITEM_TO_CODE_SHEET_H__
#define __CG_ADD_ITEM_TO_CODE_SHEET_H__

#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////////////
// class CGAddItemToCodeSheet;
//////////////////////////////////////////////////////////////////////////////

class CGAddItemToCodeSheet : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_CG_ADD_ITEM_TO_CODE_SHEET; }
	PacketSize_t getPacketSize()  { return szObjectID + szCoordInven + szCoordInven; }
	string getPacketName()  { return "CGAddItemToCodeSheet"; }
	string toString() ;

public:
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	CoordInven_t getX()  { return m_X; }
	void setX(Coord_t X) throw() { m_X = X; }

	CoordInven_t getY()  { return m_Y; }
	void setY(Coord_t Y) throw() { m_Y = Y; }

private :
	ObjectID_t   m_ObjectID;	// ObjectID
	CoordInven_t m_X;			// Coord X
	CoordInven_t m_Y;			// Coord Y
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddItemToCodeSheetFactory;
//////////////////////////////////////////////////////////////////////////////

class CGAddItemToCodeSheetFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGAddItemToCodeSheet(); }
	string getPacketName()  { return "CGAddItemToCodeSheet"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_ADD_ITEM_TO_CODE_SHEET; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + szCoordInven + szCoordInven; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddItemToCodeSheetHandler;
//////////////////////////////////////////////////////////////////////////////

class CGAddItemToCodeSheetHandler 
{
public:
	static void execute(CGAddItemToCodeSheet* pCGAddItemToCodeSheet, Player* pPlayer) throw(Error);

};

#endif
