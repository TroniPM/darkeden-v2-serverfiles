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
	GCCastingSkill() throw();
	
	// destructor
	~GCCastingSkill() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_CASTING_SKILL; }
	
	// get packet size
	PacketSize_t getPacketSize() const throw() { return szSkillType; }
	
	// get packet's name
	string getPacketName() const throw() { return "GCCastingSkill"; }
	
	// get packet's debug string
	string toString() const throw();
	
	// get/set SkillType
	SkillType_t getSkillType() const throw() { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

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
	 GCCastingSkillFactory() throw() {}
	
	// destructor
	virtual ~GCCastingSkillFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCCastingSkill(); }

	// get packet name
	string getPacketName() const throw() { return "GCCastingSkill"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_CASTING_SKILL; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return  szSkillType; }

};


//////////////////////////////////////////////////////////////////////
//
// class  GCCastingSkillHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCCastingSkillHandler {

public :

	// execute packet's handler
	static void execute( GCCastingSkill* pGCCastingSkill, Player* pPlayer) throw(Error);

};

#endif	// __GC_CASTING_SKILL_H__
