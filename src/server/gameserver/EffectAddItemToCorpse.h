//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectAddItemToCorpse.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_ADD_ITEM_TO_CORPSE_H__
#define __EFFECT_ADD_ITEM_TO_CORPSE_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectAddItemToCorpse;
// �������� ��ü�� �߰��Ѵ�.
//////////////////////////////////////////////////////////////////////////////

class Item;

class EffectAddItemToCorpse : public Effect 
{
public:
	EffectAddItemToCorpse(Zone* pZone, Item* pItem, ObjectID_t corpseObjectID, Turn_t delay);
	virtual ~EffectAddItemToCorpse();

public:
	virtual EffectClass getEffectClass()  { return EFFECT_CLASS_ADD_ITEM_TO_CORPSE; }

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

	void		setCorpseObjectID(ObjectID_t objectID) 	{ m_CorpseObjectID = objectID; }
	ObjectID_t	getCorpseObjectID() const				{ return m_CorpseObjectID; }
	
	// get debug string
	virtual string toString() ;

private:
	ObjectID_t m_CorpseObjectID;
};

#endif
