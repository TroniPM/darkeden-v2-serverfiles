//////////////////////////////////////////////////////////////////////////////
// Filename    : Paralyze.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CURSE_OF_BLOOD1_HANDLER_H__
#define __SKILL_CURSE_OF_BLOOD1_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Paralyze;
//////////////////////////////////////////////////////////////////////////////

class CurseOfBlood1: public SkillHandler 
{
public:
	CurseOfBlood1() throw() {}
	~CurseOfBlood1() throw() {}
	
public:
    string getSkillHandlerName()  { return "CurseOfBlood1"; }
	SkillType_t getSkillType()  { return SKILL_CURSE_OF_BLOOD1; }

	void execute(Vampire* pSlayer, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	//void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	//void executeMonster(Zone* pZone, Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern CurseOfBlood1 g_CurseOfBlood1;

#endif // __SKILL_PARALYZE_HANDLER_H__
