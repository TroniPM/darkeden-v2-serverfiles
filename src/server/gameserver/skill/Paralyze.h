//////////////////////////////////////////////////////////////////////////////
// Filename    : Paralyze.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_PARALYZE_HANDLER_H__
#define __SKILL_PARALYZE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Paralyze;
//////////////////////////////////////////////////////////////////////////////

class Paralyze: public SkillHandler 
{
public:
	Paralyze()  {}
	~Paralyze()  {}
	
public:
    string getSkillHandlerName()  { return "Paralyze"; }
	SkillType_t getSkillType()  { return SKILL_PARALYZE; }

	void execute(Vampire* pVampire, ObjectID_t targetObject, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);

	void executeMonster(Zone* pZone, Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Paralyze g_Paralyze;

#endif // __SKILL_PARALYZE_HANDLER_H__
