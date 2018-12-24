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
	TiffaugesGusionCBlue() throw() { }
	~TiffaugesGusionCBlue() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "TiffaugesGusionCBlue"; }
	SkillType_t getSkillType() const throw() { return SKILL_TIFFAUGES_GUSION_C_BLUE; }

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesGusionCBlue g_TiffaugesGusionCBlue;

#endif // __SKILL_ICE_HAIL_HANDLER_H__
