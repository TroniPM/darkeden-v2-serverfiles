//////////////////////////////////////////////////////////////////////////////
// Filename    : Visible.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_VISIBLE_HANDLER_H__
#define __SKILL_VISIBLE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Visible;
//////////////////////////////////////////////////////////////////////////////

class Visible: public SkillHandler 
{
public:
	Visible()  {}
	~Visible()  {}
	
public:
    string getSkillHandlerName()  { return "Visible"; }
	SkillType_t getSkillType()  { return SKILL_VISIBLE; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Visible g_Visible;

#endif // __SKILL_VISIBLE_HANDLER_H__
