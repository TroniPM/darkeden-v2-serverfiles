//////////////////////////////////////////////////////////////////////////////
// Filename    : ShadowDancing.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SHADOW_DANCING_HANDLER_H__
#define __SKILL_SHADOW_DANCING_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ShadowDancing;
//////////////////////////////////////////////////////////////////////////////

class ShadowDancing : public SkillHandler 
{
public:
	ShadowDancing()  {}
	~ShadowDancing()  {}
	
public:
    string getSkillHandlerName()  { return "ShadowDancing"; }
	SkillType_t getSkillType()  { return SKILL_SHADOW_DANCING; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ShadowDancing g_ShadowDancing;

#endif // __SKILL_SHADOW_DANCING_HANDLER_H__
