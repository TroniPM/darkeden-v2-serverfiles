//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGPhoneSay.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_PHONE_SAY_H__
#define __CG_PHONE_SAY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGPhoneSay;
//
// Ŭ���̾�Ʈ�� �������� ������ PhoneSay ��Ŷ�̴�.
// ���ο� PhoneSay String ���� ����Ÿ �ʵ�� ������.
//
//////////////////////////////////////////////////////////////////////

class CGPhoneSay : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_PHONE_SAY; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szSlotID + szBYTE + m_Message.size(); }

	// get packet name
	string getPacketName() const throw() { return "CGPhoneSay"; }
	
	// get packet's debug string
	string toString() const throw();

	// get/set SlotID
	SlotID_t getSlotID() const throw() { return m_SlotID; }
	void setSlotID(SlotID_t SlotID) throw() { m_SlotID = SlotID; }

	// get/set chatting message
	string getMessage() const throw() { return m_Message; }
	void setMessage(const string & msg) throw() { m_Message = msg; }
	

private :

	// SlotID
	SlotID_t m_SlotID;
	
	// chatting message
	string m_Message;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGPhoneSayFactory;
//
// Factory for CGPhoneSay
//
//////////////////////////////////////////////////////////////////////

class CGPhoneSayFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CGPhoneSay(); }

	// get packet name
	string getPacketName() const throw() { return "CGPhoneSay"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_PHONE_SAY; }

	// get packet's max body size
	// message �� �ִ� ũ�⿡ ���� ������ �ʿ��ϴ�.
	PacketSize_t getPacketMaxSize() const throw() { return szSlotID + szBYTE + 128; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGPhoneSayHandler;
//
//////////////////////////////////////////////////////////////////////

class CGPhoneSayHandler {

public:

	// execute packet's handler
	static void execute(CGPhoneSay* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
