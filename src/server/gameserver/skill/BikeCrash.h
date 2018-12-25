//////////////////////////////////////////////////////////////////////////////
// Filename    : BikeCrash.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BIKE_CRASH_HANDLER_H__
#define __SKILL_BIKE_CRASH_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BikeCrash;
//////////////////////////////////////////////////////////////////////////////

class BikeCrash : public SkillHandler 
{
public:
	BikeCrash() throw() {}
	~BikeCrash() throw() {}
	
public:
    string getSkillHandlerName()  { return "BikeCrash"; }
	SkillType_t getSkillType()  { return SKILL_BIKE_CRASH; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BikeCrash g_BikeCrash;

#endif // __SKILL_BIKE_CRASH_HANDLER_H__
