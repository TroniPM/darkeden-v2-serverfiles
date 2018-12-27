//////////////////////////////////////////////////////////////////////////////
// Filename    : SharpRound.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SHARP_ROUND_HANDLER_H__
#define __SKILL_SHARP_ROUND_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SharpRound;
//////////////////////////////////////////////////////////////////////////////

class SharpRound: public SkillHandler 
{
public:
	SharpRound()  {}
	~SharpRound()  {}
	
public:
    string getSkillHandlerName()  { return "SharpRound"; }

	SkillType_t getSkillType()  { return SKILL_SHARP_ROUND; }

	void execute(Ousters* pOusters, ObjectID_t targetObject, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SharpRound g_SharpRound;

#endif // __SKILL_SHARP_ROUND_HANDLER_H__
