//////////////////////////////////////////////////////////////////////////////
// Filename    : SwordOfThor.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CRUSHING_STORM_HANDLER_H__
#define __SKILL_CRUSHING_STORM_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SwordOfThor;
//////////////////////////////////////////////////////////////////////////////

class CrushingStorm : public SkillHandler 
{
public:
	CrushingStorm() throw() {}
	~CrushingStorm() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "CrushingStorm"; }
	SkillType_t getSkillType() const throw() { return SKILL_CRUSHING_STORM; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern CrushingStorm g_CrushingStorm;

#endif // __SKILL_SWORD_OF_THOR_HANDLER_H__
