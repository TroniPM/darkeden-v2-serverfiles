//////////////////////////////////////////////////////////////////////////////
// Filename    : Paralyze.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CURSE_OF_BLOOD2_HANDLER_H__
#define __SKILL_CURSE_OF_BLOOD2_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Paralyze;
//////////////////////////////////////////////////////////////////////////////

class CurseOfBlood2: public SkillHandler 
{
public:
	CurseOfBlood2() throw() {}
	~CurseOfBlood2() throw() {}
	
public:
    string getSkillHandlerName()  { return "CurseOfBlood2"; }
	SkillType_t getSkillType()  { return SKILL_CURSE_OF_BLOOD2; }

	void execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Vampire* pVampire, Creature* pTargetCreature, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	//void execute(Monster* pMonster, Creature* pEnemy);

	//void executeMonster(Zone* pZone, Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern CurseOfBlood2 g_CurseOfBlood2;

#endif // __SKILL_PARALYZE_HANDLER_H__
