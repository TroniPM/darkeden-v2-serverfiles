////////////////////////////////////////////////////////////////////////////////
// Filename    : CGStashDeposit.h 
// Written By  : ±è¼º¹Î
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_STASH_DEPOSIT_H__
#define __CG_STASH_DEPOSIT_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class CGStashDeposit;
//
////////////////////////////////////////////////////////////////////////////////

class CGStashDeposit : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_CG_STASH_DEPOSIT; }
	PacketSize_t getPacketSize()  { return szGold; }
	string getPacketName()  { return "CGStashDeposit"; }
	string toString() ;
	
public:
	Gold_t getAmount(void)  { return m_Amount;}
	void setAmount(Gold_t amount) throw() { m_Amount = amount;}

private :
	Gold_t m_Amount;
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGStashDepositFactory;
//
////////////////////////////////////////////////////////////////////////////////

class CGStashDepositFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGStashDeposit(); }
	string getPacketName()  { return "CGStashDeposit"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_STASH_DEPOSIT; }
	PacketSize_t getPacketMaxSize()  { return szGold; }

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGStashDepositHandler;
//
////////////////////////////////////////////////////////////////////////////////

class CGStashDepositHandler {
	
public:

	// execute packet's handler
	static void execute(CGStashDeposit* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
