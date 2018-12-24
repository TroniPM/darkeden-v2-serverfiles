//////////////////////////////////////////////////////////////////////////////
// Filename    : BombingStar.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_GOMORY_B_RED_HANDLER_H__
#define __SKILL_TIFFAUGES_GOMORY_B_RED_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BombingStar;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesGomoryBRed : public SkillHandler 
{
public:
	TiffaugesGomoryBRed() throw() {}
	~TiffaugesGomoryBRed() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "TiffaugesGomoryBRed"; }

	SkillType_t getSkillType() const throw() { return SKILL_TIFFAUGES_GOMORY_B_RED; }

	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesGomoryBRed g_TiffaugesGomoryBRed;

#endif // __SKILL_BOMBING_STAR_HANDLER_H__
