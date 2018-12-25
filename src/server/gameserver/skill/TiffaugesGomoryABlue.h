//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidTouch.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_GOMORY_A_BLUE_HANDLER_H__
#define __SKILL_TIFFAUGES_GOMORY_A_BLUE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AcidTouch;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesGomoryABlue: public SkillHandler 
{
public:
	TiffaugesGomoryABlue() throw() {}
	~TiffaugesGomoryABlue() throw() {}
	
public:
    string getSkillHandlerName()  { return "TiffaugesGomoryABlue"; }

	SkillType_t getSkillType()  { return SKILL_TIFFAUGES_GOMORY_A_BLUE; }

	void execute(Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesGomoryABlue g_TiffaugesGomoryABlue;

#endif // __SKILL_ACID_TOUCH_HANDLER_H__
