//////////////////////////////////////////////////////////////////////////////
// Filename    : CGDownSkill.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_DOWN_SKILL_H__
#define __CG_DOWN_SKILL_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGDownSkill;
//////////////////////////////////////////////////////////////////////////////

class CGDownSkill : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_CG_DOWN_SKILL; }
	PacketSize_t getPacketSize()  { return szSkillType; }
	string getPacketName()  { return "CGDownSkill"; }
	string toString() ;

public:
	SkillType_t getSkillType()   { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

private:
	SkillType_t       m_SkillType;  // ����� ����
};

//////////////////////////////////////////////////////////////////////
// class CGDownSkillFactory;
//////////////////////////////////////////////////////////////////////

class CGDownSkillFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGDownSkill(); }
	string getPacketName()  { return "CGDownSkill"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_DOWN_SKILL; }
	PacketSize_t getPacketMaxSize()  { return szSkillType; }
};


//////////////////////////////////////////////////////////////////////
// class CGDownSkillHandler;
//////////////////////////////////////////////////////////////////////

class CGDownSkillHandler 
{
public:
	static void execute(CGDownSkill* pCGDownSkill, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
