//////////////////////////////////////////////////////////////////////////////
// Filename    : MercyGround.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_MERCY_GROUND_HANDLER_H__
#define __SKILL_MERCY_GROUND_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class MercyGround;
//////////////////////////////////////////////////////////////////////////////

class MercyGround : public SkillHandler 
{
public:
	MercyGround() throw() {}
	~MercyGround() throw() {}
	
public:
    string getSkillHandlerName()  { return "MercyGround"; }
	SkillType_t getSkillType()  { return SKILL_MERCY_GROUND; }

	void execute( Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID );
	void execute( Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID );

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern MercyGround g_MercyGround;

#endif // __SKILL_MERCY_GROUND_HANDLER_H__
