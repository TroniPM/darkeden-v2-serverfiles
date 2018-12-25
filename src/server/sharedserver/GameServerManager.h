//////////////////////////////////////////////////////////////////////////////
// Filename    : GameServerManager.h
// Written by  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GAME_SERVER_MANAGER_H__
#define __GAME_SERVER_MANAGER_H__

#include "Thread.h"
#include "Types.h"
#include "Timeval.h"
#include "Exception.h"
#include "GameServerPlayer.h"
#include "ServerSocket.h"
#include "Mutex.h"


//////////////////////////////////////////////////////////////////////////////
//
// class GameServerManager;
//
//////////////////////////////////////////////////////////////////////////////

class GameServerManager : public Thread
{
public:
	GameServerManager();
	~GameServerManager();

public:

	// ����弭������ �޾Ƶ��̴� �ִ� ���Ӽ��� ��
	const static uint nMaxGameServers = 100;

	// initialize 
	void init();

	void run();

	// broadcast packet to all players
	void broadcast(Packet* pPacket);
	void broadcast(Packet* pPacket, Player* pPlayer);


	// select 
	void select() throw(TimeoutException, InterruptedException, Error);

	// process all inputs
	void processInputs() throw(IOException, Error);

	// process all outputs
	void processOutputs() throw(IOException, Error);

	// process all exceptions
	void processExceptions() throw(IOException, Error);
	
	// process all commands
	void processCommands() throw(IOException, Error);

	// accept new connection
	void acceptNewConnection();

	// add/delete player
	void addGameServerPlayer(GameServerPlayer* pGameServerPlayer) throw(DuplicatedException, Error);
	void deleteGameServerPlayer(SOCKET fd) throw(OutOfBoundException, NoSuchElementException, Error);

	// lock/unlock
	void lock() throw(Error) { m_Mutex.lock(); }
	void unlock() throw(Error) { m_Mutex.unlock(); }

	void heartbeat();

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


	// ���Ӽ����� ������ �迭. ���� ��ũ���͸� �ε����� ����Ѵ�.
	GameServerPlayer* m_pGameServerPlayers[nMaxGameServers];

};

// external variable declaration
extern GameServerManager* g_pGameServerManager;

#endif
