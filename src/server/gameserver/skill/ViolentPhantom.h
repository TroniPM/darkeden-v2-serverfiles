//////////////////////////////////////////////////////////////////////////////
// Filename    : ViolentPhantom.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_VIOLENT_PHANTOM_HANDLER_H__
#define __SKILL_VIOLENT_PHANTOM_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ViolentPhantom;
//////////////////////////////////////////////////////////////////////////////

class ViolentPhantom : public SkillHandler 
{
public:
	ViolentPhantom() ;
	~ViolentPhantom()  {}
	
public:
    string getSkillHandlerName()  { return "ViolentPhantom"; }
	SkillType_t getSkillType()  { return SKILL_VIOLENT_PHANTOM; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y);

	void computeOutput(const SkillInput& input, SkillOutput& output);

protected:
	POINT m_pViolentPhantomMask[9];
};

// global variable declaration
extern ViolentPhantom g_ViolentPhantom;

#endif // __SKILL_VIOLENT_PHANTOM_HANDLER_H__
