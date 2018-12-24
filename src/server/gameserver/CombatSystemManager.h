//////////////////////////////////////////////////////////////////////////////////////////
//
// Filename    : CombatSystemManager.h
// Written by  : intblue@metrotech.co.kr
// Description : ���� �ý��� �Ŵ���
//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __COMBAT_SYSTEM_MANAGER_H__
#define __COMBAT_SYSTEM_MANAGER_H__

#include <time.h>

#include "ThreadManager.h"
#include "ThreadPool.h"
#include "ZoneGroupThread.h"
#include "ZoneGroup.h"
#include "Zone.h"
#include "ZonePlayerManager.h"
#include "Gpackets/GCSystemMessage.h"
#include "Packet.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////
//
// class CombatSystemManager;
//
// ���� �ý����� �����ϴ� �Ŵ��� ��ü
//
//////////////////////////////////////////////////////////////////////
const int VAMPIRE_HAS_SLAYER_HP_RELIC_POINT = 30;
const int VAMPIRE_HAS_SLAYER_TO_HIT_RELIC_POINT = 15;
const int SLAYER_HAS_VAMPIRE_HP_RELIC_POINT = 30;
const int SLAYER_HAS_VAMPIRE_TO_HIT_RELIC_POINT = 15;

const int RELIC_STAY_ON_BASE      = 0;
const int SAME_RACE_HAVE_RELIC    = 1;
const int ANOTHER_RACE_HAVE_RELIC = 2;
const int RELIC_STAY_ON_ZONE      = 3;

const string RELIC1NAME = "�Ҹ�����";
const string RELIC2NAME = "����";
const string RELIC3NAME = "ó������";
const string RELIC4NAME = "�����ڰ�";

class CombatSystemManager {
	public:
		CombatSystemManager() throw();
		~CombatSystemManager() throw();

		void CheckCombat() throw(Error); // ���� Ȱ��ȭ ���� üũ�Ͽ� ����/�ı� �ǽ�

		void ActiveCombat() throw(Error); // ���� ����
		void DeactiveCombat() throw(Error); // ���� ����

		void BroadcastPacket(Packet*) throw(Error); // ��� ���� ����ڿ��� �޽��� ����
		void BroadcastPacket(Packet*, int condition, int minute) throw(Error); // ��� ���� ����ڿ��� �޽��� ����

		void ActiveMonster(); // ���� ���� ����
		void DeactiveMonster(); // ���� ���� �ı�

		// Relic�� ���� �ľ�
		// 0: ���� �����뿡 ����
		// 1: �ڽ��� ������ ������ ����
		// 2: Ÿ������ ������ ����
		// 3: �ٴڿ� ������ ����
	    int  getRelicStatus(int RelicIndex) { return m_RelicStatus[RelicIndex]; }
		void setRelicStatus(int Relic, int Status) { m_RelicStatus[Relic] = Status; }

		// Relic�� ������
		string getRelicOwner(int RelicIndex) { return m_RelicOwner[RelicIndex]; }
		void   setRelicOwner(int RelicIndex, string Owner) { m_RelicOwner[RelicIndex] = Owner; }

		// �ٸ� ������ ������ ������ �� ���ʽ� ����Ʈ ���
		int getSlayerToHitPoint() const { return m_SlayerToHitPoint; }
		void setSlayerToHitPoint(int tohit) { m_SlayerToHitPoint = tohit; }

		int getSlayerHPPoint() const { return m_SlayerHPPoint; }
		void setSlayerHPPoint(int hp) { m_SlayerHPPoint = hp; }

		int getVampireToHitPoint() const  { return m_VampireToHitPoint; }
		void setVampireToHitPoint(int tohit) { m_VampireToHitPoint = tohit; }

		int getVampireHPPoint() const  { return m_VampireHPPoint; }
		void setVampireHPPoint(int hp) { m_VampireHPPoint = hp; }

		//bool getRelicAttacked() const { return m_RelicAttacked; }
		//void setRelicAttacked(bool attack) { m_RelicAttacked = attack; }

		//bool getRelicMoved() const { return m_RelicMoved; }
		//void setRelicMoved(bool move) { m_RelicMoved = move; }

		bool isCombatFlag() const { return m_bCombat; }
		bool isCombatStartFlag() const { return m_bCombatActive; }
		bool isCombatEndFlag() const { return m_bCombatDeactive; }

		void setCombatActivate() { m_bCombatActive = true; m_bCombatDeactive = false; }
		void setCombatDeactivate() { m_bCombatDeactive = true; m_bCombatActive = false; }

		void setRelic(int relicindex, bool relic) { m_Relic[relicindex] = relic; }
		bool getRelic(int relicindex) const { return m_Relic[relicindex]; }
	

		// set relic storage id, get relic storage id
		void setRelicLocation(int relicindex, int ownerobjectid, int storage, int storageid, int x, int y);

		int getRelicOwnerObjectID(int relicindex) const { return m_RelicOwnerObjectID[relicindex]; }
		int getRelicStorageID(int relicindex) const { return m_RelicStorageID[relicindex]; }
		int getRelicStorage(int relicindex) const { return m_RelicStorage[relicindex]; }
		void setRelicStorage(int relicindex, int storage) { m_RelicStorage[relicindex] = storage; }
		void setRelicStorageID(int relicindex, ObjectID_t object) { m_RelicStorageID[relicindex] = object; }

		ZoneCoord_t getRelicX(int relicindex) const { return m_RelicX[relicindex]; }
		ZoneCoord_t getRelicY(int relicindex) const { return m_RelicY[relicindex]; }


		// set relic object id, get relic object id
		void setRelicObjectID(int relicindex, ObjectID_t object) { m_RelicObjectID[relicindex] = object; }
		ObjectID_t getRelicObjectID(int relicindex) const { return m_RelicObjectID[relicindex]; }

		int getMonsterRegenFlag(int index) const { return m_RegenFlag[index]; }
		void setMonsterRegenFlag(int index, int value, int type); 

		int getMonsterRegenType(int index) const { return m_RegenTypeFlag[index]; }

		void RelicToString(int index);
	private:
		bool m_bCombat; // ������ ���� �� ���� ���θ� ǥ���ϴ� ����
		bool m_bCombatActive;
		bool m_bCombatDeactive;

		int m_RelicStatus[5];
		string m_RelicOwner[5];
		int m_RegenFlag[5];
		int m_RegenTypeFlag[5];

		int m_SlayerHPPoint;
		int m_SlayerToHitPoint;
		int m_VampireToHitPoint;
		int m_VampireHPPoint;

		// �� ������ �����ߴ°� �ϴ� �κ� 
		bool m_Relic[5];

		// �� ������ ��ġ ����
		int m_RelicOwnerObjectID[5];
		int m_RelicStorageID[5];
		int m_RelicStorage[5];
	    ZoneCoord_t m_RelicX[5], m_RelicY[5];

		// �� ������ Object ID
		ObjectID_t m_RelicObjectID[5];

		mutable Mutex m_Mutex;
};

extern CombatSystemManager* g_pCombatSystemManager;

#endif
