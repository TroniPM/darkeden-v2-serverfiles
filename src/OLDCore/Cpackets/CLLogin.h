//--------------------------------------------------------------------------------
// 
// Filename    : CLLogin.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __CL_LOGIN_H__
#define __CL_LOGIN_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CLLogin;
//
// Ŭ���̾�Ʈ�� �α��� �������� ���ʿ� �����ϴ� ��Ŷ�̴�.
// ���̵�� �н����尡 ��ȣȭ�Ǿ� �ִ�.
//
//--------------------------------------------------------------------------------

// �ִ� MAC ADDRESS ����
#define	MAX_LENGTH_MAC	6	


class CLLogin : public Packet {
public:
	CLLogin() : m_LoginMode ( LOGIN_MODE_NORMAL ) {}

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CL_LOGIN; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw();

	// get packet name
	string getPacketName() const throw() { return "CLLogin"; }
	
	// get packet's debug string
	string toString() const throw();

public:

	// get/set player's id
	string getID() const throw() { return m_ID; }
	void setID(string id) throw() { m_ID = id; }

	// get/set player's password
	string getPassword() const throw() { return m_Password; }
	void setPassword(string password) throw() { m_Password = password; }

	string getCpsso() const throw() { return m_Cpsso; }
	void setCpsso(string cpsso) throw() { m_Cpsso = cpsso; }

	// get/set Cpsso imformation
	bool isNetmarble() const throw() { return m_bNetmarble; }
	void setNetmarble(bool netmarble) throw() { m_bNetmarble = netmarble; }

	bool isAdult() const throw() { return m_bAdult; }
	void setAdult(bool adult) throw() { m_bAdult = adult; }

	// add - inthesky
	bool checkMacAddress(string currentMac) const throw();
	string getMacAddress() const throw() { return m_strMacAddress; }

	const BYTE* getRareMacAddress() const { return m_cMacAddress; }

	void setWebLogin() { m_LoginMode = LOGIN_MODE_WEBLOGIN; }
	bool isWebLogin() const { return m_LoginMode == LOGIN_MODE_WEBLOGIN; }

private :

	// �÷��̾� ���̵�
	string m_ID;

	// �÷��̾� �н�����
	string m_Password;

	// �ݸ����� ������ �̻��� String
	string m_Cpsso;

	// ������ �޴� �� �ƴ����� ������ ������ ���� �ʿ䰡 �־ ��� ���� �߰�
	// Size ����� ���� �ʴ´�. (�ݸ����� Cpsso ����� ���� ������ ��� �ִ� ���� ����)
	bool m_bNetmarble;
	bool m_bAdult;

	BYTE m_cMacAddress[6];
	string m_strMacAddress;

	BYTE m_LoginMode;
};


//--------------------------------------------------------------------------------
//
// class CLLoginFactory;
//
// Factory for CLLogin
//
//--------------------------------------------------------------------------------

class CLLoginFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CLLogin(); }

	// get packet name
	string getPacketName() const throw() { return "CLLogin"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CL_LOGIN; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw() { return szint + 2048 + szBYTE + 30 + 6 + szBYTE; }

};


//--------------------------------------------------------------------------------
//
// class CLLoginHandler;
//
//--------------------------------------------------------------------------------

class CLLoginHandler {

public:

	// execute packet's handler
	static void execute(CLLogin* pPacket, Player* pPlayer) throw(ProtocolException, Error);

private :
	static bool checkFreePass(CLLogin* pPacket, Player* pPlayer) throw (ProtocolException, Error);
	static bool	checkNetMarbleClient (CLLogin* pPacket , Player* pPlayer) throw (ProtocolException , Error);
	static bool checkWebLogin( CLLogin* pPacket, Player* pPlayer ) throw ( ProtocolException, Error );
#if defined(__THAILAND_SERVER__)
	static bool onChildGuardTimeArea(int pm, int am, string enable);
#endif
};

#endif
