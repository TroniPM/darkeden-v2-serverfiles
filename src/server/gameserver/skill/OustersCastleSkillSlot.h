#ifndef __OUSTERS_CASTLE_SKILL_SLOT_H__
#define __OUSTERS_CASTLE_SKILL_SLOT_H__

#include "OustersSkillSlot.h"

class OustersCastleSkillSlot : public OustersSkillSlot
{
public:
	OustersCastleSkillSlot() 
		: OustersSkillSlot() { }
	OustersCastleSkillSlot( SkillType_t SkillType, ulong Interval, ulong CastingTime ) 
		: OustersSkillSlot( SkillType, Interval, CastingTime ) { }
	~OustersCastleSkillSlot()  { }

public:
	virtual void save(const string & ownerID) { }
	virtual void save() { } 
	virtual void create(const string & ownerID) { }
};

#endif// __OUSTERS_CASTLE_SKILL_SLOT_H__
