//////////////////////////////////////////////////////////////////////////////
// Filename    : Unburrow.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_UN_BURROW_HANDLER_H__
#define __SKILL_UN_BURROW_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Unburrow;
//////////////////////////////////////////////////////////////////////////////

class Unburrow: public SkillHandler 
{
public:
	Unburrow()  {}
	~Unburrow()  {}
	
public:
    string getSkillHandlerName()  { return "Unburrow"; }
	SkillType_t getSkillType()  { return SKILL_UN_BURROW; }

	void execute(Vampire* pVampire);
	void execute(Monster* pMonster);

	void computeOutput(const SkillInput& input, SkillOutput& output) {}
};

// global variable declaration
extern Unburrow g_Unburrow;

#endif // __SKILL_UN_BURROW_HANDLER_H__
