//////////////////////////////////////////////////////////////////////////////
// Filename    : Concealment.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOODY_SHOUT1_HANDLER_H__
#define __SKILL_BLOODY_SHOUT1_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Concealment;
//////////////////////////////////////////////////////////////////////////////

class BloodyShout1 : public SkillHandler 
{
public:
	BloodyShout1() throw() {}
	~BloodyShout1() throw() {}
	
public:
	string getSkillHandlerName()  { return "BloodyShout1"; }
	SkillType_t getSkillType()  { return SKILL_BLOODY_SHOUT1; }

	void execute(Vampire* pSlayer,  VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BloodyShout1 g_BloodyShout1;

#endif // __SKILL_CONCEALMENT_HANDLER_H__
