//////////////////////////////////////////////////////////////////////////////
// Filename    : Striking.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_STRIKING2_HANDLER_H__
#define __SKILL_STRIKING2_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Striking;
//////////////////////////////////////////////////////////////////////////////

class Striking2 : public SkillHandler 
{
public:
	Striking2() throw() {}
	~Striking2() throw() {}

public:
    string getSkillHandlerName()  { return "Striking2"; }
	SkillType_t getSkillType()  { return SKILL_STRIKING2; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Striking2 g_Striking2;

#endif // __SKILL_STRIKING_HANDLER_H__
