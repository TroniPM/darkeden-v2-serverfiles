//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCTakeOff.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_TAKE_OFF_H__
#define __GC_TAKE_OFF_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCTakeOff;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�.(CreatureID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCTakeOff : public Packet {

public :
	
	// constructor
	GCTakeOff() throw();
	
	// destructor
	~GCTakeOff() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_TAKE_OFF; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize()  { return szObjectID + szSlotID; }

	// get packet's name
	string getPacketName()  { return "GCTakeOff"; }
	
	// get packet's debug string
	string toString() ;

	// get / set ObjectID 
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	// get/set SlotID
	SlotID_t getSlotID()  { return m_SlotID; }
	void setSlotID(SlotID_t SlotID) throw() { m_SlotID = SlotID; }

private :

	// ObjectID
	ObjectID_t m_ObjectID;

	// SlotID
	SlotID_t m_SlotID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCTakeOffFactory;
//
// Factory for GCTakeOff
//
//////////////////////////////////////////////////////////////////////

class GCTakeOffFactory : public PacketFactory {

public :
	
	// constructor
	GCTakeOffFactory() throw() {}
	
	// destructor
	virtual ~GCTakeOffFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCTakeOff(); }

	// get packet name
	string getPacketName()  { return "GCTakeOff"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_TAKE_OFF; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szObjectID + szSlotID;}

};


//////////////////////////////////////////////////////////////////////
//
// class GCTakeOffHandler;
//
//////////////////////////////////////////////////////////////////////

class GCTakeOffHandler {

public :

	// execute packet's handler
	static void execute(GCTakeOff* pGCTakeOff, Player* pPlayer) throw(Error);

};

#endif
