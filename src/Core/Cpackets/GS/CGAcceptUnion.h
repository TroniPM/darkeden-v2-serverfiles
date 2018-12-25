//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGAcceptUnion.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_ACCEPT_UNION_H__
#define __CG_ACCEPT_UNION_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGAcceptUnion;
//
//////////////////////////////////////////////////////////////////////

class CGAcceptUnion : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_ACCEPT_UNION; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szGuildID; }

	// get packet name
	string getPacketName()  { return "CGAcceptUnion"; }

	// get packet's debug string
	string toString() ;

	// get/set GuildID
	GuildID_t getGuildID()  { return m_GuildID; }
	void setGuildID( GuildID_t GuildID ) throw() { m_GuildID = GuildID; }


private :

	// Guild ID
	GuildID_t m_GuildID;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGAcceptUnionFactory;
//
// Factory for CGAcceptUnion
//
//////////////////////////////////////////////////////////////////////

class CGAcceptUnionFactory : public PacketFactory {

public:
	
	// constructor
	CGAcceptUnionFactory() throw() {}
	
	// destructor
	virtual ~CGAcceptUnionFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGAcceptUnion(); }

	// get packet name
	string getPacketName()  { return "CGAcceptUnion"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_ACCEPT_UNION; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szGuildID; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGAcceptUnionHandler;
//
//////////////////////////////////////////////////////////////////////

class CGAcceptUnionHandler {

public:

	// execute packet's handler
	static void execute(CGAcceptUnion* pCGAcceptUnion, Player* pPlayer) throw(Error);

};

#endif
