////////////////////////////////////////////////////////////////////////////////
// 
// Filename    : GCStashSell.h 
// Written By  : �輺��
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
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_STASH_SELL; }
	PacketSize_t getPacketSize()  { return szGold; }
	string getPacketName()  { return "GCStashSell"; }
	string toString() ;

public:
	Gold_t getPrice(void)  { return m_Price; }
	void  setPrice(Gold_t price)  { m_Price = price; }

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
	Packet* createPacket()  { return new GCStashSell(); }
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
	static void execute(GCStashSell* pPacket, Player* pPlayer) ;

};

#endif
