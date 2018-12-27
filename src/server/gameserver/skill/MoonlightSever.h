//////////////////////////////////////////////////////////////////////////////
// Filename    : MoonlightSever.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_MOONLIGHT_SEVER_HANDLER_H__
#define __SKILL_MOONLIGHT_SEVER_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class MoonlightSever;
//////////////////////////////////////////////////////////////////////////////

class MoonlightSever : public SkillHandler 
{
public:
	MoonlightSever()  {}
	~MoonlightSever()  {}
	
public:
    string getSkillHandlerName()  { return "MoonlightSever"; }
	SkillType_t getSkillType()  { return SKILL_MOONLIGHT_SEVER; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern MoonlightSever g_MoonlightSever;

#endif // __SKILL_MOONLIGHT_SEVER_HANDLER_H__
