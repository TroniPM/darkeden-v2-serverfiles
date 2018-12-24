//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAttackMeleeOK2.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_ATTACK_MELEE_OK_2_H__
#define __GC_ATTACK_MELEE_OK_2_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCAttackMeleeOK2;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCAttackMeleeOK2 : public ModifyInfo {

public :
	
	// constructor
	GCAttackMeleeOK2() throw();
	
	// destructor
	~GCAttackMeleeOK2() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_ATTACK_MELEE_OK_2; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize() const throw() { return szObjectID + ModifyInfo::getPacketSize(); }

	// get packet's name
	string getPacketName() const throw() { return "GCAttackMeleeOK2"; }
	
	// get packet's debug string
	string toString() const throw();

	// get / set CEffectID
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }
	

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;



};


//////////////////////////////////////////////////////////////////////
//
// class GCAttackMeleeOK2Factory;
//
// Factory for GCAttackMeleeOK2
//
//////////////////////////////////////////////////////////////////////

class GCAttackMeleeOK2Factory : public PacketFactory {

public :
	
	// constructor
	GCAttackMeleeOK2Factory() throw() {}
	
	// destructor
	virtual ~GCAttackMeleeOK2Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCAttackMeleeOK2(); }

	// get packet name
	string getPacketName() const throw() { return "GCAttackMeleeOK2"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_ATTACK_MELEE_OK_2; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + ModifyInfo::getPacketMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCAttackMeleeOK2Handler;
//
//////////////////////////////////////////////////////////////////////

class GCAttackMeleeOK2Handler {

public :

	// execute packet's handler
	static void execute(GCAttackMeleeOK2* pGCAttackMeleeOK2, Player* pPlayer) throw(Error);

};

#endif
