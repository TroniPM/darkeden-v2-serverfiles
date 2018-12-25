//////////////////////////////////////////////////////////////////////////////
// Filename    : HeavenGround.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HEAVEN_GROUND_HANDLER_H__
#define __SKILL_HEAVEN_GROUND_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class HeavenGround;
//////////////////////////////////////////////////////////////////////////////

class HeavenGround : public SkillHandler 
{
public:
	HeavenGround() throw() {}
	~HeavenGround() throw() {}
	
public:
    string getSkillHandlerName()  { return "HeavenGround"; }
	SkillType_t getSkillType()  { return SKILL_HEAVEN_GROUND; }

	void execute( Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID );
	void execute( Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID );

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern HeavenGround g_HeavenGround;

#endif // __SKILL_HEAVEN_GROUND_HANDLER_H__
