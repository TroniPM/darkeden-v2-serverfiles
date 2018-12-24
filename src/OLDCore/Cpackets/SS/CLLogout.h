//////////////////////////////////////////////////////////////////////
// 
// Filename    : CLLogout.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CL_LOGOUT_H__
#define __CL_LOGOUT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CLLogout;
//
// Ŭ���̾�Ʈ�� �������� �α׾ƿ��� �˸��� ��Ŷ�̴�.
// data field �� ���� ������ getSize()�� 0 �� �����ϸ�, read(), write() 
// �޽��� �ƹ��� ���ҵ� ���� �ʴ´�.
//
//////////////////////////////////////////////////////////////////////

class CLLogout : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CL_LOGOUT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return 0; }

	// get packet name
	string getPacketName() const throw() { return "CLLogout"; }
	
	// get packet's debug string
	string toString() const throw() { return "CLLogout"; }

};


//////////////////////////////////////////////////////////////////////
//
// class CLLogoutFactory;
//
// Factory for CLLogout
//
//////////////////////////////////////////////////////////////////////

class CLLogoutFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CLLogout(); }

	// get packet name
	string getPacketName() const throw() { return "CLLogout"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CL_LOGOUT; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw() { return 0; }

};


//////////////////////////////////////////////////////////////////////
//
// class CLLogoutHandler;
//
//////////////////////////////////////////////////////////////////////

class CLLogoutHandler {

public:

	// execute packet's handler
	static void execute(CLLogout* pPacket, Player* player) throw(ProtocolException, Error);

};

#endif
