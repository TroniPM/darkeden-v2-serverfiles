//////////////////////////////////////////////////////////////////////////////
// Filename    : TalonOfCrow.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TALON_OF_CROW_HANDLER_H__
#define __SKILL_TALON_OF_CROW_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class TalonOfCrow;
//////////////////////////////////////////////////////////////////////////////

class TalonOfCrow: public SkillHandler 
{
public:
	TalonOfCrow()  {}
	~TalonOfCrow()  {}
	
public:
    string getSkillHandlerName()  { return "TalonOfCrow"; }

	SkillType_t getSkillType()  { return SKILL_TALON_OF_CROW; }

	void execute(Vampire* pVampire, ObjectID_t targetObject, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TalonOfCrow g_TalonOfCrow;

#endif // __SKILL_TALON_OF_CROW_HANDLER_H__
