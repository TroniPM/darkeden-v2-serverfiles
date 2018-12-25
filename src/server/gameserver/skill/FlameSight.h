//////////////////////////////////////////////////////////////////////////////
// Filename    : Light.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_FLAME_SIGHT_HANDLER_H__
#define __SKILL_FLAME_SIGHT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Light;
//////////////////////////////////////////////////////////////////////////////

class FlameSight: public SkillHandler 
{
public:
	FlameSight() throw() {}
	~FlameSight() throw() {}
	
public:
    string getSkillHandlerName()  { return "FlameSight"; }
	SkillType_t getSkillType()  { return SKILL_FLAME_SIGHT; }

	void execute(Ousters* pOusters, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern FlameSight g_FlameSight;

#endif // __SKILL_LIGHT_HANDLER_H__
