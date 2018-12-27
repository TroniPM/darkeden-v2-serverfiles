//////////////////////////////////////////////////////////////////////////////
// Filename    : Expansion.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_EXPANSION_HANDLER_H__
#define __SKILL_EXPANSION_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Expansion;
//////////////////////////////////////////////////////////////////////////////

class Expansion : public SkillHandler 
{
public:
	Expansion()  {}
	~Expansion()  {}
	
public:
    string getSkillHandlerName()  { return "Expansion"; }
	SkillType_t getSkillType()  { return SKILL_EXPANSION; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Expansion g_Expansion;

#endif // __SKILL_EXPANSION_HANDLER_H__
