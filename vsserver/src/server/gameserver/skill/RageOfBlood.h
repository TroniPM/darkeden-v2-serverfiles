//////////////////////////////////////////////////////////////////////////////
// Filename    : Concealment.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_RAGE_OF_BLOOD_HANDLER_H__
#define __SKILL_RAGE_OF_BLOOD_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Concealment;
//////////////////////////////////////////////////////////////////////////////

class RageOfBlood : public SkillHandler 
{
public:
	RageOfBlood() throw() {}
	~RageOfBlood() throw() {}
	
public:
	string getSkillHandlerName() const throw() { return "RageOfBlood"; }
	SkillType_t getSkillType() const throw() { return SKILL_RAGE_OF_BLOOD; }

	void execute(Vampire* pSlayer,  VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern RageOfBlood g_RageOfBlood;

#endif // __SKILL_CONCEALMENT_HANDLER_H__
