//////////////////////////////////////////////////////////////////////////////
// Filename    : Bless.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLESS_HANDLER_H__
#define __SKILL_BLESS_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Bless;
//////////////////////////////////////////////////////////////////////////////

class Bless : public SkillHandler 
{
public:
	Bless() throw() {}
	~Bless() throw() {}
	
public :
    string getSkillHandlerName()  { return "Bless"; }
	SkillType_t getSkillType()  { return SKILL_BLESS; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Bless g_Bless;

#endif // __SKILL_BLESS_HANDLER_H__
