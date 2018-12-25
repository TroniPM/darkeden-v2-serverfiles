//////////////////////////////////////////////////////////////////////////////
// Filename    : DivineGuidance.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_VICIOUS_GUIDANCE_HANDLER_H__
#define __SKILL_VICIOUS_GUIDANCE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class DivineGuidance;
//////////////////////////////////////////////////////////////////////////////

class ViciousGuidance: public SkillHandler 
{
public:
	ViciousGuidance() throw() {}
	~ViciousGuidance() throw() {}

public:
    string getSkillHandlerName()  { return "ViciousGuidance"; }
	SkillType_t getSkillType()  { return SKILL_VICIOUS_GUIDANCE; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ViciousGuidance g_ViciousGuidance;

#endif // __SKILL_DIVINE_GUIDANCE_HANDLER_H__
