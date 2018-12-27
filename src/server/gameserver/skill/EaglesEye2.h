//////////////////////////////////////////////////////////////////////////////
// Filename    : Concealment.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_EAGLES_EYE2_HANDLER_H__
#define __SKILL_EAGLES_EYE2_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Concealment;
//////////////////////////////////////////////////////////////////////////////

class EaglesEye2 : public SkillHandler 
{
public:
	EaglesEye2()  {}
	~EaglesEye2()  {}
	
public:
	string getSkillHandlerName()  { return "EaglesEye2"; }
	SkillType_t getSkillType()  { return SKILL_EAGLES_EYE2; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern EaglesEye2 g_EaglesEye2;

#endif // __SKILL_CONCEALMENT_HANDLER_H__
