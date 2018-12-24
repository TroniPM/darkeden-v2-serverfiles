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
	CBillingServer () throw ( Error );
	
	// destructor
	~CBillingServer () throw ( Error );

	// intialize game server
	void init () throw ( Error );

	// start game server
	void start () throw ( Error );
	
	// stop game server
	void stop () throw ( Error );

};

// global variable declaration
extern CBillingServer * g_pCBillingServer;

#endif
