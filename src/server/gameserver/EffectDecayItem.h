//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDecayItem.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DECAY_ITEM_H__
#define __EFFECT_DECAY_ITEM_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDecayItem;
// ���� �ð��� ������ �ٴڿ� �ִ� �������� ������µ�, �׸� ���� ����Ʈ�̴�.
//////////////////////////////////////////////////////////////////////////////

class Item;

class EffectDecayItem : public Effect 
{
public:
	EffectDecayItem(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Item* pItem, Turn_t delay, bool bDeleteFromDB=true);
	virtual ~EffectDecayItem();

public:
	virtual EffectClass getEffectClass()  { return EFFECT_CLASS_DECAY_ITEM; }

	// OBJECT_PRIORITY_NONE ��� ����, Ÿ�Ͽ� ������ �ȵȴٴ� ���̴�.
	virtual ObjectPriority getObjectPriority()  { return OBJECT_PRIORITY_NONE; }

	virtual void affect()  { throw UnsupportedError(__PRETTY_FUNCTION__); }
	virtual void affect(Creature* pCreature)  { throw UnsupportedError(__PRETTY_FUNCTION__); }
	virtual void affect(Item* pItem)  { throw UnsupportedError(__PRETTY_FUNCTION__);}
	virtual void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget);
	
	virtual void unaffect();
	virtual void unaffect(Creature* pCreature);
	virtual void unaffect(Item* pItem = NULL)  { throw UnsupportedError(__PRETTY_FUNCTION__);}	
	virtual void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget);

	virtual void create(const string & ownerID)  {}
	virtual void save(const string & ownerID)  {}
	virtual void destroy(const string & ownerID)  {}
	
	// get debug string
	virtual string toString() ;

private:
	ObjectID_t m_ObjectID;
	bool	   m_bDeleteFromDB;
};

#endif
