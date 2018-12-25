//////////////////////////////////////////////////////////////////////////////
// Filename    : TripleBreak.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TRIPLE_BREAK_HANDLER_H__
#define __SKILL_TRIPLE_BREAK_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class TripleBreak;
//////////////////////////////////////////////////////////////////////////////

class TripleBreak : public SkillHandler 
{
public:
	TripleBreak() throw() {}
	~TripleBreak() throw() {}
	
public:
    string getSkillHandlerName()  { return "TripleBreak"; }
	SkillType_t getSkillType()  { return SKILL_TRIPLE_BREAK; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TripleBreak g_TripleBreak;

#endif // __SKILL_TRIPLE_BREAK_HANDLER_H__
