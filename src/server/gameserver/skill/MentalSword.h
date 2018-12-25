//////////////////////////////////////////////////////////////////////////////
// Filename    : MentalSword.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_MENTAL_SWORD_HANDLER_H__
#define __SKILL_MENTAL_SWORD_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class MentalSword;
//////////////////////////////////////////////////////////////////////////////

class MentalSword : public SkillHandler 
{
public:
	MentalSword() throw() {}
	~MentalSword() throw() {}
	
public:
    string getSkillHandlerName()  { return "MentalSword"; }
	SkillType_t getSkillType()  { return SKILL_MENTAL_SWORD; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pCreature);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern MentalSword g_MentalSword;

#endif // __SKILL_MENTAL_SWORD_HANDLER_H__
