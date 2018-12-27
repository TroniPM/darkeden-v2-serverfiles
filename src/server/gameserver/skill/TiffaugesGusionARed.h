//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidTouch.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_GUSION_A_RED_HANDLER_H__
#define __SKILL_TIFFAUGES_GUSION_A_RED_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AcidTouch;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesGusionARed : public SkillHandler 
{
public:
	TiffaugesGusionARed()  {}
	~TiffaugesGusionARed()  {}
	
public:
    string getSkillHandlerName()  { return "TiffaugesGusionARed"; }

	SkillType_t getSkillType()  { return SKILL_TIFFAUGES_GUSION_A_RED; }

	void execute(Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesGusionARed g_TiffaugesGusionARed;

#endif // __SKILL_ACID_TOUCH_HANDLER_H__
