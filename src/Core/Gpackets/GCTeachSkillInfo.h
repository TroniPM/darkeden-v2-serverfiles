//////////////////////////////////////////////////////////////////////////////
// Filename    : GCTeachSkillInfo.h 
// Written By  : �輺��
// Description : 
// NPC�� �÷��̾�� ��ų�� ������ �� �� ���� ���� �÷��̾��
// ���۵Ǵ� ��Ŷ�̴�. NPC�� ������ �� �� �ִ� ����� ������ ����ϴ� 
// �� ���̴� ��Ŷ�̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_TEACH_SKILL_INFO_H__
#define __GC_TEACH_SKILL_INFO_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCTeachSkillInfo;
//////////////////////////////////////////////////////////////////////////////

class GCTeachSkillInfo : public Packet 
{
public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_TEACH_SKILL_INFO; }
	PacketSize_t getPacketSize()  { return szSkillDomainType+szSkillLevel; }
	string getPacketName()  { return "GCTeachSkillInfo"; }
	string toString() ;

public :
	SkillDomainType_t getDomainType(void)  { return m_DomainType;}
	void setDomainType(SkillDomainType_t type) throw()  { m_DomainType = type;}

	SkillLevel_t getTargetLevel(void)  { return m_TargetLevel;}
	void setTargetLevel(SkillLevel_t level) throw() { m_TargetLevel = level;}

private:
	SkillDomainType_t m_DomainType;  // NPC�� �������ִ� ����� ������ Ÿ��
	SkillLevel_t      m_TargetLevel; // �÷��̾ ���� ��� ��� ����
};

//////////////////////////////////////////////////////////////////////////////
// class GCTeachSkillInfoFactory;
//////////////////////////////////////////////////////////////////////////////

class GCTeachSkillInfoFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCTeachSkillInfo(); }
	string getPacketName()  { return "GCTeachSkillInfo"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_TEACH_SKILL_INFO; }
	PacketSize_t getPacketMaxSize()  { return szSkillDomainType+szSkillLevel; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCTeachSkillInfoHandler;
//////////////////////////////////////////////////////////////////////////////

class GCTeachSkillInfoHandler 
{
public :
	static void execute(GCTeachSkillInfo* pPacket, Player* pPlayer) ;
};

#endif
