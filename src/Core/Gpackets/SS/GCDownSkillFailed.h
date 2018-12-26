//////////////////////////////////////////////////////////////////////
// 
// Filename    :  GCDownSkillFailed.h 
// Written By  :  elca@ewestsoft.com
// Description :  
//                
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_DOWN_SKILL_FAILED_H__
#define __GC_DOWN_SKILL_FAILED_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class  GCDownSkillFailed;
//
//////////////////////////////////////////////////////////////////////

class GCDownSkillFailed : public Packet 
{

public: 

	GCDownSkillFailed() ;
	virtual ~GCDownSkillFailed() ;

	
public:
	
	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read(SocketInputStream & iStream) ;
			
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_DOWN_SKILL_FAILED; }
	
	// get packet size
	PacketSize_t getPacketSize()  { return szSkillType+szBYTE; }
	
	// get packet's name
	string getPacketName()  { return "GCDownSkillFailed"; }
	
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
	                          // �ڼ��� ������ CGDownSkillHandler�� �����ϵ���.

};


//////////////////////////////////////////////////////////////////////
//
// class  GCDownSkillFailedFactory;
//
// Factory for  GCDownSkillFailed
//
//////////////////////////////////////////////////////////////////////

class  GCDownSkillFailedFactory : public PacketFactory {

public :
	
	// constructor
	 GCDownSkillFailedFactory() throw() {}
	
	// destructor
	virtual ~GCDownSkillFailedFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCDownSkillFailed(); }

	// get packet name
	string getPacketName()  { return "GCDownSkillFailed"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_DOWN_SKILL_FAILED; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szSkillType+szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class  GCDownSkillFailedHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCDownSkillFailedHandler {

public :

	// execute packet's handler
	static void execute( GCDownSkillFailed* pGCDownSkillFailed, Player* pPlayer);

};

#endif	// __GC_DOWN_SKILL_FAILED_H__
