//////////////////////////////////////////////////////////////////////////////
// Filename    : IceHorizon.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ICE_HORIZON_HANDLER_H__
#define __SKILL_ICE_HORIZON_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class IceHorizon;
//////////////////////////////////////////////////////////////////////////////

class IceHorizon : public SkillHandler 
{
public:
	IceHorizon() throw();
	~IceHorizon() throw() {}
	
public:
    string getSkillHandlerName()  { return "IceHorizon"; }
	SkillType_t getSkillType()  { return SKILL_ICE_HORIZON; }

	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);
	void execute(Ousters* pOusters, ObjectID_t, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);

};

// global variable declaration
extern IceHorizon g_IceHorizon;

#endif // __SKILL_ICE_HORIZON_HANDLER_H__
