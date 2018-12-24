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

	GCLearnSkillFailed() throw();
	virtual ~GCLearnSkillFailed() throw();

	
public:
	
	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
			
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_LEARN_SKILL_FAILED; }
	
	// get packet size
	PacketSize_t getPacketSize() const throw() { return szSkillType+szBYTE; }
	
	// get packet's name
	string getPacketName() const throw() { return "GCLearnSkillFailed"; }
	
	// get packet's debug string
	string toString() const throw();
	
	// get/set skill type
	SkillType_t getSkillType(void) const throw() { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

	// get/set description
	BYTE getDesc(void) const throw() { return m_Desc;}
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
	string getPacketName() const throw() { return "GCLearnSkillFailed"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_LEARN_SKILL_FAILED; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szSkillType+szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class  GCLearnSkillFailedHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCLearnSkillFailedHandler {

public :

	// execute packet's handler
	static void execute( GCLearnSkillFailed* pGCLearnSkillFailed, Player* pPlayer) throw(Error);

};

#endif	// __GC_LEARN_SKILL_FAILED_H__
