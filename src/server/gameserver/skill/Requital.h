//////////////////////////////////////////////////////////////////////////////
// Filename    : Requital.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_REQUITAL_HANDLER_H__
#define __SKILL_REQUITAL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Requital;
//////////////////////////////////////////////////////////////////////////////

class Requital: public SkillHandler 
{
public:
	Requital()  {}
	~Requital()  {}
	
public:
    string getSkillHandlerName()  { return "Requital"; }
	SkillType_t getSkillType()  { return SKILL_REQUITAL; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Requital g_Requital;

#endif // __SKILL_REQUITAL_HANDLER_H__
