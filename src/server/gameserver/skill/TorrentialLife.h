//////////////////////////////////////////////////////////////////////////////
// Filename    : Whitsuntide.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TORRENTTIALLIFE_HANDLER_H__
#define __SKILL_TORRENTTIALLIFE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Whitsuntide;
//////////////////////////////////////////////////////////////////////////////

class TorrentialLife : public SkillHandler 
{
public:
	TorrentialLife() throw() {}
	~TorrentialLife() throw() {}
	
public:
    string getSkillHandlerName()  { return "TorrentialLife"; }
	SkillType_t getSkillType()  { return SKILL_TORRENTIALLIFE; }

	void execute(Ousters* pOusters, ObjectID_t ObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);
	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TorrentialLife g_TorrentialLife;

#endif // __SKILL_WHITSUNTIDE_HANDLER_H__
