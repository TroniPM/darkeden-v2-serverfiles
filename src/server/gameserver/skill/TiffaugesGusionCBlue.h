//////////////////////////////////////////////////////////////////////////////
// Filename    : IceHail.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_GUSION_C_BLUE_HANDLER_H__
#define __SKILL_TIFFAUGES_GUSION_C_BLUE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class IceHail;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesGusionCBlue : public SkillHandler 
{
public:
	TiffaugesGusionCBlue()  { }
	~TiffaugesGusionCBlue()  {}
	
public:
    string getSkillHandlerName()  { return "TiffaugesGusionCBlue"; }
	SkillType_t getSkillType()  { return SKILL_TIFFAUGES_GUSION_C_BLUE; }

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesGusionCBlue g_TiffaugesGusionCBlue;

#endif // __SKILL_ICE_HAIL_HANDLER_H__
