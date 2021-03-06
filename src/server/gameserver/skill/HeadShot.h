//////////////////////////////////////////////////////////////////////////////
// Filename    : HeadShot.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HEAD_SHOT_HANDLER_H__
#define __SKILL_HEAD_SHOT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class HeadShot;
//////////////////////////////////////////////////////////////////////////////

class HeadShot : public SkillHandler 
{
public:
	HeadShot()  {}
	~HeadShot()  {}

public:
    string getSkillHandlerName()  { return "HeadShot"; }
	SkillType_t getSkillType()  { return SKILL_HEAD_SHOT; }

	void execute(Slayer* pPlayer, ObjectID_t ObjectID, SkillSlot*, CEffectID_t);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern HeadShot g_HeadShot;

#endif // __SKILL_HEAD_SHOT_HANDLER_H__
