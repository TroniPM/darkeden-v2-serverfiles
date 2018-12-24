//----------------------------------------------------------------------
// 
// Filename    : GCAddVampireFromBurrowing.h 
// Written By  : Reiot
// 
//----------------------------------------------------------------------

#ifndef __GC_ADD_VAMPIRE_FROM_BURROWING_H__
#define __GC_ADD_VAMPIRE_FROM_BURROWING_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "PCVampireInfo3.h"
#include "EffectInfo.h"

//----------------------------------------------------------------------
//
// class GCAddVampireFromBurrowing;
//
// �α����̳� ��Ż, �ڷ���Ʈ ������ �����̾ ���� ���� ���� ���, �Ǵ�
// �����̾ ������ �̵��� ���,(1) �̹� �� �����̾ ���� ������ ���� �ִ�
//(�� �� �����̾ ���� �ִ�..) ������ �����ϴ� PC�鿡�Դ� GCMove ��Ŷ��
// ��ε�ĳ��Ʈ�Ѵ�. �׷���,(2) �� �����̾ ó�� ���� �Ǵ� ������ �����ϴ�
// PC�鿡�Դ� GCAddVampireFromBurrowing ��Ŷ�� ��ε�ĳ��Ʈ�Ѵ�. ����,(3) �� �����̾��
// �ڽ��� ���� ��ô�� �þ�(?) �ȿ� �����ϴ� �����̾���� ������ GCAddVampireFromBurrowing��
// ��Ƽ� �ް� �ȴ�.
//
//----------------------------------------------------------------------

class GCAddVampireFromBurrowing : public Packet {

public :

	// constructor
	GCAddVampireFromBurrowing() throw() : m_pEffectInfo(NULL) {}
	GCAddVampireFromBurrowing(const PCVampireInfo3 & vampireInfo) throw() : m_VampireInfo(vampireInfo), m_pEffectInfo(NULL) {}

	virtual ~GCAddVampireFromBurrowing() throw();

	
public :

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_ADD_VAMPIRE_FROM_BURROWING; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return m_VampireInfo.getSize() + m_pEffectInfo->getSize(); }

	// get packet's name
	string getPacketName() const throw() { return "GCAddVampireFromBurrowing"; }
	
	// get packet's debug string
	string toString() const throw();


public :

	// get/set vampire info
	PCVampireInfo3 & getVampireInfo() throw() { return m_VampireInfo; }
	const PCVampireInfo3 & getVampireInfo() const throw() { return m_VampireInfo; }
	void setVampireInfo(const PCVampireInfo3 & vampireInfo) throw() { m_VampireInfo = vampireInfo; }

	// get /set Effect Info
	EffectInfo* getEffectInfo() const throw() { return m_pEffectInfo; }
	void setEffectInfo(EffectInfo* pEffectInfo) throw() { m_pEffectInfo = pEffectInfo; }


private :
	
	// �����̾� �ܸ� ����
	PCVampireInfo3 m_VampireInfo;

	// ����Ʈ ����
	EffectInfo* m_pEffectInfo;
	
};


//--------------------------------------------------------------------------------
//
// class GCAddVampireFromBurrowingFactory;
//
// Factory for GCAddVampireFromBurrowing
//
//--------------------------------------------------------------------------------

class GCAddVampireFromBurrowingFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCAddVampireFromBurrowing(); }

	// get packet name
	string getPacketName() const throw() { return "GCAddVampireFromBurrowing"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_ADD_VAMPIRE_FROM_BURROWING; }

	// get packet's body size
	PacketSize_t getPacketMaxSize() const throw()
	{ 
		return PCVampireInfo3::getMaxSize() + EffectInfo::getMaxSize();
	}

};


//--------------------------------------------------------------------------------
//
// class GCAddVampireFromBurrowingHandler;
//
//--------------------------------------------------------------------------------

class GCAddVampireFromBurrowingHandler {

public :

	// execute packet's handler
	static void execute(GCAddVampireFromBurrowing* pPacket, Player* pPlayer) throw(Error);

};

#endif
