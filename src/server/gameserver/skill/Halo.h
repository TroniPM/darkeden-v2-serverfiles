//////////////////////////////////////////////////////////////////////////////
// Filename    : Halo.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HALO_HANDLER_H__
#define __SKILL_HALO_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Halo;
//////////////////////////////////////////////////////////////////////////////

class Halo: public SkillHandler 
{
public:
	Halo() throw() {}
	~Halo() throw() {}
	
public:
    string getSkillHandlerName()  { return "Halo"; }

	SkillType_t getSkillType()  { return SKILL_HALO; }

	void execute(Ousters* pOusters, ObjectID_t targetObject, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Halo g_Halo;

#endif // __SKILL_HALO_HANDLER_H__
