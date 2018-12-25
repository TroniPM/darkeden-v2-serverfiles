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
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_REMOVE_FROM_GEAR; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize()  { return szSlotID; }

	// get packet's name
	string getPacketName()  { return "GCRemoveFromGear"; }
	
	// get packet's debug string
	string toString() ;

	// get/set SlotID
	SlotID_t getSlotID()  { return m_SlotID; }
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
	string getPacketName()  { return "GCRemoveFromGear"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_REMOVE_FROM_GEAR; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szSlotID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCRemoveFromGearHandler;
//
//////////////////////////////////////////////////////////////////////

class GCRemoveFromGearHandler {

public :

	// execute packet's handler
	static void execute(GCRemoveFromGear* pGCRemoveFromGear, Player* pPlayer);

};

#endif
