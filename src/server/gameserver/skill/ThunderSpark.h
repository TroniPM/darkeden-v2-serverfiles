//////////////////////////////////////////////////////////////////////////////
// Filename    : ThunderSpark.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_THUNDER_SPARK_HANDLER_H__
#define __SKILL_THUNDER_SPARK_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ThunderSpark;
//////////////////////////////////////////////////////////////////////////////

class ThunderSpark : public SkillHandler 
{
public:
	ThunderSpark()  {}
	~ThunderSpark()  {}
	
public:
    string getSkillHandlerName()  { return "ThunderSpark"; }
	SkillType_t getSkillType()  { return SKILL_THUNDER_SPARK; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ThunderSpark g_ThunderSpark;

#endif // __SKILL_THUNDER_SPARK_HANDLER_H__
