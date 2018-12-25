//////////////////////////////////////////////////////////////////////////////
// Filename    : Resurrect.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOODY_WINGS_HANDLER_H__
#define __SKILL_BLOODY_WINGS_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Resurrect;
//////////////////////////////////////////////////////////////////////////////

class BloodyWings : public SkillHandler 
{
public:
	BloodyWings() throw() {}
	~BloodyWings() throw() {}
	
public:
    string getSkillHandlerName()  { return "BloodyWings"; }

	SkillType_t getSkillType()  { return SKILL_BLOODY_WINGS; }

	void execute(Vampire* pSlayer, ObjectID_t ObjectID, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BloodyWings g_BloodyWings;

#endif // __SKILL_RESURRECT_HANDLER_H__
