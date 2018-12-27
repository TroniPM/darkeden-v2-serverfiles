
//////////////////////////////////////////////////////////////////////////////
// Filename    : ChoppingFirewood.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CHOPPING_FIREWOOD_HANDLER_H__
#define __SKILL_CHOPPING_FIREWOOD_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ChoppingFirewood;
//////////////////////////////////////////////////////////////////////////////

class ChoppingFirewood : public SkillHandler 
{
public:
	ChoppingFirewood()  {}
	~ChoppingFirewood()  {}
	
public:
    string getSkillHandlerName()  { return "ChoppingFirewood"; }
	SkillType_t getSkillType()  { return SKILL_CHOPPING_FIREWOOD; }

	void execute(Monster*, ZoneCoord_t X, ZoneCoord_t Y);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ChoppingFirewood g_ChoppingFirewood;

#endif // __SKILL_CHOPPING_FIREWOOD_HANDLER_H__
