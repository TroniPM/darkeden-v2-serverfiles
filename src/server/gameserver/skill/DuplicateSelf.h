//////////////////////////////////////////////////////////////////////////////
// Filename    : DuplicateSelf.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DUPLICATE_SELF_HANDLER_H__
#define __SKILL_DUPLICATE_SELF_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class DuplicateSelf;
//////////////////////////////////////////////////////////////////////////////

class DuplicateSelf: public SkillHandler 
{
public:
	DuplicateSelf() ;
	~DuplicateSelf()  {}
	
public:
    string getSkillHandlerName()  { return "DuplicateSelf"; }
	SkillType_t getSkillType()  { return SKILL_DUPLICATE_SELF; }

	//void execute(Slayer* pSlayer, SlayerSkillSlot* pSlayerSkillSlot, CEffectID_t CEffectID);
	//void execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster);

	void computeOutput(const SkillInput& input, SkillOutput& output);

private :
	// [원래MType] = 분신MType
	hash_map<MonsterType_t, MonsterType_t> m_DuplicateMonsterTypes;
};

// global variable declaration
extern DuplicateSelf g_DuplicateSelf;

#endif // __SKILL_HIDE_HANDLER_H__
