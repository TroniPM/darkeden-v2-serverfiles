//////////////////////////////////////////////////////////////////////////////
// Filename    : GreatHeal.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_GREAT_HEAL_HANDLER_H__
#define __SKILL_GREAT_HEAL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class GreatHeal;
//////////////////////////////////////////////////////////////////////////////

class GreatHeal: public SkillHandler 
{
public:
	GreatHeal()  {}
	~GreatHeal()  {}
	
public:
    string getSkillHandlerName()  { return "GreatHeal"; }
	SkillType_t getSkillType()  { return SKILL_GREAT_HEAL; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern GreatHeal g_GreatHeal;

#endif // __SKILL_GREAT_HEAL_HANDLER_H__
