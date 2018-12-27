//////////////////////////////////////////////////////////////////////////////
// Filename    : BombCrashWalk.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BOMB_CRASH_WALK_HANDLER_H__
#define __SKILL_BOMB_CRASH_WALK_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BombCrashWalk;
//////////////////////////////////////////////////////////////////////////////

class BombCrashWalk : public SkillHandler 
{
public:
	BombCrashWalk()  {}
	~BombCrashWalk()  {}
	
public:
    string getSkillHandlerName()  { return "BombCrashWalk"; }
	SkillType_t getSkillType()  { return SKILL_BOMB_CRASH_WALK; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BombCrashWalk g_BombCrashWalk;

#endif // __SKILL_BOMB_CRASH_WALK_HANDLER_H__
