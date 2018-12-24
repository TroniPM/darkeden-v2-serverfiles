//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCMPRecoveryEnd.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_MP_RECOVERY_END_H__
#define __GC_MP_RECOVERY_END_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "EffectInfo.h"


//////////////////////////////////////////////////////////////////////
//
// class GCMPRecoveryEnd;
//
////////////////////////////////////////////////////////////////////

class GCMPRecoveryEnd : public Packet {

public :

	GCMPRecoveryEnd() throw(Error);

	virtual ~GCMPRecoveryEnd() throw(Error);
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_MP_RECOVERY_END; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCMPRecoveryEndPacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szMP; 
	}

	// get packet's name
	string getPacketName() const throw() { return "GCMPRecoveryEnd"; }
	
	// get packet's debug string
	string toString() const throw();

public :

	// get /set CurrentMP
	MP_t getCurrentMP() const throw() { return m_CurrentMP; }
	void setCurrentMP(MP_t CurrentMP) throw() { m_CurrentMP = CurrentMP; }

private :
	
	// ���� ü��
	MP_t m_CurrentMP;

};


//////////////////////////////////////////////////////////////////////
//
// class GCMPRecoveryEndFactory;
//
// Factory for GCMPRecoveryEnd
//
//////////////////////////////////////////////////////////////////////

class GCMPRecoveryEndFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCMPRecoveryEnd(); }

	// get packet name
	string getPacketName() const throw() { return "GCMPRecoveryEnd"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_MP_RECOVERY_END; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCMPRecoveryEndPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szMP; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCMPRecoveryEndHandler;
//
//////////////////////////////////////////////////////////////////////

class GCMPRecoveryEndHandler {

public :

	// execute packet's handler
	static void execute(GCMPRecoveryEnd* pPacket, Player* pPlayer) throw(Error);

};

#endif
