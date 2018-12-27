//////////////////////////////////////////////////////////////////////////////
// Filename    : Invisibility.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_INVISIBILITY_HANDLER_H__
#define __SKILL_INVISIBILITY_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Invisibility;
//////////////////////////////////////////////////////////////////////////////

class Invisibility: public SkillHandler 
{
public:
	Invisibility()  {}
	~Invisibility()  {}
	
public:
    string getSkillHandlerName()  { return "Invisibility"; }
	SkillType_t getSkillType()  { return SKILL_INVISIBILITY; }

	void execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Invisibility g_Invisibility;

#endif // __SKILL_INVISIBILITY_HANDLER_H__
