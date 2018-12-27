//////////////////////////////////////////////////////////////////////////////
// Filename    : FirePiercing.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_FIRE_PIERCING_HANDLER_H__
#define __SKILL_FIRE_PIERCING_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class FirePiercing;
//////////////////////////////////////////////////////////////////////////////

class FirePiercing : public SkillHandler 
{
public:
	FirePiercing()  {}
	~FirePiercing()  {}
	
public:
    string getSkillHandlerName()  { return "FirePiercing"; }
	SkillType_t getSkillType()  { return SKILL_FIRE_PIERCING; }

	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);
	void execute(Ousters* pOusters, ObjectID_t, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern FirePiercing g_FirePiercing;

#endif // __SKILL_FIRE_PIERCING_HANDLER_H__
