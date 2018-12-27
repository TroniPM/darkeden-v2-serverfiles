//////////////////////////////////////////////////////////////////////////////
// Filename    : SnakeCombo.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SNAKE_COMBO_HANDLER_H__
#define __SKILL_SNAKE_COMBO_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SnakeCombo;
//////////////////////////////////////////////////////////////////////////////

class SnakeCombo : public SkillHandler 
{
public:
	SnakeCombo()  {}
	~SnakeCombo()  {}
	
public:
    string getSkillHandlerName()  { return "SnakeCombo"; }
	SkillType_t getSkillType()  { return SKILL_SNAKE_COMBO; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, Creature* pCreature);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SnakeCombo g_SnakeCombo;

#endif // __SKILL_SNAKE_COMBO_HANDLER_H__
