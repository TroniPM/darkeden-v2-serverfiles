//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidTouch.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_MORGOTH_A_RED_HANDLER_H__
#define __SKILL_TIFFAUGES_MORGOTH_A_RED_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AcidTouch;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesMorgothARed: public SkillHandler 
{
public:
	TiffaugesMorgothARed() throw() {}
	~TiffaugesMorgothARed() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "TiffaugesMorgothARed"; }

	SkillType_t getSkillType() const throw() { return SKILL_TIFFAUGES_MORGOTH_A_RED; }

	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesMorgothARed g_TiffaugesMorgothARed;

#endif // __SKILL_ACID_TOUCH_HANDLER_H__
