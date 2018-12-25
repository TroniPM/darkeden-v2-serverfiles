//////////////////////////////////////////////////////////////////////////////
// Filename    : GCWarScheduleList.h 
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_WAR_SCHEDULE_LIST_H__
#define __GC_WAR_SCHEDULE_LIST_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "Types.h"
#include <list>

#define MAX_WAR_NUM 20

struct WarScheduleInfo
{
	BYTE warType;		// 0 : ������ 1 : ������
	WORD year;
	BYTE month;
	BYTE day;
	BYTE hour;
	GuildID_t		challengerGuildID[5];
	string			challengerGuildName[5];
	GuildID_t		reinforceGuildID;
	string			reinforceGuildName;
};

typedef list<WarScheduleInfo*> 			WarScheduleInfoList;
typedef WarScheduleInfoList::const_iterator WarScheduleInfoListItor;

class GCWarScheduleList : public Packet
{
public:
	GCWarScheduleList() throw();
	virtual ~GCWarScheduleList() throw();

public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_GC_WAR_SCHEDULE_LIST; }
	PacketSize_t getPacketSize() ;
	string getPacketName()  { return "GCWarScheduleList"; }
	string toString() ;

public:
	void addWarScheduleInfo( WarScheduleInfo* warInfo ) throw() { m_WarScheduleList.push_back( warInfo ); }
	WarScheduleInfo* popWarScheduleInfo() throw();

private:
	WarScheduleInfoList m_WarScheduleList;
};

class GCWarScheduleListFactory : public PacketFactory {

public :
	
	Packet* createPacket() throw() { return new GCWarScheduleList(); }
	string getPacketName()  { return "GCWarScheduleList"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_WAR_SCHEDULE_LIST; }
	PacketSize_t getPacketMaxSize()  {
		return (
			szBYTE + 
			( szBYTE+szWORD+szBYTE+szBYTE+szBYTE+szGuildID*6+(szBYTE*16)*6 ) * MAX_WAR_NUM
		);
	}
};

class GCWarScheduleListHandler {
public :
	static void execute(GCWarScheduleList* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif // __GC_WAR_SCHEDULE_LIST_H__
