//////////////////////////////////////////////////////////////////////
// 
// Filename    : SharedServer.h 
// Written By  : reiot@ewestsoft.com
// Description : �α��� ������ ���� Ŭ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __SHARED_SERVER_H__
#define __SHARED_SERVER_H__

// �� ����� ���ԵǸ�, �α��� ���� ����� �ȴ�.
#ifndef __SHARED_SERVER__
#define __SHARED_SERVER__
#endif

// include files
#include "Types.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////
//
// class SharedServer
//
// �α��� ���� ��ü�� ��Ÿ���� Ŭ�����̴�.
//
//////////////////////////////////////////////////////////////////////

class SharedServer {

public :
	
	// constructor
	SharedServer ();
	
	// destructor
	~SharedServer ();

	// intialize game server
	void init ();

	// start game server
	void start ();
	
	// stop game server
	void stop ();

};

// global variable declaration
extern SharedServer * g_pSharedServer;

#endif
