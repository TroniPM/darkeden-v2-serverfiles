//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGDropMoney.h 
// Written By  : 
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_DROP_MONEY_H__
#define __CG_DROP_MONEY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGDropMoney;
//
//////////////////////////////////////////////////////////////////////

class CGDropMoney : public Packet {
public:

	// constructor
	CGDropMoney() throw();

	// destructor
	~CGDropMoney() throw();

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_DROP_MONEY; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGDropMoneyPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize() const throw() { return szGold; }

	// get packet name
	string getPacketName() const throw() { return "CGDropMoney"; }
	
	// get packet's debug string
	string toString() const throw();
	
public:
	Gold_t getAmount(void) const throw() { return m_Amount;}
	void setAmount(Gold_t amount) throw() { m_Amount = amount;}

private :
	
	Gold_t m_Amount;
};


//////////////////////////////////////////////////////////////////////
//
// class CGDropMoneyFactory;
//
// Factory for CGDropMoney
//
//////////////////////////////////////////////////////////////////////

class CGDropMoneyFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CGDropMoney(); }

	// get packet name
	string getPacketName() const throw() { return "CGDropMoney"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_DROP_MONEY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGDropMoneyPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize() const throw() { return szGold; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGDropMoneyHandler;
//
//////////////////////////////////////////////////////////////////////

class CGDropMoneyHandler {
	
public:

	// execute packet's handler
	static void execute(CGDropMoney* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
