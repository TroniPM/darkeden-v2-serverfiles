//--------------------------------------------------------------------------------
// 
// Filename    : GCSkillInfo.h 
// Written By  : Reiot
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __GC_SKILL_INFO_H__
#define __GC_SKILL_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "PCSkillInfo.h"
#include "SlayerSkillInfo.h"
#include "VampireSkillInfo.h"
#include "Assert.h"

//--------------------------------------------------------------------------------
//
// class GCSkillInfo;
//
// Ŭ���̾�Ʈ�� ���� ������ �����ؼ� CGConnect ��Ŷ�� ������, ���� ������ ũ��ó��
// ���� �������� �ε��ؼ� ���� �� �غ� �ϰ� �ȴ�. �״��� PC�� ������ ����,
// �׸��� �� ������ GCSkillInfo�� ��Ƽ� Ŭ���̾�Ʈ�� �����ϰ� �ȴ�.
//
//--------------------------------------------------------------------------------

class GCSkillInfo : public Packet {

public :

	// constructor
	GCSkillInfo() ;

	// destructor
	~GCSkillInfo() ;
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_SKILL_INFO; }
	
	// get packet's body size
	PacketSize_t getPacketSize() ;

	// get packet name
	string getPacketName()  { return "GCSkillInfo"; }
	
	// get packet's debug string
	string toString() ;

//--------------------------------------------------
// methods
//--------------------------------------------------
public :

	// get / set PCType
	BYTE getPCType()  { return m_PCType; }
	void setPCType(BYTE PCType) throw() { m_PCType = PCType; }

    // add / delete / clear Skill List
	void addListElement(PCSkillInfo* pPCSkillInfo) throw() { m_pPCSkillInfoList.push_back(pPCSkillInfo); }
	
	// ClearList
	void clearList() throw() { m_pPCSkillInfoList.clear(); }
	
	// pop front Element in Status List
	PCSkillInfo* popFrontListElement() throw()
	{
		PCSkillInfo* TempPCSkillInfo = m_pPCSkillInfoList.front(); m_pPCSkillInfoList.pop_front(); return TempPCSkillInfo;
	}

private :

	BYTE m_PCType;

	//---------------------------------------------------------
	// PC Skill Information
	// SlayerSkillInfo �Ǵ� VampireSkillInfo �� ����Ѵ�.
	//---------------------------------------------------------
	list<PCSkillInfo *> m_pPCSkillInfoList;

};


//--------------------------------------------------------------------------------
//
// class GCSkillInfoFactory;
//
// Factory for GCSkillInfo
//
//--------------------------------------------------------------------------------

class GCSkillInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCSkillInfo(); }

	// get packet name
	string getPacketName()  { return "GCSkillInfo"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SKILL_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSkillInfoPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  
	{ 
		return SlayerSkillInfo::getMaxSize();
	}

};


//--------------------------------------------------------------------------------
//
// class GCSkillInfoHandler;
//
//--------------------------------------------------------------------------------

class GCSkillInfoHandler {

public :

	// execute packet's handler
	static void execute(GCSkillInfo* pPacket, Player* pPlayer) ;

};

#endif
