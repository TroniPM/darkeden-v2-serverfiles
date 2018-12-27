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
	TiffaugesGusionABlue()  {}
	~TiffaugesGusionABlue()  {}
	
public:
    string getSkillHandlerName()  { return "TiffaugesGusionABlue"; }

	SkillType_t getSkillType()  { return SKILL_TIFFAUGES_GUSION_A_BLUE; }

	void execute(Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesGusionABlue g_TiffaugesGusionABlue;

#endif // __SKILL_ACID_TOUCH_HANDLER_H__
