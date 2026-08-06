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
	TiffaugesMorgothBRed() throw() { }
	~TiffaugesMorgothBRed() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "TiffaugesMorgothBRed"; }
	SkillType_t getSkillType() const throw() { return SKILL_TIFFAUGES_MORGOTH_B_RED; }

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TiffaugesMorgothBRed g_TiffaugesMorgothBRed;

#endif // __SKILL_ICE_HAIL_HANDLER_H__
