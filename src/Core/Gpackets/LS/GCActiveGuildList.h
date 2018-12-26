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
// 클라이언트에 등록 대기중인 길드 리스트를 보낸다.
//
//////////////////////////////////////////////////////////////////////

class GCActiveGuildList : public Packet {

public :

	// constructor
	GCActiveGuildList() ;

	// destructor
	~GCActiveGuildList() ;
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
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
	// const static GCSystemMessagePacketMaxSize 를 정의, 리턴하라.
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
