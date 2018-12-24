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
	virtual ActionType_t getActionType() const throw() { return ACTION_TEACH_SKILL; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
	virtual void executeSlayer(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual void executeVampire(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);

	SkillDomainType_t getDomainType(void) const throw() { return m_DomainType;}
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
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_TEACH_SKILL; }
	virtual string getActionName() const throw() { return "TeachSkill"; }
	virtual Action* createAction() const throw() { return new ActionTeachSkill(); }

};

#endif
