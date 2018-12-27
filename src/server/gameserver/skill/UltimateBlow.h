//////////////////////////////////////////////////////////////////////////////
// Filename    : UltimateBlow.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ULTIMATE_BLOW_HANDLER_H__
#define __SKILL_ULTIMATE_BLOW_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class UltimateBlow;
//////////////////////////////////////////////////////////////////////////////

class UltimateBlow : public SkillHandler 
{
public:
	UltimateBlow()  {}
	~UltimateBlow()  {}

public:
    string getSkillHandlerName()  { return "UltimateBlow"; }
	SkillType_t getSkillType()  { return SKILL_ULTIMATE_BLOW; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern UltimateBlow g_UltimateBlow;

#endif // __SKILL_ULTIMATE_BLOW_HANDLER_H__
