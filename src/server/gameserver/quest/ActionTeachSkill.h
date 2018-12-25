//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTeachSkill.h
// Written By  : 
// Description : 
// NPC가 플레이어에게 기술을 가르쳐 줄 때 쓰이는 액션이다.
// 실제적으로는 NPC가 가르쳐 줄 수 있는 기술을 패킷으로
// 전송해 줄 뿐이고, 나머지 작업들은 패킷이 왕복하는 사이에 처리된다.
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
	SkillDomainType_t m_DomainType; // 가르쳐 줄 스킬의 도메인
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
