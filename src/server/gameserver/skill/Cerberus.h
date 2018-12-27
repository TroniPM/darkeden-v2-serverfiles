//////////////////////////////////////////////////////////////////////////////
// Filename    : TalonOfCrow.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CERBERUS_HANDLER_H__
#define __SKILL_CERBERUS_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class TalonOfCrow;
//////////////////////////////////////////////////////////////////////////////

class Cerberus : public SkillHandler 
{
public:
	Cerberus()  {}
	~Cerberus()  {}
	
public:
    string getSkillHandlerName()  { return "Cerberus"; }

	SkillType_t getSkillType()  { return SKILL_CERBERUS; }

	void execute(Vampire* pVampire, ObjectID_t targetObject, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Cerberus g_Cerberus;

#endif // __SKILL_TALON_OF_CROW_HANDLER_H__
