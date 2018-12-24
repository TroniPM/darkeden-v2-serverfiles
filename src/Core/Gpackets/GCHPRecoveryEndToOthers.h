//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCHPRecoveryEndToOthers.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_HP_RECOVERY_END_TO_OTHERS_H__
#define __GC_HP_RECOVERY_END_TO_OTHERS_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "EffectInfo.h"


//////////////////////////////////////////////////////////////////////
//
// class GCHPRecoveryEndToOthers;
//
////////////////////////////////////////////////////////////////////

class GCHPRecoveryEndToOthers : public Packet {

public :

	GCHPRecoveryEndToOthers() throw(Error);

	virtual ~GCHPRecoveryEndToOthers() throw(Error);
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_HP_RECOVERY_END_TO_OTHERS; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCHPRecoveryEndToOthersPacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szObjectID + szHP; 
	}

	// get packet's name
	string getPacketName() const throw() { return "GCHPRecoveryEndToOthers"; }
	
	// get packet's debug string
	string toString() const throw();

public :

	// get/set creature ID 
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID) throw() { m_ObjectID = creatureID; }

	// get /set CurrentHP
	HP_t getCurrentHP() const throw() { return m_CurrentHP; }
	void setCurrentHP(HP_t CurrentHP) throw() { m_CurrentHP = CurrentHP; }

private :
	
    // �� �������� ����ũ�� ���̵�� ��ü ������ ���ؼ� ����Ѵ�.
    ObjectID_t m_ObjectID;

	// ���� ü��
	HP_t m_CurrentHP;

};


//////////////////////////////////////////////////////////////////////
//
// class GCHPRecoveryEndToOthersFactory;
//
// Factory for GCHPRecoveryEndToOthers
//
//////////////////////////////////////////////////////////////////////

class GCHPRecoveryEndToOthersFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCHPRecoveryEndToOthers(); }

	// get packet name
	string getPacketName() const throw() { return "GCHPRecoveryEndToOthers"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_HP_RECOVERY_END_TO_OTHERS; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCHPRecoveryEndToOthersPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szObjectID + szHP; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCHPRecoveryEndToOthersHandler;
//
//////////////////////////////////////////////////////////////////////

class GCHPRecoveryEndToOthersHandler {

public :

	// execute packet's handler
	static void execute(GCHPRecoveryEndToOthers* pPacket, Player* pPlayer) throw(Error);

};

#endif
