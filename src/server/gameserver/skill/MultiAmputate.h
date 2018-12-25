//////////////////////////////////////////////////////////////////////////////
// Filename    : MultiAmputate.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_MULTI_AMPUTATE_HANDLER_H__
#define __SKILL_MULTI_AMPUTATE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class MultiAmputate;
//////////////////////////////////////////////////////////////////////////////

class MultiAmputate : public SkillHandler 
{
public:
	MultiAmputate() throw() {}
	~MultiAmputate() throw() {}
	
public:
    string getSkillHandlerName()  { return "MultiAmputate"; }

	SkillType_t getSkillType()  { return SKILL_MULTI_AMPUTATE; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pEnemy);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern MultiAmputate g_MultiAmputate;

#endif // __SKILL_MULTI_AMPUTATE_HANDLER_H__
