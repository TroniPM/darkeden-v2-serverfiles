//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToObjectOK2.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 				����� ���� �е��� ������ ��Ŷ
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_TO_OBJECT_OK_2_H__
#define __GC_SKILL_TO_OBJECT_OK_2_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK2;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK2 : public ModifyInfo {

public :
	
	// constructor
	GCSkillToObjectOK2() throw();
	
	// destructor
	~GCSkillToObjectOK2() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_SKILL_TO_OBJECT_OK_2; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize()  { return szObjectID+ szSkillType + szDuration + szBYTE + ModifyInfo::getPacketSize(); }

	// get packet's name
	string getPacketName()  { return "GCSkillToObjectOK2"; }
	
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
	
	// get / set CEffectID 
//	CEffectID_t getCEffectID()  { return m_CEffectID; }
//	void setCEffectID(CEffectID_t e) throw() { m_CEffectID = e; }

	BYTE getGrade()  { return m_Grade; }
	void setGrade( BYTE grade ) throw() { m_Grade = grade; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// SkillType
	SkillType_t m_SkillType;

	// Duration
	Duration_t m_Duration;

	// CEffectID
//	CEffectID_t m_CEffectID;

	// grade
	BYTE m_Grade;
};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK2Factory;
//
// Factory for GCSkillToObjectOK2
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK2Factory : public PacketFactory {

public :
	
	// constructor
	GCSkillToObjectOK2Factory() throw() {}
	
	// destructor
	virtual ~GCSkillToObjectOK2Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCSkillToObjectOK2(); }

	// get packet name
	string getPacketName()  { return "GCSkillToObjectOK2"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SKILL_TO_OBJECT_OK_2; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szObjectID+ szSkillType + szDuration + szBYTE + ModifyInfo::getPacketMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK2Handler;
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK2Handler {

public :

	// execute packet's handler
	static void execute(GCSkillToObjectOK2* pGCSkillToObjectOK2, Player* pPlayer) throw(Error);

};

#endif
