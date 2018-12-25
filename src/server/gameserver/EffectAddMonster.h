//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectAddMonster.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_ADD_MONSTER_H__
#define __EFFECT_ADD_MONSTER_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectAddMonster;
// 일정 시간이 지나면 바닥에 있는 아이템은 사라지는데, 그를 위한 이펙트이다.
//////////////////////////////////////////////////////////////////////////////

class Item;

class EffectAddMonster : public Effect 
{
public:
	EffectAddMonster(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Creature* pCreature, Turn_t delay);
	virtual ~EffectAddMonster();

public:
	virtual EffectClass getEffectClass()  { return EFFECT_CLASS_ADD_MONSTER; }

	// OBJECT_PRIORITY_NONE 라는 뜻은, 타일에 들어가서는 안된다는 뜻이다.
	virtual ObjectPriority getObjectPriority()  { return OBJECT_PRIORITY_NONE; }

	virtual void affect() throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__); }
	virtual void affect(Creature* pCreature) throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__); }
	virtual void affect(Object* pObject) throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__);}
	virtual void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Creature* pCreature);
	
	virtual void unaffect();
	virtual void unaffect(Object* pObject);
	virtual void unaffect(Creature* pCreature = NULL) throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__);}	
	virtual void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Creature* pCreature);

	virtual void create(const string & ownerID) throw(Error) {}
	virtual void save(const string & ownerID) throw(Error) {}
	virtual void destroy(const string & ownerID) throw(Error) {}
	
	// get debug string
	virtual string toString() ;

private:
	ObjectID_t m_ObjectID;
	bool	   m_bAllowCreature;
};

#endif
