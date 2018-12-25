//////////////////////////////////////////////////////////////////////////////
// Filename    : SummonGoreGland.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SUMMON_DEADLY_GLAND_HANDLER_H__
#define __SKILL_SUMMON_DEADLY_GLAND_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SummonDeadlyGland;
//////////////////////////////////////////////////////////////////////////////

class SummonDeadlyGland : public SkillHandler 
{
public:
	SummonDeadlyGland() throw() {}
	~SummonDeadlyGland() throw() {}
	
public:
    string getSkillHandlerName()  { return "SummonDeadlyGland"; }
	SkillType_t getSkillType()  { return SKILL_SUMMON_DEADLY_GLAND; }

	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Vampire* pVampire, ObjectID_t,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SummonDeadlyGland g_SummonDeadlyGland;

#endif // __SKILL_SUMMON_GORE_GLAND_HANDLER_H__
