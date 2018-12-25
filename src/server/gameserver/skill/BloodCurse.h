//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodCurse.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOOD_CURSE_HANDLER_H__
#define __SKILL_BLOOD_CURSE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BloodCurse;
//////////////////////////////////////////////////////////////////////////////

class BloodCurse : public SkillHandler 
{
public:
	BloodCurse() throw() {}
	~BloodCurse() throw() {}
	
public:
    string getSkillHandlerName()  { return "BloodCurse"; }
	SkillType_t getSkillType()  { return SKILL_BLOOD_CURSE; }

	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Vampire* pVampire, ObjectID_t,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Monster*, ZoneCoord_t X, ZoneCoord_t Y);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BloodCurse g_BloodCurse;

#endif // __SKILL_BLOOD_CURSE_HANDLER_H__
