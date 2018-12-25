//////////////////////////////////////////////////////////////////////////////
// Filename    : SpitStream.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_BALBERITH_RED_HANDLER_H__
#define __SKILL_TIFFAUGES_BALBERITH_RED_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SpitStream;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesBalberithRed : public SkillHandler 
{
public:
	TiffaugesBalberithRed() throw() {}
	~TiffaugesBalberithRed() throw() {}
	
public:
    string getSkillHandlerName()  { return "TiffaugesBalberithRed"; }
	SkillType_t getSkillType()  { return SKILL_TIFFAUGES_BALBERITH_RED; }

	void execute(Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesBalberithRed g_TiffaugesBalberithRed;

#endif // __SKILL_SPIT_STREAM_H__
