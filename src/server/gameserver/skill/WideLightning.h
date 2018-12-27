//////////////////////////////////////////////////////////////////////////////
// Filename    : WideLightning.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_WIDE_LIGHTNING_HANDLER_H__
#define __SKILL_WIDE_LIGHTNING_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class WideLightning;
//////////////////////////////////////////////////////////////////////////////

class WideLightning : public SkillHandler 
{
public:
	WideLightning()  {}
	~WideLightning()  {}
	
public:
    string getSkillHandlerName()  { return "WideLightning"; }
	SkillType_t getSkillType()  { return SKILL_WIDE_LIGHTNING; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pCreature);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern WideLightning g_WideLightning;

#endif // __SKILL_WIDE_LIGHTNING_HANDLER_H__
