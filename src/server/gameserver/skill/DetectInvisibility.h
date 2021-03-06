//////////////////////////////////////////////////////////////////////////////
// Filename    : DetectInvisibility.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DETECT_INVISIBILITY_HANDLER_H__
#define __SKILL_DETECT_INVISIBILITY_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class DetectInvisibility
//////////////////////////////////////////////////////////////////////////////

class DetectInvisibility: public SkillHandler 
{
public:
	DetectInvisibility()  {}
	~DetectInvisibility()  {}
	
public:
    string getSkillHandlerName()  { return "DetectInvisibility"; }

	SkillType_t getSkillType()  { return SKILL_DETECT_INVISIBILITY; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern DetectInvisibility g_DetectInvisibility;

#endif // __SKILL_DETECT_INVISIBILITY_HANDLER_H__
