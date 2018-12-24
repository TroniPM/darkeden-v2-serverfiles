//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPcGetItem.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SUMMON_MONSTER_H__
#define __ACTION_SUMMON_MONSTER_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionPcGetItem
//////////////////////////////////////////////////////////////////////////////

class ActionSummonMonster : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_SUMMON_MONSTER; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
private:
	// 부를 몬스터, 생성될 위치.
	MonsterType_t m_Type;
	ZoneCoord_t m_X;
	ZoneCoord_t m_Y;
	// 옵션을 정해주기 위한 부분.
};


//////////////////////////////////////////////////////////////////////////////
// class ActionPcGetItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionSummonMonsterFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_SUMMON_MONSTER; }
	virtual string getActionName() const throw() { return "SummonMonster"; }
	virtual Action* createAction() const throw() { return new ActionSummonMonster(); }
};
#endif
