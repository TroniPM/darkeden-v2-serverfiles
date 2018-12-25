//////////////////////////////////////////////////////////////////////////////
// Filename    : OpenCasket.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////

#ifndef __SKILL_OPEN_CASKET_HANDLER_H__
#define __SKILL_OPEN_CASKET_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class OpenCasket;
//////////////////////////////////////////////////////////////////////////////

class OpenCasket : public SkillHandler 
{
public:
	OpenCasket() throw() {}
	~OpenCasket() throw() {}
	
public:
    string getSkillHandlerName()  { return "OpenCasket"; }
	SkillType_t getSkillType()  { return SKILL_OPEN_CASKET; }

	void execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);


	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern OpenCasket g_OpenCasket;

#endif // __SKILL_OPEN_CASKET_HANDLER_H__
