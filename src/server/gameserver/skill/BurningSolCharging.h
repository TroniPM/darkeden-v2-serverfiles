//////////////////////////////////////////////////////////////////////////////
// Filename    : BurningSolCharging.h 
// Written By  : Sequoia
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BURNING_SOL_CHARGING_HANDLER_H__
#define __SKILL_BURNING_SOL_CHARGING_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BurningSolCharging;
//////////////////////////////////////////////////////////////////////////////

class BurningSolCharging : public SkillHandler 
{
public:
	BurningSolCharging()  {}
	~BurningSolCharging()  {}
	
public:
    string getSkillHandlerName()  { return "BurningSolCharging"; }
	SkillType_t getSkillType()  { return SKILL_BURNING_SOL_CHARGING; }

	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID);
//	void execute(Slayer* pSlayer,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BurningSolCharging g_BurningSolCharging;

#endif // __SKILL_BURNING_SOL_CHARGING_HANDLER_H__
