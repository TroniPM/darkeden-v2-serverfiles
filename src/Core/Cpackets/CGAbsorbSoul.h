//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGAbsorbSoul 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_ABSORB_SOUL_H__
#define __CG_ABSORB_SOUL_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGAbsorbSoul;
//
//////////////////////////////////////////////////////////////////////

class CGAbsorbSoul : public Packet {

public:
	
	// constructor
	CGAbsorbSoul() throw();
	
	// destructor
	~CGAbsorbSoul() throw();

	
public:
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_ABSORB_SOUL; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szObjectID + szZoneCoord + szZoneCoord + szObjectID + szCoordInven + szCoordInven + szCoordInven + szCoordInven; }

	// get packet name
	string getPacketName()  { return "CGAbsorbSoul"; }
	
	// get packet's debug string
	string toString() ;

	// get/set ObjectID
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }
	
	ZoneCoord_t getTargetZoneX()  { return m_TargetZoneX; }
	void setTargetZoneX( ZoneCoord_t x ) throw() { m_TargetZoneX = x; }

	ZoneCoord_t getTargetZoneY()  { return m_TargetZoneY; }
	void setTargetZoneY( ZoneCoord_t y ) throw() { m_TargetZoneY = y; }

	ObjectID_t getInvenObjectID()  { return m_InvenObjectID; }
	void setInvenObjectID(ObjectID_t invenObjectID) throw() { m_InvenObjectID = invenObjectID; }

	Coord_t getInvenX()  { return m_InvenX; }
	void setInvenX( CoordInven_t x ) throw() { m_InvenX = x; }

	Coord_t getInvenY()  { return m_InvenY; }
	void setInvenY( CoordInven_t y ) throw() { m_InvenY = y; }

	Coord_t getTargetInvenX()  { return m_TargetInvenX; }
	void setTargetInvenX( CoordInven_t x ) throw() { m_TargetInvenX = x; }

	Coord_t getTargetInvenY()  { return m_TargetInvenY; }
	void setTargetInvenY( CoordInven_t y ) throw() { m_TargetInvenY = y; }

private :
	
	ObjectID_t m_ObjectID;  // ObjectID

	ZoneCoord_t	m_TargetZoneX;
	ZoneCoord_t	m_TargetZoneY;
	
	ObjectID_t m_InvenObjectID; // ����� ObjectID
	CoordInven_t m_InvenX;			// X ��ǥ
	CoordInven_t m_InvenY;			// Y ��ǥ
	CoordInven_t m_TargetInvenX;	// Target X ��ǥ
	CoordInven_t m_TargetInvenY;	// Target Y ��ǥ
};


//////////////////////////////////////////////////////////////////////
//
// class CGAbsorbSoulFactory;
//
// Factory for CGAbsorbSoul
//
//////////////////////////////////////////////////////////////////////

class CGAbsorbSoulFactory : public PacketFactory {

public:
	
	// constructor
	CGAbsorbSoulFactory() throw() {}
	
	// destructor
	virtual ~CGAbsorbSoulFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGAbsorbSoul(); }

	// get packet name
	string getPacketName()  { return "CGAbsorbSoul"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_ABSORB_SOUL; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szObjectID + szZoneCoord + szZoneCoord + szObjectID + szCoordInven + szCoordInven + szCoordInven + szCoordInven; }

};

//////////////////////////////////////////////////////////////////////
//
// class CGAbsorbSoulHandler;
//
//////////////////////////////////////////////////////////////////////

class CGAbsorbSoulHandler {
	
public:

	// execute packet's handler
	static void execute(CGAbsorbSoul* pCGAbsorbSoul, Player* player) throw(Error);
};

#endif
