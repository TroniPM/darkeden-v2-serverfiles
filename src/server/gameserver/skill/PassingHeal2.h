//////////////////////////////////////////////////////////////////////////////
// Filename    : PassingHeal.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_PASSING_HEAL2_HANDLER_H__
#define __SKILL_PASSING_HEAL2_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class PassingHeal;
//////////////////////////////////////////////////////////////////////////////

class PassingHeal2: public SkillHandler 
{
public:
	PassingHeal2()  {}
	~PassingHeal2()  {}

public:
    string getSkillHandlerName()  { return "PassingHeal2"; }
	SkillType_t getSkillType()  { return SKILL_PASSING_HEAL2; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern PassingHeal2 g_PassingHeal2;

#endif // __SKILL_PASSING_HEAL_HANDLER_H__
