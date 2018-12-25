//--------------------------------------------------------------------------------
// 
// Filename    : CLQueryCharacterName.h 
// Written By  : Reiot
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __CL_QUERY_CHARACTER_NAME_H__
#define __CL_QUERY_CHARACTER_NAME_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CLQueryCharacterName;
//
// Ŭ���̾�Ʈ�� �α��� �������� ���ʿ� �����ϴ� ��Ŷ�̴�.
// ���̵�� �н����尡 ��ȣȭ�Ǿ� �ִ�.
//
//--------------------------------------------------------------------------------

class CLQueryCharacterName : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CL_QUERY_CHARACTER_NAME; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  
	{ 
		return szBYTE + m_CharacterName.size(); 
	}

	// get packet name
	string getPacketName()  { return "CLQueryCharacterName"; }
	
	// get packet's debug string
	string toString() ;

public:

	// get/set player's id
	string getCharacterName()  { return m_CharacterName; }
	void setCharacterName(const string & playerID) throw() { m_CharacterName = playerID; }

private :

	// �÷��̾� ���̵�
	string m_CharacterName;

};


//--------------------------------------------------------------------------------
//
// class CLQueryCharacterNameFactory;
//
// Factory for CLQueryCharacterName
//
//--------------------------------------------------------------------------------

class CLQueryCharacterNameFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CLQueryCharacterName(); }

	// get packet name
	string getPacketName()  { return "CLQueryCharacterName"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CL_QUERY_CHARACTER_NAME; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize()  
	{ 
		return szBYTE + 20; 
	}

};


//--------------------------------------------------------------------------------
//
// class CLQueryCharacterNameHandler;
//
//--------------------------------------------------------------------------------

class CLQueryCharacterNameHandler {

public:

	// execute packet's handler
	static void execute(CLQueryCharacterName* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
