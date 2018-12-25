//////////////////////////////////////////////////////////////////////////////
// Filename    : HeavenGround.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_MAGMA_DETONATION1_HANDLER_H__
#define __SKILL_MAGMA_DETONATION1_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class MagmaDetonation1;
//////////////////////////////////////////////////////////////////////////////

class MagmaDetonation1 : public SkillHandler 
{
public:
	MagmaDetonation1() throw() {}
	~MagmaDetonation1() throw() {}
	
public:
    string getSkillHandlerName()  { return "MagmaDetonation1"; }
	SkillType_t getSkillType()  { return SKILL_MAGMA_DETONATION1; }

	void execute( Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID );
	void execute( Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID );

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern MagmaDetonation1 g_MagmaDetonation1;

#endif // __SKILL_HEAVEN_GROUND_HANDLER_H__
