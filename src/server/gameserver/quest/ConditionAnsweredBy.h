//////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionAnsweredBy.h
// Written By  : 
// Description :
// PC�� NPC�� ������ ������� ��쿡 �߻��ϴ� ������̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ANSWEREDBY_H__
#define __ANSWEREDBY_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionAnsweredBy;
//////////////////////////////////////////////////////////////////////////////

class ConditionAnsweredBy : public Condition 
{
public:
	virtual ConditionType_t getConditionType()  { return CONDITION_ANSWERED_BY; }

	virtual bool isActive()  { return false;}
	virtual bool isPassive()  { return true; } // ��Ŷ�� ������ �ϴϱ�... passive condition�̴�.
	virtual bool isNeutral()  { return false; }

	virtual bool isSatisfied(Creature* pCreature1, Creature* pCreature2 = NULL, void* pParam = NULL) ;

	virtual void read(PropertyBuffer & propertyBuffer);

	virtual string toString() ;

public :
	ScriptID_t getScriptID(void) const { return m_ScriptID;}
	AnswerID_t getAnswerID(void) const { return m_AnswerID;}
	
	void setScriptID(ScriptID_t scriptID) { m_ScriptID = scriptID;}
	void setAnswerID(ScriptID_t answerID) { m_AnswerID = answerID;}

private :
	ScriptID_t m_ScriptID;
	AnswerID_t m_AnswerID;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionAnsweredByFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionAnsweredByFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType()  { return Condition::CONDITION_ANSWERED_BY; }
    virtual Condition* createCondition()  { return new ConditionAnsweredBy(); }
    virtual string getConditionName()  { return "AnsweredBy"; }
};

#endif
