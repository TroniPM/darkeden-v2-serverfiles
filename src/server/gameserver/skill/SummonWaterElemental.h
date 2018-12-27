//////////////////////////////////////////////////////////////////////////////
// Filename    : SummonWaterElemental.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SUMMON_WATER_ELEMENTAL_HANDLER_H__
#define __SKILL_SUMMON_WATER_ELEMENTAL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SummonWaterElemental;
//////////////////////////////////////////////////////////////////////////////

class SummonWaterElemental : public SkillHandler 
{
public:
	SummonWaterElemental()  {}
	~SummonWaterElemental()  {}
	
public:
    string getSkillHandlerName()  { return "SummonWaterElemental"; }
	SkillType_t getSkillType()  { return SKILL_SUMMON_WATER_ELEMENTAL; }

	void execute(Ousters* pOusters,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SummonWaterElemental g_SummonWaterElemental;

#endif // __SKILL_SUMMON_WATER_ELEMENTAL_HANDLER_H__
