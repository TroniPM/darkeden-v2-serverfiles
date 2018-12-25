//////////////////////////////////////////////////////////////////////////////
// Filename    : EventRefreshHolyLandPlayer.h
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_REFRESH_HOLY_LAND_PLAYER_H__
#define __EVENT_REFRESH_HOLY_LAND_PLAYER_H__

#include "Event.h"

//////////////////////////////////////////////////////////////////////////////
// class EventRefreshHolyLandPlayer
//////////////////////////////////////////////////////////////////////////////

class EventRefreshHolyLandPlayer : public Event 
{
public:
	EventRefreshHolyLandPlayer( GamePlayer* pGamePlayer ) throw();
	~EventRefreshHolyLandPlayer() throw() {}
			
public:
	virtual EventClass getEventClass()  { return EVENT_CLASS_REFRESH_HOLY_LAND_PLAYER; }
	virtual void activate();
	virtual string toString() ;

private:
};

#endif
