//////////////////////////////////////////////////////////////////////////////
// Filename    : CGLearnSkill.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_LEARN_SKILL_H__
#define __CG_LEARN_SKILL_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGLearnSkill;
//////////////////////////////////////////////////////////////////////////////

class CGLearnSkill : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_CG_LEARN_SKILL; }
	PacketSize_t getPacketSize()  { return szSkillType+szSkillDomainType; }
	string getPacketName()  { return "CGLearnSkill"; }
	string toString() ;

public:
	SkillType_t getSkillType()   { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

	SkillDomainType_t getSkillDomainType()  { return m_DomainType;}
	void setSkillDomainType(SkillDomainType_t DomainType) throw() { m_DomainType = DomainType;}

private:
	SkillType_t       m_SkillType;  // 기술의 종류
	SkillDomainType_t m_DomainType; // 기술의 도메인
};

//////////////////////////////////////////////////////////////////////
// class CGLearnSkillFactory;
//////////////////////////////////////////////////////////////////////

class CGLearnSkillFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGLearnSkill(); }
	string getPacketName()  { return "CGLearnSkill"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_LEARN_SKILL; }
	PacketSize_t getPacketMaxSize()  { return szSkillType+szSkillDomainType; }
};


//////////////////////////////////////////////////////////////////////
// class CGLearnSkillHandler;
//////////////////////////////////////////////////////////////////////

class CGLearnSkillHandler 
{
public:
	static void execute(CGLearnSkill* pCGLearnSkill, Player* pPlayer) throw(ProtocolException, Error);
	static void executeSlayerSkill(CGLearnSkill* pCGLearnSkill, Player* pPlayer) throw(ProtocolException, Error);
	static void executeVampireSkill(CGLearnSkill* pCGLearnSkill, Player* pPlayer) throw(ProtocolException, Error);
	static void executeOustersSkill(CGLearnSkill* pCGLearnSkill, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
