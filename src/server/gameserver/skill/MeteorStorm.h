//////////////////////////////////////////////////////////////////////////////
// Filename    : MeteorStorm.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_METEOR_STORM_HANDLER_H__
#define __SKILL_METEOR_STORM_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class MeteorStorm;
//////////////////////////////////////////////////////////////////////////////

class MeteorStorm : public SkillHandler 
{
public:
	MeteorStorm()  {}
	~MeteorStorm()  {}
	
public:
    string getSkillHandlerName()  { return "MeteorStorm"; }
	SkillType_t getSkillType()  { return SKILL_METEOR_STORM; }

	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);
	void execute(Ousters* pOusters, ObjectID_t ObjectID,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern MeteorStorm g_MeteorStorm;

#endif // __SKILL_METEOR_STORM_HANDLER_H__
