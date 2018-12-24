//////////////////////////////////////////////////////////////////////
//
// Filename    : LoginPlayerManager.h
// Written by  : reiot@ewestsoft.com
// Description : �α��� ������ �α��� �÷��̾� �Ŵ���
//
//////////////////////////////////////////////////////////////////////

#ifndef __LOGIN_PLAYER_MANAGER_H__
#define __LOGIN_PLAYER_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "PlayerManager.h"
#include "ServerSocket.h"

class LoginPlayer;

//////////////////////////////////////////////////////////////////////
//
// class LoginPlayerManager;
//
// �α��� ������ ������ ��� �÷��̾���� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class LoginPlayerManager : public PlayerManager {

public :

	// constructor
	LoginPlayerManager () throw ( Error );

	// destructor
	~LoginPlayerManager () throw ( Error );

public :

	// Ŭ���̾�Ʈ �Ŵ����� �ʱ�ȭ�Ѵ�.
	void init () throw ( Error );

	// accept new connection
	void acceptNewConnection () throw ( Error );

	// select() �ý������� ����ؼ� I/O Multiplexing�� �Ѵ�.
	void select () throw ( Error );

	// ������ ��� ������� �Է��� �Է� ���۷� �����Ѵ�.
	void processInputs () throw ( Error );

	// ������ ��� ������� ����� Ŭ���̾�Ʈ�� �����Ѵ�.
	void processOutputs () throw ( Error );

	// ������ ��� ������� ��Ŷ�� ó���Ѵ�.
	void processCommands () throw ( Error );

	// OOB ����Ÿ�� ó���Ѵ�. ^^;
	void processExceptions () throw ( Error );

public :

	// �α��� ������ ������ ��� �÷��̾�鿡�� Ư�� ��Ŷ�� �����Ѵ�.
	void broadcastPacket ( Packet * pPacket ) throw ( Error );

	// Ư�� ���̵��� �÷��̾�� Ư�� ��Ŷ�� �����Ѵ�.
	void sendPacket ( const string & id , Packet * pPacket ) throw ( Error );

	// �÷��̾� ��ü�� �߰��Ѵ�.
	void addPlayer ( Player * pPlayer ) throw ( DuplicatedException , Error );
	void addPlayer_NOLOCKED ( Player * pPlayer ) throw ( DuplicatedException , Error );

	// �÷��̾� ��ü�� �����Ѵ�.
	void deletePlayer ( SOCKET fd ) throw ( OutOfBoundException , NoSuchElementException , Error );
	void deletePlayer_NOLOCKED ( SOCKET fd ) throw ( OutOfBoundException , NoSuchElementException , Error );

	// �÷��̾� ��ü�� �����Ѵ�.
	LoginPlayer * getPlayer ( const string & PCName ) const throw ( NoSuchElementException , Error );
	LoginPlayer * getPlayer_NOLOCKED ( const string & PCName ) const throw ( NoSuchElementException , Error );

	// lock/unlock
	void lock () throw ( Error ) { m_Mutex.lock(); }
	void unlock () throw ( Error ) { m_Mutex.unlock(); }

	// get debug string
	string toString () const throw ();

private :

	// ���� ����
	ServerSocket * m_pServerSocket;

	// ���� ���� ��ũ���� ( for fast reference )
	SOCKET m_ServerFD;

	// �Ҽӵ� �÷��̾���� ���� ��ũ������ �����̴�.
	// m_XXXXFDs[0]�� ������̸�, m_XXXFDs[1]�� ������ select()�� �Ķ���ͷ� ���ȴ�.
	// �� select()�ϱ� ���� [0] -> [1] �� ���簡 �̷������ �Ѵ�.
	fd_set m_ReadFDs[2];
	fd_set m_WriteFDs[2];
	fd_set m_ExceptFDs[2];

	// select�� ���Ǵ� �ð�
	Timeval m_Timeout[2];

	// min_fd , max_fd
	// select()�� iterating �� �� �ӵ� ������ ���ؼ� ����Ѵ�.
	// ���� select()�� ù��° �Ķ���͸� ����ϱ� ���ؼ� ����Ѵ�.
	SOCKET m_MinFD;
	SOCKET m_MaxFD;

	// �α��� ������ ���� ������ ���� ������� �����ȴ�.
	// ����, mutex �� ������� �ʾƵ� �� ��ó�� ��������.. 
	// ���Ӽ����κ��� �����ͱ׷��� �޾Ƽ� ó���ϴ� ��ƾ�� 
	// �������� ������� �����ȴ�. ��, �� �����尡 LPM��
	// �÷��̾� �迭�� manipulate�� �� ���������� �߻���
	// ���ɼ��� ����. - -;
	mutable Mutex m_Mutex;

};

// external variable declaration
extern LoginPlayerManager * g_pLoginPlayerManager;

#endif
