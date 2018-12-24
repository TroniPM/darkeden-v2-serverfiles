//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCCrossCounterOK2.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_CROSS_COUNTER_OK_2_H__
#define __GC_CROSS_COUNTER_OK_2_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCCrossCounterOK2;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCCrossCounterOK2 : public ModifyInfo {

public :
	
	// constructor
	GCCrossCounterOK2() throw();
	
	// destructor
	~GCCrossCounterOK2() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_CROSS_COUNTER_OK_2; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize() const throw() { return szObjectID + ModifyInfo::getPacketSize() + szSkillType; }

	// get packet's name
	string getPacketName() const throw() { return "GCCrossCounterOK2"; }
	
	// get packet's debug string
	string toString() const throw();

	// get / set CEffectID
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	SkillType_t getSkillType() const throw() { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }
	

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	SkillType_t m_SkillType;

};


//////////////////////////////////////////////////////////////////////
//
// class GCCrossCounterOK2Factory;
//
// Factory for GCCrossCounterOK2
//
//////////////////////////////////////////////////////////////////////

class GCCrossCounterOK2Factory : public PacketFactory {

public :
	
	// constructor
	GCCrossCounterOK2Factory() throw() {}
	
	// destructor
	virtual ~GCCrossCounterOK2Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCCrossCounterOK2(); }

	// get packet name
	string getPacketName() const throw() { return "GCCrossCounterOK2"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_CROSS_COUNTER_OK_2; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + ModifyInfo::getPacketMaxSize() + szSkillType; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCCrossCounterOK2Handler;
//
//////////////////////////////////////////////////////////////////////

class GCCrossCounterOK2Handler {

public :

	// execute packet's handler
	static void execute(GCCrossCounterOK2* pGCCrossCounterOK2, Player* pPlayer) throw(Error);

};

#endif
