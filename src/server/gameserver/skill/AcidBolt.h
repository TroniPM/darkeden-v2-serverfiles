//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidBolt.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ACID_BOLT_HANDLER_H__
#define __SKILL_ACID_BOLT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AcidBolt;
//////////////////////////////////////////////////////////////////////////////

class AcidBolt : public SkillHandler 
{
public:
	AcidBolt() throw() {}
	~AcidBolt() throw() {}
	
public:
    string getSkillHandlerName()  { return "AcidBolt"; }
	SkillType_t getSkillType()  { return SKILL_ACID_BOLT; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern AcidBolt g_AcidBolt;

#endif // __SKILL_ACID_BOLT_HANDLER_H__
