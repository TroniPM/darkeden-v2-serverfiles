//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyStrike.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOODY_STRIKE_HANDLER_H__
#define __SKILL_BLOODY_STRIKE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BloodyStrike;
//////////////////////////////////////////////////////////////////////////////

class BloodyStrike : public SkillHandler 
{
public:
	BloodyStrike() throw() {}
	~BloodyStrike() throw() {}
	
public:
    string getSkillHandlerName()  { return "BloodyStrike"; }
	SkillType_t getSkillType()  { return SKILL_BLOODY_STRIKE; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BloodyStrike g_BloodyStrike;

#endif // __SKILL_BLOODY_STRIKE_HANDLER_H__
