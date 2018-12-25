//////////////////////////////////////////////////////////////////////////////
// Filename    : Concealment.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ALLYSTER_WIND_HANDLER_H__
#define __SKILL_ALLYSTER_WIND_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Concealment;
//////////////////////////////////////////////////////////////////////////////

class AllysterWind : public SkillHandler 
{
public:
	AllysterWind() throw() {}
	~AllysterWind() throw() {}
	
public:
	string getSkillHandlerName()  { return "AllysterWind"; }
	SkillType_t getSkillType()  { return SKILL_ALLYSTER_WIND; }

	void execute(Ousters* pSlayer,  OustersSkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern AllysterWind g_AllysterWind;

#endif // __SKILL_CONCEALMENT_HANDLER_H__
