//////////////////////////////////////////////////////////////////////////////
// Filename    : GunShotGuidance.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_GUN_SHOT_GUIDANCE_HANDLER_H__
#define __SKILL_GUN_SHOT_GUIDANCE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class GunShotGuidance;
//////////////////////////////////////////////////////////////////////////////

class GunShotGuidance : public SkillHandler 
{
public:
	GunShotGuidance() throw() {}
	~GunShotGuidance() throw() {}
	
public:
    string getSkillHandlerName()  { return "GunShotGuidance"; }
	SkillType_t getSkillType()  { return SKILL_GUN_SHOT_GUIDANCE; }

	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, ObjectID_t,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Monster*, ZoneCoord_t X, ZoneCoord_t Y);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern GunShotGuidance g_GunShotGuidance;

#endif // __SKILL_GUN_SHOT_GUIDANCE_HANDLER_H__
