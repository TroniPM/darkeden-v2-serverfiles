//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCPhoneDisconnected.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_PHONE_DISCONNECTED_H__
#define __GC_PHONE_DISCONNECTED_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCPhoneDisconnected;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�.(CreatureID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCPhoneDisconnected : public Packet {

public :
	
	// constructor
	GCPhoneDisconnected() throw();
	
	// destructor
	~GCPhoneDisconnected() throw();

	
public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_PHONE_DISCONNECTED; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize() const throw() { return szPhoneNumber + szSlotID; }

	// get packet's name
	string getPacketName() const throw() { return "GCPhoneDisconnected"; }
	
	// get packet's debug string
	string toString() const throw();

	// get/set PhoneNumber
	PhoneNumber_t getPhoneNumber() const throw() { return m_PhoneNumber; }
	void setPhoneNumber(PhoneNumber_t PhoneNumber) throw() { m_PhoneNumber = PhoneNumber; }

	// get/set SlotID
	SlotID_t getSlotID() const throw() { return m_SlotID; }
	void setSlotID(SlotID_t SlotID) throw() { m_SlotID = SlotID; }

private :

	// PhoneNumber
	PhoneNumber_t m_PhoneNumber;

	// SlotID
	SlotID_t m_SlotID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCPhoneDisconnectedFactory;
//
// Factory for GCPhoneDisconnected
//
//////////////////////////////////////////////////////////////////////

class GCPhoneDisconnectedFactory : public PacketFactory {

public :
	
	// constructor
	GCPhoneDisconnectedFactory() throw() {}
	
	// destructor
	virtual ~GCPhoneDisconnectedFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCPhoneDisconnected(); }

	// get packet name
	string getPacketName() const throw() { return "GCPhoneDisconnected"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_PHONE_DISCONNECTED; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szPhoneNumber + szSlotID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCPhoneDisconnectedHandler;
//
//////////////////////////////////////////////////////////////////////

class GCPhoneDisconnectedHandler {

public :

	// execute packet's handler
	static void execute(GCPhoneDisconnected* pGCPhoneDisconnected, Player* pPlayer) throw(Error);

};

#endif
