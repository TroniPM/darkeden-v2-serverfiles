//////////////////////////////////////////////////////////////////////////////
// Filename    : CreatureManager.h 
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __CREATURE_MANANGER_H__
#define __CREATURE_MANANGER_H__

#include "Creature.h"
#include "Mutex.h"
#include <hash_map>

class Packet;

//////////////////////////////////////////////////////////////////////////////
// class CreatureManager
//////////////////////////////////////////////////////////////////////////////

class CreatureManager 
{
public:
	CreatureManager() ;
	virtual ~CreatureManager() ;
	
public:
	virtual void addCreature(Creature* pCreature) throw(DuplicatedException, Error);
	virtual void deleteCreature(ObjectID_t objectID) ;//NoSuchElementException, Error);
	Creature* getCreature(ObjectID_t objectID) ;//NoSuchElementException, Error);
	Creature* getCreature(const string& Name) ;//NoSuchElementException, Error);

	virtual void processCreatures();
	virtual void killCreature(Creature* pDeadCreature);

	void broadcastPacket(Packet* pPacket, Creature* owner);
	void broadcastDarkLightPacket(Packet* pPacket1, Packet* pPacket2, Creature* owner);
	void broadcastLevelWarBonusPacket(Packet* pPacket, Creature* owner);

	WORD getSize()  { return m_Creatures.size(); }

	hash_map< ObjectID_t, Creature* > & getCreatures()  { return m_Creatures; }
	const hash_map< ObjectID_t, Creature* > & getCreatures()  { return m_Creatures; }

	string toString() ;

protected:
	hash_map< ObjectID_t, Creature* > m_Creatures;
	mutable Mutex m_Mutex;
};

#endif
