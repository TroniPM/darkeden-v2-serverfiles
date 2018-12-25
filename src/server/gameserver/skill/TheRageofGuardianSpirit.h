//////////////////////////////////////////////////////////////////////////////
// Filename    : HandsOfFire.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_THE_RAGE_OF_GUARDIAN_SPIRIT_HANDLER_H__
#define __SKILL_THE_RAGE_OF_GUARDIAN_SPIRIT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class HandsOfFire;
//////////////////////////////////////////////////////////////////////////////

class TheRageofGuardianSpirit : public SkillHandler 
{
public:
	TheRageofGuardianSpirit() throw() {}
	~TheRageofGuardianSpirit() throw() {}
	
public:
    string getSkillHandlerName()  { return "TheRageofGuardianSpirit"; }
	SkillType_t getSkillType()  { return SKILL_THE_RAGE_OF_GUARDIAN_SPIRIT; }

	void execute(Ousters* pOusters,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TheRageofGuardianSpirit g_TheRageofGuardianSpirit;

#endif // __SKILL_HANDS_OF_FIRE_HANDLER_H__
