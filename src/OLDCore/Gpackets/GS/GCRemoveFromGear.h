//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRemoveFromGear.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_REMOVE_FROM_GEAR_H__
#define __GC_REMOVE_FROM_GEAR_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCRemoveFromGear;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�.(CreatureID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCRemoveFromGear : public Packet {

public :
	
	// constructor
	GCRemoveFromGear() throw();
	
	// destructor
	~GCRemoveFromGear() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_REMOVE_FROM_GEAR; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize() const throw() { return szSlotID; }

	// get packet's name
	string getPacketName() const throw() { return "GCRemoveFromGear"; }
	
	// get packet's debug string
	string toString() const throw();

	// get/set SlotID
	SlotID_t getSlotID() const throw() { return m_SlotID; }
	void setSlotID(SlotID_t SlotID) throw() { m_SlotID = SlotID; }

private :

	// SlotID
	SlotID_t m_SlotID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCRemoveFromGearFactory;
//
// Factory for GCRemoveFromGear
//
//////////////////////////////////////////////////////////////////////

class GCRemoveFromGearFactory : public PacketFactory {

public :
	
	// constructor
	GCRemoveFromGearFactory() throw() {}
	
	// destructor
	virtual ~GCRemoveFromGearFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCRemoveFromGear(); }

	// get packet name
	string getPacketName() const throw() { return "GCRemoveFromGear"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_REMOVE_FROM_GEAR; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szSlotID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCRemoveFromGearHandler;
//
//////////////////////////////////////////////////////////////////////

class GCRemoveFromGearHandler {

public :

	// execute packet's handler
	static void execute(GCRemoveFromGear* pGCRemoveFromGear, Player* pPlayer) throw(Error);

};

#endif
