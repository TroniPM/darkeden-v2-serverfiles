
//////////////////////////////////////////////////////////////////////////////
// Filename    : SMGAttack.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SMG_ATTACK_HANDLER_H__
#define __SKILL_SMG_ATTACK_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SMGAttack;
//////////////////////////////////////////////////////////////////////////////

class SMGAttack : public SkillHandler 
{
public:
	SMGAttack() throw() {}
	~SMGAttack() throw() {}
	
public:
    string getSkillHandlerName()  { return "SMGAttack"; }
	SkillType_t getSkillType()  { return SKILL_SMG_ATTACK; }

	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SMGAttack g_SMGAttack;

#endif // __SKILL_SMG_ATTACK_HANDLER_H__
