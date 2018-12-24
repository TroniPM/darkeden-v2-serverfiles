//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidTouch.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_GUSION_A_BLUE_HANDLER_H__
#define __SKILL_TIFFAUGES_GUSION_A_BLUE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AcidTouch;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesGusionABlue : public SkillHandler 
{
public:
	TiffaugesGusionABlue() throw() {}
	~TiffaugesGusionABlue() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "TiffaugesGusionABlue"; }

	SkillType_t getSkillType() const throw() { return SKILL_TIFFAUGES_GUSION_A_BLUE; }

	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesGusionABlue g_TiffaugesGusionABlue;

#endif // __SKILL_ACID_TOUCH_HANDLER_H__
