//////////////////////////////////////////////////////////////////////////////
// Filename    : PassingHeal.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_PASSING_HEAL_HANDLER_H__
#define __SKILL_PASSING_HEAL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class PassingHeal;
//////////////////////////////////////////////////////////////////////////////

class PassingHeal: public SkillHandler 
{
public:
	PassingHeal()  {}
	~PassingHeal()  {}

public:
    string getSkillHandlerName()  { return "PassingHeal"; }
	SkillType_t getSkillType()  { return SKILL_PASSING_HEAL; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern PassingHeal g_PassingHeal;

#endif // __SKILL_PASSING_HEAL_HANDLER_H__
