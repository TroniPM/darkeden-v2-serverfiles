//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodySnake.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOODY_SNAKE_HANDLER_H__
#define __SKILL_BLOODY_SNAKE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BloodySnake;
//////////////////////////////////////////////////////////////////////////////

class BloodySnake : public SkillHandler 
{
public:
	BloodySnake()  {}
	~BloodySnake()  {}
	
public:
    string getSkillHandlerName()  { return "BloodySnake"; }
	SkillType_t getSkillType()  { return SKILL_BLOODY_SNAKE; }

	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Vampire* pVampire, ObjectID_t, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);
	void execute(Monster*, ZoneCoord_t x, ZoneCoord_t y);

	void computeOutput(const SkillInput& input, SkillOutput& output);

private:
};

// global variable declaration
extern BloodySnake g_BloodySnake;

#endif // __SKILL_BLOODY_SNAKE_HANDLER_H__
