//////////////////////////////////////////////////////////////////////
// 
// Filename    : CBillingServer.h 
// Written By  : reiot@ewestsoft.com
// Description : �α��� ������ ���� Ŭ����
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
// �α��� ���� ��ü�� ��Ÿ���� Ŭ�����̴�.
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
