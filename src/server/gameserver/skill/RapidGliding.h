//////////////////////////////////////////////////////////////////////////////
// Filename    : RapidGliding.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_RAPID_GLIDING_HANDLER_H__
#define __SKILL_RAPID_GLIDING_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class RapidGliding;
//////////////////////////////////////////////////////////////////////////////

class RapidGliding : public SkillHandler 
{
public:
	RapidGliding() throw() {}
	~RapidGliding() throw() {}
	
public:
    string getSkillHandlerName()  { return "RapidGliding"; }
	SkillType_t getSkillType()  { return SKILL_RAPID_GLIDING; }

	void execute(Vampire* pVampire, ObjectID_t TargetObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern RapidGliding g_RapidGliding;

#endif // __SKILL_RAPID_GLIDING_HANDLER_H__
