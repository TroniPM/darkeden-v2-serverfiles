//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCDeleteEffectFromTile.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_DELETE_EFFECT_FROM_TILE_H__
#define __GC_DELETE_EFFECT_FROM_TILE_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCDeleteEffectFromTile;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCDeleteEffectFromTile : public Packet {

public :
	
	// constructor
	GCDeleteEffectFromTile() throw();
	
	// destructor
	~GCDeleteEffectFromTile() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_DELETE_EFFECT_FROM_TILE; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize()  { return szObjectID + szCoord*2 + szEffectID; }

	// get packet's name
	string getPacketName()  { return "GCDeleteEffectFromTile"; }
	
	// get packet's debug string
	string toString() ;

	// get / set EffectID 
	EffectID_t getEffectID()  { return m_EffectID; }
	void setEffectID(EffectID_t e) throw() { m_EffectID = e; }
	

	// get / set ObjectID 
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t d) throw() { m_ObjectID = d; }

	// get & set X, Y
	Coord_t getX()  { return m_X;}
	Coord_t getY()  { return m_Y;}
	void setXY(Coord_t x, Coord_t y) throw() { m_X = x; m_Y = y;}
	
private :
	
	Coord_t  m_X, m_Y;
	ObjectID_t m_ObjectID;

	EffectID_t	m_EffectID;
};


//////////////////////////////////////////////////////////////////////
//
// class GCDeleteEffectFromTileFactory;
//
// Factory for GCDeleteEffectFromTile
//
//////////////////////////////////////////////////////////////////////

class GCDeleteEffectFromTileFactory : public PacketFactory {

public :
	
	// constructor
	GCDeleteEffectFromTileFactory() throw() {}
	
	// destructor
	virtual ~GCDeleteEffectFromTileFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCDeleteEffectFromTile(); }

	// get packet name
	string getPacketName()  { return "GCDeleteEffectFromTile"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_DELETE_EFFECT_FROM_TILE; }

	// get Packet Max Size
	// PacketSize_t getPacketMaxSize()  { return szSkillType + szCEffectID + szDuration + szBYTE + szBYTE* m_ListNum* 2 ; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + szCoord*2 + szEffectID ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCDeleteEffectFromTileHandler;
//
//////////////////////////////////////////////////////////////////////

class GCDeleteEffectFromTileHandler {

public :

	// execute packet's handler
	static void execute(GCDeleteEffectFromTile* pGCDeleteEffectFromTile, Player* pPlayer) throw(Error);

};

#endif
