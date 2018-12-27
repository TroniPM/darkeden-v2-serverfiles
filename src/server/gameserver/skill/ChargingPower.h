//////////////////////////////////////////////////////////////////////////////
// Filename    : ChargingPower.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CHARGING_POWER_HANDLER_H__
#define __SKILL_CHARGING_POWER_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ChargingPower;
//////////////////////////////////////////////////////////////////////////////

class ChargingPower : public SkillHandler 
{
public:
	ChargingPower()  {}
	~ChargingPower()  {}
	
public:
    string getSkillHandlerName()  { return "ChargingPower"; }
	SkillType_t getSkillType()  { return SKILL_CHARGING_POWER; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ChargingPower g_ChargingPower;

#endif // __SKILL_CHARGING_POWER_HANDLER_H__
