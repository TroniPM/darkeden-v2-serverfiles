//////////////////////////////////////////////////////////////////////////////
// Filename    : DuckingWallop.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DUCKING_WALLOP_HANDLER_H__
#define __SKILL_DUCKING_WALLOP_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class DuckingWallop;
//////////////////////////////////////////////////////////////////////////////

class DuckingWallop: public SkillHandler 
{
public:
	DuckingWallop() ;
	~DuckingWallop() throw() {}
	
public:
    string getSkillHandlerName()  { return "DuckingWallop"; }

	SkillType_t getSkillType()  { return SKILL_DUCKING_WALLOP; }

	void execute(Ousters* pOusters, ObjectID_t targetObject, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);
	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);

private:
	POINT m_pDuckingWallopMask[8][18];
	int m_DamageRatio[18];
};

// global variable declaration
extern DuckingWallop g_DuckingWallop;

#endif // __SKILL_DUCKING_WALLOP_HANDLER_H__
