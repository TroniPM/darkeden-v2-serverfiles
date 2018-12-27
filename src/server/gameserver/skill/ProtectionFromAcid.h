//////////////////////////////////////////////////////////////////////////////
// Filename    : ProtectionFromAcid.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_PROTECTION_FROM_ACID_HANDLER_H__
#define __SKILL_PROTECTION_FROM_ACID_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ProtectionFromAcid;
//////////////////////////////////////////////////////////////////////////////

class ProtectionFromAcid: public SkillHandler 
{
public:
	ProtectionFromAcid()  {}
	~ProtectionFromAcid()  {}

public:
    string getSkillHandlerName()  { return "ProtectionFromAcid"; }
	SkillType_t getSkillType()  { return SKILL_PROTECTION_FROM_ACID; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ProtectionFromAcid g_ProtectionFromAcid;

#endif // __SKILL_PROTECTION_FROM_ACID_HANDLER_H__
