//////////////////////////////////////////////////////////////////////////////
// Filename    : LarSlash.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_LAR_STROKE_HANDLER_H__
#define __SKILL_LAR_STROKE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class LarSlash;
//////////////////////////////////////////////////////////////////////////////

class LarStroke : public SkillHandler 
{
public:
	LarStroke()  {}
	~LarStroke()  {}
	
public:
    string getSkillHandlerName()  { return "LarStroke"; }
	SkillType_t getSkillType()  { return SKILL_LAR_STROKE; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern LarStroke g_LarStroke;

#endif // __SKILL_LAR_SLASH_HANDLER_H__
