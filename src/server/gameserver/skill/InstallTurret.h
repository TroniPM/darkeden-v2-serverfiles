//////////////////////////////////////////////////////////////////////////////
// Filename    : InstallTurret.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_INSTALL_TURRET_HANDLER_H__
#define __SKILL_INSTALL_TURRET_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class InstallTurret;
//////////////////////////////////////////////////////////////////////////////

class InstallTurret : public SkillHandler 
{
public:
	InstallTurret() throw() {}
	~InstallTurret() throw() {}
	
public:
    string getSkillHandlerName()  { return "InstallTurret"; }
	SkillType_t getSkillType()  { return SKILL_INSTALL_TURRET; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern InstallTurret g_InstallTurret;

#endif // __SKILL_INSTALL_TURRET_HANDLER_H__
