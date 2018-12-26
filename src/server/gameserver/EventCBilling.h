//////////////////////////////////////////////////////////////////////////////
// Filename    : EventCBilling.h
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_CBILLING_H__
#define __EVENT_CBILLING_H__

#include "Event.h"

//////////////////////////////////////////////////////////////////////////////
// class EventCBilling;
//////////////////////////////////////////////////////////////////////////////

class EventCBilling : public Event 
{
public:
	EventCBilling(GamePlayer* pGamePlayer);
	virtual ~EventCBilling() ;

public:
	virtual EventClass getEventClass()  { return EVENT_CLASS_CBILLING; }

	virtual bool isTemporary()  { return false; }
	virtual bool isPermanent()  { return true; }

	virtual void activate();
	
	virtual string toString()  { return "CBilling Event"; }

private:
	int		m_TrySendLoginCount;		// Login ��Ŷ�� ������ �õ� ȸ��

};

#endif
