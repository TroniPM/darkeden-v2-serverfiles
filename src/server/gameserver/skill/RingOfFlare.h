//////////////////////////////////////////////////////////////////////////////
// Filename    : RingOfFlare.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_RING_OF_FLARE_HANDLER_H__
#define __SKILL_RING_OF_FLARE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class RingOfFlare;
//////////////////////////////////////////////////////////////////////////////

class RingOfFlare : public SkillHandler 
{
public:
	RingOfFlare() throw() {}
	~RingOfFlare() throw() {}
	
public:
    string getSkillHandlerName()  { return "RingOfFlare"; }
	SkillType_t getSkillType()  { return SKILL_RING_OF_FLARE; }

	void execute(Ousters* pOusters,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern RingOfFlare g_RingOfFlare;

#endif // __SKILL_RING_OF_FLARE_HANDLER_H__
