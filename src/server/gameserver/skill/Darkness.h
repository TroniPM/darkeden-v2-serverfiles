//////////////////////////////////////////////////////////////////////////////
// Filename    : Darkness.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DARKNESS_HANDLER_H__
#define __SKILL_DARKNESS_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Darkness;
//////////////////////////////////////////////////////////////////////////////

class Darkness : public SkillHandler 
{
public:
	Darkness()  {}
	~Darkness()  {}
	
public:
    string getSkillHandlerName()  { return "Darkness"; }
	SkillType_t getSkillType()  { return SKILL_DARKNESS; }

	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Vampire* pVampire, ObjectID_t, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);
	void execute(Monster*, ZoneCoord_t x, ZoneCoord_t y);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Darkness g_Darkness;

#endif // __SKILL_DARKNESS_HANDLER_H__
