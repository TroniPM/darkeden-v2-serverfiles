//////////////////////////////////////////////////////////////////////////////
// Filename    : MasterLairInfoManager.h
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __MASTER_LAIR_INFO_MANAGER_H__
#define __MASTER_LAIR_INFO_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include <hash_map>

// ������ �׿����� ������ �޴� ��� ����ġ
const int MASTER_KILL_RANK_EXP = 23300;

//                            0x00bbggrr
const uint MASTER_SAY_COLOR = 0x003030FF;

//////////////////////////////////////////////////////////////////////////////
// class MasterLairInfo;
//////////////////////////////////////////////////////////////////////////////

class MasterLairInfo 
{
public:
	MasterLairInfo();
	~MasterLairInfo();

public:
	ZoneID_t getZoneID()  { return m_ZoneID; }
	void setZoneID(ZoneID_t zoneID)  { m_ZoneID = zoneID; }

	MonsterType_t getMasterNotReadyMonsterType()  { return m_MasterNotReadyMonsterType; }
	void setMasterNotReadyMonsterType(MonsterType_t mt)  { m_MasterNotReadyMonsterType = mt; }

	MonsterType_t getMasterMonsterType()  { return m_MasterMonsterType; }
	void setMasterMonsterType(MonsterType_t mt)  { m_MasterMonsterType = mt; }
	
	bool isMasterRemainNotReady()  { return m_MasterRemainNotReady; }
	void setMasterRemainNotReady(bool toCorpse=true)  { m_MasterRemainNotReady = toCorpse; }

	ZoneCoord_t getMasterX()  { return m_MasterX; }
	void setMasterX(ZoneCoord_t x)  { m_MasterX = x; }

	ZoneCoord_t getMasterY()  { return m_MasterY; }
	void setMasterY(ZoneCoord_t y)  { m_MasterY = y; }

	Dir_t getMasterDir()  { return m_MasterDir; }
	void setMasterDir(Dir_t dir)  { m_MasterDir = dir; }

	int  getMaxPassPlayer()  { return m_MaxPassPlayer; }
	void setMaxPassPlayer(int mp)  { m_MaxPassPlayer = mp; }

	//int  getMaxSummonMonster()  { return m_MasterMonsterType; }
	//void setMaxSummonMonster(int mt)  { m_MasterMonsterType = mt; }

	ZoneCoord_t  getSummonX()  { return m_SummonX; }
	void setSummonX(ZoneCoord_t x)  { m_SummonX = x; }

	ZoneCoord_t  getSummonY()  { return m_SummonY; }
	void setSummonY(ZoneCoord_t y)  { m_SummonY = y; }

	int  getFirstRegenDelay()  { return m_FirstRegenDelay; }
	void setFirstRegenDelay(int delay)  { m_FirstRegenDelay = delay; }

	int  getRegenDelay()  { return m_RegenDelay; }
	void setRegenDelay(int delay)  { m_RegenDelay = delay; }

	int  getStartDelay()  { return m_StartDelay; }
	void setStartDelay(int delay)  { m_StartDelay = delay; }

	int  getEndDelay()  { return m_EndDelay; }
	void setEndDelay(int delay)  { m_EndDelay = delay; }

	int  getKickOutDelay()  { return m_KickOutDelay; }
	void setKickOutDelay(int delay)  { m_KickOutDelay = delay; }

	ZoneID_t  getKickZoneID()  { return m_KickZoneID; }
	void setKickZoneID(ZoneID_t zoneID)  { m_KickZoneID = zoneID; }

	ZoneCoord_t  getKickZoneX()  { return m_KickZoneX; }
	void setKickZoneX(ZoneCoord_t x)  { m_KickZoneX = x; }

	ZoneCoord_t  getKickZoneY()  { return m_KickZoneY; }
	void setKickZoneY(ZoneCoord_t y)  { m_KickZoneY = y; }

	int  getLairAttackTick()  { return m_LairAttackTick; }
	void setLairAttackTick(int t)  { m_LairAttackTick = t; }

	int  getLairAttackMinNumber()  { return m_LairAttackMinNumber; }
	void setLairAttackMinNumber(int t)  { m_LairAttackMinNumber = t; }

	int  getLairAttackMaxNumber()  { return m_LairAttackMaxNumber; }
	void setLairAttackMaxNumber(int t)  { m_LairAttackMaxNumber = t; }

	void setSayText(vector<string>& sayWords, const string& text) ;
	void setMasterSummonSay(const string& text) ;
	void setMasterDeadSlayerSay(const string& text) ;
	void setMasterDeadVampireSay(const string& text) ;
	void setMasterNotDeadSay(const string& text) ;

	const string& getRandomMasterSummonSay() ;
	const string& getRandomMasterDeadSlayerSay() ;
	const string& getRandomMasterDeadVampireSay() ;
	const string& getRandomMasterNotDeadSay() ;

	string toString() ;

private:
	ZoneID_t       m_ZoneID;                    // �� ���̵�
	MonsterType_t  m_MasterNotReadyMonsterType;         // �������� NotReady ���¿����� MonsterType
	MonsterType_t  m_MasterMonsterType;         // �������� MonsterType
	bool           m_MasterRemainNotReady;	// NotReady������ Master�� ��ü�� �ٲٱ�
	ZoneCoord_t    m_MasterX;                   // �������� X��ǥ
	ZoneCoord_t    m_MasterY;         			// �������� Y��ǥ
	Dir_t          m_MasterDir;         		// �������� ����
	int            m_MaxPassPlayer;            // �ִ� ����� ��
	//int            m_MaxSummonMonster;          // �ִ� ���� ��ȯ ����
	ZoneCoord_t    m_SummonX;                   // ���� ��ȯ ��ǥ
	ZoneCoord_t    m_SummonY;         			// ���� ��ȯ ��ǥ
	int            m_FirstRegenDelay;           // ������ ������ ���� ���� �ֱ�(��)
	int            m_RegenDelay;                // ������ ���� ���� �ֱ�(��)
	int            m_StartDelay;                // ���� ����, ������ ��Ȱ �ð�
	int            m_EndDelay;                  // �����͸� ���� �� �ִ� �ð�, �� �ð� ���Ŀ��� ���� �߹�
	int            m_KickOutDelay;              // �����͸� ���� ��, �����߹������ �ð�

	// �����߹��ų ��
	ZoneID_t       m_KickZoneID;                 
	ZoneCoord_t    m_KickZoneX;
	ZoneCoord_t    m_KickZoneY;

	// Lair ��ü ����
	int            m_LairAttackTick;	
	int            m_LairAttackMinNumber;	
	int            m_LairAttackMaxNumber;	

	// �� ��ȯ�Ҷ� �ϴ� ��
	vector<string> m_MasterSummonSay;

	// �����Ͱ� ���� �� �ϴ� ��
	vector<string> m_MasterDeadSlayerSay;
	vector<string> m_MasterDeadVampireSay;

	// �����Ͱ� �� �׾����� �ϴ� ��
	vector<string> m_MasterNotDeadSay;
};

//////////////////////////////////////////////////////////////////////////////
// class MasterLairInfoManager;
// ZoneID �� Ű������ �ؼ� �� ������ �˻��� �� �ִ� ����� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////

class MasterLairInfoManager 
{
public:
	MasterLairInfoManager() ;
	~MasterLairInfoManager() ;

public:
	void init();
	void load();
	void reload();
	
	void addMasterLairInfo(MasterLairInfo* pMasterLairInfo);
	void deleteMasterLairInfo(ZoneID_t zoneID) ;
	MasterLairInfo* getMasterLairInfo(ZoneID_t zoneID) ;
	int  size() const	{ return m_MasterLairInfos.size(); }

	string toString() ;

private:
	hash_map<ZoneID_t, MasterLairInfo*> m_MasterLairInfos; // zone info �� �ؽ���
};

extern MasterLairInfoManager* g_pMasterLairInfoManager;

#endif
