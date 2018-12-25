//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGRequestGuildMemberList.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_REQUER_GUILD_MEMBER_LIST_H__
#define __CG_REQUER_GUILD_MEMBER_LIST_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGRequestGuildMemberList;
//
//////////////////////////////////////////////////////////////////////

class CGRequestGuildMemberList : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_REQUEST_GUILD_MEMBER_LIST; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szGuildID; }

	// get packet name
	string getPacketName()  { return "CGRequestGuildMemberList"; }

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
// class CGRequestGuildMemberListFactory;
//
// Factory for CGRequestGuildMemberList
//
//////////////////////////////////////////////////////////////////////

class CGRequestGuildMemberListFactory : public PacketFactory {

public:
	
	// constructor
	CGRequestGuildMemberListFactory() throw() {}
	
	// destructor
	virtual ~CGRequestGuildMemberListFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGRequestGuildMemberList(); }

	// get packet name
	string getPacketName()  { return "CGRequestGuildMemberList"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_REQUEST_GUILD_MEMBER_LIST; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szGuildID; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGRequestGuildMemberListHandler;
//
//////////////////////////////////////////////////////////////////////

class CGRequestGuildMemberListHandler {

public:

	// execute packet's handler
	static void execute(CGRequestGuildMemberList* pCGRequestGuildMemberList, Player* pPlayer) throw(Error);

};

#endif
