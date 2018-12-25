//////////////////////////////////////////////////////////////////////////////
// Filename    : GoreGlandFire.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BOGLE_H_HANDLER_H__
#define __SKILL_BOGLE_H_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class GoreGlandFire;
//////////////////////////////////////////////////////////////////////////////

class BogleH : public SkillHandler 
{
public:
	BogleH() throw();
	~BogleH() throw() {}
	
public:
    string getSkillHandlerName()  { return "BogleH"; }
	SkillType_t getSkillType()  { return SKILL_BOGLE_H; }

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

protected:
	POINT m_pBogleHMask[9];
};

// global variable declaration
extern BogleH g_BogleH;

#endif // __SKILL_GORE_GLAND_FIRE_HANDLER_H__
