//////////////////////////////////////////////////////////////////////
// 
// Filename    : CBillingServer.h 
// Written By  : reiot@ewestsoft.com
// Description : 로그인 서버용 메인 클래스
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CBILLING_SERVER_H__
#define __CBILLING_SERVER_H__

// include files
#include "Types.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////
//
// class CBillingServer
//
// 로그인 서버 자체를 나타내는 클래스이다.
//
//////////////////////////////////////////////////////////////////////

class CBillingServer {

public :
	
	// constructor
	CBillingServer ();
	
	// destructor
	~CBillingServer ();

	// intialize game server
	void init ();

	// start game server
	void start ();
	
	// stop game server
	void stop ();

};

// global variable declaration
extern CBillingServer * g_pCBillingServer;

#endif
