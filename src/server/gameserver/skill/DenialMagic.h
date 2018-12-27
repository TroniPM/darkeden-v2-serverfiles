//////////////////////////////////////////////////////////////////////////////
// Filename    : DenialMagic.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DENIAL_MAGIC_HANDLER_H__
#define __SKILL_DENIAL_MAGIC_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class DenialMagic;
//////////////////////////////////////////////////////////////////////////////

class DenialMagic : public SkillHandler 
{
public:
	DenialMagic()  {}
	~DenialMagic()  {}
	
public:
    string getSkillHandlerName()  { return "DenialMagic"; }
	SkillType_t getSkillType()  { return SKILL_DENIAL_MAGIC; }

	void execute(Slayer* pSlayer,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern DenialMagic g_DenialMagic;

#endif // __SKILL_DENIAL_MAGIC_HANDLER_H__
