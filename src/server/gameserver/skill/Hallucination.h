//////////////////////////////////////////////////////////////////////////////
// Filename    : Hallucination.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HALLUCINATION_HANDLER_H__
#define __SKILL_HALLUCINATION_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Hallucination;
//////////////////////////////////////////////////////////////////////////////

class Hallucination : public SkillHandler 
{
public:
	Hallucination()  {}
	~Hallucination()  {}
	
public:
    string getSkillHandlerName()  { return "Hallucination"; }
	SkillType_t getSkillType()  { return SKILL_HALLUCINATION; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);
	void executeMonster(Zone* pZone, Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Hallucination g_Hallucination;

#endif // __SKILL_HALLUCINATION_HANDLER_H__
