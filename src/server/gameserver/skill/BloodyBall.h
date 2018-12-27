//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyBall.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOODY_BALL_HANDLER_H__
#define __SKILL_BLOODY_BALL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BloodyBall;
//////////////////////////////////////////////////////////////////////////////

class BloodyBall : public SkillHandler 
{
public:
	BloodyBall() ;
	~BloodyBall()  {}
	
public:
    string getSkillHandlerName()  { return "BloodyBall"; }
	SkillType_t getSkillType()  { return SKILL_BLOODY_BALL; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y);

	void computeOutput(const SkillInput& input, SkillOutput& output);

protected:
	POINT m_pBloodyBallMask[9];
};

// global variable declaration
extern BloodyBall g_BloodyBall;

#endif // __SKILL_BLOODY_BALL_HANDLER_H__
