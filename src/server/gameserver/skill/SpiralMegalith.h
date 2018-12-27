//////////////////////////////////////////////////////////////////////////////
// Filename    : MeteorStorm.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SPIRAL_MEGALITH_HANDLER_H__
#define __SKILL_SPIRAL_MEGALITH_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class MeteorStorm;
//////////////////////////////////////////////////////////////////////////////

class SpiralMegalith : public SkillHandler 
{
public:
	SpiralMegalith()  {}
	~SpiralMegalith()  {}
	
public:
    string getSkillHandlerName()  { return "SpiralMegalith"; }
	SkillType_t getSkillType()  { return SKILL_SPIRAL_MEGALITH; }

	void execute(Ousters* pOusters, ObjectID_t ObjectID,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SpiralMegalith g_SpiralMegalith;

#endif // __SKILL_METEOR_STORM_HANDLER_H__
