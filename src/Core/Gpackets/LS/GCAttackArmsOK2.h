//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAttackArmsOK2.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_ATTACK_ARMS_OK_2_H__
#define __GC_ATTACK_ARMS_OK_2_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCAttackArmsOK2;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCAttackArmsOK2 : public ModifyInfo {

public :
	
	// constructor
	GCAttackArmsOK2() throw();
	
	// destructor
	~GCAttackArmsOK2() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_ATTACK_ARMS_OK_2; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize()  { return szSkillType + szObjectID + ModifyInfo::getPacketSize(); }

	// get packet's name
	string getPacketName()  { return "GCAttackArmsOK2"; }
	
	// get packet's debug string
	string toString() ;

	SkillType_t getSkillType() const { return m_SkillType; }
	void setSkillType( SkillType_t skillType ) { m_SkillType = skillType; }
	// get / set CEffectID
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

private :
	
	SkillType_t m_SkillType;
	// ObjectID
	ObjectID_t m_ObjectID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCAttackArmsOK2Factory;
//
// Factory for GCAttackArmsOK2
//
//////////////////////////////////////////////////////////////////////

class GCAttackArmsOK2Factory : public PacketFactory {

public :
	
	// constructor
	GCAttackArmsOK2Factory() throw() {}
	
	// destructor
	virtual ~GCAttackArmsOK2Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCAttackArmsOK2(); }

	// get packet name
	string getPacketName()  { return "GCAttackArmsOK2"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_ATTACK_ARMS_OK_2; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szSkillType + szObjectID + ModifyInfo::getPacketMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCAttackArmsOK2Handler;
//
//////////////////////////////////////////////////////////////////////

class GCAttackArmsOK2Handler {

public :

	// execute packet's handler
	static void execute(GCAttackArmsOK2* pGCAttackArmsOK2, Player* pPlayer) throw(Error);

};

#endif
