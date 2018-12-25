//////////////////////////////////////////////////////////////////////////////
// Filename    : Typhoon.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TYPHOON_HANDLER_H__
#define __SKILL_TYPHOON_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Typhoon;
//////////////////////////////////////////////////////////////////////////////

class Typhoon : public SkillHandler 
{
public:
	Typhoon() throw() {}
	~Typhoon() throw() {}
	
public:
    string getSkillHandlerName()  { return "Typhoon"; }
	SkillType_t getSkillType()  { return SKILL_TYPHOON; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Typhoon g_Typhoon;

#endif // __SKILL_TYPHOON_HANDLER_H__
