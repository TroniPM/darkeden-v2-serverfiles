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
    string getSkillHandlerName() const throw() { return "TiffaugesBerithBlue"; }
	SkillType_t getSkillType() const throw() { return SKILL_TIFFAUGES_BERITH_BLUE; }

	void execute(Monster* pMonster, Creature* pCreature) throw(Error);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesBerithBlue g_TiffaugesBerithBlue;

#endif // __SKILL_MENTAL_SWORD_HANDLER_H__
