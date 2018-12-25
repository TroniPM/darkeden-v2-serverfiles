//////////////////////////////////////////////////////////////////////////////
// Filename    : Regeneration.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_REGENERATION_HANDLER_H__
#define __SKILL_REGENERATION_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Regeneration;
//////////////////////////////////////////////////////////////////////////////

class Regeneration : public SkillHandler 
{
public:
	Regeneration() throw() {}
	~Regeneration() throw() {}
	
public:
    string getSkillHandlerName()  { return "Regeneration"; }
	SkillType_t getSkillType()  { return SKILL_REGENERATION; }

	void execute( Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID );
	void execute( Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID );

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Regeneration g_Regeneration;

#endif // __SKILL_REGENERATION_HANDLER_H__
