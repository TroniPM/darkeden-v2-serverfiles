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
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_TEACH_SKILL_INFO; }
	PacketSize_t getPacketSize() const throw() { return szSkillDomainType+szSkillLevel; }
	string getPacketName() const throw() { return "GCTeachSkillInfo"; }
	string toString() const throw();

public :
	SkillDomainType_t getDomainType(void) const throw() { return m_DomainType;}
	void setDomainType(SkillDomainType_t type) throw()  { m_DomainType = type;}

	SkillLevel_t getTargetLevel(void) const throw() { return m_TargetLevel;}
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
	string getPacketName() const throw() { return "GCTeachSkillInfo"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_TEACH_SKILL_INFO; }
	PacketSize_t getPacketMaxSize() const throw() { return szSkillDomainType+szSkillLevel; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCTeachSkillInfoHandler;
//////////////////////////////////////////////////////////////////////////////

class GCTeachSkillInfoHandler 
{
public :
	static void execute(GCTeachSkillInfo* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
