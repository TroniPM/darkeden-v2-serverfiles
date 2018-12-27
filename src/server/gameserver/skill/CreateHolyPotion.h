//////////////////////////////////////////////////////////////////////////////
// Filename    : CreateHolyPotion.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CREATE_HOLY_POTION_HANDLER_H__
#define __SKILL_CREATE_HOLY_POTION_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class CreateHolyPotion;
//////////////////////////////////////////////////////////////////////////////

class CreateHolyPotion : public SkillHandler 
{
public:
	CreateHolyPotion()  {}
	~CreateHolyPotion()  {}
	
public:
    string getSkillHandlerName()  { return "CreateHolyPotion"; }
	SkillType_t getSkillType()  { return SKILL_CREATE_HOLY_POTION; }

	void execute(Slayer* pSlayer, ObjectID_t, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, SkillSlot* pSkillSlot);

	void computeOutput(const SkillInput& input, SkillOutput& output);

protected:
	bool canMake(ItemType_t waterType, int DomainLevel, int SkillLevel) ;
};

// global variable declaration
extern CreateHolyPotion g_CreateHolyPotion;

#endif // __SKILL_CREATE_HOLY_POTION_HANDLER_H__
