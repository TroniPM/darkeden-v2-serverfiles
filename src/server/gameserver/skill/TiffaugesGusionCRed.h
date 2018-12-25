//////////////////////////////////////////////////////////////////////////////
// Filename    : IceHail.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TIFFAUGES_GUSION_C_RED_HANDLER_H__
#define __SKILL_TIFFAUGES_GUSION_C_RED_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class IceHail;
//////////////////////////////////////////////////////////////////////////////

class TiffaugesGusionCRed : public SkillHandler 
{
public:
	TiffaugesGusionCRed() throw() { }
	~TiffaugesGusionCRed() throw() {}
	
public:
    string getSkillHandlerName()  { return "TiffaugesGusionCRed"; }
	SkillType_t getSkillType()  { return SKILL_TIFFAUGES_GUSION_C_RED; }

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesGusionCRed g_TiffaugesGusionCRed;

#endif // __SKILL_ICE_HAIL_HANDLER_H__
