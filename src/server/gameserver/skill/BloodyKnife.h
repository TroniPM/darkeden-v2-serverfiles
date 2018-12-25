//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyKnife.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOODY_KNIFE_HANDLER_H__
#define __SKILL_BLOODY_KNIFE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BloodyKnife;
//////////////////////////////////////////////////////////////////////////////

class BloodyKnife : public SkillHandler 
{
public:
	BloodyKnife() throw() {}
	~BloodyKnife() throw() {}
	
public:
    string getSkillHandlerName()  { return "BloodyKnife"; }
	SkillType_t getSkillType()  { return SKILL_BLOODY_KNIFE; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BloodyKnife g_BloodyKnife;

#endif // __SKILL_BLOODY_KNIFE_HANDLER_H__
