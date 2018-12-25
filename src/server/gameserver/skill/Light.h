//////////////////////////////////////////////////////////////////////////////
// Filename    : Light.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_LIGHT_HANDLER_H__
#define __SKILL_LIGHT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Light;
//////////////////////////////////////////////////////////////////////////////

class Light: public SkillHandler 
{
public:
	Light() throw() {}
	~Light() throw() {}
	
public:
    string getSkillHandlerName()  { return "Light"; }
	SkillType_t getSkillType()  { return SKILL_LIGHT; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Light g_Light;

#endif // __SKILL_LIGHT_HANDLER_H__
