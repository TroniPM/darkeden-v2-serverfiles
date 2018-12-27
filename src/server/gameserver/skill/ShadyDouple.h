//////////////////////////////////////////////////////////////////////////////
// Filename    : BlazeWalk.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SHADY_DOUPLE_HANDLER_H__
#define __SKILL_SHADY_DOUPLE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BlazeWalk;
//////////////////////////////////////////////////////////////////////////////

class ShadyDouple : public SkillHandler 
{
public:
	ShadyDouple()  {}
	~ShadyDouple()  {}

public :
    string getSkillHandlerName()  { return "ShadyDouple"; }
	SkillType_t getSkillType()  { return SKILL_SHADY_DOUPLE; }

	void execute(Vampire * pVampire, ObjectID_t TargetObjectID, VampireSkillSlot * pVampireSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ShadyDouple g_ShadyDouple;

#endif // __SKILL_SHADY_DOUPLE_HANDLER_H__
