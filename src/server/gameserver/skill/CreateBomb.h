//////////////////////////////////////////////////////////////////////////////
// Filename    : CreateBomb.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CREATE_BOMB_HANDLER_H__
#define __SKILL_CREATE_BOMB_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class CreateBomb;
//////////////////////////////////////////////////////////////////////////////

class CreateBomb : public SkillHandler 
{
public:
	CreateBomb()  {}
	~CreateBomb()  {}
	
public:
    string getSkillHandlerName()  { return "CreateBomb"; }
	SkillType_t getSkillType()  { return SKILL_CREATE_BOMB; }

	void execute(Slayer* pSlayer, ObjectID_t, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, SkillSlot* pSkillSlot);

	void computeOutput(const SkillInput& input, SkillOutput& output);

protected:
	bool canMake(ItemType_t waterType, int DomainLevel, int SkillLevel) ;
};

// global variable declaration
extern CreateBomb g_CreateBomb;

#endif // __SKILL_CREATE_BOMB_HANDLER_H__
