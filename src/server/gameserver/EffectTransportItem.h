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
	EffectTransportItem(Zone* pZone, ZoneCoord_t sx, ZoneCoord_t sy, Zone* pTargetZone, ZoneCoord_t x, ZoneCoord_t y, Item* pItem, Turn_t delay);
	virtual ~EffectTransportItem();

public:
	virtual EffectClass getEffectClass()  { return EFFECT_CLASS_TRANSPORT_ITEM; }

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
	ZoneCoord_t m_StartX; 
	ZoneCoord_t m_StartY;
	Zone*		m_pTargetZone;
	ObjectID_t  m_ObjectID;
};

#endif
