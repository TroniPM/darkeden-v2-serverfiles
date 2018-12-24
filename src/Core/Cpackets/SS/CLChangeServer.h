//////////////////////////////////////////////////////////////////////
// 
// Filename    : CLChangeServer.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CL_CHANGE_SERVER_H__
#define __CL_CHANGE_SERVER_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CLChangeServer;
//
//////////////////////////////////////////////////////////////////////

class CLChangeServer : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CL_CHANGE_SERVER; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szServerGroupID; }

	// get packet name
	string getPacketName() const throw() { return "CLChangeServer"; }

	// get / set ServerGroupID
	ServerGroupID_t getServerGroupID() const throw() { return m_ServerGroupID; }
	void setServerGroupID(ServerGroupID_t ServerGroupID) throw() { m_ServerGroupID = ServerGroupID; }
	
	// get packet's debug string
	string toString() const throw() { return "CLChangeServer"; }

private :

	ServerGroupID_t m_ServerGroupID;

};


//////////////////////////////////////////////////////////////////////
//
// class CLChangeServerFactory;
//
// Factory for CLChangeServer
//
//////////////////////////////////////////////////////////////////////

class CLChangeServerFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CLChangeServer(); }

	// get packet name
	string getPacketName() const throw() { return "CLChangeServer"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CL_CHANGE_SERVER; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw() { return szServerGroupID; }

};


//////////////////////////////////////////////////////////////////////
//
// class CLChangeServerHandler;
//
//////////////////////////////////////////////////////////////////////

class CLChangeServerHandler {

public:

	// execute packet's handler
	static void execute(CLChangeServer* pPacket, Player* player) throw(ProtocolException, Error);

};

#endif
