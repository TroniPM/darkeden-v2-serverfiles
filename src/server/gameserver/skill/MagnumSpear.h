//////////////////////////////////////////////////////////////////////////////
// Filename    : MagnumSpear.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_MAGNUM_SPEAR_HANDLER_H__
#define __SKILL_MAGNUM_SPEAR_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class MagnumSpear;
//////////////////////////////////////////////////////////////////////////////

class MagnumSpear : public SkillHandler 
{
public:
	MagnumSpear() throw() {}
	~MagnumSpear() throw() {}
	
public:
    string getSkillHandlerName()  { return "MagnumSpear"; }
	SkillType_t getSkillType()  { return SKILL_MAGNUM_SPEAR; }

	void execute(Ousters* pOusters, ObjectID_t ObjectID,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern MagnumSpear g_MagnumSpear;

#endif // __SKILL_MAGNUM_SPEAR_HANDLER_H__
