//////////////////////////////////////////////////////////////////////////////
// Filename    : BlazeBolt.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLAZE_BOLT_HANDLER_H__
#define __SKILL_BLAZE_BOLT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BlazeBolt;
//////////////////////////////////////////////////////////////////////////////

class BlazeBolt : public SkillHandler 
{
public:
	BlazeBolt()  {}
	~BlazeBolt()  {}
	
public:
    string getSkillHandlerName()  { return "BlazeBolt"; }
	SkillType_t getSkillType()  { return SKILL_BLAZE_BOLT; }

	void execute(Ousters* pOusters, ObjectID_t ObjectID,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BlazeBolt g_BlazeBolt;

#endif // __SKILL_BLAZE_BOLT_HANDLER_H__
