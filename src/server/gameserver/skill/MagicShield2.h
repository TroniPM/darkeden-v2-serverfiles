//////////////////////////////////////////////////////////////////////////////
// Filename    : Concealment.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_MAGIC_SHIELD2_HANDLER_H__
#define __SKILL_MAGIC_SHIELD2_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Concealment;
//////////////////////////////////////////////////////////////////////////////

class MagicShield2 : public SkillHandler 
{
public:
	MagicShield2() throw() {}
	~MagicShield2() throw() {}
	
public:
	string getSkillHandlerName()  { return "MagicShield2"; }
	SkillType_t getSkillType()  { return SKILL_MAGIC_SHIELD2; }

	void execute(Slayer* pSlayer,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern MagicShield2 g_MagicShield2;

#endif // __SKILL_CONCEALMENT_HANDLER_H__
