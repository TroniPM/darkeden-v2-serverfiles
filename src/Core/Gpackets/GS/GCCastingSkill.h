//////////////////////////////////////////////////////////////////////
// 
// Filename    :  GCCastingSkill.h 
// Written By  :  elca@ewestsoft.com
// Description :  �
//                
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_CASTING_SKILL_H__
#define __GC_CASTING_SKILL_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class  GCCastingSkill;
//
//////////////////////////////////////////////////////////////////////

class GCCastingSkill : public Packet {

public :
	
	// constructor
	GCCastingSkill() ;
	
	// destructor
	~GCCastingSkill() ;

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_CASTING_SKILL; }
	
	// get packet size
	PacketSize_t getPacketSize()  { return szSkillType; }
	
	// get packet's name
	string getPacketName()  { return "GCCastingSkill"; }
	
	// get packet's debug string
	string toString() ;
	
	// get/set SkillType
	SkillType_t getSkillType()  { return m_SkillType; }
	void setSkillType(SkillType_t SkillType)  { m_SkillType = SkillType; }

private : 

	// SkillType
	SkillType_t m_SkillType;

};


//////////////////////////////////////////////////////////////////////
//
// class  GCCastingSkillFactory;
//
// Factory for  GCCastingSkill
//
//////////////////////////////////////////////////////////////////////

class  GCCastingSkillFactory : public PacketFactory {

public :
	
	// constructor
	 GCCastingSkillFactory()  {}
	
	// destructor
	virtual ~GCCastingSkillFactory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCCastingSkill(); }

	// get packet name
	string getPacketName()  { return "GCCastingSkill"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_CASTING_SKILL; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return  szSkillType; }

};


//////////////////////////////////////////////////////////////////////
//
// class  GCCastingSkillHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCCastingSkillHandler {

public :

	// execute packet's handler
	static void execute( GCCastingSkill* pGCCastingSkill, Player* pPlayer);

};

#endif	// __GC_CASTING_SKILL_H__
