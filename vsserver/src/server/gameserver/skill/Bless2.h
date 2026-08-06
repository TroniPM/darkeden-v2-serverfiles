//////////////////////////////////////////////////////////////////////////////
// Filename    : Bless.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLESS2_HANDLER_H__
#define __SKILL_BLESS2_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Bless;
//////////////////////////////////////////////////////////////////////////////

class Bless2 : public SkillHandler 
{
public:
	Bless2() throw() {}
	~Bless2() throw() {}
	
public :
    string getSkillHandlerName() const throw() { return "Bless2"; }
	SkillType_t getSkillType() const throw() { return SKILL_BLESS2; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Bless2 g_Bless2;

#endif // __SKILL_BLESS_HANDLER_H__
