//////////////////////////////////////////////////////////////////////
//
// Filename    : PlayerManager.cc
// Written by  : reiot@ewestsoft.com
// Description : 
//
//////////////////////////////////////////////////////////////////////

// include files
#include "PlayerManager.h"
#include "Assert.h"
#include "SocketAPI.h"
#include "Socket.h"
#include "Player.h"
#include "gameserver/Creature.h"
#include "gameserver/Slayer.h"
#include <algorithm>


//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
PlayerManager::PlayerManager () 
	
: m_nPlayers(0)
{
	__BEGIN_TRY

	// �÷��̾� ������ �迭�� NULL �� �ʱ�ȭ�Ѵ�.
	for ( uint i = 0 ; i < nMaxPlayers ; i ++ )
		m_pPlayers[i] = NULL;

	// �÷��̾� ������ �迭�� NULL �� �ʱ�ȭ�Ѵ�.
	for ( uint i = 0 ; i < nMaxPlayers ; i ++ )
		m_pCopyPlayers[i] = NULL;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
PlayerManager::~PlayerManager () 
	
{
	__BEGIN_TRY

	for ( uint i = 0 ; i < nMaxPlayers ; i ++ ) {

		if ( m_pPlayers[i] != NULL ) {
			// �÷��̾� ��ü�� �����ϸ�, destructor���� ������ �����Ѵ�.
			delete m_pPlayers[i];
			m_pPlayers[i] = NULL;
		}
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void PlayerManager::broadcastPacket ( Packet * pPacket )
	
{
	__BEGIN_TRY

	for ( uint i = 0 ; i < nMaxPlayers ; i ++ ) {
		if ( m_pPlayers[i] != NULL ) {
			try {
				m_pPlayers[i]->sendPacket(pPacket);
			} catch (Throwable& t) {
				filelog("playerManager.log", "broadcastPacket: %s", t.toString().c_str());
			}
		}
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// Ư�� �÷��̾ �Ŵ����� �߰��Ѵ�.
//////////////////////////////////////////////////////////////////////
void PlayerManager::addPlayer ( Player * pPlayer ) 
	throw ( DuplicatedException , Error )
{
	__BEGIN_TRY

	SOCKET fd = pPlayer->getSocket()->getSOCKET();

	// bound check
	Assert( fd >= 0 && fd < (SOCKET)nMaxPlayers );

	// null check
	if ( m_pPlayers[ fd ] != NULL )
	{
		ofstream file("Socket_Error.txt", ios::out | ios::app);
		file << "socket descriptor duplicated" << endl;
		file.close();

		cout << "socket descriptor duplicated" << endl;
		throw DuplicatedException("socket descriptor duplicated");
	}

	// �������� �����͸� �����Ѵ�.
	m_pPlayers[ fd ] = pPlayer;

	// �÷��̾� ���ڸ� ������Ų��.
	m_nPlayers ++;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// Ư�� �÷��̾ �Ŵ������� �����Ѵ�.
// ��ü�� �������� ������, �������� NULL�� �����.
//////////////////////////////////////////////////////////////////////
void PlayerManager::deletePlayer ( SOCKET fd ) 
	throw ( OutOfBoundException , NoSuchElementException , Error )
{
	__BEGIN_TRY

	// bound check
	if ( fd < 0 || fd >= (SOCKET)nMaxPlayers )
		throw OutOfBoundException();

	// null check
	if ( m_pPlayers[ fd ] == NULL )
		throw NoSuchElementException();

	// �迭�� fd��°�� Ŭ�����Ѵ�.
	m_pPlayers[ fd ] = NULL;

	// �÷��̾� ���ڸ� ���ҽ�Ų��.
	m_nPlayers --;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// Ư�� �÷��̾� ��ü�� �����´�.
//////////////////////////////////////////////////////////////////////
Player * PlayerManager::getPlayer ( SOCKET fd ) 
	throw ( OutOfBoundException , NoSuchElementException , Error )
{
	__BEGIN_TRY

	// bound check
	if ( fd < 0 || fd >= (SOCKET)nMaxPlayers )
		throw OutOfBoundException();

	// null check
	if ( m_pPlayers[ fd ] == NULL )
		throw NoSuchElementException();

	return m_pPlayers[ fd ];

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// �÷��̾ �����Ѵ�.
//////////////////////////////////////////////////////////////////////
void PlayerManager::copyPlayers()
	
{
	__BEGIN_TRY

	for ( uint i = 0 ; i < nMaxPlayers ; i ++ ) {
		m_pCopyPlayers[i] = m_pPlayers[i];
	}

	__END_CATCH
}

