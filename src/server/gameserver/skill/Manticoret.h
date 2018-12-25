//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidBall.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_MANTICORET_HANDLER_H__
#define __SKILL_MANTICORET_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AcidBall
//////////////////////////////////////////////////////////////////////////////

class Manticoret : public SkillHandler 
{
public:
	Manticoret() throw() {}
	~Manticoret() throw() {}
	
public:
    string getSkillHandlerName()  { return "Manticoret"; }
	SkillType_t getSkillType()  { return SKILL_MANTICORET; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Manticoret g_Manticoret;

#endif // __SKILL_ACID_BALL_HANDLER_H__
