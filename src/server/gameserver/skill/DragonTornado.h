//////////////////////////////////////////////////////////////////////////////
// Filename    : DragonTornado.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DRAGON_TORNADO_HANDLER_H__
#define __SKILL_DRAGON_TORNADO_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class DragonTornado;
//////////////////////////////////////////////////////////////////////////////

class DragonTornado : public SkillHandler 
{
public:
	DragonTornado()  {}
	~DragonTornado()  {}
	
public:
    string getSkillHandlerName()  { return "DragonTornado"; }
	SkillType_t getSkillType()  { return SKILL_DRAGON_TORNADO; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern DragonTornado g_DragonTornado;

#endif // __SKILL_DRAGON_TORNADO_HANDLER_H__
