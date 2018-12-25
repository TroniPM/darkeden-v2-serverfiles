//////////////////////////////////////////////////////////////////////
// 
// Filename    : GLIncomingConnectionError.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GL_INCOMING_CONNECTION_ERROR_H__
#define __GL_INCOMING_CONNECTION_ERROR_H__

// include files
#include "DatagramPacket.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GLIncomingConnectionError;
//
//////////////////////////////////////////////////////////////////////

class GLIncomingConnectionError : public DatagramPacket {

public :
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(Datagram & iDatagram) throw(ProtocolException, Error);
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(Datagram & oDatagram) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GL_INCOMING_CONNECTION_ERROR; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szBYTE + m_Message.size(); }

	// get packet name
	string getPacketName()  { return "GLIncomingConnectionError"; }
	
	// get packet's debug string
	string toString() ;

	// get/set error message
	string getMessage()  { return m_Message; }
	void setMessage(string message) throw() { m_Message = message; }

	// get/set player id
	string getPlayerID()  { return m_PlayerID; }
	void setPlayerID(string playerID) throw() { m_PlayerID = playerID; }

private :

	// error message
	string m_Message;

	// player id
	string m_PlayerID;

};


//////////////////////////////////////////////////////////////////////
//
// class GLIncomingConnectionErrorFactory;
//
// Factory for GLIncomingConnectionError
//
//////////////////////////////////////////////////////////////////////

class GLIncomingConnectionErrorFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GLIncomingConnectionError(); }

	// get packet name
	string getPacketName()  { return "GLIncomingConnectionError"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GL_INCOMING_CONNECTION_ERROR; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GLIncomingConnectionErrorPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  { return szBYTE + 128; }

};


//////////////////////////////////////////////////////////////////////
//
// class GLIncomingConnectionErrorHandler;
//
//////////////////////////////////////////////////////////////////////

class GLIncomingConnectionErrorHandler {
	
public :

	// execute packet's handler
	static void execute(GLIncomingConnectionError* pPacket) throw(ProtocolException, Error);

};

#endif
