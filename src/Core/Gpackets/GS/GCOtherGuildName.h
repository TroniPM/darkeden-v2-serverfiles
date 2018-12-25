//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCOtherGuildName.h 
// Written By  : Reiot
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_OTHER_GUILD_NAME_H__
#define __GC_OTHER_GUILD_NAME_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCOtherGuildName;
//
// ���� ������ Ư�� �÷��̾��� OtherGuildName �� �ٸ� �÷��̾�鿡�� ��ε�ĳ��Ʈ
// �� �� �����ϴ� ��Ŷ�̴�. ���ο� ĳ���͸�� OtherGuildName ��Ʈ���� ����Ÿ
// �ʵ�� ������ �ִ�.
//
//////////////////////////////////////////////////////////////////////

class GCOtherGuildName : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_OTHER_GUILD_NAME; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szObjectID + szGuildID + szBYTE + m_GuildName.size(); }

	// get packet name
	string getPacketName()  { return "GCOtherGuildName"; }
	
	// get packet's debug string
	string toString() ;

	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID( ObjectID_t objectID ) throw() { m_ObjectID = objectID; }

	// get/set Guild ID
	GuildID_t getGuildID()  { return m_GuildID; }
	void setGuildID( GuildID_t guildID ) throw() { m_GuildID = guildID; }

	// get/set Guild Name
	string getGuildName()  { return m_GuildName; }
	void setGuildName(const string& guildName) throw() { m_GuildName = guildName; }

private :

	ObjectID_t m_ObjectID;

	// Guild ID
	GuildID_t m_GuildID;

	// Guild Name
	string m_GuildName;

};


//////////////////////////////////////////////////////////////////////
//
// class GCOtherGuildNameFactory;
//
// Factory for GCOtherGuildName
//
//////////////////////////////////////////////////////////////////////

class GCOtherGuildNameFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCOtherGuildName(); }

	// get packet name
	string getPacketName()  { return "GCOtherGuildName"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_OTHER_GUILD_NAME; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCOtherGuildNamePacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  { return szObjectID + szGuildID + szBYTE + 30; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCOtherGuildNameHandler;
//
//////////////////////////////////////////////////////////////////////

class GCOtherGuildNameHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCOtherGuildName* pPacket, Player* pPlayer) ;

};

#endif
