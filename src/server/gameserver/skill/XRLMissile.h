//////////////////////////////////////////////////////////////////////////////
// Filename    : XRL Missile.h 
// Written By  : rallser
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_XRL_Missile_HANDLER_H__
#define __SKILL_XRL_Missile_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class XRLMissile;
//////////////////////////////////////////////////////////////////////////////

class XRLMissile: public SkillHandler 
{
public:
	XRLMissile()  {}
	~XRLMissile()  {}

public:
    string getSkillHandlerName()  { return "XRLMissile"; }
	SkillType_t getSkillType()  { return SKILL_XRL_Missile; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern XRLMissile g_XRLMissile;

#endif // __SKILL_XRL_Missile_HANDLER_H__
