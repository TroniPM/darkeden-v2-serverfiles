//////////////////////////////////////////////////////////////////////////////
// Filename    : NooseOfWraith.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_PLUMYBOAR_HANDLER_H__
#define __SKILL_PLUMYBOAR_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class NooseOfWraith;
//////////////////////////////////////////////////////////////////////////////

class PlumyBoar : public SkillHandler 
{
public:
	PlumyBoar() throw();
	~PlumyBoar() throw() {}
	
public:
    string getSkillHandlerName()  { return "PlumyBoar"; }
	SkillType_t getSkillType()  { return SKILL_PLUMYBOAR; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y);

	void computeOutput(const SkillInput& input, SkillOutput& output);

};

// global variable declaration
extern PlumyBoar g_PlumyBoar;

#endif // __SKILL_NOOSE_OF_WRAITH_HANDLER_H__
