//////////////////////////////////////////////////////////////////////////////
// Filename    : ShadowOfStorm.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_MAGMATIC_ERUPTION_HANDLER_H__
#define __SKILL_MAGMATIC_ERUPTION_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ShadowOfStorm;
//////////////////////////////////////////////////////////////////////////////

class MagmaticEruption : public SkillHandler 
{
public:
	MagmaticEruption() throw() {}
	~MagmaticEruption() throw() {}
	
public:
    string getSkillHandlerName()  { return "MagmaticEruption"; }
	SkillType_t getSkillType()  { return SKILL_MAGMATIC_ERUPTION; }

	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern MagmaticEruption g_MagmaticEruption;

#endif // __SKILL_SHADOW_OF_STORM_HANDLER_H__
