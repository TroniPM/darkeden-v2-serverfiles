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
    string getSkillHandlerName() const throw() { return "CurseOfBlood2"; }
	SkillType_t getSkillType() const throw() { return SKILL_CURSE_OF_BLOOD2; }

	void execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Vampire* pVampire, Creature* pTargetCreature, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	//void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	//void executeMonster(Zone* pZone, Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern CurseOfBlood2 g_CurseOfBlood2;

#endif // __SKILL_PARALYZE_HANDLER_H__
