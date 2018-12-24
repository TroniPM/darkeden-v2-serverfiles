//////////////////////////////////////////////////////////////////////////////
// Filename    : EventSave.h
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SAVE_H__
#define __SAVE_H__

#include "Event.h"

//////////////////////////////////////////////////////////////////////////////
// class EventSave;
// �� ĳ���͸� �ֱ������� �����ϵ��� ���ִ� �̺�Ʈ�̴�.
//////////////////////////////////////////////////////////////////////////////

class EventSave : public Event 
{
public:
	EventSave(GamePlayer* pGamePlayer) throw(Error);
	virtual ~EventSave() throw();

public:
	virtual EventClass getEventClass() const throw() { return EVENT_SAVE; }

	// get event life-cycle
	// EventSave �̺�Ʈ�� �ֱ������� ��� ����Ǿ�� �ϹǷ�, �����Ǿ�� �ȵȴ�.
	virtual bool isTemporary() const throw() { return false; }
	virtual bool isPermanent() const throw() { return true; }

	virtual void activate() throw(Error);
	
	virtual string toString() const throw() { return "EventSave Event"; }
};

#endif
