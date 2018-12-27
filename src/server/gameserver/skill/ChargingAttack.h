//////////////////////////////////////////////////////////////////////////////
// Filename    : ChargingAttack.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CHARGING_ATTACK_HANDLER_H__
#define __SKILL_CHARGING_ATTACK_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ChargingAttack;
//////////////////////////////////////////////////////////////////////////////

class ChargingAttack : public SkillHandler 
{
public:
	ChargingAttack()  {}
	~ChargingAttack()  {}
	
public:
    string getSkillHandlerName()  { return "ChargingAttack"; }
	SkillType_t getSkillType()  { return SKILL_CHARGING_ATTACK; }

	void execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ChargingAttack g_ChargingAttack;

#endif // __SKILL_CHARGING_ATTACK_HANDLER_H__
