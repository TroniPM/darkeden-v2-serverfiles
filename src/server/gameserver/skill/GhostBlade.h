//////////////////////////////////////////////////////////////////////////////
// Filename    : GhostBlade.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_GHOST_BLADE_HANDLER_H__
#define __SKILL_GHOST_BLADE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class GhostBlade;
//////////////////////////////////////////////////////////////////////////////

class GhostBlade : public SkillHandler 
{
public:
	GhostBlade()  {}
	~GhostBlade()  {}
	
public:
    string getSkillHandlerName()  { return "GhostBlade"; }
	SkillType_t getSkillType()  { return SKILL_GHOST_BLADE; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern GhostBlade g_GhostBlade;

#endif // __SKILL_GHOST_BLADE_HANDLER_H__
