//////////////////////////////////////////////////////////////////////////////
// Filename    : Tendril.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TENDRIL_HANDLER_H__
#define __SKILL_TENDRIL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Tendril;
//////////////////////////////////////////////////////////////////////////////

class Tendril : public SkillHandler 
{
public:
	Tendril()  {}
	~Tendril()  {}
	
public:
    string getSkillHandlerName()  { return "Tendril"; }
	SkillType_t getSkillType()  { return SKILL_TENDRIL; }

	void execute(Ousters* pOusters, ObjectID_t ObjectID, OustersSkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Tendril g_Tendril;

#endif // __SKILL_TENDRIL_HANDLER_H__
