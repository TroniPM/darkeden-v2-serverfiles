//////////////////////////////////////////////////////////////////////////////
// Filename    : MasterLairManager.h 
// Written by  : ��
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __MASTER_LAIR_MANAGER_H__
#define __MASTER_LAIR_MANAGER_H__

#include "MonsterCounter.h"
#include "Item.h"
#include "Timeval.h"
#include "Mutex.h"
#include <hash_map>
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// class MasterLairManager
//////////////////////////////////////////////////////////////////////////////

class Zone;

class MasterLairManager
{
public : 
	enum MasterLairEvent 
	{ 
		EVENT_WAITING_PLAYER,     // ������� ������ ��ٸ���. 
		EVENT_MINION_COMBAT,      // ��ȯ�� ���Ϳ� �ο��. 
		EVENT_MASTER_COMBAT,      // �����Ϳ� �ο��. 
		EVENT_WAITING_KICK_OUT,    // ����� �����߹� ���(������ ���� ����� ���� �ð�) 
		EVENT_WAITING_REGEN,      // �ٽ� �����Ǳ� ��ٸ���. 

		EVENT_MAX
	}; 


public:
	MasterLairManager(Zone* pZone);
	~MasterLairManager() ;

	MasterLairEvent getCurrentEvent() const { return m_Event; }

	bool enterCreature(Creature* pCreature);  // ���� ������ �����Ѱ�? 
	bool leaveCreature(Creature* pCreature);  // ������ ���� ���

	bool heartbeat();

	//void increaseSummonedMonsterNumber(int num);
	bool isMasterReady() const { return m_bMasterReady; }
	void setMasterReady(bool bReady=true) { m_bMasterReady = bReady; }

	void startEvent();
	void stopEvent();

	void lock()  { m_Mutex.lock(); }
    void ulnock()  { m_Mutex.unlock(); }

	string toString() ;

protected :
	void processEventWaitingPlayer();
	void processEventMinionCombat();
	void processEventMasterCombat();
	void processEventWaitingKickOut();
	void processEventWaitingRegen();

	void activeEventWaitingPlayer();
	void activeEventMinionCombat();
	void activeEventMasterCombat();
	void activeEventWaitingKickOut();
	void activeEventWaitingRegen();

	void deleteAllMonsters();		// ��� ���� ����
	void kickOutPlayers();		// ����� ���� �߹�
	void giveKillingReward();		// ������ �׿��� �� �޴� ����
	void killAllMonsters();		// ��� ���͸� ���δ�

private : 
	Zone*             m_pZone;  
	ObjectID_t        m_MasterID;           // ������ �� ���� 
	ZoneCoord_t       m_MasterX;
	ZoneCoord_t       m_MasterY;

	bool              m_bMasterReady;      // �����Ͱ� �ο� �غ� �Ǿ���? 

	//int               m_nMaxSummonMonster; // �����Ͱ� ��ȯ�� �ִ��� ���� �� 
	//int               m_nSummonedMonster;  // �����Ͱ� ��ȯ�� ���� �� 

	int               m_nMaxPassPlayer;	   // �ִ� ���� ����� ��
	int               m_nPassPlayer;       // Pass�� ���� ��� �� 

	MasterLairEvent   m_Event;             // ������ �̺�Ʈ ���� 
	Timeval           m_EventTime;         // ������ �̺�Ʈ�� ���ӵ� �ð�
	int               m_EventValue;		   // �̺�Ʈ�� ���õ� ��

	Timeval           m_RegenTime;         // �� �����ϰ� �ٽ� �����ϴ� �ð� 


	mutable Mutex     m_Mutex;				// m_nPassPlayer�� Ȯ���� üũ�ҷ���..
};

#endif
