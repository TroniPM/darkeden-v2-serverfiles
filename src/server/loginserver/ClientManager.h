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
	ClientManager () throw ( Error );

	// destructor
	~ClientManager () throw ( Error );

	// Ŭ���̾�Ʈ �Ŵ����� �ʱ�ȭ�Ѵ�.
	void init () throw ( Error );

	// Ŭ���̾�Ʈ �Ŵ����� �����Ѵ�.
	void start () throw ( Error );

	// Ŭ���̾�Ʈ �Ŵ����� �ߴ��Ѵ�.
	void stop () throw ( Error );

	// Ŭ���̾�Ʈ �Ŵ����� ���� �޽��
	void run () throw ( Error );

};

// external variable declaration
extern ClientManager * g_pClientManager;

#endif
