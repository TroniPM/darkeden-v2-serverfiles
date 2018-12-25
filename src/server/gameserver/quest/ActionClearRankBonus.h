//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionClearRankBonus.h
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_CLEAR_RANK_BONUS_H__
#define __ACTION_CLEAR_RANK_BONUS_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionClearRankBonus;
//////////////////////////////////////////////////////////////////////////////

class ActionClearRankBonus : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_CLEAR_RANK_BONUS; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

private:
	Rank_t m_Rank;
};

//////////////////////////////////////////////////////////////////////////////
// class ActionClearRankBonusFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionClearRankBonusFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType()  { return Action::ACTION_CLEAR_RANK_BONUS; }
	virtual string getActionName()  { return "ClearRankBonus"; }
    virtual Action* createAction()  { return new ActionClearRankBonus(); }
};

#endif
