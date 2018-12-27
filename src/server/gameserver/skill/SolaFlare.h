//////////////////////////////////////////////////////////////////////////////
// Filename    : ShadowOfStorm.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SOLA_FLARE_HANDLER_H__
#define __SKILL_SOLA_FLARE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ShadowOfStorm;
//////////////////////////////////////////////////////////////////////////////

class SolaFlare : public SkillHandler 
{
public:
	SolaFlare()  {}
	~SolaFlare()  {}
	
public:
    string getSkillHandlerName()  { return "SolaFlare"; }
	SkillType_t getSkillType()  { return SKILL_SOLA_FLARE; }

	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SolaFlare g_SolaFlare;

#endif // __SKILL_SHADOW_OF_STORM_HANDLER_H__
