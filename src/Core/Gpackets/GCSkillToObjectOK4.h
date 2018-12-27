//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToObjectOK4.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 				����� ���� ����� �� �� �ִ� �е��� �����ô� ��Ŷ(����� ����� ����� ���� ����)
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_TO_OBJECT_OK_4_H__
#define __GC_SKILL_TO_OBJECT_OK_4_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK4;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK4 : public Packet {

public :
	
	// constructor
	GCSkillToObjectOK4() ;
	
	// destructor
	~GCSkillToObjectOK4() ;

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_SKILL_TO_OBJECT_OK_4; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize()  { return szObjectID + szSkillType + szDuration + szBYTE; }

	// get packet's name
	string getPacketName()  { return "GCSkillToObjectOK4"; }
	
	// get packet's debug string
	string toString() ;

	// get / set ObjectID
	ObjectID_t getTargetObjectID()  { return m_ObjectID; }
	void setTargetObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	// get / set SkillType
	SkillType_t getSkillType()  { return m_SkillType; }
	void setSkillType(SkillType_t SkillType)  { m_SkillType = SkillType; }
	
/*
	// get / set Target X,Y
	Coord_t getTargetX()  { return m_TargetX; }
	Coord_t getTargetY()  { return m_TargetY; }
	void setTargetXY(Coord_t X, Coord_t Y)  { m_TargetX = X; m_TargetY = Y; }
*/
	
	// get / set Duration
	Duration_t getDuration()  { return m_Duration; }
	void setDuration(Duration_t Duration)  { m_Duration = Duration; }
	
	// get / set CEffectID 
//	CEffectID_t getCEffectID()  { return m_CEffectID; }
//	void setCEffectID(CEffectID_t e)  { m_CEffectID = e; }

	BYTE getGrade()  { return m_Grade; }
	void setGrade( BYTE grade )  { m_Grade = grade; }

private :
	
	// ObjectID(Target)
	ObjectID_t m_ObjectID;

	// SkillType
	SkillType_t m_SkillType;

	// Duration
	Duration_t m_Duration;

	// CEffectID
//	CEffectID_t m_CEffectID;

	BYTE m_Grade;

};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK4Factory;
//
// Factory for GCSkillToObjectOK4
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK4Factory : public PacketFactory {

public :
	
	// constructor
	GCSkillToObjectOK4Factory()  {}
	
	// destructor
	virtual ~GCSkillToObjectOK4Factory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCSkillToObjectOK4(); }

	// get packet name
	string getPacketName()  { return "GCSkillToObjectOK4"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SKILL_TO_OBJECT_OK_4; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szObjectID + szSkillType + szDuration + szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK4Handler;
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK4Handler {

public :

	// execute packet's handler
	static void execute(GCSkillToObjectOK4* pGCSkillToObjectOK4, Player* pPlayer);

};

#endif
