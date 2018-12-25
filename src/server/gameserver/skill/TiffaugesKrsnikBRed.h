//////////////////////////////////////////////////////////////////////////////
// Filename    : BombingStar.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_KRSNIK_B_RED_HANDLER_H__
#define __SKILL_TIFFAUGES_KRSNIK_B_RED_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BombingStar;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesKrsnikBRed : public SkillHandler 
{
public:
	TiffaugesKrsnikBRed() throw() {}
	~TiffaugesKrsnikBRed() throw() {}
	
public:
    string getSkillHandlerName()  { return "TiffaugesKrsnikBRed"; }

	SkillType_t getSkillType()  { return SKILL_TIFFAUGES_KRSNIK_B_RED; }

	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesKrsnikBRed g_TiffaugesKrsnikBRed;

#endif // __SKILL_BOMBING_STAR_HANDLER_H__
