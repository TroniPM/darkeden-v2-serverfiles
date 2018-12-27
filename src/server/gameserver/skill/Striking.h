//////////////////////////////////////////////////////////////////////////////
// Filename    : Striking.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_STRIKING_HANDLER_H__
#define __SKILL_STRIKING_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Striking;
//////////////////////////////////////////////////////////////////////////////

class Striking : public SkillHandler 
{
public:
	Striking()  {}
	~Striking()  {}

public:
    string getSkillHandlerName()  { return "Striking"; }
	SkillType_t getSkillType()  { return SKILL_STRIKING; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Striking g_Striking;

#endif // __SKILL_STRIKING_HANDLER_H__
