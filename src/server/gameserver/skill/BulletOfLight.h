//////////////////////////////////////////////////////////////////////////////
// Filename    : BulletOfLight.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BULLET_OF_LIGHT_HANDLER_H__
#define __SKILL_BULLET_OF_LIGHT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BulletOfLight;
//////////////////////////////////////////////////////////////////////////////

class BulletOfLight : public SkillHandler 
{
public:
	BulletOfLight()  {}
	~BulletOfLight()  {}

public:
    string getSkillHandlerName()  { return "BulletOfLight"; }
	SkillType_t getSkillType()  { return SKILL_BULLET_OF_LIGHT; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BulletOfLight g_BulletOfLight;

#endif // __SKILL_BULLET_OF_LIGHT_HANDLER_H__
