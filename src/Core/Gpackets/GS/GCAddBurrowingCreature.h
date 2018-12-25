//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddBurrowingCreature.h 
// Written By  : crazydog 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_BURROWING_CREATURE_H__
#define __GC_ADD_BURROWING_CREATURE_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddBurrowingCreature;
// 시야 안에 BurrowingCreature 가 들어왔을 경우, 
// 이 패킷에 BurrowingCreature 정보를 담아서 전송받는다.
//////////////////////////////////////////////////////////////////////////////

class GCAddBurrowingCreature : public Packet 
{
public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_ADD_BURROWING_CREATURE; }
	PacketSize_t getPacketSize()  
	{ 
		return szObjectID + szBYTE + m_Name.size() + szCoord + szCoord; 
	}
	string getPacketName()  { return "GCAddBurrowingCreature"; }
	string toString() ;

public:
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID) throw() { m_ObjectID = creatureID; }

	string getName()  { return m_Name; }
	void setName(string name) throw() { m_Name = name; }

	Coord_t getX()  { return m_X; }
	void setX(Coord_t x) throw() { m_X = x; }
	
	Coord_t getY()  { return m_Y; }
	void setY(Coord_t y) throw() { m_Y = y; }

private:
    ObjectID_t m_ObjectID;
    string     m_Name;
   	Coord_t    m_X;
	Coord_t    m_Y;
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddBurrowingCreatureFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddBurrowingCreatureFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCAddBurrowingCreature(); }
	string getPacketName()  { return "GCAddBurrowingCreature"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_ADD_BURROWING_CREATURE; }
	PacketSize_t getPacketMaxSize()  
	{
		return szObjectID + szBYTE + 20 + szCoord + szCoord; 
	}
};

//////////////////////////////////////////////////////////////////////////////
//
// class GCAddBurrowingCreatureHandler;
//
//////////////////////////////////////////////////////////////////////////////

class GCAddBurrowingCreatureHandler 
{
public:
	static void execute(GCAddBurrowingCreature* pPacket, Player* pPlayer);
};

#endif
