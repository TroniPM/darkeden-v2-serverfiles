//////////////////////////////////////////////////////////////////////////////
// Filename    : Concealment.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ENERGY_BURST_HANDLER_H__
#define __SKILL_ENERGY_BURST_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Concealment;
//////////////////////////////////////////////////////////////////////////////

class EnergyBurst : public SkillHandler 
{
public:
	EnergyBurst()  {}
	~EnergyBurst()  {}
	
public:
	string getSkillHandlerName()  { return "EnergyBurst"; }
	SkillType_t getSkillType()  { return SKILL_ENERGY_BURST; }

	void execute(Ousters* pSlayer,  OustersSkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern EnergyBurst g_EnergyBurst;

#endif // __SKILL_CONCEALMENT_HANDLER_H__
