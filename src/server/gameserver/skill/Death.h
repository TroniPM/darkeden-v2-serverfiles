//////////////////////////////////////////////////////////////////////////////
// Filename    : Death.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DEATH_HANDLER_H__
#define __SKILL_DEATH_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Death;
//////////////////////////////////////////////////////////////////////////////

class Death : public SkillHandler 
{
public:
	Death()  {}
	~Death()  {}
	
public:
    string getSkillHandlerName()  { return "Death"; }
	SkillType_t getSkillType()  { return SKILL_DEATH; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);

	void executeMonster(Zone* pZone, Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Death g_Death;

#endif // __SKILL_DEATH_HANDLER_H__
