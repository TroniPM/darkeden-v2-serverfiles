//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUsePowerPoint.h 
// Written By  : bezz
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_USE_POWER_POINT_H__
#define __CG_USE_POWER_POINT_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGUsePowerPoint;
//////////////////////////////////////////////////////////////////////////////

class CGUsePowerPoint : public Packet
{
public:
	CGUsePowerPoint ();
	~CGUsePowerPoint ();
	
public:
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
    void write ( SocketOutputStream & oStream ) ;
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );
    PacketID_t getPacketID ()  { return PACKET_CG_USE_POWER_POINT; }
	PacketSize_t getPacketSize ()  { return 0; }
	string getPacketName ()  { return "CGUsePowerPoint"; }
	string toString () ;
};

//////////////////////////////////////////////////////////////////////////////
// class CGUsePowerPointFactory;
//////////////////////////////////////////////////////////////////////////////

class CGUsePowerPointFactory : public PacketFactory 
{
public:
	Packet * createPacket () throw () { return new CGUsePowerPoint(); }
	string getPacketName ()  { return "CGUsePowerPoint"; }
	PacketID_t getPacketID ()  { return Packet::PACKET_CG_USE_POWER_POINT; }
	PacketSize_t getPacketMaxSize ()  { return 0; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGUsePowerPointHandler;
//////////////////////////////////////////////////////////////////////////////

class CGUsePowerPointHandler 
{
public:
	static void execute ( CGUsePowerPoint * pCGUsePowerPoint , Player * pPlayer );
};


#endif

