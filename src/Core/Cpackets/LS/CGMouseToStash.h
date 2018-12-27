////////////////////////////////////////////////////////////////////////////////
// Filename    : CGMouseToStash.h 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_MOUSE_TO_STASH_H__
#define __CG_MOUSE_TO_STASH_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class CGMouseToStash
//
////////////////////////////////////////////////////////////////////////////////

class CGMouseToStash : public Packet 
{
public:
    void         read(SocketInputStream & iStream) ;
    void         write(SocketOutputStream & oStream) ;
	void         execute(Player* pPlayer) ;
	PacketID_t   getPacketID()  { return PACKET_CG_MOUSE_TO_STASH; }
	PacketSize_t getPacketSize()  { return szObjectID + szBYTE*2; }
	string       getPacketName()  { return "CGMouseToStash"; }
	string       toString() ;
	
public:
	ObjectID_t getObjectID(void)  { return m_ObjectID; }
	void       setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }
	BYTE       getRack(void)  { return m_Rack;}
	void       setRack(BYTE rack)  { m_Rack = rack;}
	BYTE       getIndex(void)  { return m_Index;}
	void       setIndex(BYTE index)  { m_Index = index;}

private:
	ObjectID_t m_ObjectID;
	BYTE       m_Rack;
	BYTE       m_Index;

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGMouseToStashFactory;
//
////////////////////////////////////////////////////////////////////////////////

class CGMouseToStashFactory : public PacketFactory 
{
public:
	Packet*      createPacket()  { return new CGMouseToStash(); }
	string       getPacketName()  { return "CGMouseToStash"; }
	PacketID_t   getPacketID()  { return Packet::PACKET_CG_MOUSE_TO_STASH; }
	PacketSize_t getPacketMaxSize()  { return szObjectID+szBYTE*2; }

};

////////////////////////////////////////////////////////////////////////////////
//
// class CGMouseToStashHandler;
//
////////////////////////////////////////////////////////////////////////////////

class CGMouseToStashHandler 
{
public:
	static void execute(CGMouseToStash* pPacket, Player* player) ;
	//static void executeSlayer(CGMouseToStash* pPacket, Player* player) ;
	//static void executeVampire(CGMouseToStash* pPacket, Player* player) ;
};


#endif
