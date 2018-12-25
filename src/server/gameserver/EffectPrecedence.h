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
	EffectPrecedence(Creature* pCreature);
	EffectPrecedence(Item* pItem);
	
public:
	virtual EffectClass getEffectClass()  { return EFFECT_CLASS_PRECEDENCE; }

	// OBJECT_PRIORITY_NONE ��� ����, Ÿ�Ͽ� ������ �ȵȴٴ� ���̴�.
	virtual ObjectPriority getObjectPriority()  { return OBJECT_PRIORITY_NONE; }

	virtual void affect();
	virtual void affect(Creature* pCreature);
	virtual void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget);
	
	virtual void unaffect();
	virtual void unaffect(Creature* pCreature);
	virtual void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget);
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
