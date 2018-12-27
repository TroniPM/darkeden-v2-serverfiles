//////////////////////////////////////////////////////////////////////////////
// Filename    : Bless.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_GLADIATOR_HANDLER_H__
#define __SKILL_GLADIATOR_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Bless;
//////////////////////////////////////////////////////////////////////////////

class Gladiator : public SkillHandler 
{
public:
	Gladiator()  {}
	~Gladiator()  {}
	
public :
    string getSkillHandlerName()  { return "Gladiator"; }
	SkillType_t getSkillType()  { return SKILL_GLADIATOR; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Gladiator g_Gladiator;

#endif // __SKILL_BLESS_HANDLER_H__
