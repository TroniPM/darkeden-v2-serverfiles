//////////////////////////////////////////////////////////////////////////////
// Filename    : Doom.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DOOM_HANDLER_H__
#define __SKILL_DOOM_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Doom;
//////////////////////////////////////////////////////////////////////////////

class Doom : public SkillHandler 
{
public:
	Doom()  {}
	~Doom()  {}
	
public:
    string getSkillHandlerName()  { return "Doom"; }
	SkillType_t getSkillType()  { return SKILL_DOOM; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);

	void executeMonster(Zone* pZone, Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Doom g_Doom;

#endif // __SKILL_DOOM_HANDLER_H__
