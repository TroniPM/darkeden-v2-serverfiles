//////////////////////////////////////////////////////////////////////////////
// Filename    : Rebuke.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_REBUKE_HANDLER_H__
#define __SKILL_REBUKE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Rebuke;
//////////////////////////////////////////////////////////////////////////////

class Rebuke : public SkillHandler 
{
public:
	Rebuke()  {}
	~Rebuke()  {}
	
public:
    string getSkillHandlerName()  { return "Rebuke"; }
	SkillType_t getSkillType()  { return SKILL_REBUKE; }

	void execute(Slayer* pSlayer,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Rebuke g_Rebuke;

#endif // __SKILL_REBUKE_HANDLER_H__
