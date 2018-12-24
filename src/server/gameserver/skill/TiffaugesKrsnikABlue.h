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
	TiffaugesKrsnikABlue() throw() {}
	~TiffaugesKrsnikABlue() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "TiffaugesKrsnikABlue"; }

	SkillType_t getSkillType() const throw() { return SKILL_TIFFAUGES_KRSNIK_A_BLUE; }

	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesKrsnikABlue g_TiffaugesKrsnikABlue;

#endif // __SKILL_ACID_TOUCH_HANDLER_H__
