//////////////////////////////////////////////////////////////////////////////
// Filename    : MultiThrowingAxe.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_MULTI_THROWING_AXE_HANDLER_H__
#define __SKILL_MULTI_THROWING_AXE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class MultiThrowingAxe;
//////////////////////////////////////////////////////////////////////////////

class MultiThrowingAxe : public SkillHandler 
{
public:
	MultiThrowingAxe()  {}
	~MultiThrowingAxe()  {}
	
public:
    string getSkillHandlerName()  { return "MultiThrowingAxe"; }
	SkillType_t getSkillType()  { return SKILL_MULTI_THROWING_AXE; }

	void execute(Monster*, ZoneCoord_t X, ZoneCoord_t Y);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern MultiThrowingAxe g_MultiThrowingAxe;

#endif // __SKILL_MULTI_THROWING_AXE_HANDLER_H__
