//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectCallMotorcycle.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DECAY_ITEM_H__
#define __EFFECT_DECAY_ITEM_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectCallMotorcycle;
// ���� �ð� �� heartbeat�� ����ڿ��� ������̸� ȣ���� �ִ� �̺�Ʈ�̴�.
//////////////////////////////////////////////////////////////////////////////

class Item;

class EffectCallMotorcycle : public Effect 
{
public:
	EffectCallMotorcycle(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Item* pItem, Turn_t delay, bool bDeleteFromDB=true);
	virtual ~EffectCallMotorcycle();

public:
	virtual EffectClass getEffectClass()  { return EFFECT_CLASS_DECAY_ITEM; }

	// OBJECT_PRIORITY_NONE ��� ����, Ÿ�Ͽ� ������ �ȵȴٴ� ���̴�.
	virtual ObjectPriority getObjectPriority()  { return OBJECT_PRIORITY_NONE; }

	virtual void affect() throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__); }
	virtual void affect(Creature* pCreature) throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__); }
	virtual void affect(Item* pItem) throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__);}
	virtual void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget);
	
	virtual void unaffect();
	virtual void unaffect(Creature* pCreature);
	virtual void unaffect(Item* pItem = NULL) throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__);}	
	virtual void unaffect(Zone* pZone, Zone* pTargetZone, ZoneCoord_t TargetX, ZoneCoord_t TargetY, Object* pTarget);

	virtual void create(const string & ownerID) throw(Error) {}
	virtual void save(const string & ownerID) throw(Error) {}
	virtual void destroy(const string & ownerID) throw(Error) {}
	
	// get debug string
	virtual string toString() ;

private:
	ObjectID_t m_ObjectID;
	bool	   m_bDeleteFromDB;
};

#endif
