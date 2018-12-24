//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCQueryResultCharacterName.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_QUERY_RESULT_CHARACTER_NAME_H__
#define __LC_QUERY_RESULT_CHARACTER_NAME_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCQueryResultCharacterName;
//
// Ŭ���̾�Ʈ�� �α��� �������� ���ʿ� �����ϴ� ��Ŷ�̴�.
// ���̵�� �н����尡 ��ȣȭ�Ǿ� �ִ�.
//
//////////////////////////////////////////////////////////////////////

class LCQueryResultCharacterName : public Packet {

public:

	// constructor
	LCQueryResultCharacterName() throw() : m_bExist(false) {}

public:

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_LC_QUERY_RESULT_CHARACTER_NAME; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szbool
			+ szBYTE + m_CharacterName.size(); 
	}

	// get packet name
	string getPacketName() const throw() { return "LCQueryResultCharacterName"; }
	
	// get packet's debug string
	string toString() const throw();

public:

	// get/set player id
	string getCharacterName() const throw() { return m_CharacterName; }
	void setCharacterName(const string & playerID) throw() { m_CharacterName = playerID; }

	// get/set player id's existence
	bool isExist() const throw() { return m_bExist; }
	void setExist(bool bExist = true) throw() { m_bExist = bExist; }

private :

	// player id
	string m_CharacterName;

	// player id's existence
	bool m_bExist;

};


//////////////////////////////////////////////////////////////////////
//
// class LCQueryResultCharacterNameFactory;
//
// Factory for LCQueryResultCharacterName
//
//////////////////////////////////////////////////////////////////////

class LCQueryResultCharacterNameFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new LCQueryResultCharacterName(); }

	// get packet name
	string getPacketName() const throw() { return "LCQueryResultCharacterName"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_LC_QUERY_RESULT_CHARACTER_NAME; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw()
	{ 
		return szbool
			+ szBYTE + 20; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LCQueryResultCharacterNameHandler;
//
//////////////////////////////////////////////////////////////////////

class LCQueryResultCharacterNameHandler {

public:

	// execute packet's handler
	static void execute(LCQueryResultCharacterName* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
