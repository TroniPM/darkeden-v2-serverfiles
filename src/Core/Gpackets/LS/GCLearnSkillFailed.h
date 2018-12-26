//////////////////////////////////////////////////////////////////////
// 
// Filename    :  GCLearnSkillFailed.h 
// Written By  :  elca@ewestsoft.com
// Description :  �
//                
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_LEARN_SKILL_FAILED_H__
#define __GC_LEARN_SKILL_FAILED_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class  GCLearnSkillFailed;
//
//////////////////////////////////////////////////////////////////////

class GCLearnSkillFailed : public Packet 
{

public: 

	GCLearnSkillFailed() ;
	virtual ~GCLearnSkillFailed() ;

	
public:
	
	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read(SocketInputStream & iStream) ;
			
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_LEARN_SKILL_FAILED; }
	
	// get packet size
	PacketSize_t getPacketSize()  { return szSkillType+szBYTE; }
	
	// get packet's name
	string getPacketName()  { return "GCLearnSkillFailed"; }
	
	// get packet's debug string
	string toString() ;
	
	// get/set skill type
	SkillType_t getSkillType(void)  { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

	// get/set description
	BYTE getDesc(void)  { return m_Desc;}
	void setDesc(BYTE desc) throw() { m_Desc = desc;}

private:

	SkillType_t m_SkillType;
	BYTE        m_Desc;       // ����� ���� �� ������ �����̴�.
	                          // �ڼ��� ������ CGLearnSkillHandler�� �����ϵ���.

};


//////////////////////////////////////////////////////////////////////
//
// class  GCLearnSkillFailedFactory;
//
// Factory for  GCLearnSkillFailed
//
//////////////////////////////////////////////////////////////////////

class  GCLearnSkillFailedFactory : public PacketFactory {

public :
	
	// constructor
	 GCLearnSkillFailedFactory() throw() {}
	
	// destructor
	virtual ~GCLearnSkillFailedFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCLearnSkillFailed(); }

	// get packet name
	string getPacketName()  { return "GCLearnSkillFailed"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_LEARN_SKILL_FAILED; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szSkillType+szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class  GCLearnSkillFailedHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCLearnSkillFailedHandler {

public :

	// execute packet's handler
	static void execute( GCLearnSkillFailed* pGCLearnSkillFailed, Player* pPlayer);

};

#endif	// __GC_LEARN_SKILL_FAILED_H__
