//////////////////////////////////////////////////////////////////////////////
// Filename    : GuildManager.h
// Written By  : �輺��
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GUILDMANAGER_H__
#define __GUILDMANAGER_H__

#include "Types.h"
#include "Assert.h"
#include "Exception.h"
#include "Mutex.h"
#include "Timeval.h"
#include <hash_map>

//////////////////////////////////////////////////////////////////////////////
// class GuildManager
// ���� Ȱ������ ���� ��� ������� ��带 �޸𸮿� map ���·� ������ �ְ�,
// ���ο� ����� ���/������ ����Ѵ�.
//
//////////////////////////////////////////////////////////////////////////////

class Guild;

typedef hash_map<GuildID_t, Guild*> HashMapGuild;
typedef hash_map<GuildID_t, Guild*>::iterator HashMapGuildItor;
typedef hash_map<GuildID_t, Guild*>::const_iterator HashMapGuildConstItor;

#ifdef __SHARED_SERVER__
class SGGuildInfo;
#endif

class GCWaitGuildList;
class GCActiveGuildList;
class PlayerCreature;

class GuildManager
{

///// Member methods /////
	
public: // constructor & destructor 
	GuildManager() throw();
	~GuildManager() throw();


public: // initializing related methods
	void init() throw();
	void load() throw();


public: // memory related methods
	void addGuild(Guild* pGuild) throw(DuplicatedException);
	void addGuild_NOBLOCKED(Guild* pGuild) throw(DuplicatedException);
	void deleteGuild(GuildID_t id) throw(NoSuchElementException);
	Guild* getGuild(GuildID_t id) throw();
	Guild* getGuild_NOBLOCKED(GuildID_t id) throw();

	void clear() throw();
	void clear_NOBLOCKED();


public: // misc methods
	ushort getGuildSize()  { return m_Guilds.size(); }
	HashMapGuild& getGuilds() throw() { return m_Guilds; }
	const HashMapGuild& getGuilds_const()  { return m_Guilds; }

#ifdef __SHARED_SERVER__
public:
	void makeSGGuildInfo( SGGuildInfo& sgGuildInfo ) throw();
#endif

	void makeWaitGuildList( GCWaitGuildList& gcWaitGuildList, GuildRace_t race ) throw();
	void makeActiveGuildList( GCActiveGuildList& gcWaitGuildList, GuildRace_t race ) throw();

public:
	void lock() { m_Mutex.lock(); }
	void unlock() { m_Mutex.unlock(); }


public:
	void heartbeat();

public:
	bool isGuildMaster( GuildID_t guildID, PlayerCreature* pPC );

	string getGuildName( GuildID_t guildID );

	// ��尡 ���� ������?
	bool hasCastle( GuildID_t guildID );
	bool hasCastle( GuildID_t guildID, ServerID_t& serverID, ZoneID_t& zoneID );

	// ��尡 �����û�� �߳�?
	bool hasWarSchedule( GuildID_t guildID );

	// ���� �������� ������ �ִ°�?
	bool hasActiveWar( GuildID_t guidlID );

public: // debug
	string toString(void) ;


///// Member data /////
	
protected:
	hash_map<GuildID_t, Guild*> m_Guilds;		// ��� ������ ��

	Timeval m_WaitMemberClearTime;				// heartbeat ���� Wait ���� ����� ���� �ð�

	// mutex
	mutable Mutex m_Mutex;
};

extern GuildManager* g_pGuildManager;

#endif // __GUILDINFO_H__
