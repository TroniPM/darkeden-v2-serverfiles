//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCBloodDrainOK1.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_BLOOD_DRAIN_OK_1_H__
#define __GC_BLOOD_DRAIN_OK_1_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCBloodDrainOK1;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCBloodDrainOK1 : public ModifyInfo {

public :
	
	// constructor
	GCBloodDrainOK1() throw();
	
	// destructor
	~GCBloodDrainOK1() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_BLOOD_DRAIN_OK_1; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize()  { return szObjectID + ModifyInfo::getPacketSize(); }

	// get packet's name
	string getPacketName()  { return "GCBloodDrainOK1"; }
	
	// get packet's debug string
	string toString() ;

	// get / set CEffectID
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;
};


//////////////////////////////////////////////////////////////////////
//
// class GCBloodDrainOK1Factory;
//
// Factory for GCBloodDrainOK1
//
//////////////////////////////////////////////////////////////////////

class GCBloodDrainOK1Factory : public PacketFactory {

public :
	
	// constructor
	GCBloodDrainOK1Factory() throw() {}
	
	// destructor
	virtual ~GCBloodDrainOK1Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCBloodDrainOK1(); }

	// get packet name
	string getPacketName()  { return "GCBloodDrainOK1"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_BLOOD_DRAIN_OK_1; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szObjectID + ModifyInfo::getPacketMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCBloodDrainOK1Handler;
//
//////////////////////////////////////////////////////////////////////

class GCBloodDrainOK1Handler {

public :

	// execute packet's handler
	static void execute(GCBloodDrainOK1* pGCBloodDrainOK1, Player* pPlayer);

};

#endif
