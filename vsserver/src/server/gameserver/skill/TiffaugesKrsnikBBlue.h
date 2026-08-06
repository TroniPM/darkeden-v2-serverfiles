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
	TiffaugesKrsnikBBlue() throw() {}
	~TiffaugesKrsnikBBlue() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "TiffaugesKrsnikBBlue"; }

	SkillType_t getSkillType() const throw() { return SKILL_TIFFAUGES_KRSNIK_B_BLUE; }

	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesKrsnikBBlue g_TiffaugesKrsnikBBlue;

#endif // __SKILL_BOMBING_STAR_HANDLER_H__
