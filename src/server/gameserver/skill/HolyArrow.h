//////////////////////////////////////////////////////////////////////////////
// Filename    : HolyArrow.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HOLY_ARROW_HANDLER_H__
#define __SKILL_HOLY_ARROW_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class HolyArrow;
//////////////////////////////////////////////////////////////////////////////

class HolyArrow : public SkillHandler 
{
public:
	HolyArrow() throw() {}
	~HolyArrow() throw() {}
	
public:
    string getSkillHandlerName()  { return "HolyArrow"; }
	SkillType_t getSkillType()  { return SKILL_HOLY_ARROW; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern HolyArrow g_HolyArrow;

#endif // __SKILL_HOLY_ARROW_HANDLER_H__
