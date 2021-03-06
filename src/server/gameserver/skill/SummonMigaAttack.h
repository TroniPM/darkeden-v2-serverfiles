//////////////////////////////////////////////////////////////////////////////
// Filename    : SummonMigaAttack.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SUMMON_MIGA_ATTACK_HANDLER_H__
#define __SKILL_SUMMON_MIGA_ATTACK_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SummonMigaAttack;
//////////////////////////////////////////////////////////////////////////////

class SummonMigaAttack: public SkillHandler 
{
public:
	SummonMigaAttack() ;
	~SummonMigaAttack()  {}
	
public:
    string getSkillHandlerName()  { return "SummonMigaAttack"; }
	SkillType_t getSkillType()  { return SKILL_SUMMON_MIGA_ATTACK; }

	void execute(Monster* pMonster);

	void computeOutput(const SkillInput& input, SkillOutput& output);

private :
};

// global variable declaration
extern SummonMigaAttack g_SummonMigaAttack;

#endif // __SKILL_HIDE_HANDLER_H__
