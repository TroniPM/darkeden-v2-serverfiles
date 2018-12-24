//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDecayCorpse.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DECAY_CORPSE_H__
#define __EFFECT_DECAY_CORPSE_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDecayCorpse;
// ���� �ð��� ������, ��ü�� ��� �������� �ϰ�, ������ �������� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////

class Corpse;

class EffectDecayCorpse : public Effect 
{
public:
	EffectDecayCorpse(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Corpse* pCorpse, Turn_t delay) throw(Error);
	virtual ~EffectDecayCorpse() throw(Error);

public:
	virtual EffectClass getEffectClass() const throw() { return EFFECT_CLASS_DECAY_CORPSE; }

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
	
	virtual string toString() const throw();

private:
	ObjectID_t m_ObjectID;
};

#endif
