//--------------------------------------------------------------------------------
//
// Filename    : PlayerManager.h
// Written by  : reiot@ewestsoft.com
// Description : 
//
//--------------------------------------------------------------------------------

#ifndef __PLAYER_MANAGER_H__
#define __PLAYER_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Timeval.h"
#include "SocketAPI.h"
#include "Mutex.h"

// forward declaration
class Player;
class Packet;

//--------------------------------------------------------------------------------
//
// class PlayerManager;
//
// �÷��̾ �����ϴ� ��ü�̴�. ���� �ӵ��� ���ؼ� socket descriptor
// �� �ε����� �ϴ� �迭�� ����Ѵ�. �� �迭�� ũ��� ���� �������� 
// ó���� �� �ִ� �ִ� �÷��̾��� ����(������ �ִ� ����)�̴�.
// ��� �޸� ���� �ֱ� ������.. ������ �� ���� �����̴�.
//
// �� ���׷쿡 ��� 100���� �÷��̾ �ִٸ�, 
//
// 		900 x 4(byte) x 10(#ZoneGroup) = 36k 
//
// ������ ���� �ִ�.
//
//--------------------------------------------------------------------------------

class PlayerManager {

public :

	// ���� �÷��̾� �迭�� ũ��
	const static uint nMaxPlayers = 2000;

public :

	// constructor
	PlayerManager ();

	// destructor
	virtual ~PlayerManager ();

	// broadcast message
	virtual void broadcastPacket ( Packet * pPacket );

	// Ư�� �÷��̾ �Ŵ����� �߰��Ѵ�.
	virtual void addPlayer ( Player * pPlayer ) throw ( DuplicatedException , Error );

	// Ư�� �÷��̾ �Ŵ������� �����Ѵ�.
	virtual void deletePlayer ( SOCKET fd ) throw ( OutOfBoundException , NoSuchElementException , Error );

	// Ư�� �÷��̾� ��ü�� �����´�.
	virtual Player * getPlayer ( SOCKET fd ) throw ( OutOfBoundException , NoSuchElementException , Error );

	// Ư�� ���� ���� �÷��̾��� ��ü�� �����´�.
	virtual Player * getPlayerByPhoneNumber( PhoneNumber_t PhoneNumber ) throw( OutOfBoundException, NoSuchElementException, Error ) { return NULL; }

	// ���� �������� �÷��̾� ���ڸ� �����Ѵ�.
	uint size ()  { return m_nPlayers; }

	// Copy Player
	void copyPlayers() ;

protected :

	// �÷��̾��� �������� �迭�̴�. ���� ��ũ���͸� �ε����� ����Ѵ�.
	Player * m_pPlayers[nMaxPlayers];

	// number of Players
	uint m_nPlayers;

	// Player�� ���纻�� �����ϴ� ���̴�.
	Player * m_pCopyPlayers[nMaxPlayers];

};

#endif
