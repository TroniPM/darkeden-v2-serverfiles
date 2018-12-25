//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTeachSkill.h
// Written By  : 
// Description : 
// NPC�� �÷��̾�� ����� ������ �� �� ���̴� �׼��̴�.
// ���������δ� NPC�� ������ �� �� �ִ� ����� ��Ŷ����
// ������ �� ���̰�, ������ �۾����� ��Ŷ�� �պ��ϴ� ���̿� ó���ȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_HEIGHT_TEACH_SKILL_H__
#define __ACTION_HEIGHT_TEACH_SKILL_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

#define TEACH_SKILL_SLAYER  0
#define TEACH_SKILL_VAMPIRE 1

//////////////////////////////////////////////////////////////////////////////
// class ActionTeachSkill;
//////////////////////////////////////////////////////////////////////////////

class ActionHeightTeachSkill : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_HEIGHT_TEACH_SKILL; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;

private:
	SkillDomainType_t m_DomainType; // ������ �� ��ų�� ������
};


////////////////////////////////////////////////////////////////////////////////
// class ActionTeachSkillFactory;
////////////////////////////////////////////////////////////////////////////////

class ActionHeightTeachSkillFactory : public ActionFactory 
{
public :
	virtual ActionType_t getActionType()  { return Action::ACTION_HEIGHT_TEACH_SKILL; }
	virtual string getActionName()  { return "HeightTeachSkill"; }
	virtual Action* createAction()  { return new ActionHeightTeachSkill(); }

};

#endif
