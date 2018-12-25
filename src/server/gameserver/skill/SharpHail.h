//////////////////////////////////////////////////////////////////////////////
// Filename    : SharpHail.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SHARP_HAIL_HANDLER_H__
#define __SKILL_SHARP_HAIL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SharpHail;
//////////////////////////////////////////////////////////////////////////////

class SharpHail : public SkillHandler 
{
public:
	SharpHail() throw() {}
	~SharpHail() throw() {}
	
public:
    string getSkillHandlerName()  { return "SharpHail"; }
	SkillType_t getSkillType()  { return SKILL_SHARP_HAIL; }

	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);
	void execute(Ousters* pOusters, ObjectID_t, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SharpHail g_SharpHail;

#endif // __SKILL_SHARP_HAIL_HANDLER_H__
