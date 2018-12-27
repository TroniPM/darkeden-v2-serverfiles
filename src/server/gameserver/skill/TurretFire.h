//////////////////////////////////////////////////////////////////////////////
// Filename    : TurretFire.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TURRET_FIRE_HANDLER_H__
#define __SKILL_TURRET_FIRE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class TurretFire;
//////////////////////////////////////////////////////////////////////////////

class TurretFire : public SkillHandler 
{
public:
	TurretFire()  { }
	~TurretFire()  {}
	
public:
    string getSkillHandlerName()  { return "TurretFire"; }
	SkillType_t getSkillType()  { return SKILL_TURRET_FIRE; }

	void execute(Slayer* pSlayer, ObjectID_t targetObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TurretFire g_TurretFire;

#endif // __SKILL_TURRET_FIRE_H__
