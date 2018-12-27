//////////////////////////////////////////////////////////////////////////////
// Filename    : InstallTrap.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_INSTALL_TRAP_HANDLER_H__
#define __SKILL_INSTALL_TRAP_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class InstallTrap;
//////////////////////////////////////////////////////////////////////////////

class InstallTrap : public SkillHandler 
{
public:
	InstallTrap()  {}
	~InstallTrap()  {}
	
public:
    string getSkillHandlerName()  { return "InstallTrap"; }
	SkillType_t getSkillType()  { return SKILL_INSTALL_TRAP; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern InstallTrap g_InstallTrap;

#endif // __SKILL_INSTALL_TRAP_HANDLER_H__
