//////////////////////////////////////////////////////////////////////////////
// Filename    : Destinies.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DEMOLISHER_HANDLER_H__
#define __SKILL_DEMOLISHER_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Destinies;
//////////////////////////////////////////////////////////////////////////////

class Demolisher: public SkillHandler 
{
public:
	Demolisher()  {}
	~Demolisher()  {}
	
public:
    string getSkillHandlerName()  { return "Demolisher"; }

	SkillType_t getSkillType()  { return SKILL_DEMOLISHER; }

	void execute(Ousters* pOusters, ObjectID_t targetObject, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Demolisher g_Demolisher;

#endif // __SKILL_DESTINIES_HANDLER_H__
