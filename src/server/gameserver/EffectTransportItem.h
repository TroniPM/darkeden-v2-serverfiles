//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTransportItem.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_TRANSPORT_ITEM_H__
#define __EFFECT_TRANSPORT_ITEM_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectTransportItem;
// ���� �ð��� ������ �ٴ��� �������� �������
// �ٸ� ������ �Ű����� �ȴ�.
//////////////////////////////////////////////////////////////////////////////

class Item;

class EffectTransportItem : public Effect 
{
public:
	EffectTransportItem(Zone* pZone, ZoneCoord_t sx, ZoneCoord_t sy, Zone* pTargetZone, ZoneCoord_t x, ZoneCoord_t y, Item* pItem, Turn_t delay) throw(Error);
	virtual ~EffectTransportItem() throw(Error);

public:
	virtual EffectClass getEffectClass() const throw() { return EFFECT_CLASS_TRANSPORT_ITEM; }

	// OBJECT_PRIORITY_NONE ��� ����, Ÿ�Ͽ� ������ �ȵȴٴ� ���̴�.
	virtual ObjectPriority getObjectPriority() const throw() { return OBJECT_PRIORITY_NONE; }

	virtual void affect() throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__); }
	virtual void affect(Creature* pCreature) throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__); }
	virtual void affect(Item* pItem) throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__);}
	virtual void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget) throw(Error);
	
	virtual void unaffect() throw(Error);
	virtual void unaffect(Creature* pCreature) throw(Error);
	virtual void unaffect(Item* pItem = NULL) throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__);}	
	virtual void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget) throw(Error);

	virtual void create(const string & ownerID) throw(Error) {}
	virtual void save(const string & ownerID) throw(Error) {}
	virtual void destroy(const string & ownerID) throw(Error) {}
	
	// get debug string
	virtual string toString() const throw();

private:
	ZoneCoord_t m_StartX; 
	ZoneCoord_t m_StartY;
	Zone*		m_pTargetZone;
	ObjectID_t  m_ObjectID;
};

#endif
