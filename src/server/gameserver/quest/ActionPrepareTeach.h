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
	virtual ActionType_t getActionType()  { return ACTION_PREPARE_TEACH; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public:
	SkillLevel_t getMaxLevel(void)  { return m_MaxLevel;}
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
	virtual ActionType_t getActionType()  { return Action::ACTION_PREPARE_TEACH; }
	virtual string getActionName()  { return "PrepareTeach"; }
	virtual Action* createAction()  { return new ActionPrepareTeach(); }

};

#endif
