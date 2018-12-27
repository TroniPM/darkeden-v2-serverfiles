
//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPetGamble.h 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_PET_GAMBLE_H__
#define __CG_PET_GAMBLE_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGPetGamble;
//////////////////////////////////////////////////////////////////////////////

class CGPetGamble : public Packet 
{
public:
	CGPetGamble() ;
	~CGPetGamble() ;

public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_CG_PET_GAMBLE; }
	PacketSize_t getPacketSize()  { return 0; }
	string getPacketName()  { return "CGPetGamble"; }
	string toString() ;
	
public:
private :
};

//////////////////////////////////////////////////////////////////////////////
// class CGPetGambleFactory;
//////////////////////////////////////////////////////////////////////////////

class CGPetGambleFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGPetGamble(); }
	string getPacketName()  { return "CGPetGamble"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_PET_GAMBLE; }
	PacketSize_t getPacketMaxSize()  { return 0; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGPetGambleHandler;
//////////////////////////////////////////////////////////////////////////////

class CGPetGambleHandler 
{
public:
	static void execute(CGPetGamble* pPacket, Player* player) ;
};

#endif
