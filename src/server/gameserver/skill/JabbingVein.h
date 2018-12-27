//////////////////////////////////////////////////////////////////////////////
// Filename    : JabbingVein.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_JABBING_VEIN_HANDLER_H__
#define __SKILL_JABBING_VEIN_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class JabbingVein;
//////////////////////////////////////////////////////////////////////////////

class JabbingVein : public SkillHandler 
{
public:
	JabbingVein()  {}
	~JabbingVein()  {}

public:
    string getSkillHandlerName()  { return "JabbingVein"; }
	SkillType_t getSkillType()  { return SKILL_JABBING_VEIN; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern JabbingVein g_JabbingVein;

#endif // __SKILL_JABBING_VEIN_HANDLER_H__
