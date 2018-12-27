//////////////////////////////////////////////////////////////////////////////
// Filename    : IceHail.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ICE_HAIL_HANDLER_H__
#define __SKILL_ICE_HAIL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class IceHail;
//////////////////////////////////////////////////////////////////////////////

class IceHail : public SkillHandler 
{
public:
	IceHail()  { }
	~IceHail()  {}
	
public:
    string getSkillHandlerName()  { return "IceHail"; }
	SkillType_t getSkillType()  { return SKILL_ICE_HAIL; }

	void execute(Monster*, ZoneCoord_t X, ZoneCoord_t Y);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern IceHail g_IceHail;

#endif // __SKILL_ICE_HAIL_HANDLER_H__
