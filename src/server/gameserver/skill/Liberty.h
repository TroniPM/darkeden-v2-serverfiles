//////////////////////////////////////////////////////////////////////////////
// Filename    : Liberty.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_LIBERTY_HANDLER_H__
#define __SKILL_LIBERTY_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Liberty;
//////////////////////////////////////////////////////////////////////////////

class Liberty : public SkillHandler 
{
public:
	Liberty()  {}
	~Liberty()  {}
	
public:
    string getSkillHandlerName()  { return "Liberty"; }
	SkillType_t getSkillType()  { return SKILL_LIBERTY; }

	void execute(Ousters* pOusters, ObjectID_t ObjectID, OustersSkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Liberty g_Liberty;

#endif // __SKILL_LIBERTY_HANDLER_H__
