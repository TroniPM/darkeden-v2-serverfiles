//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGCastingSkill.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_CASTING_SKILL_H__
#define __CG_CASTING_SKILL_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGCastingSkill;
//
//////////////////////////////////////////////////////////////////////

class CGCastingSkill : public Packet {

public:
	
	// constructor
	CGCastingSkill() throw();
	
	// destructor
	~CGCastingSkill() throw();

	
public:
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_CASTING_SKILL; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szSkillType; }

	// get packet name
	string getPacketName()  { return "CGCastingSkill"; }

	// get/set SkillType
	SkillType_t getSkillType()   { return m_SkillType; }
	void setObjectID(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

	// get packet's debug string
	string toString() ;

private :

	// SkillType
	SkillType_t m_SkillType;

};


//////////////////////////////////////////////////////////////////////
//
// class CGCastingSkillFactory;
//
// Factory for CGCastingSkill
//
//////////////////////////////////////////////////////////////////////

class CGCastingSkillFactory : public PacketFactory {

public:
	
	// constructor
	CGCastingSkillFactory() throw() {}
	
	// destructor
	virtual ~CGCastingSkillFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGCastingSkill(); }

	// get packet name
	string getPacketName()  { return "CGCastingSkill"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_CASTING_SKILL; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szSkillType; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGCastingSkillHandler;
//
//////////////////////////////////////////////////////////////////////

class CGCastingSkillHandler {

public:

	// execute packet's handler
	static void execute(CGCastingSkill* pCGCastingSkill, Player* pPlayer) throw(Error);

};

#endif
