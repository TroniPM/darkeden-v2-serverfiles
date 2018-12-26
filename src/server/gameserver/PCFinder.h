//////////////////////////////////////////////////////////////////////////////
// Filename    : PCFinder.h
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __PC_FINDER_H__
#define __PC_FINDER_H__

#include "Types.h"
#include "Exception.h"
#include "Creature.h"
#include "NPC.h"
#include "Mutex.h"
#include <hash_map>
#include <map>

//////////////////////////////////////////////////////////////////////////////
// class PCFinder;
// ���� ������ �۷ι� �Ŵ��� ��ü��, PC �̸��� ����ؼ� PC��ü�� ������ �� �ֵ���
// ���ش�. ���������� hash_map �� ����ؼ�, �˻� �ӵ��� ����Ų��.
//////////////////////////////////////////////////////////////////////////////

class PCFinder 
{
public:
	PCFinder() ;
	~PCFinder() ;

public:
	// add creature to hash_map
	// execute just once at PC's login
	void addCreature(Creature* pCreature) throw(DuplicatedException, Error);

	// delete creature from hash_map
	// execute just once at PC's logout
	void deleteCreature(const string & name) ;//NoSuchElementException, Error);

	// get creature with PC-name
	Creature* getCreature(const string & name) ; //NoSuchElementException, Error);

	// get creature with PC-name
	Creature* getCreature_LOCKED(const string & name) ; //NoSuchElementException, Error);

	// PlayerID. for BillingServer. by sigi. 2002.11.18
	Creature* getCreatureByID(const string & ID) ; //NoSuchElementException, Error);
	Creature* getCreatureByID_LOCKED(const string & ID) ; //NoSuchElementException, Error);

	// add NPC to hash_map
	void addNPC(NPC *npc) throw(DuplicatedException, Error);
	
	// delete NPC from hash_map
	void deleteNPC(const string & name) ;

	// get NPC 
	NPC* getNPC(const string & name) ;
	NPC* getNPC_LOCKED(const string & name) ;

	// get creature's IP address
	IP_t getIP(const string & name) ;

	list<Creature*>	getGuildCreatures(GuildID_t gID, uint Num);

/*	pair<multimap< GuildID_t, Creature* >::const_iterator, multimap< GuildID_t, Creature* >::const_iterator>
		getGuildRange(GuildID_t gID) const { return m_GuildMap.equal_range(gID); }*/

	void lock()  { m_Mutex.lock(); }
	void unlock()  { m_Mutex.unlock(); }

private:
	hash_map< string, Creature* > 	m_PCs;
	hash_map< string, Creature* > 	m_IDs;	// PlayerID. for BillingServer. by sigi. 2002.11.18
	hash_map< string, NPC* > 		m_NPCs;	// NPCs.. for NPC trace ;; by DEW  2003. 04. 16
//	multimap< GuildID_t, Creature* >	m_GuildMap;
	mutable Mutex m_Mutex;
};

// global variable declaration
extern PCFinder* g_pPCFinder;

#endif
