//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCModifyMoney.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_MODIFY_MONEY_H__
#define __GC_MODIFY_MONEY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCModifyMoney;
//
// Ŭ���̾�Ʈ�� ��� ��� â�� ��쵵�� �Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCModifyMoney : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_MODIFY_MONEY; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szGold; }

	// get packet name
	string getPacketName()  { return "GCModifyMoney"; }
	
	// get packet's debug string
	string toString() ;

	// get/set amount
	Gold_t getAmount()  { return m_Amount; }
	void setAmount( Gold_t amount ) throw() { m_Amount = amount; }
	

private :
	
	// Amount
	Gold_t m_Amount;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCModifyMoneyFactory;
//
// Factory for GCModifyMoney
//
//////////////////////////////////////////////////////////////////////

class GCModifyMoneyFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCModifyMoney(); }

	// get packet name
	string getPacketName()  { return "GCModifyMoney"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_MODIFY_MONEY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  { return szGold; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCModifyMoney;
//
//////////////////////////////////////////////////////////////////////

class GCModifyMoneyHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCModifyMoney* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
