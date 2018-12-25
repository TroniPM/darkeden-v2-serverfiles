//////////////////////////////////////////////////////////////////////////////
// Filename    : SetAfire.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SET_AFIRE_HANDLER_H__
#define __SKILL_SET_AFIRE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SetAfire;
//////////////////////////////////////////////////////////////////////////////

class SetAfire: public SkillHandler 
{
public:
	SetAfire() throw() {}
	~SetAfire() throw() {}
	
public:
    string getSkillHandlerName()  { return "SetAfire"; }

	SkillType_t getSkillType()  { return SKILL_SET_AFIRE; }

	void execute(Vampire* pVampire, ObjectID_t targetObject, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SetAfire g_SetAfire;

#endif // __SKILL_SET_AFIRE_HANDLER_H__
