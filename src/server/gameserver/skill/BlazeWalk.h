//////////////////////////////////////////////////////////////////////////////
// Filename    : BlazeWalk.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLAZE_WALK_HANDLER_H__
#define __SKILL_BLAZE_WALK_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BlazeWalk;
//////////////////////////////////////////////////////////////////////////////

class BlazeWalk : public SkillHandler 
{
public:
	BlazeWalk()  {}
	~BlazeWalk()  {}

public :
    string getSkillHandlerName()  { return "BlazeWalk"; }
	SkillType_t getSkillType()  { return SKILL_BLAZE_WALK; }

	void execute(Slayer* pSlayer,ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BlazeWalk g_BlazeWalk;

#endif // __SKILL_BLAZE_WALK_HANDLER_H__
