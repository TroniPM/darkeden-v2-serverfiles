//////////////////////////////////////////////////////////////////////////////
// Filename    : EventRegeneration.h
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENTREGENERATION_H__
#define __EVENTREGENERATION_H__

#include "Event.h"

//////////////////////////////////////////////////////////////////////////////
// class EventRegeneration;
//////////////////////////////////////////////////////////////////////////////

class EventRegeneration : public Event 
{
public:
	EventRegeneration(GamePlayer* pGamePlayer);
	virtual ~EventRegeneration() throw();

public:
	virtual EventClass getEventClass()  { return EVENT_CLASS_REGENERATION; }

	virtual bool isTemporary()  { return false; }
	virtual bool isPermanent()  { return true; }

	virtual void activate();
	
	virtual string toString()  { return "Regeneration Event"; }

};

#endif
