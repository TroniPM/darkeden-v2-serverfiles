//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToObjectOK1.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 					����� �� �ڽſ��� ������ ��Ŷ
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_TO_OBJECT_OK_1_H__
#define __GC_SKILL_TO_OBJECT_OK_1_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK1;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK1 : public ModifyInfo {

public :
	
	// constructor
	GCSkillToObjectOK1() ;
	
	// destructor
	~GCSkillToObjectOK1() ;

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_SKILL_TO_OBJECT_OK_1; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize()  { return szSkillType + szCEffectID + szObjectID + szDuration + szBYTE + ModifyInfo::getPacketSize(); }

	// get packet's name
	string getPacketName()  { return "GCSkillToObjectOK1"; }
	
	// get packet's debug string
	string toString() ;

	// get / set SkillType
	SkillType_t getSkillType()  { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

	// get / set CEffectID
	CEffectID_t getCEffectID()  { return m_CEffectID; }
	void setCEffectID(CEffectID_t CEffectID) throw() { m_CEffectID = CEffectID; }

	// get / set TargetObjectID
	ObjectID_t getTargetObjectID()  { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t TargetObjectID) throw() { m_TargetObjectID = TargetObjectID; }

	// get / set Duration
	Duration_t getDuration()  { return m_Duration; }
	void setDuration(Duration_t Duration) throw() { m_Duration = Duration; }

	BYTE getGrade()  { return m_Grade; }
	void setGrade(BYTE grade) throw() { m_Grade = grade; }

private :
	
	// SkillType
	SkillType_t m_SkillType;

	// CEffectID
	CEffectID_t m_CEffectID;

	// TargetObjectID
	ObjectID_t m_TargetObjectID;

	// Duration
	Duration_t m_Duration;

	// Grade
	BYTE m_Grade;
};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK1Factory;
//
// Factory for GCSkillToObjectOK1
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK1Factory : public PacketFactory {

public :
	
	// constructor
	GCSkillToObjectOK1Factory() throw() {}
	
	// destructor
	virtual ~GCSkillToObjectOK1Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCSkillToObjectOK1(); }

	// get packet name
	string getPacketName()  { return "GCSkillToObjectOK1"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SKILL_TO_OBJECT_OK_1; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szSkillType + szCEffectID + szObjectID + szDuration + szBYTE + ModifyInfo::getPacketMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK1Handler;
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK1Handler {

public :

	// execute packet's handler
	static void execute(GCSkillToObjectOK1* pGCSkillToObjectOK1, Player* pPlayer);

};

#endif
