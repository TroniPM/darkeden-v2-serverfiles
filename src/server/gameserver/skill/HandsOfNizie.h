//////////////////////////////////////////////////////////////////////////////
// Filename    : HandsOfNizie.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HANDS_OF_NIZIE_HANDLER_H__
#define __SKILL_HANDS_OF_NIZIE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class HandsOfNizie;
//////////////////////////////////////////////////////////////////////////////

class HandsOfNizie: public SkillHandler 
{
public:
	HandsOfNizie()  {}
	~HandsOfNizie()  {}
	
public:
    string getSkillHandlerName()  { return "HandsOfNizie"; }

	SkillType_t getSkillType()  { return SKILL_HANDS_OF_NIZIE; }

	void execute(Ousters* pOusters, ObjectID_t targetObject, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern HandsOfNizie g_HandsOfNizie;

#endif // __SKILL_HANDS_OF_NIZIE_HANDLER_H__
