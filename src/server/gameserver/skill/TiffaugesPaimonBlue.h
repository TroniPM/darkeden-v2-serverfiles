//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidStorm.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_PAIMON_BLUE_HANDLER_H__
#define __SKILL_TIFFAUGES_PAIMON_BLUE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AcidStorm;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesPaimonBlue : public SkillHandler 
{
public:
	TiffaugesPaimonBlue()  {}
	~TiffaugesPaimonBlue()  {}
	
public:
    string getSkillHandlerName()  { return "TiffaugesPaimonBlue"; }
	SkillType_t getSkillType()  { return SKILL_TIFFAUGES_PAIMON_BLUE; }

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesPaimonBlue g_TiffaugesPaimonBlue;

#endif // __SKILL_ACID_STORM_HANDLER_H__
