//////////////////////////////////////////////////////////////////////////////
// Filename    : DetectHidden.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DETECT_HIDDEN_HANDLER_H__
#define __SKILL_DETECT_HIDDEN_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class DetectHidden;
//////////////////////////////////////////////////////////////////////////////

class DetectHidden: public SkillHandler 
{
public:
	DetectHidden()  {}
	~DetectHidden()  {}
	
public:
    string getSkillHandlerName()  { return "DetectHidden"; }
	SkillType_t getSkillType()  { return SKILL_DETECT_HIDDEN; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern DetectHidden g_DetectHidden;

#endif // __SKILL_DETECT_HIDDEN_HANDLER_H__
