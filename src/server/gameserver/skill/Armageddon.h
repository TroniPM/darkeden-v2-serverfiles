//////////////////////////////////////////////////////////////////////////////
// Filename    : Armageddon.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ARMAGEDDON_HANDLER_H__
#define __SKILL_ARMAGEDDON_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Armageddon;
//////////////////////////////////////////////////////////////////////////////

class Armageddon: public SkillHandler 
{
public:
	Armageddon() throw() {}
	~Armageddon() throw() {}
	
public:
    string getSkillHandlerName()  { return "Armageddon"; }
	SkillType_t getSkillType()  { return SKILL_ARMAGEDDON; }

	void execute(Vampire* pVampire, ObjectID_t targetObject, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Armageddon g_Armageddon;

#endif // __SKILL_ARMAGEDDON_HANDLER_H__
