//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCQueryResultPlayerID.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_QUERY_RESULT_PLAYER_ID_H__
#define __LC_QUERY_RESULT_PLAYER_ID_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCQueryResultPlayerID;
//
// Ŭ���̾�Ʈ�� �α��� �������� ���ʿ� �����ϴ� ��Ŷ�̴�.
// ���̵�� �н����尡 ��ȣȭ�Ǿ� �ִ�.
//
//////////////////////////////////////////////////////////////////////

class LCQueryResultPlayerID : public Packet {

public:

	// constructor
	LCQueryResultPlayerID() throw() : m_bExist(false) {}

public:

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_LC_QUERY_RESULT_PLAYER_ID; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szbool
			+ szBYTE + m_PlayerID.size(); 
	}

	// get packet name
	string getPacketName() const throw() { return "LCQueryResultPlayerID"; }
	
	// get packet's debug string
	string toString() const throw();

public:

	// get/set player id
	string getPlayerID() const throw() { return m_PlayerID; }
	void setPlayerID(const string & playerID) throw() { m_PlayerID = playerID; }

	// get/set player id's existence
	bool isExist() const throw() { return m_bExist; }
	void setExist(bool bExist = true) throw() { m_bExist = bExist; }

private :

	// player id
	string m_PlayerID;

	// player id's existence
	bool m_bExist;

};


//////////////////////////////////////////////////////////////////////
//
// class LCQueryResultPlayerIDFactory;
//
// Factory for LCQueryResultPlayerID
//
//////////////////////////////////////////////////////////////////////

class LCQueryResultPlayerIDFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new LCQueryResultPlayerID(); }

	// get packet name
	string getPacketName() const throw() { return "LCQueryResultPlayerID"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_LC_QUERY_RESULT_PLAYER_ID; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw()
	{ 
		return szbool
			+ szBYTE + 20; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LCQueryResultPlayerIDHandler;
//
//////////////////////////////////////////////////////////////////////

class LCQueryResultPlayerIDHandler {

public:

	// execute packet's handler
	static void execute(LCQueryResultPlayerID* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
