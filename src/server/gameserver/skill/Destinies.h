//////////////////////////////////////////////////////////////////////////////
// Filename    : Destinies.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DESTINIES_HANDLER_H__
#define __SKILL_DESTINIES_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Destinies;
//////////////////////////////////////////////////////////////////////////////

class Destinies: public SkillHandler 
{
public:
	Destinies()  {}
	~Destinies()  {}
	
public:
    string getSkillHandlerName()  { return "Destinies"; }

	SkillType_t getSkillType()  { return SKILL_DESTINIES; }

	void execute(Ousters* pOusters, ObjectID_t targetObject, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Destinies g_Destinies;

#endif // __SKILL_DESTINIES_HANDLER_H__
