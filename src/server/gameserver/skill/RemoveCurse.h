//////////////////////////////////////////////////////////////////////////////
// Filename    : RemoveCurse.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_REMOVE_CURSE_HANDLER_H__
#define __SKILL_REMOVE_CURSE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class RemoveCurse;
//////////////////////////////////////////////////////////////////////////////

class RemoveCurse: public SkillHandler 
{
public:
	RemoveCurse() throw() {}
	~RemoveCurse() throw() {}
	
public:
    string getSkillHandlerName()  { return "RemoveCurse"; }
	SkillType_t getSkillType()  { return SKILL_REMOVE_CURSE; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern RemoveCurse g_RemoveCurse;

#endif // __SKILL_REMOVE_CURSE_HANDLER_H__
