//////////////////////////////////////////////////////////////////////////////
// Filename    : HeavenGround.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_MAGMA_DETONATION2_HANDLER_H__
#define __SKILL_MAGMA_DETONATION2_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class MagmaDetonation2;
//////////////////////////////////////////////////////////////////////////////

class MagmaDetonation2 : public SkillHandler 
{
public:
	MagmaDetonation2() throw() {}
	~MagmaDetonation2() throw() {}
	
public:
    string getSkillHandlerName()  { return "MagmaDetonation2"; }
	SkillType_t getSkillType()  { return SKILL_MAGMA_DETONATION2; }

	void execute( Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID );
	void execute( Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID );

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern MagmaDetonation2 g_MagmaDetonation2;

#endif // __SKILL_HEAVEN_GROUND_HANDLER_H__
