//////////////////////////////////////////////////////////////////////////////
// Filename    : DeadlyClaw.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CHAOS_SPLITTER_HANDLER_H__
#define __SKILL_CHAOS_SPLITTER_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ChaosSplitter;
//////////////////////////////////////////////////////////////////////////////

class ChaosSplitter : public SkillHandler 
{
public:
	ChaosSplitter() throw();
	~ChaosSplitter() throw() {}
	
public:
    string getSkillHandlerName()  { return "ChaosSplitter"; }
	SkillType_t getSkillType()  { return SKILL_CHAOS_SPLITTER; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y);

	void computeOutput(const SkillInput& input, SkillOutput& output);

protected:
	POINT m_pChaosSplitterMask[9];
};

// global variable declaration
extern ChaosSplitter g_ChaosSplitter;

#endif // __SKILL_Deadly_Claw_HANDLER_H__
