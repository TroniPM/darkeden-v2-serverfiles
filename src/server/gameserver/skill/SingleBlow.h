//////////////////////////////////////////////////////////////////////////////
// Filename    : SingleBlow.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SINGLE_BLOW_HANDLER_H__
#define __SKILL_SINGLE_BLOW_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SingleBlow;
//////////////////////////////////////////////////////////////////////////////

class SingleBlow : public SkillHandler 
{
public:
	SingleBlow() throw() {}
	~SingleBlow() throw() {}
	
public:
    string getSkillHandlerName()  { return "SingleBlow"; }
	SkillType_t getSkillType()  { return SKILL_SINGLE_BLOW; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SingleBlow g_SingleBlow;

#endif // __SKILL_SINGLE_BLOW_HANDLER_H__
