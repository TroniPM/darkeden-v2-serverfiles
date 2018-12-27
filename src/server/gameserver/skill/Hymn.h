//////////////////////////////////////////////////////////////////////////////
// Filename    : Hymn.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HYMN_HANDLER_H__
#define __SKILL_HYMN_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Hymn;
//////////////////////////////////////////////////////////////////////////////

class Hymn : public SkillHandler 
{
public:
	Hymn()  {}
	~Hymn()  {}
	
public:
    string getSkillHandlerName()  { return "Hymn"; }
	SkillType_t getSkillType()  { return SKILL_HYMN; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Hymn g_Hymn;

#endif // __SKILL_HYMN_HANDLER_H__
