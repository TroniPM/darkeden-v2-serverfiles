//////////////////////////////////////////////////////////////////////////////
// Filename    : Paralyze.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_MIST_OF_SOUL2_HANDLER_H__
#define __SKILL_MIST_OF_SOUL2_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Paralyze;
//////////////////////////////////////////////////////////////////////////////

class MistOfSoul2: public SkillHandler 
{
public:
	MistOfSoul2() throw() {}
	~MistOfSoul2() throw() {}
	
public:
    string getSkillHandlerName()  { return "MistOfSoul2"; }
	SkillType_t getSkillType()  { return SKILL_MIST_OF_SOUL2; }

	void execute(Ousters* pOusters, OustersSkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern MistOfSoul2 g_MistOfSoul2;

#endif // __SKILL_PARALYZE_HANDLER_H__
