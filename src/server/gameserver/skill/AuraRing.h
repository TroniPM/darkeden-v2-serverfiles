//////////////////////////////////////////////////////////////////////////////
// Filename    : AuraRing.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_AURA_RING_HANDLER_H__
#define __SKILL_AURA_RING_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AuraRing;
//////////////////////////////////////////////////////////////////////////////

class AuraRing : public SkillHandler 
{
public:
	AuraRing() throw() {}
	~AuraRing() throw() {}
	
public:
    string getSkillHandlerName()  { return "AuraRing"; }

	SkillType_t getSkillType()  { return SKILL_AURA_RING; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern AuraRing g_AuraRing;

#endif // __SKILL_AURA_RING_HANDLER_H__
