//////////////////////////////////////////////////////////////////////////////
// Filename    : BombingStar.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_KRSNIK_B_BLUE_HANDLER_H__
#define __SKILL_TIFFAUGES_KRSNIK_B_BLUE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BombingStar;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesKrsnikBBlue : public SkillHandler 
{
public:
	TiffaugesKrsnikBBlue()  {}
	~TiffaugesKrsnikBBlue()  {}
	
public:
    string getSkillHandlerName()  { return "TiffaugesKrsnikBBlue"; }

	SkillType_t getSkillType()  { return SKILL_TIFFAUGES_KRSNIK_B_BLUE; }

	void execute(Monster* pMonster, Creature* pEnemy);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesKrsnikBBlue g_TiffaugesKrsnikBBlue;

#endif // __SKILL_BOMBING_STAR_HANDLER_H__
