//----------------------------------------------------------------------
// 
// Filename    : SGGuildMemberLogOnOK.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __SG_GUILDMEMBER_LOGON_OK_H__
#define __SG_GUILDMEMBER_LOGON_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class SGGuildMemberLogOnOK;
//
// ���� �߰� �Ǿ����� ���Ӽ����� �˸���.
//
// *CAUTION*
//
//----------------------------------------------------------------------

class SGGuildMemberLogOnOK : public Packet {

public:
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream& iStream) throw(ProtocolException, Error);
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream& oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_SG_GUILDMEMBER_LOGON_OK; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  
	{ 
		return szGuildID +			// guild ID
			   szBYTE +				// name length
			   m_Name.size() +		// name size
			   szbool +				// log on
			   szServerID;			// server id
	}

	// get packet name
	string getPacketName()  { return "SGGuildMemberLogOnOK"; }
	
	// get packet's debug string
	string toString() ;

public:

	// get/set guildID
	GuildID_t getGuildID()  { return m_GuildID; }
	void setGuildID( GuildID_t guildID ) throw() { m_GuildID = guildID; }

	// get/set guild name
	const string& getName()  { return m_Name; }
	void setName( const string& name ) throw() { m_Name = name; }

	// get/set logon
	bool getLogOn()  { return m_bLogOn; }
	void setLogOn( bool logOn ) throw() { m_bLogOn = logOn; }

	// get/set serverid
	ServerID_t	getServerID()  { return m_ServerID; }
	void		setServerID( ServerID_t ServerID ) throw() { m_ServerID = ServerID; }
	
private :

	// GuildID
	GuildID_t m_GuildID;

	// name
	string m_Name;

	// logon
	bool m_bLogOn;

	// serverid
	ServerID_t	m_ServerID;

};


//////////////////////////////////////////////////////////////////////
//
// class SGGuildMemberLogOnOKFactory;
//
// Factory for SGGuildMemberLogOnOK
//
//////////////////////////////////////////////////////////////////////

class SGGuildMemberLogOnOKFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new SGGuildMemberLogOnOK(); }

	// get packet name
	string getPacketName()  { return "SGGuildMemberLogOnOK"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_SG_GUILDMEMBER_LOGON_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  
	{ 
		return szGuildID +				// guild ID
			   szBYTE +					// name length
			   20 + 					// name max size
			   szbool +					// logon
			   szServerID;				// serverid
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class SGGuildMemberLogOnOKHandler {
	
public:

	// execute packet's handler
	static void execute(SGGuildMemberLogOnOK* pPacket) throw(ProtocolException, Error);

};

#endif
