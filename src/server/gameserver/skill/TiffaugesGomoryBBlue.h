//////////////////////////////////////////////////////////////////////////////
// Filename    : BombingStar.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_GOMORY_B_BLUE_HANDLER_H__
#define __SKILL_TIFFAUGES_GOMORY_B_BLUE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BombingStar;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesGomoryBBlue : public SkillHandler 
{
public:
	TiffaugesGomoryBBlue() throw() {}
	~TiffaugesGomoryBBlue() throw() {}
	
public:
    string getSkillHandlerName()  { return "TiffaugesGomoryBBlue"; }

	SkillType_t getSkillType()  { return SKILL_TIFFAUGES_GOMORY_B_BLUE; }

	void execute(Monster* pMonster, Creature* pEnemy);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesGomoryBBlue g_TiffaugesGomoryBBlue;

#endif // __SKILL_BOMBING_STAR_HANDLER_H__
