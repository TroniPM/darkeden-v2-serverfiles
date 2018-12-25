//////////////////////////////////////////////////////////////////////
// 
// Filename    :  GCLearnSkillOK.h 
// Written By  :  elca@ewestsoft.com
// Description :  �
//                
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_LEARN_SKILL_OK_H__
#define __GC_LEARN_SKILL_OK_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class  GCLearnSkillOK;
//
//////////////////////////////////////////////////////////////////////

class GCLearnSkillOK : public Packet {

public :
	
	// constructor
	GCLearnSkillOK() throw();
	
	// destructor
	~GCLearnSkillOK() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_LEARN_SKILL_OK; }
	
	// get packet size
	PacketSize_t getPacketSize()  { return szSkillType+szSkillDomainType; }
	
	// get packet's name
	string getPacketName()  { return "GCLearnSkillOK"; }
	
	// get packet's debug string
	string toString() ;
	
	// get/set m_SkillType
	SkillType_t getSkillType()  { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

	// get/set m_SkillDomainType
	SkillDomainType_t getSkillDomainType()  { return m_DomainType;}
	void setSkillDomainType(SkillDomainType_t DomainType) throw() { m_DomainType = DomainType;}

private : 

	// SkillType
	SkillType_t m_SkillType; 

	// DomainType
	SkillDomainType_t m_DomainType;
};


//////////////////////////////////////////////////////////////////////
//
// class  GCLearnSkillOKFactory;
//
// Factory for  GCLearnSkillOK
//
//////////////////////////////////////////////////////////////////////

class  GCLearnSkillOKFactory : public PacketFactory {

public :
	
	// constructor
	 GCLearnSkillOKFactory() throw() {}
	
	// destructor
	virtual ~GCLearnSkillOKFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCLearnSkillOK(); }

	// get packet name
	string getPacketName()  { return "GCLearnSkillOK"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_LEARN_SKILL_OK; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szSkillType+szSkillDomainType; }

};


//////////////////////////////////////////////////////////////////////
//
// class  GCLearnSkillOKHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCLearnSkillOKHandler {

public :

	// execute packet's handler
	static void execute( GCLearnSkillOK* pGCLearnSkillOK, Player* pPlayer) throw(Error);

};

#endif	// __GC_LEARN_SKILL_OK_H__
