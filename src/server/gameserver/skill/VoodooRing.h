//////////////////////////////////////////////////////////////////////////////
// Filename    : VoodooRing.h 
// Written By  : rallser
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_Voodoo_Ring_HANDLER_H__
#define __SKILL_Voodoo_Ring_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Voodoo Ring;
//////////////////////////////////////////////////////////////////////////////

class VoodooRing : public SkillHandler 
{
public:
	VoodooRing() throw();
	~VoodooRing() throw() {}
	
public:
    string getSkillHandlerName()  { return "VoodooRing"; }
	SkillType_t getSkillType()  { return SKILL_Voodoo_Ring; }

	void execute(Vampire* pVampire,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);

};

// global variable declaration
extern VoodooRing g_VoodooRing;

#endif // __SKILL_Voodoo_Ring_HANDLER_H__
