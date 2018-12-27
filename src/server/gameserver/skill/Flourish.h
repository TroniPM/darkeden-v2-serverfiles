//////////////////////////////////////////////////////////////////////////////
// Filename    : Flourish.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_FLOURISH_HANDLER_H__
#define __SKILL_FLOURISH_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Flourish;
//////////////////////////////////////////////////////////////////////////////

class Flourish: public SkillHandler 
{
public:
	Flourish()  {}
	~Flourish()  {}
	
public:
    string getSkillHandlerName()  { return "Flourish"; }

	SkillType_t getSkillType()  { return SKILL_FLOURISH; }

	void execute(Ousters* pOusters, ObjectID_t targetObject, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Flourish g_Flourish;

#endif // __SKILL_FLOURISH_HANDLER_H__
