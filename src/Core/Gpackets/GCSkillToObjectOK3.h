//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToObjectOK3.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 				����� ����� ����� �� �� �ִ� �е��� �����ô� ��Ŷ(����� ���� ����� ���� ����)
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_TO_OBJECT_OK_3_H__
#define __GC_SKILL_TO_OBJECT_OK_3_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK3;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK3 : public Packet {

public :
	
	// constructor
	GCSkillToObjectOK3() throw();
	
	// destructor
	~GCSkillToObjectOK3() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_SKILL_TO_OBJECT_OK_3; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize()  { return szObjectID + szSkillType + szCoord*2 + szBYTE; }

	// get packet's name
	string getPacketName()  { return "GCSkillToObjectOK3"; }
	
	// get packet's debug string
	string toString() ;

	// get / set ObjectID
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	// get / set SkillType
	SkillType_t getSkillType()  { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

	// get / set Target X,Y
	Coord_t getTargetX()  { return m_TargetX; }
	Coord_t getTargetY()  { return m_TargetY; }
	void setTargetXY(Coord_t X, Coord_t Y) throw() { m_TargetX = X; m_TargetY = Y; }

	
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

	// TargetObjectID
	Coord_t m_TargetX, m_TargetY;
	

	// CEffectID
//	CEffectID_t m_CEffectID;

	BYTE m_Grade;

};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK3Factory;
//
// Factory for GCSkillToObjectOK3
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK3Factory : public PacketFactory {

public :
	
	// constructor
	GCSkillToObjectOK3Factory() throw() {}
	
	// destructor
	virtual ~GCSkillToObjectOK3Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCSkillToObjectOK3(); }

	// get packet name
	string getPacketName()  { return "GCSkillToObjectOK3"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SKILL_TO_OBJECT_OK_3; }

	PacketSize_t getPacketMaxSize()  { return szObjectID + szSkillType + szCoord*2 + szBYTE; }


};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK3Handler;
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK3Handler {

public :

	// execute packet's handler
	static void execute(GCSkillToObjectOK3* pGCSkillToObjectOK3, Player* pPlayer);

};

#endif
