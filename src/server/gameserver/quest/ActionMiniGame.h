//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionMiniGame.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_MINI_GAME_H__
#define __ACTION_MINI_GAME_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionMiniGame
//////////////////////////////////////////////////////////////////////////////

class ActionMiniGame : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_MINI_GAME; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;

public:
	int  getGameType()  { return m_GameType; }
	void setGameType(int gameType) throw() { m_GameType = gameType; }

private:
	int m_GameType;   // 말할 대사 아이디
};


//////////////////////////////////////////////////////////////////////////////
// class ActionMiniGameFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionMiniGameFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_MINI_GAME; }
	virtual string getActionName()  { return "MiniGame"; }
	virtual Action* createAction()  { return new ActionMiniGame(); }
};
#endif
