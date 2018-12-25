//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTeachSkill.h
// Written By  : 
// Description : 
// NPC�� �÷��̾�� ����� ������ �� �� ���̴� �׼��̴�.
// ���������δ� NPC�� ������ �� �� �ִ� ����� ��Ŷ����
// ������ �� ���̰�, ������ �۾����� ��Ŷ�� �պ��ϴ� ���̿� ó���ȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_TEACH_SKILL_H__
#define __ACTION_TEACH_SKILL_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

#define TEACH_SKILL_SLAYER  0
#define TEACH_SKILL_VAMPIRE 1

//////////////////////////////////////////////////////////////////////////////
// class ActionTeachSkill;
//////////////////////////////////////////////////////////////////////////////

class ActionTeachSkill : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_TEACH_SKILL; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;

public:
	virtual void executeSlayer(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual void executeVampire(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);

	SkillDomainType_t getDomainType(void)  { return m_DomainType;}
	void setDomainType(SkillDomainType_t domain) throw() { m_DomainType = domain;}

private:
	SkillDomainType_t m_DomainType; // ������ �� ��ų�� ������
};


////////////////////////////////////////////////////////////////////////////////
// class ActionTeachSkillFactory;
////////////////////////////////////////////////////////////////////////////////

class ActionTeachSkillFactory : public ActionFactory 
{
public :
	virtual ActionType_t getActionType()  { return Action::ACTION_TEACH_SKILL; }
	virtual string getActionName()  { return "TeachSkill"; }
	virtual Action* createAction()  { return new ActionTeachSkill(); }

};

#endif
