//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidStorm.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BAT_STORM2_HANDLER_H__
#define __SKILL_BAT_STORM2_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AcidStorm;
//////////////////////////////////////////////////////////////////////////////

class BatStorm2 : public SkillHandler 
{
public:
	BatStorm2() throw() {}
	~BatStorm2() throw() {}
	
public:
    string getSkillHandlerName()  { return "BatStorm2"; }
	SkillType_t getSkillType()  { return SKILL_BAT_STORM2; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BatStorm2 g_BatStorm2;

#endif // __SKILL_ACID_STORM_HANDLER_H__
