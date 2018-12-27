//////////////////////////////////////////////////////////////////////////////
// Filename    : IceHail.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_MORGOTH_B_BLUE_HANDLER_H__
#define __SKILL_TIFFAUGES_MORGOTH_B_BLUE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class IceHail;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesMorgothBBlue : public SkillHandler 
{
public:
	TiffaugesMorgothBBlue()  { }
	~TiffaugesMorgothBBlue()  {}
	
public:
    string getSkillHandlerName()  { return "TiffaugesMorgothBBlue"; }
	SkillType_t getSkillType()  { return SKILL_TIFFAUGES_MORGOTH_B_BLUE; }

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesMorgothBBlue g_TiffaugesMorgothBBlue;

#endif // __SKILL_ICE_HAIL_HANDLER_H__
