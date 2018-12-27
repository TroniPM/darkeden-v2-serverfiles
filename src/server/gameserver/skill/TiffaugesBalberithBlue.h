//////////////////////////////////////////////////////////////////////////////
// Filename    : SpitStream.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_BALBERITH_BLUE_HANDLER_H__
#define __SKILL_TIFFAUGES_BALBERITH_BLUE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SpitStream;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesBalberithBlue : public SkillHandler 
{
public:
	TiffaugesBalberithBlue()  {}
	~TiffaugesBalberithBlue()  {}
	
public:
    string getSkillHandlerName()  { return "TiffaugesBalberithBlue"; }
	SkillType_t getSkillType()  { return SKILL_TIFFAUGES_BALBERITH_BLUE; }

	void execute(Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesBalberithBlue g_TiffaugesBalberithBlue;

#endif // __SKILL_SPIT_STREAM_H__
