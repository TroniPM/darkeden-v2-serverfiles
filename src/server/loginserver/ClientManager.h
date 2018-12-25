//////////////////////////////////////////////////////////////////////
//
// Filename    : ClientManager.h
// Written by  : reiot@ewestsoft.com
// Description : �α��� ������ Ŭ���̾�Ʈ �Ŵ���
//
//////////////////////////////////////////////////////////////////////

#ifndef __LOGIN_CLIENT_MANAGER_H__
#define __LOGIN_CLIENT_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////
//
// class ClientManager;
//
// �α��� ������ ������ ��� �÷��̾���� ������� ó���ϸ�,
// ���ο� Ŭ���̾�Ʈ�� ���� �õ��� ó���Ѵ�.
//
// Ŭ���̾�Ʈ�� run()�� �α��� ���� ���μ����� ���� �����忡�� ���ư���.
// ����, Thread�� ��ӹ��� �ʿ䰡 ����. �׷���, Ŭ������ ������ ������
// Thread �� ��ӹ��� �ٸ� Ŭ������ �����ϴ�.
//
// *NOTES*
//
// LoginPlayerManager�� ClientManager�� ������ ����� ������ ���� ������,
// ��Ŷ �ڵ鷯���� ���� �����ϱ� ���ؼ��� �۷ι� ������ ���ǵǾ�� �Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class ClientManager {

public :

	// constructor
	ClientManager ();

	// destructor
	~ClientManager ();

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
extern ClientManager * g_pClientManager;

#endif
