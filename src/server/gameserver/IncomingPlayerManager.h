//////////////////////////////////////////////////////////////////////////////
// Filename    : IncomingPlayerManager.h
// Written by  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __INCOMING_PLAYER_MANAGER_H__
#define __INCOMING_PLAYER_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "PlayerManager.h"
#include "GamePlayer.h"
#include "ServerSocket.h"
#include "DatagramSocket.h"
#include "ConnectionInfoManager.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class IncomingPlayerManager;
//
// PlayerManager�� ���� ������ ������ ��ü �÷��̾ ����ϸ�,
// ZonePlayerManager�� �� ���׷쿡 ���ӵ� �÷��̾���� ����ϴ� �ݸ�,
// IncomingPlayerManager�� ���� ������ ������ �̷�������� ���� ũ��ó��
// �ε����� ���� �ӽ����� ������ �÷��̾���� �����Ѵ�.
//
// ���ο� ������ ������ ��, ũ��ó�� �ε��ؼ� �÷��̾�� ������Ų��.
// ũ��ó�� �ε��Ǹ� �÷��̾� �� ũ��ó�� �ٸ� ���׷����� �Ѱ��ش�.
//////////////////////////////////////////////////////////////////////////////

class IncomingPlayerManager : public PlayerManager 
{
public:
	IncomingPlayerManager();
	~IncomingPlayerManager();

public:
	// initialize 
	void init();

	// broadcast packet to all players
	void broadcast(Packet* pPacket);

	// ������ �޽����� ZoneThread�� ���ؼ� ȣ��ȴ�.

	// select 
	void select() throw(TimeoutException, InterruptedException, Error);

	// process all players' inputs
	void processInputs() ;

	// process all players' outputs
	void processOutputs() ;

	// process all players' exceptions
	void processExceptions() ;
	
	// process all players' commands
	void processCommands() ;

	// accept new connection
	bool acceptNewConnection();

	void copyPlayers() ;

	// add/delete player
	void addPlayer(Player* pGamePlayer) throw(DuplicatedException, Error);
	void addPlayer_NOBLOCKED(Player* pGamePlayer) throw(DuplicatedException, Error);
	void deletePlayer(SOCKET fd) throw(OutOfBoundException, NoSuchElementException, Error);
	void deletePlayer_NOBLOCKED(SOCKET fd) throw(OutOfBoundException, NoSuchElementException, Error);

	// get Player by string
	GamePlayer* getPlayer_NOBLOCKED(const string & id) throw(NoSuchElementException, Error);
	GamePlayer* getPlayer(const string & id) throw(NoSuchElementException, Error);
	GamePlayer* getReadyPlayer(const string & id) throw(NoSuchElementException, Error);

	// lock/unlock
	void lock()  { m_Mutex.lock(); }
	void unlock()  { m_Mutex.unlock(); }

    // push Player to queue
    void pushPlayer(GamePlayer* pGamePlayer);

    void pushOutPlayer(GamePlayer* pGamePlayer);

    // Queue's Player Add Manager
	void heartbeat();

    void deleteQueuePlayer(GamePlayer* pGamePlayer) throw(NoSuchElementException, Error);

	// ��� �÷��̾ �����Ѵ�.
	void clearPlayers();

private:

	// TCP ���� ���ϰ� ���� ��ũ����
	ServerSocket* m_pServerSocket;
	SOCKET m_SocketID;

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

    list< GamePlayer* > m_PlayerListQueue;
	list< GamePlayer* > m_PlayerOutListQueue;

	int m_CheckValue;	// by sigi. for debugging. 2002.11.11

	mutable Mutex 	m_MutexOut;
};

// external variable declaration
extern IncomingPlayerManager* g_pIncomingPlayerManager;

#endif
