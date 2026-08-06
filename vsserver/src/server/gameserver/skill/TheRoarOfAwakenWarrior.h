//////////////////////////////////////////////////////////////////////////////
// Filename    : Bless.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_THE_ROAR_OF_AWAKEN_WARRIOR_HANDLER_H__
#define __SKILL_THE_ROAR_OF_AWAKEN_WARRIOR_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Bless;
//////////////////////////////////////////////////////////////////////////////

class TheRoarOfAwakenWarrior : public SkillHandler 
{
public:
	TheRoarOfAwakenWarrior() throw() {}
	~TheRoarOfAwakenWarrior() throw() {}
	
public :
    string getSkillHandlerName() const throw() { return "TheRoarOfAwakenWarrior"; }
	SkillType_t getSkillType() const throw() { return SKILL_THE_ROAR_OF_AWAKEN_WARRIOR; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TheRoarOfAwakenWarrior g_TheRoarOfAwakenWarrior;

#endif // __SKILL_BLESS_HANDLER_H__
