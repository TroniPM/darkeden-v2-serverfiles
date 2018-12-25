//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidTouch.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_GOMORY_A_RED_HANDLER_H__
#define __SKILL_TIFFAUGES_GOMORY_A_RED_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AcidTouch;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesGomoryARed: public SkillHandler 
{
public:
	TiffaugesGomoryARed() throw() {}
	~TiffaugesGomoryARed() throw() {}
	
public:
    string getSkillHandlerName()  { return "TiffaugesGomoryARed"; }

	SkillType_t getSkillType()  { return SKILL_TIFFAUGES_GOMORY_A_RED; }

	void execute(Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesGomoryARed g_TiffaugesGomoryARed;

#endif // __SKILL_ACID_TOUCH_HANDLER_H__
