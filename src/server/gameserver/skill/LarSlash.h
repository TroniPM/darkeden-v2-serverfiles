//////////////////////////////////////////////////////////////////////////////
// Filename    : LarSlash.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_LAR_SLASH_HANDLER_H__
#define __SKILL_LAR_SLASH_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class LarSlash;
//////////////////////////////////////////////////////////////////////////////

class LarSlash : public SkillHandler 
{
public:
	LarSlash() throw() {}
	~LarSlash() throw() {}
	
public:
    string getSkillHandlerName()  { return "LarSlash"; }
	SkillType_t getSkillType()  { return SKILL_LAR_SLASH; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern LarSlash g_LarSlash;

#endif // __SKILL_LAR_SLASH_HANDLER_H__
