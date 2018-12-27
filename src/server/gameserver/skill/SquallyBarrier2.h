//////////////////////////////////////////////////////////////////////////////
// Filename    : Concealment.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SQUALLY_BARRIER2_HANDLER_H__
#define __SKILL_SQUALLY_BARRIER2_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Concealment;
//////////////////////////////////////////////////////////////////////////////

class SquallyBarrier2 : public SkillHandler 
{
public:
	SquallyBarrier2()  {}
	~SquallyBarrier2()  {}
	
public:
	string getSkillHandlerName()  { return "SquallyBarrier2"; }
	SkillType_t getSkillType()  { return SKILL_SQUALLY_BARRIER2; }

	void execute(Ousters* pSlayer,  OustersSkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SquallyBarrier2 g_SquallyBarrier2;

#endif // __SKILL_CONCEALMENT_HANDLER_H__
