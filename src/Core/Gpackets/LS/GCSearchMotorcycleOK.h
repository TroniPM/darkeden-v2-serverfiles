//--------------------------------------------------------------------------------
// 
// Filename    : GCSearchMotorcycleOK.h 
// Written By  : �輺��
// Description : �÷��̾�� ���� ���� ���� ������ �˷��� �� ���̴� ��Ŷ�̴�.
// 
//--------------------------------------------------------------------------------

#ifndef __GC_SEARCH_MOTORCYCLE_OK_H__
#define __GC_SEARCH_MOTORCYCLE_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//--------------------------------------------------------------------------------
//
// class GCSearchMotorcycleOK;
//
//--------------------------------------------------------------------------------

class GCSearchMotorcycleOK : public Packet 
{
public :
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_SEARCH_MOTORCYCLE_OK; }
	PacketSize_t getPacketSize()  { return szZoneID+szCoord*2; }
	string getPacketName()  { return "GCSearchMotorcycleOK"; }
	string toString() ;

public :
	ZoneID_t getZoneID(void)   { return m_ZoneID;}
	Coord_t  getX(void)        { return m_ZoneX;}
	Coord_t  getY(void)        { return m_ZoneY;}
	void     setZoneID(ZoneID_t id)  { m_ZoneID = id;}
	void     setX(Coord_t x)         { m_ZoneX = x;}
	void     setY(Coord_t y)         { m_ZoneY = y;}

private :
	ZoneID_t m_ZoneID;
	Coord_t  m_ZoneX;
	Coord_t  m_ZoneY;

};


//////////////////////////////////////////////////////////////////////
//
// class GCSearchMotorcycleOKFactory;
//
// Factory for GCSearchMotorcycleOK
//
//////////////////////////////////////////////////////////////////////

class GCSearchMotorcycleOKFactory : public PacketFactory 
{

public :
	
	// create packet
	Packet* createPacket()  { return new GCSearchMotorcycleOK(); }

	// get packet name
	string getPacketName()  { return "GCSearchMotorcycleOK"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SEARCH_MOTORCYCLE_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSearchMotorcycleOKPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  { return szZoneID + szCoord*2; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCSearchMotorcycleOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GCSearchMotorcycleOKHandler 
{
	
public :
	
	// execute packet's handler
	static void execute(GCSearchMotorcycleOK* pPacket, Player* pPlayer) ;

};

#endif
