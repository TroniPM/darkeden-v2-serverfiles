//////////////////////////////////////////////////////////////////////////////
// Filename    : TriggerManager.h
// Written By  : 
// Description :
// Ʈ���ŵ��� ������ �����ϴ� Ŭ����. ũ��ó/������/�� �� Ʈ���Ÿ� ����
// �� �ִ� ��ü�鿡 ���ӵȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __TRIGGER_MANAGER_H__
#define __TRIGGER_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Trigger.h"

//////////////////////////////////////////////////////////////////////////////
// class TriggerManager;
//////////////////////////////////////////////////////////////////////////////

class TriggerManager 
{
public:
	TriggerManager() throw(Error);
	~TriggerManager() throw(Error);

public:
	void load(const string & name) throw(Error);
	void load(ZoneID_t zoneid, int left, int top, int right, int bottom) throw(Error);

	void refresh() throw(Error);

	void addTrigger(Trigger* pTrigger) throw(DuplicatedException, Error);

	void deleteTrigger(TriggerID_t triggerID) throw(NoSuchElementException, Error);

	Trigger* getTrigger(TriggerID_t triggerID) throw(NoSuchElementException, Error);

	bool hasCondition(ConditionType_t conditionType) const throw() { return m_ConditionSet.test(conditionType); }

	list<Trigger*> & getTriggers() throw() { return m_Triggers; }
	const list<Trigger*> & getTriggers() const throw() { return m_Triggers; }

	string toString() const throw();

private:

	// bitset of condition for fastest reference
	ConditionSet m_ConditionSet;

	// list of triggers
	// ��Ÿ�ӿ� Ʈ���Ű� �߰��� ���ɼ��� �ִ�.
    list<Trigger*> m_Triggers;

};

#endif
