//////////////////////////////////////////////////////////////////////////////
// Filename    : PoisonStorm.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_POISON_STORM_HANDLER_H__
#define __SKILL_POISON_STORM_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class PoisonStorm;
//////////////////////////////////////////////////////////////////////////////

class PoisonStorm : public SkillHandler 
{
public:
	PoisonStorm() throw() {}
	~PoisonStorm() throw() {}
	
public:
    string getSkillHandlerName()  { return "PoisonStorm"; }
	SkillType_t getSkillType()  { return SKILL_POISON_STORM; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern PoisonStorm g_PoisonStorm;

#endif // __SKILL_POISON_STORM_HANDLER_H__
