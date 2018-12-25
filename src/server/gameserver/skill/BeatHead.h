//////////////////////////////////////////////////////////////////////////////
// Filename    : BeatHead.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BEAT_HEAD_HANDLER_H__
#define __SKILL_BEAT_HEAD_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BeatHead;
//////////////////////////////////////////////////////////////////////////////

class BeatHead : public SkillHandler 
{
public:
	BeatHead() throw() {}
	~BeatHead() throw() {}
	
public:
    string getSkillHandlerName()  { return "BeatHead"; }
	SkillType_t getSkillType()  { return SKILL_BEAT_HEAD; }

	void execute(Ousters* pOusters, ObjectID_t ObjectID,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BeatHead g_BeatHead;

#endif // __SKILL_BEAT_HEAD_HANDLER_H__
