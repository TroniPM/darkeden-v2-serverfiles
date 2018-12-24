//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToInventoryOK2.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_TO_INVENTORY_OK_2_H__
#define __GC_SKILL_TO_INVENTORY_OK_2_H__


// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCSkillToInventoryOK2;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCSkillToInventoryOK2 : public Packet {

public :
	
	// constructor
	GCSkillToInventoryOK2() throw();
	
	// destructor
	~GCSkillToInventoryOK2() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_SKILL_TO_INVENTORY_OK_2; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize() const throw() { return szSkillType + szObjectID + szDuration; }

	// get packet's name
	string getPacketName() const throw() { return "GCSkillToInventoryOK2"; }
	
	// get packet's debug string
	string toString() const throw();

	// get / set ObjectID 
	CEffectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	// get / set SkillType
	SkillType_t getSkillType() const throw() { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

	// get / set Duration
	Duration_t getDuration() const throw() { return m_Duration; }
	void setDuration(Duration_t Duration) throw() { m_Duration = Duration; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// SkillType
	SkillType_t m_SkillType;

	// Duration
	Duration_t m_Duration;

};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToInventoryOK2Factory;
//
// Factory for GCSkillToInventoryOK2
//
//////////////////////////////////////////////////////////////////////

class GCSkillToInventoryOK2Factory : public PacketFactory {

public :
	
	// constructor
	GCSkillToInventoryOK2Factory() throw() {}
	
	// destructor
	virtual ~GCSkillToInventoryOK2Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCSkillToInventoryOK2(); }

	// get packet name
	string getPacketName() const throw() { return "GCSkillToInventoryOK2"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SKILL_TO_INVENTORY_OK_2; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szSkillType + szObjectID + szDuration; }
};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToInventoryOK2Handler;
//
//////////////////////////////////////////////////////////////////////

class GCSkillToInventoryOK2Handler {

public :

	// execute packet's handler
	static void execute(GCSkillToInventoryOK2* pGCSkillToInventoryOK2, Player* pPlayer) throw(Error);

};

#endif
