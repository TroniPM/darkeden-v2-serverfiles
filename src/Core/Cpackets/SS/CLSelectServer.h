//////////////////////////////////////////////////////////////////////
// 
// Filename    : CLSelectServer.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CL_SELECT_SERVER_H__
#define __CL_SELECT_SERVER_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CLSelectServer;
//
//////////////////////////////////////////////////////////////////////

class CLSelectServer : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CL_SELECT_SERVER; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szServerGroupID; }

	// get packet name
	string getPacketName() const throw() { return "CLSelectServer"; }

	// get / set ServerGroupID
	ServerGroupID_t getServerGroupID() const throw() { return m_ServerGroupID; }
	void setServerGroupID(ServerGroupID_t ServerGroupID) throw() { m_ServerGroupID = ServerGroupID; }
	
	// get packet's debug string
	string toString() const throw() { return "CLSelectServer"; }

private :

	ServerGroupID_t m_ServerGroupID;

};


//////////////////////////////////////////////////////////////////////
//
// class CLSelectServerFactory;
//
// Factory for CLSelectServer
//
//////////////////////////////////////////////////////////////////////

class CLSelectServerFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CLSelectServer(); }

	// get packet name
	string getPacketName() const throw() { return "CLSelectServer"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CL_SELECT_SERVER; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw() { return szServerGroupID; }

};


//////////////////////////////////////////////////////////////////////
//
// class CLSelectServerHandler;
//
//////////////////////////////////////////////////////////////////////

class CLSelectServerHandler {

public:

	// execute packet's handler
	static void execute(CLSelectServer* pPacket, Player* player) throw(ProtocolException, Error);

};

#endif
