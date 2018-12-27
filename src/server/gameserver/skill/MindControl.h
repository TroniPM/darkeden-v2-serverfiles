//////////////////////////////////////////////////////////////////////////////
// Filename    : MindControl.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_MIND_CONTROL_HANDLER_H__
#define __SKILL_MIND_CONTROL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class MindControl;
//////////////////////////////////////////////////////////////////////////////

class MindControl : public SkillHandler 
{
public:
	MindControl()  {}
	~MindControl()  {}
	
public :
    string getSkillHandlerName()  { return "MindControl"; }
	SkillType_t getSkillType()  { return SKILL_MIND_CONTROL; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern MindControl g_MindControl;

#endif // __SKILL_MIND_CONTROL_HANDLER_H__
