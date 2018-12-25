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
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CL_VERSION_CHECK; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szDWORD + szDWORD; }

	// get packet name
	string getPacketName()  { return "CLVersionCheck"; }
	
	// get packet's debug string
	string toString() ;

public:

	// get/set Client Version
	DWORD getVersion()  { return m_Version; }
	void setVersion(DWORD Version) throw() { m_Version = Version; }

	DWORD getServerVersion()  { return m_ServerVersion; }
	void setServerVersion(DWORD ServerVersion) throw() { m_ServerVersion= ServerVersion; }

private :

	// Ŭ���̾�Ʈ ����
	DWORD m_Version;
	DWORD m_ServerVersion;
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
	string getPacketName()  { return "CLVersionCheck"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CL_VERSION_CHECK; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize()  { return szDWORD + szDWORD; }

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
