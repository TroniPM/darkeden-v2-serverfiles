//////////////////////////////////////////////////////////////////////////////
// Filename    : SatelliteBomb.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SATELLITE_BOMB2_HANDLER_H__
#define __SKILL_SATELLITE_BOMB2_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SatelliteBomb;
//////////////////////////////////////////////////////////////////////////////

class SatelliteBomb2 : public SkillHandler 
{
public:
	SatelliteBomb2()  {}
	~SatelliteBomb2()  {}
	
public:
    string getSkillHandlerName()  { return "SatelliteBomb2"; }
	SkillType_t getSkillType()  { return SKILL_SATELLITE_BOMB2; }

	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, ObjectID_t,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Monster*, ZoneCoord_t X, ZoneCoord_t Y);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SatelliteBomb2 g_SatelliteBomb2;

#endif // __SKILL_SATELLITE_BOMB_HANDLER_H__
