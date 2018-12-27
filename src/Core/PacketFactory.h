//////////////////////////////////////////////////////////////////////
// 
// Filename    : PacketFactory.h 
// Written By  : reiot@ewestsoft.com
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __PACKET_FACTORY_H__
#define __PACKET_FACTORY_H__

// include files
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class PacketFactory
//
//////////////////////////////////////////////////////////////////////

class PacketFactory {

public :
	
	// destructor
	virtual ~PacketFactory ()  {}

	// create packet
	virtual Packet* createPacket ()  = 0;

	// get packet name
	virtual string getPacketName ()  = 0;
	
	// get packet id
	virtual PacketID_t getPacketID ()  = 0;

	// get packet's max body size
	virtual PacketSize_t getPacketMaxSize ()  = 0;

};

#endif
