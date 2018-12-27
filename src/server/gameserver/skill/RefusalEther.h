//////////////////////////////////////////////////////////////////////////////
// Filename    : RefusalEther.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_REFUSAL_ETHER_HANDLER_H__
#define __SKILL_REFUSAL_ETHER_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class RefusalEther;
//////////////////////////////////////////////////////////////////////////////

class RefusalEther : public SkillHandler 
{
public:
	RefusalEther() ;
	~RefusalEther()  {}
	
public:
    string getSkillHandlerName()  { return "RefusalEther"; }
	SkillType_t getSkillType()  { return SKILL_REFUSAL_ETHER; }

	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);
	void execute(Ousters* pOusters, ObjectID_t, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);

private:
};

// global variable declaration
extern RefusalEther g_RefusalEther;

#endif // __SKILL_REFUSAL_ETHER_HANDLER_H__
