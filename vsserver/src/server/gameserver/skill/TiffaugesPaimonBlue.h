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
	TiffaugesPaimonBlue() throw() {}
	~TiffaugesPaimonBlue() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "TiffaugesPaimonBlue"; }
	SkillType_t getSkillType() const throw() { return SKILL_TIFFAUGES_PAIMON_BLUE; }

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesPaimonBlue g_TiffaugesPaimonBlue;

#endif // __SKILL_ACID_STORM_HANDLER_H__
