//////////////////////////////////////////////////////////////////////////////
// Filename    : EventAuth.h
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_AUTH_H__
#define __EVENT_AUTH_H__

#include "Event.h"

//////////////////////////////////////////////////////////////////////////////
// class EventAuth;
//////////////////////////////////////////////////////////////////////////////

class EventAuth : public Event 
{
public:
	EventAuth(GamePlayer* pGamePlayer) throw(Error);
	virtual ~EventAuth() throw();

public:
	virtual EventClass getEventClass()  { return EVENT_CLASS_AUTH; }

	virtual bool isTemporary()  { return false; }
	virtual bool isPermanent()  { return true; }

	virtual void activate() throw(Error);

	virtual string toString()  { return "Auth Event"; }
};

#endif
