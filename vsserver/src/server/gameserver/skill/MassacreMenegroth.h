//////////////////////////////////////////////////////////////////////////////
// Filename    : GoreGlandFire.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_MASSACRE_MENEGROTH_HANDLER_H__
#define __SKILL_MASSACRE_MENEGROTH_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class GoreGlandFire;
//////////////////////////////////////////////////////////////////////////////

class MassacreMenegroth : public SkillHandler 
{
public:
	MassacreMenegroth() throw();
	~MassacreMenegroth() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "MassacreMenegroth"; }
	SkillType_t getSkillType() const throw() { return SKILL_MASSACRE_MENEGROTH; }

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

protected:
	POINT m_pMassacreMenegrothMask[9];
};

// global variable declaration
extern MassacreMenegroth g_MassacreMenegroth;

#endif // __SKILL_GORE_GLAND_FIRE_HANDLER_H__
