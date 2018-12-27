//////////////////////////////////////////////////////////////////////////////
// Filename    : ReputoFactum.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_REPUTO_FACTUM_HANDLER_H__
#define __SKILL_REPUTO_FACTUM_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ReputoFactum;
//////////////////////////////////////////////////////////////////////////////

class ReputoFactum : public SkillHandler 
{
public:
	ReputoFactum()  {}
	~ReputoFactum()  {}
	
public:
    string getSkillHandlerName()  { return "ReputoFactum"; }
	SkillType_t getSkillType()  { return SKILL_REPUTO_FACTUM; }

	void execute(Ousters* pOusters, ObjectID_t ObjectID, OustersSkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ReputoFactum g_ReputoFactum;

#endif // __SKILL_REPUTO_FACTUM_HANDLER_H__
