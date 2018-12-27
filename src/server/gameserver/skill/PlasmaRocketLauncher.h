//////////////////////////////////////////////////////////////////////////////
// Filename    : PlasmaRocketLauncher.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_PLASMA_ROCKET_LAUNCHER_HANDLER_H__
#define __SKILL_PLASMA_ROCKET_LAUNCHER_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class PlasmaRocketLauncher;
//////////////////////////////////////////////////////////////////////////////

class PlasmaRocketLauncher: public SkillHandler 
{
public:
	PlasmaRocketLauncher()  {}
	~PlasmaRocketLauncher()  {}

public:
    string getSkillHandlerName()  { return "PlasmaRocketLauncher"; }
	SkillType_t getSkillType()  { return SKILL_PLASMA_ROCKET_LAUNCHER; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern PlasmaRocketLauncher g_PlasmaRocketLauncher;

#endif // __SKILL_PLASMA_ROCKET_LAUNCHER_HANDLER_H__
