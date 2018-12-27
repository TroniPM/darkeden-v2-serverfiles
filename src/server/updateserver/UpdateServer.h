//--------------------------------------------------------------------------------
// 
// Filename    : UpdateServer.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __UPDATE_SERVER_H__
#define __UPDATE_SERVER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Properties.h"
#include "ServerSocket.h"


//--------------------------------------------------------------------------------
//
// class UpdateServer
//
//--------------------------------------------------------------------------------

class UpdateServer {

public :
	
	// constructor
	UpdateServer ();
	
	// destructor
	~UpdateServer ();

	// intialize game server
	void init ();

	// start game server
	void start ();
	
	// stop game server
	void stop ();

	// main loop
	void run ();

private :

	// system level initialization
	void sysinit ();

	// become daemon
	void goBackground ();

	// update client
	void updateClient ( Socket * pClient );

	int getGuildMarkVersion()  { return m_GuildMarkVersion; }
	int getLastGuildMarkVersion()  { return m_LastGuildMarkVersion; }

private :

	ServerSocket* 	m_pServerSocket;
	int				m_GuildMarkVersion; 
	int				m_LastGuildMarkVersion; 

};


// global variable
extern UpdateServer * g_pUpdateServer;

#endif
