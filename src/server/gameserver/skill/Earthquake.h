//////////////////////////////////////////////////////////////////////////////
// Filename    : Earthquake.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_EARTHQUAKE_HANDLER_H__
#define __SKILL_EARTHQUAKE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Earthquake;
//////////////////////////////////////////////////////////////////////////////

class Earthquake : public SkillHandler 
{
public:
	Earthquake() throw() {}
	~Earthquake() throw() {}
	
public:
    string getSkillHandlerName()  { return "Earthquake"; }
	SkillType_t getSkillType()  { return SKILL_EARTHQUAKE; }

	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ObjectID_t targetObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Earthquake g_Earthquake;

#endif // __SKILL_EARTHQUAKE_H__
