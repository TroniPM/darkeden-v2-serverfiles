//////////////////////////////////////////////////////////////////////////////
// Filename    : ThunderStorm.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_THUNDER_STORM_HANDLER_H__
#define __SKILL_THUNDER_STORM_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ThunderStorm;
//////////////////////////////////////////////////////////////////////////////

class ThunderStorm : public SkillHandler 
{
public:
	ThunderStorm()  {}
	~ThunderStorm()  {}
	
public:
    string getSkillHandlerName()  { return "ThunderStorm"; }
	SkillType_t getSkillType()  { return SKILL_THUNDER_STORM; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pTargetCreature);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ThunderStorm g_ThunderStorm;

#endif // __SKILL_THUNDER_STORM_HANDLER_H__
