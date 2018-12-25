////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionCanEnterQuestZone.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __CAN_ENTER_QUEST_ZONE_H__
#define __CAN_ENTER_QUEST_ZONE_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanEnterQuestZone;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanEnterQuestZone : public Condition 
{
public:
	virtual ConditionType_t getConditionType()  { return CONDITION_CAN_ENTER_QUEST_ZONE; }
	virtual bool isPassive()  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) ;
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() ;

public:
	ZoneID_t	m_QuestZoneID;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanEnterQuestZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanEnterQuestZoneFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType()  { return Condition::CONDITION_CAN_ENTER_QUEST_ZONE; }
    virtual Condition* createCondition()  { return new ConditionCanEnterQuestZone(); }
    virtual string getConditionName()  { return "CanEnterQuestZone"; }
};

#endif
