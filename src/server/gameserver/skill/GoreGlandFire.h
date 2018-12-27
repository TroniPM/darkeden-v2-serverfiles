//////////////////////////////////////////////////////////////////////////////
// Filename    : GoreGlandFire.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_GORE_GLAND_FIRE_HANDLER_H__
#define __SKILL_GORE_GLAND_FIRE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class GoreGlandFire;
//////////////////////////////////////////////////////////////////////////////

class GoreGlandFire : public SkillHandler 
{
public:
	GoreGlandFire() ;
	~GoreGlandFire()  {}
	
public:
    string getSkillHandlerName()  { return "GoreGlandFire"; }
	SkillType_t getSkillType()  { return SKILL_GORE_GLAND_FIRE; }

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y);

	void computeOutput(const SkillInput& input, SkillOutput& output);

protected:
	POINT m_pGoreGlandFireMask[9];
};

// global variable declaration
extern GoreGlandFire g_GoreGlandFire;

#endif // __SKILL_GORE_GLAND_FIRE_HANDLER_H__
