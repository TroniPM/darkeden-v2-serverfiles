//////////////////////////////////////////////////////////////////////////////
// Filename    : Trident.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TRIDENT_HANDLER_H__
#define __SKILL_TRIDENT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Trident;
//////////////////////////////////////////////////////////////////////////////

class Trident : public SkillHandler 
{
public:
	Trident() throw() {}
	~Trident() throw() {}

public:
    string getSkillHandlerName()  { return "Trident"; }
	SkillType_t getSkillType()  { return SKILL_TRIDENT; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Trident g_Trident;

#endif // __SKILL_TRIDENT_HANDLER_H__
