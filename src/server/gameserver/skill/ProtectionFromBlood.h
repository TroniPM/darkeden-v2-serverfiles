//////////////////////////////////////////////////////////////////////////////
// Filename    : ProtectionFromBlood.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_PROTECTION_FROM_BLOOD_HANDLER_H__
#define __SKILL_PROTECTION_FROM_BLOOD_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ProtectionFromBlood;
//////////////////////////////////////////////////////////////////////////////

class ProtectionFromBlood: public SkillHandler 
{
public:
	ProtectionFromBlood() throw() {}
	~ProtectionFromBlood() throw() {}

public:
    string getSkillHandlerName()  { return "ProtectionFromBlood"; }
	SkillType_t getSkillType()  { return SKILL_PROTECTION_FROM_BLOOD; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ProtectionFromBlood g_ProtectionFromBlood;

#endif // __SKILL_PROTECTION_FROM_BLOOD_HANDLER_H__
