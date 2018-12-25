//////////////////////////////////////////////////////////////////////////////
// Filename    : DragonTornado.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DRAGON_HURRICANE_HANDLER_H__
#define __SKILL_DRAGON_HURRICANE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class DragonTornado;
//////////////////////////////////////////////////////////////////////////////

class DragonHurricane : public SkillHandler 
{
public:
	DragonHurricane() throw() {}
	~DragonHurricane() throw() {}
	
public:
    string getSkillHandlerName()  { return "DragonHurricane"; }
	SkillType_t getSkillType()  { return SKILL_DRAGON_HURRICANE; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern DragonHurricane g_DragonHurricane;

#endif // __SKILL_DRAGON_TORNADO_HANDLER_H__
