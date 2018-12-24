//////////////////////////////////////////////////////////////////////////////
// Filename    : Regeneration.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_GLORYGROUND_HANDLER_H__
#define __SKILL_GLORYGROUND_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Regeneration;
//////////////////////////////////////////////////////////////////////////////

class GloryGround : public SkillHandler 
{
public:
	GloryGround() throw() {}
	~GloryGround() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "GloryGround"; }
	SkillType_t getSkillType() const throw() { return SKILL_GLORYGROUND; }

	void execute( Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID ) throw(Error);
	void execute( Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID ) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern GloryGround g_GloryGround;

#endif // __SKILL_REGENERATION_HANDLER_H__
