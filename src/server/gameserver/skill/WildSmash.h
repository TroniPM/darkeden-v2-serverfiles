//////////////////////////////////////////////////////////////////////////////
// Filename    : WildSmash.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_WILD_SMASH_HANDLER_H__
#define __SKILL_WILD_SMASH_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class WildSmash;
//////////////////////////////////////////////////////////////////////////////

class WildSmash : public SkillHandler 
{
public:
	WildSmash() throw() {}
	~WildSmash() throw() {}
	
public:
    string getSkillHandlerName()  { return "WildSmash"; }
	SkillType_t getSkillType()  { return SKILL_WILD_SMASH; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern WildSmash g_WildSmash;

#endif // __SKILL_WILD_SMASH_HANDLER_H__
