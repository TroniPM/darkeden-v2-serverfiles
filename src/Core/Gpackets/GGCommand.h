//----------------------------------------------------------------------
// 
// Filename    : GGCommand.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __GG_COMMAND_H__
#define __GG_COMMAND_H__

// include files
#include "DatagramPacket.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class GGCommand;
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

class GGCommand : public DatagramPacket {

public :
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(Datagram & iDatagram) throw(ProtocolException, Error);
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(Datagram & oDatagram) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GG_COMMAND; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szBYTE + m_Command.size();
	}

	// get packet name
	string getPacketName() const throw() { return "GGCommand"; }
	
	// get packet's debug string
	string toString() const throw();

public :

	// get/set playerID
	const string& getCommand() const throw() { return m_Command; }
	void setCommand(const string& command) throw() { m_Command = command; }
	
private :

	string m_Command;
};


//////////////////////////////////////////////////////////////////////
//
// class GGCommandFactory;
//
// Factory for GGCommand
//
//////////////////////////////////////////////////////////////////////

class GGCommandFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GGCommand(); }

	// get packet name
	string getPacketName() const throw() { return "GGCommand"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GG_COMMAND; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GGCommandPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szBYTE + 80;
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GGCommandHandler;
//
//////////////////////////////////////////////////////////////////////

class GGCommandHandler {
	
public :

	// execute packet's handler
	static void execute(GGCommand* pPacket) throw(ProtocolException, Error);

};

#endif
