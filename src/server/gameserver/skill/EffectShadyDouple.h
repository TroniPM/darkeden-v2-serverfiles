//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBlazeWalk.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_CLASS_SHADY_DOUPLE__
#define __EFFECT_CLASS_SHADY_DOUPLE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectBlazeWalk
//////////////////////////////////////////////////////////////////////////////

class EffectShadyDouple : public Effect 
{
public:
	EffectShadyDouple(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_SHADY_DOUPLE; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);

	string toString() ;

public:
	HP_t getPoint()  { return m_Point; }
	void setPoint(HP_t Point) throw() { m_Point = Point; }

	void setUserObjectID(ObjectID_t oid) throw() { m_UserObjectID = oid; }
	ObjectID_t getUserObjectID()  { return m_UserObjectID; }

	uint getAttackNum() const { return m_AttackNum; }
	void setAttackNum( uint AttackNum ) { m_AttackNum = AttackNum; }


private:
	HP_t    m_Point;
	ObjectID_t m_UserObjectID;
	uint m_AttackNum;
};

#endif // __EFFECT_BLAZE_WALK__
