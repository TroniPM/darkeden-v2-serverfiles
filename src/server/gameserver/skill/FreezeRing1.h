//////////////////////////////////////////////////////////////////////////////
// Filename    : Paralyze.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_FREEZE_RING1_HANDLER_H__
#define __SKILL_FREEZE_RING1_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Paralyze;
//////////////////////////////////////////////////////////////////////////////

class FreezeRing1: public SkillHandler 
{
public:
	FreezeRing1() throw() {}
	~FreezeRing1() throw() {}
	
public:
    string getSkillHandlerName()  { return "FreezeRing1"; }
	SkillType_t getSkillType()  { return SKILL_FREEZE_RING1; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern FreezeRing1 g_FreezeRing1;

#endif // __SKILL_PARALYZE_HANDLER_H__
