//////////////////////////////////////////////////////////////////////////////
// Filename    : MultiAmputate.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_VALKYRJA_BLUE_HANDLER_H__
#define __SKILL_TIFFAUGES_VALKYRJA_BLUE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class TiffaugesValkyrjaBlue;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesValkyrjaBlue : public SkillHandler 
{
public:
	TiffaugesValkyrjaBlue() throw() {}
	~TiffaugesValkyrjaBlue() throw() {}
	
public:
    string getSkillHandlerName()  { return "TiffaugesValkyrjaBlue"; }

	SkillType_t getSkillType()  { return SKILL_TIFFAUGES_VALKYRJA_BLUE; }

	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesValkyrjaBlue g_TiffaugesValkyrjaBlue;

#endif // __SKILL_MULTI_AMPUTATE_HANDLER_H__
