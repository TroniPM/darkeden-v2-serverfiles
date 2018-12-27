//////////////////////////////////////////////////////////////////////////////
// Filename    : PoisonMesh.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_POISON_MESH_HANDLER_H__
#define __SKILL_POISON_MESH_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class PoisonMesh;
//////////////////////////////////////////////////////////////////////////////

class PoisonMesh: public SkillHandler 
{
public:
	PoisonMesh()  {}
	~PoisonMesh()  {}
	
public:
    string getSkillHandlerName()  { return "PoisonMesh"; }
	SkillType_t getSkillType()  { return SKILL_POISON_MESH; }

	void execute(Vampire* pVampire, ObjectID_t targetObject, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern PoisonMesh g_PoisonMesh;

#endif // __SKILL_POISON_MESH_HANDLER_H__
