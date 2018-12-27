//////////////////////////////////////////////////////////////////////////////
// Filename    : Eternity.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ETERNITY_HANDLER_H__
#define __SKILL_ETERNITY_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Eternity;
//////////////////////////////////////////////////////////////////////////////

class Eternity : public SkillHandler 
{
public:
	Eternity()  {}
	~Eternity()  {}
	
public:
    string getSkillHandlerName()  { return "Eternity"; }
	SkillType_t getSkillType()  { return SKILL_ETERNITY; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Eternity g_Eternity;

#endif // __SKILL_ETERNITY_HANDLER_H__
