//----------------------------------------------------------------------
// 
// Filename    : SGGuildInfo.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __SG_GUILD_INFO_H__
#define __SG_GUILD_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

#include "GuildInfo2.h"
#include "GuildMemberInfo2.h"


typedef slist<GuildInfo2*> GuildInfoList2;
typedef slist<GuildInfo2*>::const_iterator GuildInfoListConstItor2;

//----------------------------------------------------------------------
//
// class SGGuildInfo;
//
//----------------------------------------------------------------------

class SGGuildInfo : public Packet {

public:

	// constructor
	SGGuildInfo() ;

	// destructor
	~SGGuildInfo() ;
	
    void read(SocketInputStream& iStream) ;
		    
    void write(SocketOutputStream& oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_SG_GUILD_INFO; }
	
	// get packet's body size
	PacketSize_t getPacketSize() ; 

	// get packet name
	string getPacketName()  { return "SGGuildInfo"; }
	
	// get packet's debug string
	string toString() ;

public:

	// get guild info list num
	WORD getGuildInfoListNum()  { return m_GuildInfoList.size(); }

	// add GuildInfo
	void addGuildInfo( GuildInfo2* pGuildInfo ) throw() { m_GuildInfoList.push_front( pGuildInfo ); }

	// clear GuildInfoList
	void clearGuildInfoList() ;

	// pop front element in GuildInfoList
	GuildInfo2* popFrontGuildInfoList() throw()
	{
		if ( m_GuildInfoList.empty() )
			return NULL;

		GuildInfo2* pGuildInfo = m_GuildInfoList.front();
		m_GuildInfoList.pop_front();
		return pGuildInfo;
	}

private :

	// guild list
	GuildInfoList2 m_GuildInfoList;

};


//////////////////////////////////////////////////////////////////////
//
// class SGGuildInfoFactory;
//
// Factory for SGGuildInfo
//
//////////////////////////////////////////////////////////////////////

class SGGuildInfoFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new SGGuildInfo(); }

	// get packet name
	string getPacketName()  { return "SGGuildInfo"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_SG_GUILD_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	PacketSize_t getPacketMaxSize()  
	{ 
		return szWORD + GuildInfo2::getMaxSize() * 500;
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class SGGuildInfoHandler {
	
public:

	// execute packet's handler
	static void execute(SGGuildInfo* pPacket) ;

};

#endif
