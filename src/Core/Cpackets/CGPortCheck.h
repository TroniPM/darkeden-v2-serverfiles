//----------------------------------------------------------------------
// 
// Filename    : CGPortCheck.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __CG_PORT_CHECK_H__
#define __CG_PORT_CHECK_H__

// include files
#include "DatagramPacket.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class CGPortCheck;
//
// �α��� �������� ����ڰ� ���� ������ �����Ϸ��� �� ��, �α��� ������
// �� ���� �������� � �ּҿ��� � ����ڰ� � ũ��ó�� �α�����
// ���̴�.. ��� �˷��ִ� ��Ŷ�̴�.
//
// *CAUTION*
//
// ���� ũ��ó �̸��� �ʿ��Ѱ�? �ϴ� �ǹ��� ���� �� �ְڴµ�, ������ ����
// ��츦 ��������� �ʿ��ϰ� �ȴ�. �α��� �����κ��� Slot3 ĳ���͸� ����
// �س���, ������ ���� ������ �����ؼ��� SLOT2 ĳ���͸� �ε��ش޶�� ��
// ���� �ִ� ���̴�. �̸� ���� ���ؼ�, CLSelectPC�� ������ ĳ���͸� 
// ���� �������� �˷���� �ϸ�, CGConnect ������ ĳ���� ���̵� �����ؼ�
// �ٷ� �ε��ϵ��� �ؾ� �Ѵ�.
//
//----------------------------------------------------------------------

class CGPortCheck : public DatagramPacket {

public:
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(Datagram & iDatagram) ;
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(Datagram & oDatagram) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_PORT_CHECK; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  
	{ 
		return szBYTE + m_PCName.size();		// PC name
	}

	// get packet name
	string getPacketName()  { return "CGPortCheck"; }
	
	// get packet's debug string
	string toString() ;

public:

	// get/set pcName
	string getPCName()  { return m_PCName; }
	void setPCName(const string& pcName) throw() { m_PCName = pcName; }

private :

	// PC name
	string m_PCName;
};


//////////////////////////////////////////////////////////////////////
//
// class CGPortCheckFactory;
//
// Factory for CGPortCheck
//
//////////////////////////////////////////////////////////////////////

class CGPortCheckFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CGPortCheck(); }

	// get packet name
	string getPacketName()  { return "CGPortCheck"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_PORT_CHECK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGPortCheckPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  
	{ 
		return szBYTE + 20;		// PC name
	}

};


//////////////////////////////////////////////////////////////////////
//
// class CGPortCheckHandler;
//
//////////////////////////////////////////////////////////////////////

class CGPortCheckHandler {
	
public:

	// execute packet's handler
	static void execute(CGPortCheck* pPacket) ;

};

#endif
