//////////////////////////////////////////////////////////////////////////////
// Filename    : HolyArmor.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HOLY_ARMOR2_HANDLER_H__
#define __SKILL_HOLY_ARMOR2_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class HolyArmor;
//////////////////////////////////////////////////////////////////////////////

class HolyArmor2 : public SkillHandler 
{
public:
	HolyArmor2()  {}
	~HolyArmor2()  {}
	
public:
    string getSkillHandlerName()  { return "HolyArmor2"; }
	SkillType_t getSkillType()  { return SKILL_HOLY_ARMOR2; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern HolyArmor2 g_HolyArmor2;

#endif // __SKILL_HOLY_ARMOR_HANDLER_H__
