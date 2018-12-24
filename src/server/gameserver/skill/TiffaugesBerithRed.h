//////////////////////////////////////////////////////////////////////////////
// Filename    : MentalSword.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_BERITH_RED_HANDLER_H__
#define __SKILL_TIFFAUGES_BERITH_RED_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class MentalSword;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesBerithRed : public SkillHandler 
{
public:
	TiffaugesBerithRed() throw() {}
	~TiffaugesBerithRed() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "TiffaugesBerithRed"; }
	SkillType_t getSkillType() const throw() { return SKILL_TIFFAUGES_BERITH_RED; }

	void execute(Monster* pMonster, Creature* pCreature) throw(Error);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesBerithRed g_TiffaugesBerithRed;

#endif // __SKILL_MENTAL_SWORD_HANDLER_H__
