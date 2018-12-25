//////////////////////////////////////////////////////////////////////////////
// Filename    : EnergyDrop.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_METEO_BLAZE_HANDLER_H__
#define __SKILL_METEO_BLAZE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class EnergyDrop;
//////////////////////////////////////////////////////////////////////////////

class MeteoBlaze : public SkillHandler 
{
public:
	MeteoBlaze() throw() {}
	~MeteoBlaze() throw() {}
	
public:
    string getSkillHandlerName()  { return "MeteoBlaze"; }
	SkillType_t getSkillType()  { return SKILL_METEO_BLAZE; }

	void execute(Ousters* pOusters, ObjectID_t ObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern MeteoBlaze g_MeteoBlaze;

#endif // __SKILL_ENERGY_DROP_HANDLER_H__
