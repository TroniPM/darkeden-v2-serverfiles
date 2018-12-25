//////////////////////////////////////////////////////////////////////
// 
// Filename    : TheOneServer.h 
// Written By  : reiot@ewestsoft.com
// Description : �α��� ������ ���� Ŭ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __THE_ONE_SERVER_H__
#define __THE_ONE_SERVER_H__

// �� ����� ���ԵǸ�, �α��� ���� ����� �ȴ�.
#ifndef __THE_ONE_SERVER__
#define __THE_ONE_SERVER__
#endif

// include files
#include "Types.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////
//
// class TheOneServer
//
// �α��� ���� ��ü�� ��Ÿ���� Ŭ�����̴�.
//
//////////////////////////////////////////////////////////////////////

class TheOneServer {

public :
	
	// constructor
	TheOneServer ();
	
	// destructor
	~TheOneServer ();

	// intialize game server
	void init ();

	// start game server
	void start ();
	
	// stop game server
	void stop ();

};

// global variable declaration
extern TheOneServer * g_pTheOneServer;

#endif
