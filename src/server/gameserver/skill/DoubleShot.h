//////////////////////////////////////////////////////////////////////////////
// Filename    : DoubleShot.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DOUBLE_SHOT_HANDLER_H__
#define __SKILL_DOUBLE_SHOT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class DoubleShot;
//////////////////////////////////////////////////////////////////////////////

class DoubleShot : public SkillHandler 
{
public:
	DoubleShot() throw() {}
	~DoubleShot() throw() {}

public:
    string getSkillHandlerName()  { return "DoubleShot"; }
	SkillType_t getSkillType()  { return SKILL_DOUBLE_SHOT; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern DoubleShot g_DoubleShot;

#endif // __SKILL_DOUBLE_SHOT_HANDLER_H__
