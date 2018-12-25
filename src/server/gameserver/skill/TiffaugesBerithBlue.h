//////////////////////////////////////////////////////////////////////////////
// Filename    : MentalSword.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_BERITH_BLUE_HANDLER_H__
#define __SKILL_TIFFAUGES_BERITH_BLUE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class MentalSword;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesBerithBlue : public SkillHandler 
{
public:
	TiffaugesBerithBlue() throw() {}
	~TiffaugesBerithBlue() throw() {}
	
public:
    string getSkillHandlerName()  { return "TiffaugesBerithBlue"; }
	SkillType_t getSkillType()  { return SKILL_TIFFAUGES_BERITH_BLUE; }

	void execute(Monster* pMonster, Creature* pCreature);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesBerithBlue g_TiffaugesBerithBlue;

#endif // __SKILL_MENTAL_SWORD_HANDLER_H__
