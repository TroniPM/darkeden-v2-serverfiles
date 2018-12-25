//////////////////////////////////////////////////////////////////////////////
// Filename    : CriticalGround.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CRITICAL_GROUND_HANDLER_H__
#define __SKILL_CRITICAL_GROUND_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class CriticalGround;
//////////////////////////////////////////////////////////////////////////////

class CriticalGround: public SkillHandler 
{
public:
	CriticalGround() throw();
	~CriticalGround() throw() {}
	
public:
    string getSkillHandlerName()  { return "CriticalGround"; }
	SkillType_t getSkillType()  { return SKILL_CRITICAL_GROUND; }

	//void execute(Slayer* pSlayer, SlayerSkillSlot* pSlayerSkillSlot, CEffectID_t CEffectID);
	//void execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster);

	void computeOutput(const SkillInput& input, SkillOutput& output);

private :
	POINT	m_pCriticalGroundMask[8];
};

// global variable declaration
extern CriticalGround g_CriticalGround;

#endif // __SKILL_HIDE_HANDLER_H__
