//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDecayMotorcycle.h
// Written by  : Reiot
// Description :
//               ���� �ð��� ������ �ٴڿ� �ִ� �������� ������� �ϴ� 
//               EffectDecayItem�� ��������,
//               Motorcycle���� ����ȴ�. 
//               ������ Motorcycle�� �ٸ� Zone�� ������ �ִ� ����ڰ� 
//               Motorcycle�� call�ϰ� �Ǹ�, ������ motorcycle�� ���ְ�
//               ���ο� Motorcycle�� ����� �־�� �Ѵ�.
//               �� ��������
//                 1. ���ͻ���Ŭ�� ���ִ� ����
//                 2. ���� ����ȭ�� ������ ���������� �Ͼ�� �ϸ�
//               �ٸ� ���� ������ ���ļ��� �� �ȴ�. �׷��Ƿ� �̷� �������
//               Effect�� ���ؼ� heartbeat�ÿ� motorcycle�� ���ְ�
//               ���ο� Effect�� ���ؼ� ���� heartbeat�ÿ� motorcycle�� �����.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DECAY_MOTORCYCLE_H__
#define __EFFECT_DECAY_MOTORCYCLE_H__

#include "Effect.h"

class Item;
class Zone;
class Slayer;

class EffectDecayMotorcycle : public Effect 
{
public:
	EffectDecayMotorcycle(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Item* pItem, Turn_t delay, bool bDeleteFromDB=true) throw(Error);
	virtual ~EffectDecayMotorcycle() throw(Error);

public:
	virtual EffectClass getEffectClass() const throw() { return EFFECT_CLASS_DECAY_ITEM; }

	// OBJECT_PRIORITY_NONE ��� ����, Ÿ�Ͽ� ������ �ȵȴٴ� ���̴�.
	virtual ObjectPriority getObjectPriority() const throw() { return OBJECT_PRIORITY_NONE; }

	virtual void affect() throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__); }
	virtual void affect(Creature* pCreature) throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__); }
	virtual void affect(Item* pItem) throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__);}
	virtual void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget) throw(Error);
	
	virtual void unaffect() throw(Error);
	virtual void unaffect(Creature* pCreature) throw(Error);
	virtual void unaffect(Item* pItem = NULL) throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__);}	
	virtual void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget, Slayer* pSlayer) throw(Error);

	virtual void create(const string & ownerID) throw(Error) {}
	virtual void save(const string & ownerID) throw(Error) {}
	virtual void destroy(const string & ownerID) throw(Error) {}
	
	// get debug string
	virtual string toString() const throw();

private:
	ObjectID_t m_ObjectID;
	bool	   m_bDeleteFromDB;
};

#endif
