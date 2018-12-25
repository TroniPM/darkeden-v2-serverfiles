//////////////////////////////////////////////////////////////////////////////
// Filename    : ChainOfDemon.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CHAIN_OF_DEMON_HANDLER_H__
#define __SKILL_CHAIN_OF_DEMON_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ChainOfDemon;
//////////////////////////////////////////////////////////////////////////////

class ChainOfDemon: public SkillHandler 
{
public:
	ChainOfDemon() throw() {}
	~ChainOfDemon() throw() {}
	
public:
    string getSkillHandlerName()  { return "ChainOfDemon"; }
	SkillType_t getSkillType()  { return SKILL_CHAIN_OF_DEMON; }

	void execute(Vampire* pVampire, ObjectID_t targetObject, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ChainOfDemon g_ChainOfDemon;

#endif // __SKILL_POISON_MESH_HANDLER_H__
