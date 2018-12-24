//////////////////////////////////////////////////////////////////////////////
// Filename    : IllusionInversion.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SPECTOR_INVERSE_HANDLER_H__
#define __SKILL_SPECTOR_INVERSE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class IllusionInversion;
//////////////////////////////////////////////////////////////////////////////

class SpectorInverse : public SkillHandler 
{
public:
	SpectorInverse() throw() {}
	~SpectorInverse() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "SpectorInverse"; }

	SkillType_t getSkillType() const throw() { return SKILL_SPECTOR_INVERSE; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SpectorInverse g_SpectorInverse;

#endif // __SKILL_ILLUSION_INVERSION_HANDLER_H__
