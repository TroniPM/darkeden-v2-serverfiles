//////////////////////////////////////////////////////////////////////////////
// Filename    : LoginServerManager.h
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __LOGIN_SERVER_MANANGER_H__
#define __LOGIN_SERVER_MANANGER_H__

#include "Types.h"
#include "Exception.h"
#include "Thread.h"
#include "DatagramSocket.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class LoginServerManager;
//
// �α��� �������� ����� �����ϴ� �������̴�.
// ���ο� �����ͱ׷� ���������� �ϳ� ������ ���ŷ ������� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////

class LoginServerManager : public Thread 
{
public:
	LoginServerManager();
	~LoginServerManager();

public:
	void init()  {}

	void stop();

	void run() ;

	void sendDatagram(Datagram* pDatagram) ;

	void sendPacket(const string& host, uint port, DatagramPacket* pPacket) ;

	void lock()  { m_Mutex.lock(); }
	void unlock()  { m_Mutex.unlock(); }

private:
	DatagramSocket* m_pDatagramSocket; // UDP ���� ����

	mutable Mutex 	m_Mutex;
};

// global variable declaration
extern LoginServerManager* g_pLoginServerManager;

#endif
