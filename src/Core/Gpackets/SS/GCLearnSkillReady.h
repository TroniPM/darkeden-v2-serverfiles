//////////////////////////////////////////////////////////////////////
// 
// Filename    :  GCLearnSkillReady.h 
// Written By  :  elca@ewestsoft.com
// Description :  �
//                
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_LEARN_SKILL_READY_H__
#define __GC_LEARN_SKILL_READY_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class  GCLearnSkillReady;
//
//////////////////////////////////////////////////////////////////////

class GCLearnSkillReady : public Packet {

public :
	
	// constructor
	GCLearnSkillReady() ;
	
	// destructor
	~GCLearnSkillReady() ;

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_LEARN_SKILL_READY; }
	
	// get packet size
	PacketSize_t getPacketSize()  { return szSkillDomainType; }
	
	// get packet's name
	string getPacketName()  { return "GCLearnSkillReady"; }
	
	// get packet's debug string
	string toString() ;
	
	SkillDomainType_t getSkillDomainType()  { return m_SkillDomainType;}
	void setSkillDomainType(SkillDomainType_t SkillDomainType) throw()
	{
		m_SkillDomainType = SkillDomainType;
	}
private : 

	// ��ų Ÿ��
	SkillDomainType_t m_SkillDomainType;

};


//////////////////////////////////////////////////////////////////////
//
// class  GCLearnSkillReadyFactory;
//
// Factory for  GCLearnSkillReady
//
//////////////////////////////////////////////////////////////////////

class  GCLearnSkillReadyFactory : public PacketFactory {

public :
	
	// constructor
	 GCLearnSkillReadyFactory() throw() {}
	
	// destructor
	virtual ~GCLearnSkillReadyFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCLearnSkillReady(); }

	// get packet name
	string getPacketName()  { return "GCLearnSkillReady"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_LEARN_SKILL_READY; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szSkillDomainType;}

};


//////////////////////////////////////////////////////////////////////
//
// class  GCLearnSkillReadyHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCLearnSkillReadyHandler {

public :

	// execute packet's handler
	static void execute( GCLearnSkillReady* pGCLearnSkillReady, Player* pPlayer);

};

#endif	// __GC_LEARN_SKILL_READY_H__
