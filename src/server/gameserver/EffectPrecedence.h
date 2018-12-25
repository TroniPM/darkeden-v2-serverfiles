//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPrecedence.h
// Written by  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_PRECEDENCE_H__
#define __EFFECT_PRECEDENCE_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectPrecedence;
//////////////////////////////////////////////////////////////////////////////

class EffectPrecedence : public Effect 
{
public:
	EffectPrecedence(Creature* pCreature) throw(Error);
	EffectPrecedence(Item* pItem) throw(Error);
	
public:
	virtual EffectClass getEffectClass()  { return EFFECT_CLASS_PRECEDENCE; }

	// OBJECT_PRIORITY_NONE 라는 뜻은, 타일에 들어가서는 안된다는 뜻이다.
	virtual ObjectPriority getObjectPriority()  { return OBJECT_PRIORITY_NONE; }

	virtual void affect() throw(Error);
	virtual void affect(Creature* pCreature) throw(Error);
	virtual void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget) throw(Error);
	
	virtual void unaffect() throw(Error);
	virtual void unaffect(Creature* pCreature) throw(Error);
	virtual void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget) throw(Error);
	void unaffect(Item* pItem) throw(Error) {}

	void create(const string & ownerID) throw(Error) {}
	void save(const string & ownerID) throw(Error) {}
	void destroy(const string & ownerID) throw(Error) {}
	
	virtual string toString() ;

public:
	string getHostName(void) const { return m_HostName; }
	void setHostName(const string& ID) { m_HostName = ID; }

	int getHostPartyID(void) const { return m_HostPartyID; }
	void setHostPartyID(int ID) { m_HostPartyID = ID; }

private:
	string m_HostName;
	int    m_HostPartyID;
	bool   m_bItem;
};

#endif
