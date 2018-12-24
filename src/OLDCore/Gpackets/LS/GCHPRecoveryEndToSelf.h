//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCHPRecoveryEndToSelf.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_HP_RECOVERY_END_TO_SELF_H__
#define __GC_HP_RECOVERY_END_TO_SELF_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "EffectInfo.h"


//////////////////////////////////////////////////////////////////////
//
// class GCHPRecoveryEndToSelf;
//
////////////////////////////////////////////////////////////////////

class GCHPRecoveryEndToSelf : public Packet {

public :

	GCHPRecoveryEndToSelf() throw(Error);

	virtual ~GCHPRecoveryEndToSelf() throw(Error);
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_HP_RECOVERY_END_TO_SELF; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCHPRecoveryEndToSelfPacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szHP; 
	}

	// get packet's name
	string getPacketName() const throw() { return "GCHPRecoveryEndToSelf"; }
	
	// get packet's debug string
	string toString() const throw();

public :

	// get /set CurrentHP
	HP_t getCurrentHP() const throw() { return m_CurrentHP; }
	void setCurrentHP(HP_t CurrentHP) throw() { m_CurrentHP = CurrentHP; }

private :
	
	// ���� ü��
	HP_t m_CurrentHP;

};


//////////////////////////////////////////////////////////////////////
//
// class GCHPRecoveryEndToSelfFactory;
//
// Factory for GCHPRecoveryEndToSelf
//
//////////////////////////////////////////////////////////////////////

class GCHPRecoveryEndToSelfFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCHPRecoveryEndToSelf(); }

	// get packet name
	string getPacketName() const throw() { return "GCHPRecoveryEndToSelf"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_HP_RECOVERY_END_TO_SELF; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCHPRecoveryEndToSelfPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szHP; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCHPRecoveryEndToSelfHandler;
//
//////////////////////////////////////////////////////////////////////

class GCHPRecoveryEndToSelfHandler {

public :

	// execute packet's handler
	static void execute(GCHPRecoveryEndToSelf* pPacket, Player* pPlayer) throw(Error);

};

#endif
