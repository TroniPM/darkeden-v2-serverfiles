//////////////////////////////////////////////////////////////////////////////
// Filename    : ShineSword.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SHINE_SWORD_HANDLER_H__
#define __SKILL_SHINE_SWORD_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ShineSword;
//////////////////////////////////////////////////////////////////////////////

class ShineSword : public SkillHandler 
{
public:
	ShineSword() throw() {}
	~ShineSword() throw() {}
	
public:
    string getSkillHandlerName()  { return "ShineSword"; }
	SkillType_t getSkillType()  { return SKILL_SHINE_SWORD; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ShineSword g_ShineSword;

#endif // __SKILL_MENTAL_SWORD_HANDLER_H__
