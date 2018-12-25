//////////////////////////////////////////////////////////////////////
// 
// Filename    :  GCDownSkillOK.h 
// Written By  :  elca@ewestsoft.com
// Description :  �
//                
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_DOWN_SKILL_OK_H__
#define __GC_DOWN_SKILL_OK_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class  GCDownSkillOK;
//
//////////////////////////////////////////////////////////////////////

class GCDownSkillOK : public Packet {

public :
	
	// constructor
	GCDownSkillOK() throw();
	
	// destructor
	~GCDownSkillOK() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_DOWN_SKILL_OK; }
	
	// get packet size
	PacketSize_t getPacketSize()  { return szSkillType; }
	
	// get packet's name
	string getPacketName()  { return "GCDownSkillOK"; }
	
	// get packet's debug string
	string toString() ;
	
	// get/set m_SkillType
	SkillType_t getSkillType()  { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

private : 

	// SkillType
	SkillType_t m_SkillType; 

};


//////////////////////////////////////////////////////////////////////
//
// class  GCDownSkillOKFactory;
//
// Factory for  GCDownSkillOK
//
//////////////////////////////////////////////////////////////////////

class  GCDownSkillOKFactory : public PacketFactory {

public :
	
	// constructor
	 GCDownSkillOKFactory() throw() {}
	
	// destructor
	virtual ~GCDownSkillOKFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCDownSkillOK(); }

	// get packet name
	string getPacketName()  { return "GCDownSkillOK"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_DOWN_SKILL_OK; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szSkillType; }

};


//////////////////////////////////////////////////////////////////////
//
// class  GCDownSkillOKHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCDownSkillOKHandler {

public :

	// execute packet's handler
	static void execute( GCDownSkillOK* pGCDownSkillOK, Player* pPlayer) throw(Error);

};

#endif	// __GC_DOWN_SKILL_OK_H__
