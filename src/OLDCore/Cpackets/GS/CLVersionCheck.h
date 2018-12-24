//--------------------------------------------------------------------------------
// 
// Filename    : CLVersionCheck.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __CL_VERSION_CHECK_H__
#define __CL_VERSION_CHECK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CLVersionCheck;
//
// Ŭ���̾�Ʈ�� �α��� �������� ���ʿ� �����ϴ� ��Ŷ�̴�.
// ���̵�� �н����尡 ��ȣȭ�Ǿ� �ִ�.
//
//--------------------------------------------------------------------------------

class CLVersionCheck : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CL_VERSION_CHECK; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szDWORD; }

	// get packet name
	string getPacketName() const throw() { return "CLVersionCheck"; }
	
	// get packet's debug string
	string toString() const throw();

public:

	// get/set Client Version
	DWORD getVersion() const throw() { return m_Version; }
	void setVersion(DWORD Version) throw() { m_Version = Version; }

private :

	// Ŭ���̾�Ʈ ����
	DWORD m_Version;

};


//--------------------------------------------------------------------------------
//
// class CLVersionCheckFactory;
//
// Factory for CLVersionCheck
//
//--------------------------------------------------------------------------------

class CLVersionCheckFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CLVersionCheck(); }

	// get packet name
	string getPacketName() const throw() { return "CLVersionCheck"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CL_VERSION_CHECK; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw() { return szDWORD; }

};


//--------------------------------------------------------------------------------
//
// class CLVersionCheckHandler;
//
//--------------------------------------------------------------------------------

class CLVersionCheckHandler {

public:

	// execute packet's handler
	static void execute(CLVersionCheck* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
