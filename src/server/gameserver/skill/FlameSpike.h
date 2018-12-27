//////////////////////////////////////////////////////////////////////////////
// Filename    : FirePiercing.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_FLAME_SPIKE_HANDLER_H__
#define __SKILL_FLAME_SPIKE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class FirePiercing;
//////////////////////////////////////////////////////////////////////////////

class FlameSpike : public SkillHandler 
{
public:
	FlameSpike()  {}
	~FlameSpike()  {}
	
public:
    string getSkillHandlerName()  { return "FlameSpike"; }
	SkillType_t getSkillType()  { return SKILL_FLAME_SPIKE; }

	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);
	void execute(Ousters* pOusters, ObjectID_t, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern FlameSpike g_FlameSpike;

#endif // __SKILL_FIRE_PIERCING_HANDLER_H__
