//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCCrossCounterOK1.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_CROSS_COUNTER_OK_1_H__
#define __GC_CROSS_COUNTER_OK_1_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCCrossCounterOK1;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCCrossCounterOK1 : public ModifyInfo {

public :
	
	// constructor
	GCCrossCounterOK1() throw();
	
	// destructor
	~GCCrossCounterOK1() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_CROSS_COUNTER_OK_1; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize()  { return szObjectID + ModifyInfo::getPacketSize() + szSkillType; }

	// get packet's name
	string getPacketName()  { return "GCCrossCounterOK1"; }
	
	// get packet's debug string
	string toString() ;

	// get / set CEffectID
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	SkillType_t getSkillType()  { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// Counter SkillType
	SkillType_t m_SkillType;
};


//////////////////////////////////////////////////////////////////////
//
// class GCCrossCounterOK1Factory;
//
// Factory for GCCrossCounterOK1
//
//////////////////////////////////////////////////////////////////////

class GCCrossCounterOK1Factory : public PacketFactory {

public :
	
	// constructor
	GCCrossCounterOK1Factory() throw() {}
	
	// destructor
	virtual ~GCCrossCounterOK1Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCCrossCounterOK1(); }

	// get packet name
	string getPacketName()  { return "GCCrossCounterOK1"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_CROSS_COUNTER_OK_1; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szObjectID + ModifyInfo::getPacketMaxSize() + szSkillType; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCCrossCounterOK1Handler;
//
//////////////////////////////////////////////////////////////////////

class GCCrossCounterOK1Handler {

public :

	// execute packet's handler
	static void execute(GCCrossCounterOK1* pGCCrossCounterOK1, Player* pPlayer);

};

#endif
