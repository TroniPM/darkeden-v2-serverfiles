//////////////////////////////////////////////////////////////////////////////
// Filename    : BombingStar.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_MORGOTH_C_BLUE_HANDLER_H__
#define __SKILL_TIFFAUGES_MORGOTH_C_BLUE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BombingStar;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesMorgothCBlue : public SkillHandler 
{
public:
	TiffaugesMorgothCBlue() throw() {}
	~TiffaugesMorgothCBlue() throw() {}
	
public:
    string getSkillHandlerName()  { return "TiffaugesMorgothCBlue"; }

	SkillType_t getSkillType()  { return SKILL_TIFFAUGES_MORGOTH_C_BLUE; }

	void execute(Monster* pMonster, Creature* pEnemy);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesMorgothCBlue g_TiffaugesMorgothCBlue;

#endif // __SKILL_BOMBING_STAR_HANDLER_H__
