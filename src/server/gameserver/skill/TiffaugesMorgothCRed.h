//////////////////////////////////////////////////////////////////////////////
// Filename    : BombingStar.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_MORGOTH_C_RED_HANDLER_H__
#define __SKILL_TIFFAUGES_MORGOTH_C_RED_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BombingStar;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesMorgothCRed : public SkillHandler 
{
public:
	TiffaugesMorgothCRed()  {}
	~TiffaugesMorgothCRed()  {}
	
public:
    string getSkillHandlerName()  { return "TiffaugesMorgothCRed"; }

	SkillType_t getSkillType()  { return SKILL_TIFFAUGES_MORGOTH_C_RED; }

	void execute(Monster* pMonster, Creature* pEnemy);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesMorgothCRed g_TiffaugesMorgothCRed;

#endif // __SKILL_BOMBING_STAR_HANDLER_H__
