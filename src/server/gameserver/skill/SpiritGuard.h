//////////////////////////////////////////////////////////////////////////////
// Filename    : SpiritGuard.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SPIRIT_GUARD_HANDLER_H__
#define __SKILL_SPIRIT_GUARD_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SpiritGuard;
//////////////////////////////////////////////////////////////////////////////

class SpiritGuard : public SkillHandler 
{
public:
	SpiritGuard() throw() {}
	~SpiritGuard() throw() {}
	
public:
    string getSkillHandlerName()  { return "SpiritGuard"; }
	SkillType_t getSkillType()  { return SKILL_SPIRIT_GUARD; }

	void execute(Slayer* pSlayer,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SpiritGuard g_SpiritGuard;

#endif // __SKILL_SPIRIT_GUARD_HANDLER_H__
