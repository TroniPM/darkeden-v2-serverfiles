//----------------------------------------------------------------------
// 
// Filename    : GCAddVampireCorpse.h 
// Written By  : Reiot
// 
//----------------------------------------------------------------------

#ifndef __GC_ADD_VAMPIRE_CORPSE_H__
#define __GC_ADD_VAMPIRE_CORPSE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "PCVampireInfo3.h"


//----------------------------------------------------------------------
//
// class GCAddVampireCorpse;
//
// �α����̳� ��Ż, �ڷ���Ʈ ������ �����̾ ���� ���� ���� ���, �Ǵ�
// �����̾ ������ �̵��� ���,(1) �̹� �� �����̾ ���� ������ ���� �ִ�
//(�� �� �����̾ ���� �ִ�..) ������ �����ϴ� PC�鿡�Դ� GCMove ��Ŷ��
// ��ε�ĳ��Ʈ�Ѵ�. �׷���,(2) �� �����̾ ó�� ���� �Ǵ� ������ �����ϴ�
// PC�鿡�Դ� GCAddVampireCorpse ��Ŷ�� ��ε�ĳ��Ʈ�Ѵ�. ����,(3) �� �����̾��
// �ڽ��� ���� ��ô�� �þ�(?) �ȿ� �����ϴ� �����̾���� ������ GCAddVampireCorpse��
// ��Ƽ� �ް� �ȴ�.
//
//----------------------------------------------------------------------

class GCAddVampireCorpse : public Packet {

public :

	// constructor
	GCAddVampireCorpse() throw() { m_TreasureCount = 0; }
	GCAddVampireCorpse(const PCVampireInfo3 & vampireInfo) throw() : m_VampireInfo(vampireInfo) {}

	
public :

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_ADD_VAMPIRE_CORPSE; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return m_VampireInfo.getSize() + szBYTE; }

	// get packet's name
	string getPacketName() const throw() { return "GCAddVampireCorpse"; }
	
	// get packet's debug string
	string toString() const throw();


public :

	// get vampire info
	PCVampireInfo3 & getVampireInfo() throw() { return m_VampireInfo; }
	const PCVampireInfo3 & getVampireInfo() const throw() { return m_VampireInfo; }
	void setVampireInfo(const PCVampireInfo3 & vampireInfo) throw() { m_VampireInfo = vampireInfo; }

	// get/set Treasure Count
	BYTE getTreasureCount() const throw() { return m_TreasureCount; }
	void setTreasureCount(BYTE Count) throw() { m_TreasureCount = Count; }
	
private :
	
	// �����̾� �ܸ� ����
	PCVampireInfo3 m_VampireInfo;

	BYTE m_TreasureCount;
	
};


//--------------------------------------------------------------------------------
//
// class GCAddVampireCorpseFactory;
//
// Factory for GCAddVampireCorpse
//
//--------------------------------------------------------------------------------

class GCAddVampireCorpseFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCAddVampireCorpse(); }

	// get packet name
	string getPacketName() const throw() { return "GCAddVampireCorpse"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_ADD_VAMPIRE_CORPSE; }

	// get packet's body size
	PacketSize_t getPacketMaxSize() const throw() { return PCVampireInfo3::getMaxSize() + szBYTE; }

};


//--------------------------------------------------------------------------------
//
// class GCAddVampireCorpseHandler;
//
//--------------------------------------------------------------------------------

class GCAddVampireCorpseHandler {

public :

	// execute packet's handler
	static void execute(GCAddVampireCorpse* pPacket, Player* pPlayer) throw(Error);

};

#endif
