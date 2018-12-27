//////////////////////////////////////////////////////////////////////////////
// Filename    : PoisonousHands.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_POISONOUS_HANDS_HANDLER_H__
#define __SKILL_POISONOUS_HANDS_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class PoisonousHands;
//////////////////////////////////////////////////////////////////////////////

class PoisonousHands: public SkillHandler 
{
public:
	PoisonousHands()  {}
	~PoisonousHands()  {}
	
public:
    string getSkillHandlerName()  { return "PoisonousHands"; }
	SkillType_t getSkillType()  { return SKILL_POISONOUS_HANDS; }

	void execute(Vampire* pVampire, ObjectID_t targetObject, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern PoisonousHands g_PoisonousHands;

#endif // __SKILL_POISONOUS_HANDS_HANDLER_H__
