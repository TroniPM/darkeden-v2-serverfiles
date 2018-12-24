//////////////////////////////////////////////////////////////////////////////
// Filename    : SnakeCombo.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TANNING_HANDLER_H__
#define __SKILL_TANNING_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SnakeCombo;
//////////////////////////////////////////////////////////////////////////////

class Tanning : public SkillHandler 
{
public:
	Tanning() throw() {}
	~Tanning() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Tanning"; }
	SkillType_t getSkillType() const throw() { return SKILL_TANNING; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Ousters* pOusters, ObjectID_t ObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, Creature* pCreature) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Tanning g_Tanning;

#endif // __SKILL_SNAKE_COMBO_HANDLER_H__
