//////////////////////////////////////////////////////////////////////////////
// Filename    : ShadowOfStorm.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_LIGHTING_SHOCK_HANDLER_H__
#define __SKILL_LIGHTING_SHOCK_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ShadowOfStorm;
//////////////////////////////////////////////////////////////////////////////

class LightingShock : public SkillHandler 
{
public:
	LightingShock() throw() {}
	~LightingShock() throw() {}
	
public:
    string getSkillHandlerName()  { return "LightingShock"; }
	SkillType_t getSkillType()  { return SKILL_LIGHTING_SHOCK; }

	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern LightingShock g_LightingShock;

#endif // __SKILL_SHADOW_OF_STORM_HANDLER_H__
