//////////////////////////////////////////////////////////////////////////////
// Filename    : DancingSword.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DANCING_SWORD_HANDLER_H__
#define __SKILL_DANCING_SWORD_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class DancingSword;
//////////////////////////////////////////////////////////////////////////////

class DancingSword : public SkillHandler 
{
public:
	DancingSword()  {}
	~DancingSword()  {}
	
public:
    string getSkillHandlerName()  { return "DancingSword"; }
	SkillType_t getSkillType()  { return SKILL_DANCING_SWORD; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern DancingSword g_DancingSword;

#endif // __SKILL_DANCING_SWORD_HANDLER_H__
