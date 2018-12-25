////////////////////////////////////////////////////////////////////////////////
// 
// Filename    : GCStashSell.h 
// Written By  : ±è¼º¹Î
// Description : 
// 
////////////////////////////////////////////////////////////////////////////////

#ifndef __GC_STASH_SELL_H__
#define __GC_STASH_SELL_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class GCStashSell;
//
////////////////////////////////////////////////////////////////////////////////

class GCStashSell : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_GC_STASH_SELL; }
	PacketSize_t getPacketSize()  { return szGold; }
	string getPacketName()  { return "GCStashSell"; }
	string toString() ;

public:
	Gold_t getPrice(void)  { return m_Price; }
	void  setPrice(Gold_t price) throw() { m_Price = price; }

private:
	Gold_t m_Price;

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCStashSellFactory;
//
////////////////////////////////////////////////////////////////////////////////

class GCStashSellFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCStashSell(); }
	string getPacketName()  { return "GCStashSell"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_STASH_SELL; }
	PacketSize_t getPacketMaxSize()  { return szGold; }
};


////////////////////////////////////////////////////////////////////////////////
//
// class GCStashSellHandler;
//
////////////////////////////////////////////////////////////////////////////////

class GCStashSellHandler 
{
public:
	static void execute(GCStashSell* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
