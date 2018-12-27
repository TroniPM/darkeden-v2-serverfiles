//////////////////////////////////////////////////////////////////////////////
// Filename    : Trigger.h
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __TRIGGER_H__
#define __TRIGGER_H__

#include "Types.h"
#include "Exception.h"
#include <vector>
#include "Condition.h"

const string TriggerType2String [] = 
{
	"NPC_TRIGGER" ,
	"QUEST_TRIGGER",
	"MONSTER_TRIGGER"
};

//////////////////////////////////////////////////////////////////////////////
// class Trigger;
//////////////////////////////////////////////////////////////////////////////

class Action;
class Creature;

class Trigger 
{
public:
	enum TriggerType 
	{
		NPC_TRIGGER,
		QUEST_TRIGGER,
		MONSTER_TRIGGER
	};

	enum TriggerMode 
	{
		ACTIVE_TRIGGER,
		PASSIVE_TRIGGER,
		NEUTRAL_TRIGGER
	};

	const static char Comment;
	const static char Separator;
	const static char EOL;
	const static char* WhiteSpaces;
	const static char* SpaceTab;

public:
	Trigger();
	~Trigger();


public:
	void addCondition(Condition* pCondition);
	void addAction(Action* pAction);
	void addCounterAction(Action* pAction);
	bool hasCondition(ConditionType_t conditionType)  { return m_ConditionSet.test(conditionType); }
	bool isAllSatisfied(TriggerMode triggerMode, Creature* pCreature1, Creature* pCreature2 = NULL, void* pParam = NULL) ;
	bool activate(Creature* pCreature1, Creature* pCreature2 = NULL) ; 
	bool activateCounter(Creature* pCreature1, Creature* pCreature2 = NULL) ; 
	string toString() ;

public:
	TriggerType getTriggerType()  { return m_TriggerType; }
	void setTriggerType(TriggerType triggerType)  { m_TriggerType = triggerType; }
	void setTriggerType(const string & triggerType)  
	{ 
		if(triggerType == "NPC") m_TriggerType = NPC_TRIGGER; 
		else if(triggerType == "QUEST") m_TriggerType = QUEST_TRIGGER; 
		else if(triggerType == "MONSTER") m_TriggerType = MONSTER_TRIGGER; 
		else throw Error("invalid triggerType");
	}

	TriggerID_t getTriggerID()  { return m_TriggerID; }
	void setTriggerID(TriggerID_t triggerID)  { m_TriggerID = triggerID; }

	QuestID_t getQuestID()  { return m_QuestID; }
	void setQuestID(QuestID_t questID)  { m_QuestID = questID; }

	string getComment()  { return m_Comment; }
	void setComment(string comment)  { m_Comment = comment; }

	ConditionSet & getConditionSet()  { return m_ConditionSet; }
	const ConditionSet & getConditionSet()  { return m_ConditionSet; }

	void setConditions(const string & str);
	void setActions(const string & str);
	void setCounterActions(const string & str);



private:

	// Ʈ���� Ÿ��
	TriggerType m_TriggerType;

	// Ʈ���� ���̵�
	TriggerID_t m_TriggerID;

	// �����Ǵ� ����Ʈ ���̵�
	// m_TriggerType == QUEST_TRIGGER �� ��쿡�� �ǹ̰� �ִ�.
	QuestID_t m_QuestID;

	// bitset of conditions for fastest reference
	ConditionSet m_ConditionSet;

	// comment
	string m_Comment;

	// vector of conditions
	vector<Condition*> m_Conditions;

	// vector of actions
	vector<Action*> m_Actions;

	// vector of counter actions
	vector<Action*> m_CounterActions;

};

#endif
