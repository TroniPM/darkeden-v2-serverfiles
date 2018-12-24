//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPrepareTeach.h
// Written By  : 
// Description : 
// ���� NPC�� ������ �� �� �ִ� ����� ������ ���ϴ� �׼��̴�.
// PrepareShop�� ����ϰ� AtFirst ������� �̿��Ͽ� ó��
// �ѹ��� �����ϰ� �ٽô� �������� �ʴ´�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_PREPARE_TEACH_H__
#define __ACTION_PREPARE_TEACH_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionPrepareTeach;
//////////////////////////////////////////////////////////////////////////////

class ActionPrepareTeach : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_PREPARE_TEACH; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
	SkillLevel_t getMaxLevel(void) const throw() { return m_MaxLevel;}
	void setMaxLevel(SkillLevel_t level) throw() { m_MaxLevel = level;}

private:
	SkillLevel_t m_MaxLevel; // ������ �� ��ų�� �ƽ� ����

};


//////////////////////////////////////////////////////////////////////////////
// class ActionPrepareTeachFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionPrepareTeachFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_PREPARE_TEACH; }
	virtual string getActionName() const throw() { return "PrepareTeach"; }
	virtual Action* createAction() const throw() { return new ActionPrepareTeach(); }

};

#endif
