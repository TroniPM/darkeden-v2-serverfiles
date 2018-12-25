//////////////////////////////////////////////////////////////////////////////
// Filename    : SummonSylph.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SUMMON_SYLPH_HANDLER_H__
#define __SKILL_SUMMON_SYLPH_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SummonSylph;
//////////////////////////////////////////////////////////////////////////////

class SummonSylph : public SkillHandler 
{
public:
	SummonSylph() throw() {}
	~SummonSylph() throw() {}
	
public:
    string getSkillHandlerName()  { return "SummonSylph"; }
	SkillType_t getSkillType()  { return SKILL_SUMMON_SYLPH; }

	void execute(Ousters* pOusters,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);

//	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SummonSylph g_SummonSylph;

#endif // __SKILL_SUMMON_SYLPH_HANDLER_H__
