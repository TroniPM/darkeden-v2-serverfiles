//////////////////////////////////////////////////////////////////////////////
// Filename    : EventMorph.h
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENTMORPH_H__
#define __EVENTMORPH_H__

#include "Event.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class EventMorph
//////////////////////////////////////////////////////////////////////////////

class EventMorph : public Event 
{
public:
	EventMorph(GamePlayer* pGamePlayer) throw();
	~EventMorph() throw();
			
public:
	virtual EventClass getEventClass()  { return EVENT_CLASS_MORPH; }
	virtual void activate();
	virtual string toString() ;

public:
	Creature* getCreature()  { return m_pTargetCreature; }
	void setCreature(Creature* pCreature) throw() { m_pTargetCreature = pCreature; }

private:
	Creature* m_pTargetCreature;
};

#endif
