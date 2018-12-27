//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGDialUp.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_DIAL_UP_H__
#define __CG_DIAL_UP_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGDialUp;
//
//////////////////////////////////////////////////////////////////////

class CGDialUp : public Packet {
public:

	// constructor
	CGDialUp() ;

	// destructor
	~CGDialUp() ;

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_DIAL_UP; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGDialUpPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize()  { return szPhoneNumber; }

	// get packet name
	string getPacketName()  { return "CGDialUp"; }
	
	// get packet's debug string
	string toString() ;
	
public:

	// get / set phoneNumber
	PhoneNumber_t getPhoneNumber()  { return m_PhoneNumber; }
	void setPhoneNumber(PhoneNumber_t PhoneNumber)  { m_PhoneNumber = PhoneNumber; }

private :
	
	// SlotID
	PhoneNumber_t m_PhoneNumber;

};


//////////////////////////////////////////////////////////////////////
//
// class CGDialUpFactory;
//
// Factory for CGDialUp
//
//////////////////////////////////////////////////////////////////////

class CGDialUpFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CGDialUp(); }

	// get packet name
	string getPacketName()  { return "CGDialUp"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_DIAL_UP; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGDialUpPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize()  { return szPhoneNumber; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGDialUpHandler;
//
//////////////////////////////////////////////////////////////////////

class CGDialUpHandler {
	
public:

	// execute packet's handler
	static void execute(CGDialUp* pPacket, Player* player) ;
};

#endif
