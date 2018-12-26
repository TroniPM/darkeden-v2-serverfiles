//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCActiveGuildList.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_ACTIVE_GUILD_LIST_H__
#define __GC_ACTIVE_GUILD_LIST_H__

// include files
#include <slist>
#include "Packet.h"
#include "PacketFactory.h"
#include "GuildInfo.h"

typedef slist<GuildInfo*> GuildInfoList;
typedef slist<GuildInfo*>::const_iterator GuildInfoListConstItor;


//////////////////////////////////////////////////////////////////////
//
// class GCActiveGuildList;
//
// Ŭ���̾�Ʈ�� ��� ������� ��� ����Ʈ�� ������.
//
//////////////////////////////////////////////////////////////////////

class GCActiveGuildList : public Packet {

public :

	// constructor
	GCActiveGuildList() ;

	// destructor
	~GCActiveGuildList() ;
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_ACTIVE_GUILD_LIST; }
	
	// get packet's body size
	PacketSize_t getPacketSize() ;

	// get packet name
	string getPacketName()  { return "GCActiveGuildList"; }
	
	// get packet's debug string
	string toString() ;

public:

	BYTE getListNum()  { return m_GuildInfoList.size(); }

	// add GuildInfo
	void addGuildInfo( GuildInfo* pGuildInfo ) throw() { m_GuildInfoList.push_front( pGuildInfo ); }

	// clear GuildInfoList
	void clearGuildInfoList() ;

	// pop front Element in GuildInfoList
	GuildInfo* popFrontGuildInfoList() throw()
	{
		if ( !m_GuildInfoList.empty() )
		{
			GuildInfo* pGuildInfo = m_GuildInfoList.front();
			m_GuildInfoList.pop_front();
			return pGuildInfo;
		}
		return NULL;
	}


private :
	
	GuildInfoList m_GuildInfoList;	
};


//////////////////////////////////////////////////////////////////////
//
// class GCActiveGuildListFactory;
//
// Factory for GCActiveGuildList
//
//////////////////////////////////////////////////////////////////////

class GCActiveGuildListFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCActiveGuildList(); }

	// get packet name
	string getPacketName()  { return "GCActiveGuildList"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_ACTIVE_GUILD_LIST; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  { return szWORD + (GuildInfo::getMaxSize() * 5000); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCActiveGuildList;
//
//////////////////////////////////////////////////////////////////////

class GCActiveGuildListHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCActiveGuildList* pPacket, Player* pPlayer) ;

};

#endif
