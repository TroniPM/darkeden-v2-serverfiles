//////////////////////////////////////////////////////////////////////////////
// Filename    : TurnUndead.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TURN_UNDEAD_HANDLER_H__
#define __SKILL_TURN_UNDEAD_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class TurnUndead;
//////////////////////////////////////////////////////////////////////////////

class TurnUndead : public SkillHandler 
{
public:
	TurnUndead()  {}
	~TurnUndead()  {}
	
public:
    string getSkillHandlerName()  { return "TurnUndead"; }
	SkillType_t getSkillType()  { return SKILL_TURN_UNDEAD; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TurnUndead g_TurnUndead;

#endif // __SKILL_TURN_UNDEAD_HANDLER_H__
