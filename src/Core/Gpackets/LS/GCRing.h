//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRing.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_RING_H__
#define __GC_RING_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCRing;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�.(CreatureID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCRing : public Packet {

public :
	
	// constructor
	GCRing() throw();
	
	// destructor
	~GCRing() throw();

	
public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_RING; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize() const throw() { return szPhoneNumber + szSlotID + szBYTE + m_Name.size(); }

	// get packet's name
	string getPacketName() const throw() { return "GCRing"; }
	
	// get packet's debug string
	string toString() const throw();

	// get/set PhoneNumber
	PhoneNumber_t getPhoneNumber() const throw() { return m_PhoneNumber; }
	void setPhoneNumber(PhoneNumber_t PhoneNumber) throw() { m_PhoneNumber = PhoneNumber; }

	// get/set SlotID
	SlotID_t getSlotID() const throw() { return m_SlotID; }
	void setSlotID(SlotID_t SlotID) throw() { m_SlotID = SlotID; }

	// get / set Name 
	string getName() const throw() { return m_Name; }
	void setName(const string & Name) { m_Name = Name; }

private :

	// PhoneNumber
	PhoneNumber_t m_PhoneNumber;

	// SlotID
	SlotID_t m_SlotID;

	// ��ȭ �� ����� �̸�.
	string m_Name;

};


//////////////////////////////////////////////////////////////////////
//
// class GCRingFactory;
//
// Factory for GCRing
//
//////////////////////////////////////////////////////////////////////

class GCRingFactory : public PacketFactory {

public :
	
	// constructor
	GCRingFactory() throw() {}
	
	// destructor
	virtual ~GCRingFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCRing(); }

	// get packet name
	string getPacketName() const throw() { return "GCRing"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_RING; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szPhoneNumber + szSlotID + szBYTE + 20; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCRingHandler;
//
//////////////////////////////////////////////////////////////////////

class GCRingHandler {

public :

	// execute packet's handler
	static void execute(GCRing* pGCRing, Player* pPlayer) throw(Error);

};

#endif
