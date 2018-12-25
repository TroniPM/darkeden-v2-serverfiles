//////////////////////////////////////////////////////////////////////////////
// Filename    : UDPManager.h
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __UDP_MANAGER_H__
#define __UDP_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Thread.h"
#include "DatagramSocket.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class UDPManager;
//
// �α��� �������� ����� �����ϴ� �������̴�.
// ���ο� �����ͱ׷� ���������� �ϳ� ������ ���ŷ ������� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////

class UDPManager 
{
public:
	UDPManager() throw(Error);
	~UDPManager() throw(Error);

public:
	void sendDatagram(Datagram* pDatagram) ;

	void sendPacket(const string& host, uint port, DatagramPacket* pPacket) ;


private:
	DatagramSocket* m_pDatagramSocket; // UDP ���� ����

};

// global variable declaration
extern UDPManager* g_pUDPManager;

#endif
