//////////////////////////////////////////////////////////////////////////////
// Filename    : Concealment.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_MAGIC_SHIELD1_HANDLER_H__
#define __SKILL_MAGIC_SHIELD1_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Concealment;
//////////////////////////////////////////////////////////////////////////////

class MagicShield1 : public SkillHandler 
{
public:
	MagicShield1() throw() {}
	~MagicShield1() throw() {}
	
public:
	string getSkillHandlerName()  { return "MagicShield1"; }
	SkillType_t getSkillType()  { return SKILL_MAGIC_SHIELD1; }

	void execute(Slayer* pSlayer,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern MagicShield1 g_MagicShield1;

#endif // __SKILL_CONCEALMENT_HANDLER_H__
