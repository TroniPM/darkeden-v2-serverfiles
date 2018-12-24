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
	PassingHeal2() throw() {}
	~PassingHeal2() throw() {}

public:
    string getSkillHandlerName() const throw() { return "PassingHeal2"; }
	SkillType_t getSkillType() const throw() { return SKILL_PASSING_HEAL2; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern PassingHeal2 g_PassingHeal2;

#endif // __SKILL_PASSING_HEAL_HANDLER_H__
