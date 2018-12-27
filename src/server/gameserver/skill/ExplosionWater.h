//////////////////////////////////////////////////////////////////////////////
// Filename    : ExplosionWater.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_EXPLOSION_WATER_HANDLER_H__
#define __SKILL_EXPLOSION_WATER_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ExplosionWater;
//////////////////////////////////////////////////////////////////////////////

class ExplosionWater : public SkillHandler 
{
public:
	ExplosionWater()  {}
	~ExplosionWater()  {}
	
public:
    string getSkillHandlerName()  { return "ExplosionWater"; }
	SkillType_t getSkillType()  { return SKILL_EXPLOSION_WATER; }

	void execute(Ousters* pOusters, ObjectID_t ObjectID,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);

	void executeMonster(Zone* pZone, Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ExplosionWater g_ExplosionWater;

#endif // __SKILL_EXPLOSION_WATER_HANDLER_H__
