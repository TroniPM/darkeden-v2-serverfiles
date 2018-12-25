////////////////////////////////////////////////////////////////////////////////
// 
// Filename    : CGStashRequestBuy.h 
// Written By  : �輺��
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
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
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
	static void execute(CGStashRequestBuy* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
