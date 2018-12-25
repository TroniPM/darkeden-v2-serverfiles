//////////////////////////////////////////////////////////////////////////////
// Filename    : CGResurrect.h 
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_RESURRECT_H__
#define __CG_RESURRECT_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGResurrect;
//////////////////////////////////////////////////////////////////////////////

class CGResurrect : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_CG_RESURRECT; }
	PacketSize_t getPacketSize()  { return 0; }
	string getPacketName()  { return "CGResurrect"; }
	string toString() ;
};

//////////////////////////////////////////////////////////////////////////////
// class CGResurrectFactory;
//////////////////////////////////////////////////////////////////////////////

class CGResurrectFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGResurrect(); }
	string getPacketName()  { return "CGResurrect"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_RESURRECT; }
	PacketSize_t getPacketMaxSize()  { return 0; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGResurrectHandler;
//////////////////////////////////////////////////////////////////////////////

class CGResurrectHandler 
{
public:
	static void execute(CGResurrect* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
