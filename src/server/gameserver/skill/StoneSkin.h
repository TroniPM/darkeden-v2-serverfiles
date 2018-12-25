//////////////////////////////////////////////////////////////////////////////
// Filename    : StoneSkin.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////

#ifndef __SKILL_STONE_SKIN_HANDLER_H__
#define __SKILL_STONE_SKIN_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class StoneSkin;
//////////////////////////////////////////////////////////////////////////////

class StoneSkin : public SkillHandler 
{
public:
	StoneSkin() throw() {}
	~StoneSkin() throw() {}
	
public:
    string getSkillHandlerName()  { return "StoneSkin"; }
	SkillType_t getSkillType()  { return SKILL_STONE_SKIN; }

	void execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);


	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern StoneSkin g_StoneSkin;

#endif // __SKILL_STONE_SKIN_HANDLER_H__
