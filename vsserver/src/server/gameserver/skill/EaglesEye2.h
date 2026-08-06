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
	EaglesEye2() throw() {}
	~EaglesEye2() throw() {}
	
public:
	string getSkillHandlerName() const throw() { return "EaglesEye2"; }
	SkillType_t getSkillType() const throw() { return SKILL_EAGLES_EYE2; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern EaglesEye2 g_EaglesEye2;

#endif // __SKILL_CONCEALMENT_HANDLER_H__
