//--------------------------------------------------------------------------------
// 
// Filename    : CLQueryPlayerID.h 
// Written By  : Reiot
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __CL_QUERY_PLAYER_ID_H__
#define __CL_QUERY_PLAYER_ID_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CLQueryPlayerID;
//
// Ŭ���̾�Ʈ�� �α��� �������� ���ʿ� �����ϴ� ��Ŷ�̴�.
// ���̵�� �н����尡 ��ȣȭ�Ǿ� �ִ�.
//
//--------------------------------------------------------------------------------

class CLQueryPlayerID : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CL_QUERY_PLAYER_ID; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  
	{ 
		return szBYTE + m_PlayerID.size(); 
	}

	// get packet name
	string getPacketName()  { return "CLQueryPlayerID"; }
	
	// get packet's debug string
	string toString() ;

public:

	// get/set player's id
	string getPlayerID()  { return m_PlayerID; }
	void setPlayerID(const string & playerID) throw() { m_PlayerID = playerID; }

private :

	// �÷��̾� ���̵�
	string m_PlayerID;

};


//--------------------------------------------------------------------------------
//
// class CLQueryPlayerIDFactory;
//
// Factory for CLQueryPlayerID
//
//--------------------------------------------------------------------------------

class CLQueryPlayerIDFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CLQueryPlayerID(); }

	// get packet name
	string getPacketName()  { return "CLQueryPlayerID"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CL_QUERY_PLAYER_ID; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize()  
	{ 
		return szBYTE + 20; 
	}

};


//--------------------------------------------------------------------------------
//
// class CLQueryPlayerIDHandler;
//
//--------------------------------------------------------------------------------

class CLQueryPlayerIDHandler {

public:

	// execute packet's handler
	static void execute(CLQueryPlayerID* pPacket, Player* pPlayer) ;

};

#endif
