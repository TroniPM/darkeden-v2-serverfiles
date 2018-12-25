//////////////////////////////////////////////////////////////////////
// 
// Filename    : CLReconnectLogin.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CL_RECONNECT_LOGIN_H__
#define __CL_RECONNECT_LOGIN_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CLReconnectLogin;
//
// Ŭ���̾�Ʈ�� �������� ������ ���� ��Ŷ�̴�.
// ������ �̵��� ���Ǹ�, ���� ������ �� Key �� �� �������� �����ؼ�
// ������ �޴´�. ����, �� �������� ����� ũ��ó ���̵� ��� �ִ�.
//
//////////////////////////////////////////////////////////////////////

class CLReconnectLogin : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CL_RECONNECT_LOGIN; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  
	{ 
		return szDWORD + szBYTE; 						// authentication key
	}

	// get packet name
	string getPacketName()  { return "CLReconnectLogin"; }
	
	// get packet's debug string
	string toString() ;

public:

	// get/set key
	DWORD getKey()  { return m_Key; }
	void setKey(DWORD key) throw() { m_Key = key; }

	// Web login
	void setWebLogin() { m_LoginMode = LOGIN_MODE_WEBLOGIN; }
	bool isWebLogin() const { return m_LoginMode == LOGIN_MODE_WEBLOGIN; }

private :
	
	// authentication key
	DWORD m_Key;

	// Login Mode
	BYTE m_LoginMode;

};


//////////////////////////////////////////////////////////////////////
//
// class CLReconnectLoginFactory;
//
// Factory for CLReconnectLogin
//
//////////////////////////////////////////////////////////////////////

class CLReconnectLoginFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CLReconnectLogin(); }

	// get packet name
	string getPacketName()  { return "CLReconnectLogin"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CL_RECONNECT_LOGIN; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() 
	{ 
		return szDWORD + szBYTE; 			// authentication key
	}

};

//////////////////////////////////////////////////////////////////////
//
// class CLReconnectLoginHandler;
//
//////////////////////////////////////////////////////////////////////

class CLReconnectLoginHandler {

public:

	// execute packet's handler
	static void execute(CLReconnectLogin* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static bool onChildGuardTimeArea(int pm, int am, string enable);
};

#endif
