//////////////////////////////////////////////////////////////////////////////
// Filename    : ChargingAttack.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SUDDEN_BLAST_HANDLER_H__
#define __SKILL_SUDDEN_BLAST_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ChargingAttack;
//////////////////////////////////////////////////////////////////////////////

class SuddenBlast : public SkillHandler 
{
public:
	SuddenBlast() throw() {}
	~SuddenBlast() throw() {}
	
public:
    string getSkillHandlerName()  { return "SuddenBlast"; }
	SkillType_t getSkillType()  { return SKILL_SUDDEN_BLAST; }

	void execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SuddenBlast g_SuddenBlast;

#endif // __SKILL_CHARGING_ATTACK_HANDLER_H__
