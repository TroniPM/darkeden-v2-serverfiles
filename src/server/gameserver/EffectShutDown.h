//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectShutDown.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SHUT_DOWN_H__
#define __EFFECT_SHUT_DOWN_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectShutDown;
//////////////////////////////////////////////////////////////////////////////

class Corpse;

class EffectShutDown : public Effect 
{
public:
	EffectShutDown();
	EffectShutDown(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Corpse* pCorpse, Turn_t delay);
	virtual ~EffectShutDown();

public:
	virtual EffectClass getEffectClass()  { return EFFECT_CLASS_SHUT_DOWN; }

	// OBJECT_PRIORITY_NONE ��� ����, Ÿ�Ͽ� ������ �ȵȴٴ� ���̴�.
	virtual ObjectPriority getObjectPriority()  { return OBJECT_PRIORITY_NONE; }

	virtual void affect();
	virtual void affect(Creature* pCreature);
	virtual void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget);
	
	virtual void unaffect();
	virtual void unaffect(Creature* pCreature);
	virtual void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget);
	void unaffect(Item* pItem)  {}

	void create(const string & ownerID)  {}
	void save(const string & ownerID)  {}
	void destroy(const string & ownerID)  {}

	virtual string toString() ;

public:
	void setDelay(Turn_t delay) throw() { m_Delay = delay; }
	Turn_t getDelay()  { return m_Delay; }
	
private:
	Turn_t m_Delay;

};

#endif
