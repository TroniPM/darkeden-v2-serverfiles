//////////////////////////////////////////////////////////////////////
// 
// Filename    : LGIncomingConnectionError.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LG_INCOMING_CONNECTION_ERROR_H__
#define __LG_INCOMING_CONNECTION_ERROR_H__

// include files
#include "DatagramPacket.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionError;
//
//////////////////////////////////////////////////////////////////////

class LGIncomingConnectionError : public DatagramPacket {

public:
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(Datagram & iDatagram) throw(ProtocolException, Error);
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(Datagram & oDatagram) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_LG_INCOMING_CONNECTION_ERROR; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szBYTE + m_Message.size(); }

	// get packet name
	string getPacketName() const throw() { return "LGIncomingConnectionError"; }
	
	// get packet's debug string
	string toString() const throw();

	// get/set error message
	string getMessage() const throw() { return m_Message; }
	void setMessage(string message) throw() { m_Message = message; }

	// get/set player id
	string getPlayerID() const throw() { return m_PlayerID; }
	void setPlayerID(string playerID) throw() { m_PlayerID = playerID; }

private :

	// error message
	string m_Message;

	// player id
	string m_PlayerID;

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionErrorFactory;
//
// Factory for LGIncomingConnectionError
//
//////////////////////////////////////////////////////////////////////

class LGIncomingConnectionErrorFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new LGIncomingConnectionError(); }

	// get packet name
	string getPacketName() const throw() { return "LGIncomingConnectionError"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_LG_INCOMING_CONNECTION_ERROR; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionErrorPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + 128; }

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionErrorHandler;
//
//////////////////////////////////////////////////////////////////////

class LGIncomingConnectionErrorHandler {
	
public:

	// execute packet's handler
	static void execute(LGIncomingConnectionError* pPacket) throw(ProtocolException, Error);

};

#endif
