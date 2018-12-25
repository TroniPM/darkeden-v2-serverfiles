//////////////////////////////////////////////////////////////////////////////
// Filename    : DivineSpirits.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DIVINE_SPIRITS_HANDLER_H__
#define __SKILL_DIVINE_SPIRITS_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class DivineSpirits;
//////////////////////////////////////////////////////////////////////////////

class DivineSpirits : public SkillHandler 
{
public:
	DivineSpirits() throw() {}
	~DivineSpirits() throw() {}
	
public:
    string getSkillHandlerName()  { return "DivineSpirits"; }
	SkillType_t getSkillType()  { return SKILL_DIVINE_SPIRITS; }

	void execute(Ousters* pOusters,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern DivineSpirits g_DivineSpirits;

#endif // __SKILL_DIVINE_SPIRITS_HANDLER_H__
