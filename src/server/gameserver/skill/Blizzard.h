//////////////////////////////////////////////////////////////////////////////
// Filename    : ShadowOfStorm.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLIZZARD_HANDLER_H__
#define __SKILL_BLIZZARD_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ShadowOfStorm;
//////////////////////////////////////////////////////////////////////////////

class Blizzard : public SkillHandler 
{
public:
	Blizzard() throw() {}
	~Blizzard() throw() {}
	
public:
    string getSkillHandlerName()  { return "Blizzard"; }
	SkillType_t getSkillType()  { return SKILL_BLIZZARD; }

	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Ousters* pOusters, ObjectID_t ObjectID,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Blizzard g_Blizzard;

#endif // __SKILL_SHADOW_OF_STORM_HANDLER_H__
