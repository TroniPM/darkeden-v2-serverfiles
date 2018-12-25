//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidStorm.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_PAIMON_RED_HANDLER_H__
#define __SKILL_TIFFAUGES_PAIMON_RED_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AcidStorm;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesPaimonRed : public SkillHandler 
{
public:
	TiffaugesPaimonRed() throw() {}
	~TiffaugesPaimonRed() throw() {}
	
public:
    string getSkillHandlerName()  { return "TiffaugesPaimonRed"; }
	SkillType_t getSkillType()  { return SKILL_TIFFAUGES_PAIMON_RED; }

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesPaimonRed g_TiffaugesPaimonRed;

#endif // __SKILL_ACID_STORM_HANDLER_H__
