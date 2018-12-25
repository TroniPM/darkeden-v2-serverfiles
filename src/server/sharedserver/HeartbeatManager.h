//////////////////////////////////////////////////////////////////////
//
// Filename    : HeartbeatManager.h
// Written by  : reiot@ewestsoft.com
// Description : �α��� ������ Ŭ���̾�Ʈ �Ŵ���
//
//////////////////////////////////////////////////////////////////////

#ifndef __HEARTBEAT_MANAGER_H__
#define __HEARTBEAT_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////
//
// class HeartbeatManager;
//
// �α��� ������ ������ ��� �÷��̾���� ������� ó���ϸ�,
// ���ο� Ŭ���̾�Ʈ�� ���� �õ��� ó���Ѵ�.
//
// Ŭ���̾�Ʈ�� run()�� �α��� ���� ���μ����� ���� �����忡�� ���ư���.
// ����, Thread�� ��ӹ��� �ʿ䰡 ����. �׷���, Ŭ������ ������ ������
// Thread �� ��ӹ��� �ٸ� Ŭ������ �����ϴ�.
//
//////////////////////////////////////////////////////////////////////

class HeartbeatManager {

public :

	// constructor
	HeartbeatManager ();

	// destructor
	~HeartbeatManager ();

	// Ŭ���̾�Ʈ �Ŵ����� �ʱ�ȭ�Ѵ�.
	void init ();

	// Ŭ���̾�Ʈ �Ŵ����� �����Ѵ�.
	void start ();

	// Ŭ���̾�Ʈ �Ŵ����� �ߴ��Ѵ�.
	void stop ();

	// Ŭ���̾�Ʈ �Ŵ����� ���� �޽��
	void run ();

};

// external variable declaration
extern HeartbeatManager * g_pHeartbeatManager;

#endif
