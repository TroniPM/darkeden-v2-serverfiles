//////////////////////////////////////////////////////////////////////////////
// Filename    : TalonOfCrow.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BOGLE_B_HANDLER_H__
#define __SKILL_BOGLE_B_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class TalonOfCrow;
//////////////////////////////////////////////////////////////////////////////

class BogleB: public SkillHandler 
{
public:
	BogleB()  {}
	~BogleB()  {}
	
public:
    string getSkillHandlerName()  { return "BogleB"; }
	SkillType_t getSkillType()  { return SKILL_BOGLE_B; }

	void execute(Vampire* pVampire, ObjectID_t targetObject, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BogleB g_BogleB;

#endif // __SKILL_BOGLE_B_HANDLER_H__
