//////////////////////////////////////////////////////////////////////////////
// Filename    : TransformToWolf.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TRANSFORM_TO_WOLF_HANDLER_H__
#define __SKILL_TRANSFORM_TO_WOLF_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class TransformToWolf;
//////////////////////////////////////////////////////////////////////////////

class TransformToWolf: public SkillHandler 
{
public:
	TransformToWolf()  {}
	~TransformToWolf()  {}
	
public:
    string getSkillHandlerName()  { return "TransformToWolf"; }
	SkillType_t getSkillType()  { return SKILL_TRANSFORM_TO_WOLF; }

	void execute(Vampire* pVampire, ObjectID_t TargetObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, VampireSkillSlot* pVampireSkillSlot);
	void execute(Monster* pMonster);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TransformToWolf g_TransformToWolf;

#endif // __SKILL_TRANSFORM_TO_WOLF_HANDLER_H__
