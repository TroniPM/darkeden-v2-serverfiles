//////////////////////////////////////////////////////////////////////////////
// Filename    : Restore.h 
// Written By  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_RESTORE_HANDLER_H__
#define __SKILL_RESTORE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Restore;
//////////////////////////////////////////////////////////////////////////////

class NPC;

class Restore: public SkillHandler 
{
public:
	Restore()  {}
	~Restore()  {}
	
public:
    string getSkillHandlerName()  { return "Restore"; }
	SkillType_t getSkillType()  { return SKILL_RESTORE; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(NPC* pNPC, Creature* pTargetCreature);

	void computeOutput(const SkillInput& input, SkillOutput& output) {}
};

// global variable declaration
extern Restore g_Restore;

#endif // __SKILL_RESTORE_HANDLER_H__
