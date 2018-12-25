//////////////////////////////////////////////////////////////////////////////
// Filename    : Paralyze.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_FREEZE_RING2_HANDLER_H__
#define __SKILL_FREEZE_RING2_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Paralyze;
//////////////////////////////////////////////////////////////////////////////

class FreezeRing2: public SkillHandler 
{
public:
	FreezeRing2() throw() {}
	~FreezeRing2() throw() {}
	
public:
    string getSkillHandlerName()  { return "FreezeRing2"; }
	SkillType_t getSkillType()  { return SKILL_FREEZE_RING2; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern FreezeRing2 g_FreezeRing2;

#endif // __SKILL_PARALYZE_HANDLER_H__
