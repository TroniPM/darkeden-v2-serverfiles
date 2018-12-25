//////////////////////////////////////////////////////////////////////////////
// Filename    : ShadowDancing.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BAT_BREAK_HANDLER_H__
#define __SKILL_BAT_BREAK_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BatBreak;
//////////////////////////////////////////////////////////////////////////////

class BatBreak : public SkillHandler 
{
public:
	BatBreak() throw() {}
	~BatBreak() throw() {}
	
public:
    string getSkillHandlerName()  { return "BatBreak"; }
	SkillType_t getSkillType()  { return SKILL_BAT_BREAK; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID,  VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BatBreak g_BatBreak;

#endif // __SKILL_SHADOW_DANCING_HANDLER_H__
