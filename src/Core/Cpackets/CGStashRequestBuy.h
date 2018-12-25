////////////////////////////////////////////////////////////////////////////////
// 
// Filename    : CGStashRequestBuy.h 
// Written By  : ±è¼º¹Î
// Description : 
// 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_STASH_REQUEST_BUY_H__
#define __CG_STASH_REQUEST_BUY_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class CGStashRequestBuy;
//
////////////////////////////////////////////////////////////////////////////////

class CGStashRequestBuy : public Packet 
{
public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_CG_STASH_REQUEST_BUY; }
	PacketSize_t getPacketSize()  { return 0; }
	string getPacketName()  { return "CGStashRequestBuy"; }
	string toString() ;
	
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGStashRequestBuyFactory;
//
// Factory for CGStashRequestBuy
//
////////////////////////////////////////////////////////////////////////////////

class CGStashRequestBuyFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGStashRequestBuy(); }
	string getPacketName()  { return "CGStashRequestBuy"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_STASH_REQUEST_BUY; }
	PacketSize_t getPacketMaxSize()  { return 0; }

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGStashRequestBuyHandler;
//
////////////////////////////////////////////////////////////////////////////////

class CGStashRequestBuyHandler 
{
public:
	static void execute(CGStashRequestBuy* pPacket, Player* player) ;
};

#endif
