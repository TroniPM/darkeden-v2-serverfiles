//////////////////////////////////////////////////////////////////////////////
// Filename    : IceHail.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_MORGOTH_B_RED_HANDLER_H__
#define __SKILL_TIFFAUGES_MORGOTH_B_RED_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class IceHail;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesMorgothBRed : public SkillHandler 
{
public:
	TiffaugesMorgothBRed()  { }
	~TiffaugesMorgothBRed()  {}
	
public:
    string getSkillHandlerName()  { return "TiffaugesMorgothBRed"; }
	SkillType_t getSkillType()  { return SKILL_TIFFAUGES_MORGOTH_B_RED; }

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesMorgothBRed g_TiffaugesMorgothBRed;

#endif // __SKILL_ICE_HAIL_HANDLER_H__
