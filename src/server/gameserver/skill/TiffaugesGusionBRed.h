//////////////////////////////////////////////////////////////////////////////
// Filename    : BombingStar.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_GUSION_B_RED_HANDLER_H__
#define __SKILL_TIFFAUGES_GUSION_B_RED_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BombingStar;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesGusionBRed : public SkillHandler 
{
public:
	TiffaugesGusionBRed() throw() {}
	~TiffaugesGusionBRed() throw() {}
	
public:
    string getSkillHandlerName()  { return "TiffaugesGusionBRed"; }

	SkillType_t getSkillType()  { return SKILL_TIFFAUGES_GUSION_B_RED; }

	void execute(Monster* pMonster, Creature* pEnemy);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesGusionBRed g_TiffaugesGusionBRed;

#endif // __SKILL_BOMBING_STAR_HANDLER_H__
