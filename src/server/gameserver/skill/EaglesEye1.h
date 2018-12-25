//////////////////////////////////////////////////////////////////////////////
// Filename    : Concealment.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_EAGLES_EYE1_HANDLER_H__
#define __SKILL_EAGLES_EYE1_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Concealment;
//////////////////////////////////////////////////////////////////////////////

class EaglesEye1 : public SkillHandler 
{
public:
	EaglesEye1() throw() {}
	~EaglesEye1() throw() {}
	
public:
	string getSkillHandlerName()  { return "EaglesEye1"; }
	SkillType_t getSkillType()  { return SKILL_EAGLES_EYE1; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern EaglesEye1 g_EaglesEye1;

#endif // __SKILL_CONCEALMENT_HANDLER_H__
