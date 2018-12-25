//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPcGetItem.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
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
	virtual ActionType_t getActionType()  { return ACTION_SUMMON_MONSTER; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public:
private:
	// �θ� ����, ������ ��ġ.
	MonsterType_t m_Type;
	ZoneCoord_t m_X;
	ZoneCoord_t m_Y;
	// �ɼ��� �����ֱ� ���� �κ�.
};


//////////////////////////////////////////////////////////////////////////////
// class ActionPcGetItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionSummonMonsterFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_SUMMON_MONSTER; }
	virtual string getActionName()  { return "SummonMonster"; }
	virtual Action* createAction()  { return new ActionSummonMonster(); }
};
#endif
