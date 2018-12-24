//////////////////////////////////////////////////////////////////////////////
// Filename    : PCManager.h 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PC_MANANGER_H__
#define __PC_MANANGER_H__

#include "CreatureManager.h"
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// class PCManager
//////////////////////////////////////////////////////////////////////////////
const BYTE defaultRaceValue = 0xFF;

class PCManager : public CreatureManager 
{
public:
	PCManager() throw();
	virtual ~PCManager() throw();
	
public:

	// ũ��ó �Ŵ����� �� ũ��ó ��ü�� ����Ѵ�.
	//virtual void addCreature(Creature* pCreature) throw(DuplicatedException, Error);
	
	// ũ��ó �Ŵ����� ����ִ� Ư�� ũ��ó ��ü�� �����Ѵ�.
	//virtual void deleteCreature(ObjectID_t objectID) throw(NoSuchElementException, Error);
	
	// ũ��ó �Ŵ����� ����ִ� Ư�� ũ��ó ��ü�� �����Ѵ�.
	//Creature* getCreature(ObjectID_t objectID) const throw(NoSuchElementException, Error);

	// �Ŵ����� �Ҽӵ� ũ��ó��(NPC,Monster)�� ó���Ѵ�.
	virtual void processCreatures() throw(Error);

	// ���� ũ��ó�� ó���Ѵ�.
	virtual void killCreature(Creature* pDeadCreature) throw(Error);

	// PC �Ŵ����� ���, ��ε�ĳ��Ʈ�Ѵ�.
	//void broadcastPacket(Packet* pPacket, Creature* owner) throw(Error);

	// ��� ����ڵ� �ٸ� ������ �̵���Ų��.
	void transportAllCreatures(ZoneID_t ZoneID, ZoneCoord_t ZoneX = 0xffff, ZoneCoord_t ZoneY = 0xffff, Race_t race=defaultRaceValue, Turn_t delay=10) const throw (Error);
	void transportPartyCreatures (ZoneID_t ZoneID, ZoneCoord_t ZoneX = 0xffff, ZoneCoord_t ZoneY = 0xffff, int PartyID=0, Turn_t delay=10) const throw (Error);
	
	// get debug string 
	string toString() const throw();

	// Holy Land Race Bonus ��ȭ�� ���� �÷��̾� refresh
	void setRefreshHolyLandPlayer( bool bRefresh ) { m_bRefreshHolyLandPlayer = bRefresh; }
//	void setRefreshLevelWarBonusZonePlayer( bool bRefresh ) { m_bRefreshLevelWarBonusZonePlayer = bRefresh; }

	vector<uint>	getPCNumByRace() const;
private:
	bool m_bRefreshHolyLandPlayer;
//	bool m_bRefreshLevelWarBonusZonePlayer;

};

#endif
