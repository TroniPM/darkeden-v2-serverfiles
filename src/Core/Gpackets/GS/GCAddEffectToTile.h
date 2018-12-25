//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddEffectToTile.h 
// Written By  : elca@ewestsoft.com
// Description :
// ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_EFFECT_TO_TILE_H__
#define __GC_ADD_EFFECT_TO_TILE_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddEffectToTile;
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//////////////////////////////////////////////////////////////////////////////

class GCAddEffectToTile : public Packet 
{
public:
	GCAddEffectToTile() throw();
	~GCAddEffectToTile() throw();
	
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_GC_ADD_EFFECT_TO_TILE; }
	PacketSize_t getPacketSize()  { return szObjectID + szCoord*2 + szEffectID + szTurn; }
	string getPacketName()  { return "GCAddEffectToTile"; }
	string toString() ;

public:
	EffectID_t getEffectID()  { return m_EffectID; }
	void setEffectID(EffectID_t e) throw() { m_EffectID = e; }

	Turn_t getDuration()  { return m_Duration; }
	void setDuration(Turn_t d) throw() { m_Duration = d; }

	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t d) throw() { m_ObjectID = d; }

	Coord_t getX()  { return m_X;}
	Coord_t getY()  { return m_Y;}
	void setXY(Coord_t x, Coord_t y) throw() { m_X = x; m_Y = y;}
	
private:
	Coord_t     m_X;
	Coord_t     m_Y;
	ObjectID_t  m_ObjectID;
	EffectID_t	m_EffectID;
	Turn_t	m_Duration;
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddEffectToTileFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddEffectToTileFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCAddEffectToTile(); }
	string getPacketName()  { return "GCAddEffectToTile"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_ADD_EFFECT_TO_TILE; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + szCoord*2 + szEffectID + szTurn; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddEffectToTileHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddEffectToTileHandler 
{
public:
	static void execute(GCAddEffectToTile* pGCAddEffectToTile, Player* pPlayer) throw(Error);
};

#endif
