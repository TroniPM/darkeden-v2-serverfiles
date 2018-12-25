
//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGRequestGuildList.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_REQUER_GUILD_LIST_H__
#define __CG_REQUER_GUILD_LIST_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

typedef BYTE GuildType_t;


//////////////////////////////////////////////////////////////////////
//
// class CGRequestGuildList;
//
//////////////////////////////////////////////////////////////////////

class CGRequestGuildList : public Packet
{
public:
	enum
	{
		GUILDTYPE_WAIT,             		// ��ϴ���� ���.
		GUILDTYPE_NORMAL,                   // ��ϵ� ���(�Ϲݱ��).
		GUILDTYPE_MAX
	};

	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_REQUEST_GUILD_LIST; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return sizeof(GuildType_t); }

	// get packet name
	string getPacketName()  { return "CGRequestGuildList"; }

	// get packet's debug string
	string toString() ;

	// get/set GuildType
	GuildType_t	getGuildType()	 {	return m_GuildType; }
	void		setGuildType( GuildType_t GuildType )	throw()	{ m_GuildType = GuildType; }
	
	GuildType_t	m_GuildType;
	

};


//////////////////////////////////////////////////////////////////////
//
// class CGRequestGuildListFactory;
//
// Factory for CGRequestGuildList
//
//////////////////////////////////////////////////////////////////////

class CGRequestGuildListFactory : public PacketFactory {

public:
	
	// constructor
	CGRequestGuildListFactory() throw() {}
	
	// destructor
	virtual ~CGRequestGuildListFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGRequestGuildList(); }

	// get packet name
	string getPacketName()  { return "CGRequestGuildList"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_REQUEST_GUILD_LIST; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return sizeof(GuildType_t); }
};


//////////////////////////////////////////////////////////////////////
//
// class CGRequestGuildListHandler;
//
//////////////////////////////////////////////////////////////////////

class CGRequestGuildListHandler {

public:

	// execute packet's handler
	static void execute(CGRequestGuildList* pCGRequestGuildList, Player* pPlayer) throw(Error);

};

#endif
