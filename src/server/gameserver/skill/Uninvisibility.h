//////////////////////////////////////////////////////////////////////////////
// Filename    : Uninvisibility.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_UN_INVISIBILITY_HANDLER_H__
#define __SKILL_UN_INVISIBILITY_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Uninvisibility;
//////////////////////////////////////////////////////////////////////////////

class Uninvisibility: public SkillHandler 
{
public:
	Uninvisibility()  {}
	~Uninvisibility()  {}
	
public:
    string getSkillHandlerName()  { return "Uninvisibility"; }
	SkillType_t getSkillType()  { return SKILL_UN_INVISIBILITY; }

	void execute(Vampire* pVampire);
	void execute(Monster* pMonster);

	void computeOutput(const SkillInput& input, SkillOutput& output) {}
};

// global variable declaration
extern Uninvisibility g_Uninvisibility;

#endif // __SKILL_UN_INVISIBILITY_HANDLER_H__
