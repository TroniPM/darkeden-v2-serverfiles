//--------------------------------------------------------------------------------
// MonsterKillQuest.h
//--------------------------------------------------------------------------------

#ifndef __MONSTER_KILL_QUEST_H__
#define __MONSTER_KILL_QUEST_H__

#include "MonsterKillQuest.h"
#include "SimpleQuest.h"
#include "QuestFactoryManager.h"
#include "QuestUtil.h"
#include "MonsterSelector.h"
#include <list>
#include <vector>

//--------------------------------------------------------------------------------
// MonsterKillQuest
//--------------------------------------------------------------------------------
class MonsterKillQuest : public SimpleQuest, public MonsterSelector {
public :
	MonsterKillQuest(const MonsterSelector& mtc) throw (Error)
	: MonsterSelector(mtc)
	{
	}
	MonsterKillQuest(MonsterType_t monsterType, SpriteType_t spriteType, int number) throw (Error)
	: MonsterSelector(monsterType, spriteType, number)
	{
	}

	virtual ~MonsterKillQuest() throw (Error) {}

	virtual QuestType	getQuestType() const 	{ return QUEST_MONSTER_KILL; }

	virtual void		create();
	virtual void        save();

	virtual bool		checkSuccess(const QuestEvent* pQuestEvent);
	virtual bool		checkComplete();

public :
	virtual void        setObjective(const string& text) throw (Error)	{ MonsterSelector::setMonster(text); }
	virtual string      getObjectiveToString() 		{ return MonsterSelector::toString(); }

	string				toString() ;

};

//--------------------------------------------------------------------------------
// MonsterKillQuestFactory
//--------------------------------------------------------------------------------
class MonsterKillQuestFactory : public QuestFactory {
public :
	virtual Quest::QuestType	getQuestType() const { return Quest::QUEST_MONSTER_KILL; }
	virtual Quest*				create(const QuestCreateInfo* qcInfo=NULL) ;	

	static void		initMonsterTypeInfos();
	
private :
	typedef vector<MonsterSelector>	MonsterTypeInfos;	// ������ ���� ���� ����

	static MonsterTypeInfos	m_MonsterTypeInfos;
};

#endif

