//////////////////////////////////////////////////////////////////////////////
// Filename    : BlazeWalk.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLAZE_WALK2_HANDLER_H__
#define __SKILL_BLAZE_WALK2_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BlazeWalk2;
//////////////////////////////////////////////////////////////////////////////

class BlazeWalk2 : public SkillHandler 
{
public:
	BlazeWalk2() throw() {}
	~BlazeWalk2() throw() {}

public :
    string getSkillHandlerName() const throw() { return "BlazeWalk2"; }
	SkillType_t getSkillType() const throw() { return SKILL_BLAZE_WALK2; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, Creature* pTargetCreature, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BlazeWalk2 g_BlazeWalk2;

#endif // __SKILL_BLAZE_WALK_HANDLER_H__
