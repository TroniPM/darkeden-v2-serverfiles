//////////////////////////////////////////////////////////////////////////////
// Filename    : GreatHeal.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_GREAT_HEAL2_HANDLER_H__
#define __SKILL_GREAT_HEAL2_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class GreatHeal;
//////////////////////////////////////////////////////////////////////////////

class GreatHeal2: public SkillHandler 
{
public:
	GreatHeal2()  {}
	~GreatHeal2()  {}
	
public:
    string getSkillHandlerName()  { return "GreatHeal2"; }
	SkillType_t getSkillType()  { return SKILL_GREAT_HEAL2; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern GreatHeal2 g_GreatHeal2;

#endif // __SKILL_GREAT_HEAL_HANDLER_H__
