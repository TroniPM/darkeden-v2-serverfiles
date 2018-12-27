//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToSelfOK1.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_TO_SELF_OK_1_H__
#define __GC_SKILL_TO_SELF_OK_1_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCSkillToSelfOK1;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCSkillToSelfOK1 : public ModifyInfo {

public :
	
	// constructor
	GCSkillToSelfOK1() ;
	
	// destructor
	~GCSkillToSelfOK1() ;

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_SKILL_TO_SELF_OK_1; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize()  { return szSkillType + szCEffectID + szDuration + szBYTE + ModifyInfo::getPacketSize() ; }

	// get packet's name
	string getPacketName()  { return "GCSkillToSelfOK1"; }
	
	// get packet's debug string
	string toString() ;

	// get / set SkillType
	SkillType_t getSkillType()  { return m_SkillType; }
	void setSkillType(SkillType_t SkillType)  { m_SkillType = SkillType; }

	// get / set CEffectID
	CEffectID_t getCEffectID()  { return m_CEffectID; }
	void setCEffectID(CEffectID_t CEffectID)  { m_CEffectID = CEffectID; }

	// get / set Duration
	Duration_t getDuration()  { return m_Duration; }
	void setDuration(Duration_t Duration)  { m_Duration = Duration; }

	BYTE getGrade()  { return m_Grade; }
	void setGrade( BYTE grade )  { m_Grade = grade; }

private :
	
	// SkillType
	SkillType_t m_SkillType;

	// CEffectID
	CEffectID_t m_CEffectID;

	// Duration
	Duration_t m_Duration;

	BYTE m_Grade;
};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToSelfOK1Factory;
//
// Factory for GCSkillToSelfOK1
//
//////////////////////////////////////////////////////////////////////

class GCSkillToSelfOK1Factory : public PacketFactory {

public :
	
	// constructor
	GCSkillToSelfOK1Factory()  {}
	
	// destructor
	virtual ~GCSkillToSelfOK1Factory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCSkillToSelfOK1(); }

	// get packet name
	string getPacketName()  { return "GCSkillToSelfOK1"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SKILL_TO_SELF_OK_1; }

	// get Packet Max Size
	// PacketSize_t getPacketMaxSize()  { return szSkillType + szCEffectID + szDuration + szBYTE + szBYTE* m_ListNum* 2 ; }
	PacketSize_t getPacketMaxSize()  { return szSkillType + szCEffectID + szDuration + szBYTE + ModifyInfo::getPacketMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToSelfOK1Handler;
//
//////////////////////////////////////////////////////////////////////

class GCSkillToSelfOK1Handler {

public :

	// execute packet's handler
	static void execute(GCSkillToSelfOK1* pGCSkillToSelfOK1, Player* pPlayer);

};

#endif
