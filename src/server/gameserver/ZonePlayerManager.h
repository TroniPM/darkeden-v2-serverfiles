//////////////////////////////////////////////////////////////////////
//
// Filename    : ZonePlayerManager.h
// Written by  : reiot@ewestsoft.com
// Description : 
//
//////////////////////////////////////////////////////////////////////

#ifndef __ZONE_PLAYER_MANAGER_H__
#define __ZONE_PLAYER_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "PlayerManager.h"
#include "Player.h"
#include "Socket.h"
#include "Mutex.h"
#include "Effect.h"

class GamePlayer;
class BroadcastFilter;

//////////////////////////////////////////////////////////////////////
//
// class ZonePlayerManager;
//
// ���� ZoneGroup�� �Ҽӵ� �÷��̾ �����ϴ� �Ŵ��� ��ü�̴�.
//
//////////////////////////////////////////////////////////////////////

class ZonePlayerManager : public PlayerManager {
public:
	typedef pair<BroadcastFilter*,SocketOutputStream*> PairFilterStream;

public:

	// constructor
	ZonePlayerManager() ;

	// destructor
	~ZonePlayerManager() ;

	// select 
	void select() throw(TimeoutException, InterruptedException, Error);

	// process all players' inputs
	void processInputs() throw(IOException, Error);

	// process all players' outputs
	void processOutputs() throw(IOException, Error);

	// process all players' exceptions
	void processExceptions() throw(IOException, Error);
	
	// process all players' commands
	void processCommands() throw(IOException, Error);

	// broadcast packet
	void broadcastPacket(Packet* pPacket);
	void broadcastPacket_NOBLOCKED(Packet* pPacket);
	void pushBroadcastPacket(Packet* pPacket, BroadcastFilter* pFilter=NULL);
	void flushBroadcastPacket();
	
	// add player to zone player manager
	void addPlayer(GamePlayer* pGamePlayer) throw(DuplicatedException, Error);
	void addPlayer_NOBLOCKED(GamePlayer* pGamePlayer) throw(DuplicatedException, Error);

	// delete player from zone player manager
	void deletePlayer(SOCKET fd) throw(OutOfBoundException, NoSuchElementException, Error);
	void deletePlayer_NOBLOCKED(SOCKET fd) throw(OutOfBoundException, NoSuchElementException, Error);
	void deletePlayer(Player* pPlayer) throw(OutOfBoundException, NoSuchElementException, Error)
	{
		deletePlayer(pPlayer->getSocket()->getSOCKET());
	}

	// get player
	Player* getPlayer(SOCKET fd) throw(OutOfBoundException, NoSuchElementException, Error) ;

	// get Player by PhoneNumber
	Player* getPlayerByPhoneNumber(PhoneNumber_t PhoneNumber) throw(OutOfBoundException, NoSuchElementException, Error);

	// All Member Save
	void save();

	void copyPlayers() ;

    // push Player to queue
    void pushPlayer(GamePlayer* pGamePlayer);
    void pushOutPlayer(GamePlayer* pGamePlayer);
	void processPlayerListQueue();

	// Queue's Player Add Manager
    void heartbeat();

	// delete Queue Player
	void deleteQueuePlayer(GamePlayer* pGamePlayer) throw(NoSuchElementException, Error);

	void    removeFlag (Effect::EffectClass EC);

	void lock()  { m_Mutex.lock(); }	
	void unlock()  { m_Mutex.unlock(); }	

	// ��� �÷��̾ �����Ѵ�.
	void clearPlayers();

	void setZGID( ZoneGroupID_t id ) { m_ZGID = id; }
	ZoneGroupID_t getZGID() const { return m_ZGID; }

#if defined(__THAILAND_SERVER__) 
	// add by inthesky for THAILAND ChildGuard rule
	bool onChildGuardTimeArea(int pm, int am, bool bSwitch);
#endif

private:

	// �Ҽӵ� �÷��̾���� ���� ��ũ������ �����̴�.
	// m_XXXXFDs[0]�� ������̸�, m_XXXFDs[1]�� ������ select()�� �Ķ���ͷ� ���ȴ�.
	// �� select()�ϱ� ���� [0] -> [1] �� ���簡 �̷������ �Ѵ�.
	fd_set m_ReadFDs[2];
	fd_set m_WriteFDs[2];
	fd_set m_ExceptFDs[2];

	// select�� ���Ǵ� �ð�
	Timeval m_Timeout[2];

	// min_fd, max_fd
	// select()�� iterating �� �� �ӵ� ������ ���ؼ� ����Ѵ�.
	// ���� select()�� ù��° �Ķ���͸� ����ϱ� ���ؼ� ����Ѵ�.
	SOCKET m_MinFD;
	SOCKET m_MaxFD;

	// mutex
	mutable Mutex m_Mutex;
	mutable Mutex m_Mutex2;
	mutable Mutex m_MutexBroadcast;

	list< GamePlayer* > m_PlayerListQueue;
	list< GamePlayer* > m_PlayerOutListQueue;
	list< PairFilterStream > m_BroadcastQueue;

	ZoneGroupID_t m_ZGID;

#if defined(__THAILAND_SERVER__) 
	//add by inthesky for THAILAND ChildGuard Rule
	bool    m_bChildGuard;
	int     m_nChildGuardStartTime;
	int     m_nChildGuardEndTime;
	int     m_nChildGuardKickTime;
	int     m_nChildGuardCheckTerm;
	Timeval m_tmChildGuardCheckTerm;
#endif
};

// external variable declaration
extern ZonePlayerManager* g_pZonePlayerManager;

#endif
