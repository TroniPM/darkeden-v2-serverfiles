//////////////////////////////////////////////////////////////////////////////
// Filename    : ClientManager.h
// Written By  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __CLIENT_MANAGER_H__
#define __CLIENT_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Timeval.h"
#include "EventManager.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class ClientManager;
//////////////////////////////////////////////////////////////////////////////

class ClientManager 
{
public:
	ClientManager();
	~ClientManager();

public:
	void init();

	void start() throw(Error) { run(); }

	void stop();

	void run();

	string toString() ;

	void			setBalanceZoneGroup(int afterMinutes, bool bForce=false, bool bDefault=false);
	const Timeval&	getBalanceZoneGroupTime() const		{ return m_BalanceZoneGroupTime; }

	// by sigi. 2002.9.26
	void addEvent(Event* pEvent);
	void addEvent_LOCKED(Event* pEvent);
	bool deleteEvent(Event::EventClass EClass);

private :
	Timeval	m_BalanceZoneGroupTime;	// test -_-;
	bool	m_bForceZoneGroupBalancing;
	bool	m_bDefaultZoneGroupBalancing;

	mutable Mutex	m_Mutex;
	EventManager m_EventManager;
};

// glabal variable declaration
extern ClientManager* g_pClientManager;

#endif
