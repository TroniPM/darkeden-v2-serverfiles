//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyWall.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOODY_WALL_HANDLER_H__
#define __SKILL_BLOODY_WALL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BloodyWall;
//////////////////////////////////////////////////////////////////////////////

class BloodyWall : public SkillHandler 
{
public:
	BloodyWall() ;
	~BloodyWall() throw() {}
	
public:
    string getSkillHandlerName()  { return "BloodyWall"; }
	SkillType_t getSkillType()  { return SKILL_BLOODY_WALL; }

	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Vampire* pVampire, ObjectID_t, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);
	void execute(Monster*, ZoneCoord_t x, ZoneCoord_t y);

	void computeOutput(const SkillInput& input, SkillOutput& output);

private:
	POINT		m_BloodyWallMask[8][5];	// 8����, 5����
};

// global variable declaration
extern BloodyWall g_BloodyWall;

#endif // __SKILL_BLOODY_WALL_HANDLER_H__
