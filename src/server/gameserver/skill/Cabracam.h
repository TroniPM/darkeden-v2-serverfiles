//////////////////////////////////////////////////////////////////////////////
// Filename    : GoreGlandFire.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CABRACAM_HANDLER_H__
#define __SKILL_CABRACAM_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class GoreGlandFire;
//////////////////////////////////////////////////////////////////////////////

class Cabracam : public SkillHandler 
{
public:
	Cabracam() ;
	~Cabracam()  {}
	
public:
    string getSkillHandlerName()  { return "Cabracam"; }
	SkillType_t getSkillType()  { return SKILL_CABRACAM; }

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y);

	void computeOutput(const SkillInput& input, SkillOutput& output);

protected:
	POINT m_pCabracamMask[9];
};

// global variable declaration
extern Cabracam g_Cabracam;

#endif // __SKILL_GORE_GLAND_FIRE_HANDLER_H__
