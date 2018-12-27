//----------------------------------------------------------------------
// 
// Filename    : GSAddGuild.h 
// Written By  : 
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __GS_ADD_GUILD_H__
#define __GS_ADD_GUILD_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class GSAddGuild;
//
// ���� �߰��� ����� ������ ��û�Ѵ�.
//
// *CAUTION*
//
//----------------------------------------------------------------------

class GSAddGuild : public Packet {

public:
	
    // Stream ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // Stream ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GS_ADD_GUILD; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  
	{ 
		return szBYTE +					// guild name length
			   m_GuildName.size() +		// guild name 
			   szBYTE +					// guild master length
			   m_GuildMaster.size() +	// guild master
			   szBYTE +					// guild intro length
			   m_GuildIntro.size() +	// guild intro
			   szGuildState +			// guild state
			   szGuildRace +			// guild race
			   szServerGroupID;			// server group ID
	}

	// get packet name
	string getPacketName()  { return "GSAddGuild"; }
	
	// get packet's debug string
	string toString() ;

public:

	// get/set guild Name
	const string& getGuildName()  { return m_GuildName; }
	void setGuildName( const string& name )  { m_GuildName = name; }

	// get/set guild master
	const string& getGuildMaster()  { return m_GuildMaster; }
	void setGuildMaster( const string& master )  { m_GuildMaster = master; }
	
	// get/set guild intro
	const string& getGuildIntro()  { return m_GuildIntro; }
	void setGuildIntro( const string& intro )  { m_GuildIntro = intro; }

	// get/set guild state
	GuildState_t getGuildState()  { return m_GuildState; }
	void setGuildState( GuildState_t state )  { m_GuildState = state; }

	// get/set guild race
	GuildRace_t getGuildRace()  { return m_GuildRace; }
	void setGuildRace( GuildRace_t race )  { m_GuildRace = race; }

	// get/set server group ID
	ServerGroupID_t getServerGroupID()  { return m_ServerGroupID; }
	void setServerGroupID( ServerGroupID_t serverGroupID )  { m_ServerGroupID = serverGroupID; }


private :

	// Guild Name
	string m_GuildName;

	// Guild Master
	string m_GuildMaster;

	// Guild Intro
	string m_GuildIntro;

	// Guild State
	GuildState_t m_GuildState;

	// Guild Race
	GuildRace_t m_GuildRace;

	// Server Group ID;
	ServerGroupID_t m_ServerGroupID;

};


//////////////////////////////////////////////////////////////////////
//
// class GSAddGuildFactory;
//
// Factory for GSAddGuild
//
//////////////////////////////////////////////////////////////////////

class GSAddGuildFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new GSAddGuild(); }

	// get packet name
	string getPacketName()  { return "GSAddGuild"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GS_ADD_GUILD; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  
	{ 
		return szBYTE +				// guild name length
			   30 +					// guild name max length
			   szBYTE +				// guild master length
			   20 + 				// guild manster max length
			   szBYTE +				// guild intro length
			   256 +				// guild intro max length
			   szGuildState +		// guild state size
			   szGuildRace +		// guild race
			   szServerGroupID;		// server group ID
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class GSAddGuildHandler {
	
public:

	// execute packet's handler
	static void execute(GSAddGuild* pPacket, Player* pPlayer) ;

};

#endif
