//----------------------------------------------------------------------
// 
// Filename    : SGModifyGuildOK.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __SG_MODIFY_GUILD_OK_H__
#define __SG_MODIFY_GUILD_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class SGModifyGuildOK;
//
// ���� �߰� �Ǿ����� ���Ӽ����� �˸���.
//
// *CAUTION*
//
//----------------------------------------------------------------------

class SGModifyGuildOK : public Packet {

public:
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream& iStream) throw(ProtocolException, Error);
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream& oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_SG_MODIFY_GUILD_OK; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szGuildID +  				// guild ID
			   szGuildState;				// guild state
	}

	// get packet name
	string getPacketName() const throw() { return "SGModifyGuildOK"; }
	
	// get packet's debug string
	string toString() const throw();

public:

	// get/set guildID
	GuildID_t getGuildID() const throw() { return m_GuildID; }
	void setGuildID( GuildID_t guildID ) throw() { m_GuildID = guildID; }

	// get/set GuildState
	GuildState_t getGuildState() const throw() { return m_GuildState; }
	void setGuildState( GuildState_t guildState ) throw() { m_GuildState = guildState; }

private :

	// GuildID
	GuildID_t m_GuildID;

	// Guild State
	GuildState_t m_GuildState;

};


//////////////////////////////////////////////////////////////////////
//
// class SGModifyGuildOKFactory;
//
// Factory for SGModifyGuildOK
//
//////////////////////////////////////////////////////////////////////

class SGModifyGuildOKFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new SGModifyGuildOK(); }

	// get packet name
	string getPacketName() const throw() { return "SGModifyGuildOK"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_SG_MODIFY_GUILD_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szGuildID +				// guild ID
			   szGuildState;
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class SGModifyGuildOKHandler {
	
public:

	// execute packet's handler
	static void execute(SGModifyGuildOK* pPacket) throw(ProtocolException, Error);

};

#endif
