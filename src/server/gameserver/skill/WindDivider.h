//////////////////////////////////////////////////////////////////////////////
// Filename    : WindDivider.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_WIND_DIVIDER_HANDLER_H__
#define __SKILL_WIND_DIVIDER_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class WindDivider;
//////////////////////////////////////////////////////////////////////////////

class WindDivider : public SkillHandler 
{
public:
	WindDivider()  {}
	~WindDivider()  {}
	
public:
    string getSkillHandlerName()  { return "WindDivider"; }
	SkillType_t getSkillType()  { return SKILL_WIND_DIVIDER; }

	void execute(Slayer* pSlayer, ObjectID_t targetObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pTargetCreature);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern WindDivider g_WindDivider;

#endif // __SKILL_WIND_DIVIDER_H__
