//////////////////////////////////////////////////////////////////////////////
// Filename    : RainbowSlasher.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_RAINBOW_SLASHER_HANDLER_H__
#define __SKILL_RAINBOW_SLASHER_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class RainbowSlasher;
//////////////////////////////////////////////////////////////////////////////

class RainbowSlasher : public SkillHandler 
{
public:
	RainbowSlasher()  {}
	~RainbowSlasher()  {}
	
public:
    string getSkillHandlerName()  { return "RainbowSlasher"; }
	SkillType_t getSkillType()  { return SKILL_RAINBOW_SLASHER; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern RainbowSlasher g_RainbowSlasher;

#endif // __SKILL_RAINBOW_SLASHER_HANDLER_H__
