//////////////////////////////////////////////////////////////////////////////
// Filename    : TurretFire.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_GAE_BOLT_HANDLER_H__
#define __SKILL_GAE_BOLT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class TurretFire;
//////////////////////////////////////////////////////////////////////////////

class GaeBolt : public SkillHandler 
{
public:
	GaeBolt()  { }
	~GaeBolt()  {}
	
public:
    string getSkillHandlerName()  { return "GaeBolt"; }
	SkillType_t getSkillType()  { return SKILL_GAE_BOLT; }

	void execute(Slayer* pSlayer, ObjectID_t targetObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern GaeBolt g_GaeBolt;

#endif // __SKILL_GAE_BOLT_H__
