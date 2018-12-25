//////////////////////////////////////////////////////////////////////////////
// Filename    : SimpleTileMissileSkill.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SIMPLETILEMISSILESKILL__
#define __SIMPLETILEMISSILESKILL__

#include "SimpleSkill.h"

class SimpleTileMissileSkill
{
public:
	void execute(Slayer* pSlayer, int X, int Y, SkillSlot* pSkillSlot,
		const SIMPLE_SKILL_INPUT& param, SIMPLE_SKILL_OUTPUT& result,
		CEffectID_t CEffectID=0, bool bForceKnockback=false);
	void execute(Vampire* pVampire, int X, int Y, VampireSkillSlot* pVampireSkillSlot, 
		const SIMPLE_SKILL_INPUT& param,  SIMPLE_SKILL_OUTPUT& result,
		CEffectID_t CEffectID=0, bool bForceKnockback=false, int HitBonus=0);
	void execute(Ousters* pOusters, int X, int Y, OustersSkillSlot* pOustersSkillSlot, 
		const SIMPLE_SKILL_INPUT& param,  SIMPLE_SKILL_OUTPUT& result,
		CEffectID_t CEffectID=0, bool bForceKnockback=false, int HitBonus=0);
	void execute(Monster* pMonster, int X, int Y,
		const SIMPLE_SKILL_INPUT& param,  SIMPLE_SKILL_OUTPUT& result,
		CEffectID_t CEffectID=0, bool bForceKnockback=false);
};

extern SimpleTileMissileSkill g_SimpleTileMissileSkill;

#endif
