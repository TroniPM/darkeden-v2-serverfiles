//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidTouch.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_KRSNIK_A_BLUE_HANDLER_H__
#define __SKILL_TIFFAUGES_KRSNIK_A_BLUE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AcidTouch;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesKrsnikABlue: public SkillHandler 
{
public:
	TiffaugesKrsnikABlue()  {}
	~TiffaugesKrsnikABlue()  {}
	
public:
    string getSkillHandlerName()  { return "TiffaugesKrsnikABlue"; }

	SkillType_t getSkillType()  { return SKILL_TIFFAUGES_KRSNIK_A_BLUE; }

	void execute(Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesKrsnikABlue g_TiffaugesKrsnikABlue;

#endif // __SKILL_ACID_TOUCH_HANDLER_H__
