//////////////////////////////////////////////////////////////////////////////
// Filename    : BombingStar.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_GUSION_B_BLUE_HANDLER_H__
#define __SKILL_TIFFAUGES_GUSION_B_BLUE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BombingStar;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesGusionBBlue : public SkillHandler 
{
public:
	TiffaugesGusionBBlue() throw() {}
	~TiffaugesGusionBBlue() throw() {}
	
public:
    string getSkillHandlerName()  { return "TiffaugesGusionBBlue"; }

	SkillType_t getSkillType()  { return SKILL_TIFFAUGES_GUSION_B_BLUE; }

	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesGusionBBlue g_TiffaugesGusionBBlue;

#endif // __SKILL_BOMBING_STAR_HANDLER_H__
