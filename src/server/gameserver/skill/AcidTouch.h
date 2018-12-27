//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidTouch.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ACID_TOUCH_HANDLER_H__
#define __SKILL_ACID_TOUCH_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AcidTouch;
//////////////////////////////////////////////////////////////////////////////

class AcidTouch: public SkillHandler 
{
public:
	AcidTouch()  {}
	~AcidTouch()  {}
	
public:
    string getSkillHandlerName()  { return "AcidTouch"; }

	SkillType_t getSkillType()  { return SKILL_ACID_TOUCH; }

	void execute(Vampire* pVampire, ObjectID_t targetObject, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern AcidTouch g_AcidTouch;

#endif // __SKILL_ACID_TOUCH_HANDLER_H__
