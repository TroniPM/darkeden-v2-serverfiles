//////////////////////////////////////////////////////////////////////////////
// Filename    : HarpoonBomb.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HARPOON_BOMB_HANDLER_H__
#define __SKILL_HARPOON_BOMB_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class HarpoonBomb;
//////////////////////////////////////////////////////////////////////////////

class HarpoonBomb : public SkillHandler 
{
public:
	HarpoonBomb()  {}
	~HarpoonBomb()  {}

public:
    string getSkillHandlerName()  { return "HarpoonBomb"; }
	SkillType_t getSkillType()  { return SKILL_HARPOON_BOMB; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern HarpoonBomb g_HarpoonBomb;

#endif // __SKILL_HARPOON_BOMB_HANDLER_H__
