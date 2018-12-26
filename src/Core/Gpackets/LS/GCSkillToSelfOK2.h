//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToSelfOK2.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_TO_SELF_OK_2_H__
#define __GC_SKILL_TO_SELF_OK_2_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCSkillToSelfOK2;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCSkillToSelfOK2 : public Packet {

public :
	
	// constructor
	GCSkillToSelfOK2() ;
	
	// destructor
	~GCSkillToSelfOK2() ;

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_SKILL_TO_SELF_OK_2; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize()  { return szObjectID + szSkillType + szDuration + szBYTE; }

	// get packet's name
	string getPacketName()  { return "GCSkillToSelfOK2"; }
	
	// get packet's debug string
	string toString() ;

	// get / set ObjectID
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	// get / set SkillType
	SkillType_t getSkillType()  { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

	// get / set Duration
	Duration_t getDuration()  { return m_Duration; }
	void setDuration(Duration_t Duration) throw() { m_Duration = Duration; }

	BYTE getGrade()  { return m_Grade; }
	void setGrade( BYTE grade ) throw() { m_Grade = grade; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// SkillType
	SkillType_t m_SkillType;

	// Duration
	Duration_t m_Duration;

	BYTE m_Grade;

};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToSelfOK2Factory;
//
// Factory for GCSkillToSelfOK2
//
//////////////////////////////////////////////////////////////////////

class GCSkillToSelfOK2Factory : public PacketFactory {

public :
	
	// constructor
	GCSkillToSelfOK2Factory() throw() {}
	
	// destructor
	virtual ~GCSkillToSelfOK2Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCSkillToSelfOK2(); }

	// get packet name
	string getPacketName()  { return "GCSkillToSelfOK2"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SKILL_TO_SELF_OK_2; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szObjectID + szSkillType + szDuration + szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToSelfOK2Handler;
//
//////////////////////////////////////////////////////////////////////

class GCSkillToSelfOK2Handler {

public :

	// execute packet's handler
	static void execute(GCSkillToSelfOK2* pGCSkillToSelfOK2, Player* pPlayer);

};

#endif
