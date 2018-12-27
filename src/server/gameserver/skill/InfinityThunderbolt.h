//////////////////////////////////////////////////////////////////////////////
// Filename    : InfinityThunderbolt.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_INFINITY_THUNDERBOLT_HANDLER_H__
#define __SKILL_INFINITY_THUNDERBOLT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class InfinityThunderbolt;
//////////////////////////////////////////////////////////////////////////////

class InfinityThunderbolt : public SkillHandler 
{
public:
	InfinityThunderbolt()  {}
	~InfinityThunderbolt()  {}
	
public:
    string getSkillHandlerName()  { return "InfinityThunderbolt"; }
	SkillType_t getSkillType()  { return SKILL_INFINITY_THUNDERBOLT; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern InfinityThunderbolt g_InfinityThunderbolt;

#endif // __SKILL_INFINITY_THUNDERBOLT_HANDLER_H__
