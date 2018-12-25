//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidStorm.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOODY_SKULL_HANDLER_H__
#define __SKILL_BLOODY_SKULL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BloodySkull;
//////////////////////////////////////////////////////////////////////////////

class BloodySkull : public SkillHandler 
{
public:
	BloodySkull() throw() {}
	~BloodySkull() throw() {}
	
public:
    string getSkillHandlerName()  { return "BloodySkull"; }
	SkillType_t getSkillType()  { return SKILL_BLOODY_SKULL; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BloodySkull g_BloodySkull;

#endif // __SKILL_ACID_STORM_HANDLER_H__
