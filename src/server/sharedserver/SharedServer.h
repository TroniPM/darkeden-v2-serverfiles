//////////////////////////////////////////////////////////////////////
// 
// Filename    : SharedServer.h 
// Written By  : reiot@ewestsoft.com
// Description : 로그인 서버용 메인 클래스
// 
//////////////////////////////////////////////////////////////////////

#ifndef __SHARED_SERVER_H__
#define __SHARED_SERVER_H__

// 이 모듈이 포함되면, 로그인 서버 모듈이 된다.
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
// 로그인 서버 자체를 나타내는 클래스이다.
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
