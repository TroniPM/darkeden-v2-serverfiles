//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidSwamp.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ACID_SWAMP_HANDLER_H__
#define __SKILL_ACID_SWAMP_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AcidSwamp;
//////////////////////////////////////////////////////////////////////////////

class AcidSwamp : public SkillHandler 
{
public:
	AcidSwamp()  {}
	~AcidSwamp()  {}
	
public:
    string getSkillHandlerName()  { return "AcidSwamp"; }
	SkillType_t getSkillType()  { return SKILL_ACID_SWAMP; }

	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Vampire* pVampire, ObjectID_t,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Monster*, ZoneCoord_t X, ZoneCoord_t Y);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern AcidSwamp g_AcidSwamp;

#endif // __SKILL_ACID_SWAMP_HANDLER_H__
