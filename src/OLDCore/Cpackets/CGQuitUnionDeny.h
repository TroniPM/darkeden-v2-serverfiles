//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGQuitUnionDeny.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_QUIT_UNION_DENY_H__
#define __CG_QUIT_UNION_DENY_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGQuitUnionDeny;
//
//////////////////////////////////////////////////////////////////////

class CGQuitUnionDeny : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_QUIT_UNION_DENY; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szGuildID; }

	// get packet name
	string getPacketName() const throw() { return "CGQuitUnionDeny"; }

	// get packet's debug string
	string toString() const throw();

	// get/set GuildID
	GuildID_t getGuildID() const throw() { return m_GuildID; }
	void setGuildID( GuildID_t GuildID ) throw() { m_GuildID = GuildID; }


private :

	// Guild ID
	GuildID_t m_GuildID;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGQuitUnionDenyFactory;
//
// Factory for CGQuitUnionDeny
//
//////////////////////////////////////////////////////////////////////

class CGQuitUnionDenyFactory : public PacketFactory {

public:
	
	// constructor
	CGQuitUnionDenyFactory() throw() {}
	
	// destructor
	virtual ~CGQuitUnionDenyFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGQuitUnionDeny(); }

	// get packet name
	string getPacketName() const throw() { return "CGQuitUnionDeny"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_QUIT_UNION_DENY; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szGuildID; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGQuitUnionDenyHandler;
//
//////////////////////////////////////////////////////////////////////

class CGQuitUnionDenyHandler {

public:

	// execute packet's handler
	static void execute(CGQuitUnionDeny* pCGQuitUnionDeny, Player* pPlayer) throw(Error);

};

#endif
