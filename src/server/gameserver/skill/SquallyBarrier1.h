//////////////////////////////////////////////////////////////////////////////
// Filename    : Concealment.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SQUALLY_BARRIER1_HANDLER_H__
#define __SKILL_SQUALLY_BARRIER1_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Concealment;
//////////////////////////////////////////////////////////////////////////////

class SquallyBarrier1 : public SkillHandler 
{
public:
	SquallyBarrier1() throw() {}
	~SquallyBarrier1() throw() {}
	
public:
	string getSkillHandlerName()  { return "SquallyBarrier1"; }
	SkillType_t getSkillType()  { return SKILL_SQUALLY_BARRIER1; }

	void execute(Ousters* pSlayer,  OustersSkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SquallyBarrier1 g_SquallyBarrier1;

#endif // __SKILL_CONCEALMENT_HANDLER_H__
