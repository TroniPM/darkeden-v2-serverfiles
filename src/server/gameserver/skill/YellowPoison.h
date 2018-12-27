//////////////////////////////////////////////////////////////////////////////
// Filename    : YellowPoison.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_YELLOW_POISON_HANDLER_H__
#define __SKILL_YELLOW_POISON_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class YellowPoison;
//////////////////////////////////////////////////////////////////////////////

class YellowPoison : public SkillHandler 
{
public:
	YellowPoison()  {}
	~YellowPoison()  {}
	
public:
    string getSkillHandlerName()  { return "YellowPoison"; }
	SkillType_t getSkillType()  { return SKILL_YELLOW_POISON; }

	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Vampire* pVampire, ObjectID_t,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);
	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern YellowPoison g_YellowPoison;

#endif // __SKILL_YELLOW_POISON_HANDLER_H__
