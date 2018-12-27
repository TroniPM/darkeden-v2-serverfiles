//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidStorm.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ACID_STORM_HANDLER_H__
#define __SKILL_ACID_STORM_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AcidStorm;
//////////////////////////////////////////////////////////////////////////////

class AcidStorm : public SkillHandler 
{
public:
	AcidStorm()  {}
	~AcidStorm()  {}
	
public:
    string getSkillHandlerName()  { return "AcidStorm"; }
	SkillType_t getSkillType()  { return SKILL_ACID_STORM; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern AcidStorm g_AcidStorm;

#endif // __SKILL_ACID_STORM_HANDLER_H__
