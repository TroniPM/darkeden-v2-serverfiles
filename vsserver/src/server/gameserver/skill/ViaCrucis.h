//////////////////////////////////////////////////////////////////////////////
// Filename    : ShadowOfStorm.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_VIA_CRUCIS_HANDLER_H__
#define __SKILL_VIA_CRUCIS_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ShadowOfStorm;
//////////////////////////////////////////////////////////////////////////////

class ViaCrucis : public SkillHandler 
{
public:
	ViaCrucis() throw() {}
	~ViaCrucis() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "ViaCrucis"; }
	SkillType_t getSkillType() const throw() { return SKILL_VIA_CRUCIS; }

	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ViaCrucis g_ViaCrucis;

#endif // __SKILL_SHADOW_OF_STORM_HANDLER_H__
