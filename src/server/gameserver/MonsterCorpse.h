//////////////////////////////////////////////////////////////////////////////
// Filename    : MonsterCorpse.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __MONSTER_CORPSE_H__
#define __MONSTER_CORPSE_H__

#include "Item.h"
#include "ItemFactory.h"
#include "Inventory.h"
#include "Corpse.h"

//////////////////////////////////////////////////////////////////////////////
// class MonsterCorpse;
// ���Ͱ� �׾��� ���, ����� ��ü�̴�.
//////////////////////////////////////////////////////////////////////////////

class Monster;

class MonsterCorpse : public Corpse 
{
public:
	MonsterCorpse(Monster* pMonster);
	MonsterCorpse (MonsterType_t MType, const string& name, Dir_t dir);
	virtual ~MonsterCorpse() ;

public:
	virtual void create(const string & ownerID, Storage storage, DWORD storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual bool destroy();
	virtual void save(const string & ownerID, Storage storage, DWORD storageID, BYTE x, BYTE y);
	void tinysave(const string & field)  { tinysave(field.c_str()); }
    void tinysave(const char* field)  {}

	virtual ItemClass getItemClass()  { return ITEM_CLASS_CORPSE; }

	virtual ItemType_t getItemType()  { return MONSTER_CORPSE; }
	virtual void setItemType(ItemType_t monsterType)  { throw UnsupportedError(__PRETTY_FUNCTION__); }

	bool isNextTreasureHead() { return (!m_Treasures.empty() && m_Treasures.front()->getItemClass() == ITEM_CLASS_SKULL); }

	virtual string toString() ;

// own methods
public:
	MonsterType_t getMonsterType()  { return m_MonsterType; }
	void setMonsterType(MonsterType_t monsterType)  { m_MonsterType = monsterType; }

	string getName()  { return m_Name; }
	void setName(string name)  { m_Name = name; }

	string getMonsterName()  { return m_Name; }
	void setMonsterName(string name)  { m_Name = name; }

	Dir_t getDir()  { return m_Dir; }
	void setDir(Dir_t dir)  { m_Dir = dir; }

	bool gethasHead()  { return m_bhasHead; }
	void addHead()  { m_bhasHead = true; }
	void removeHead()  { m_bhasHead = false; }

	const string& getHostName(void) const { return m_HostName; }
	void setHostName(const string& name) { m_HostName = name; }
	
	int getHostPartyID(void) const { return m_HostPartyID; }
	void setHostPartyID(int ID) { m_HostPartyID = ID; }

	const string& getQuestHostName() const { return m_QuestHostName; }
	void setQuestHostName( const string& name ) { m_QuestHostName = name; }

	bool isShrine() const { return m_bShrine; }
	void setShrine( bool bShrine = true ) { m_bShrine = bShrine; }

	void setLastKiller(ObjectID_t id) { m_LastKiller = id; }
	ObjectID_t getLastKiller() const { return m_LastKiller; }

// data members
protected:
	MonsterType_t m_MonsterType; // ���� Ÿ��
	string        m_Name;        // ���� �̸�
	Dir_t         m_Dir;         // ��ü�� ����
	bool          m_bhasHead;    // �Ӹ��� �޷� �ֳ� ����.
	string        m_HostName;    // �� ��ü���� ������ �����ۿ� ���� �켱���� ���� ���� �̸�
	int           m_HostPartyID; // �� ��ü���� ������ �����ۿ� ���� �켱���� ���� ��Ƽ�� ID
	string		  m_QuestHostName;	// �� ��ü���� ������ ����Ʈ �����ۿ� ���� �켱���� ���� ���� �̸�

	bool		  m_bShrine;	 // �����ΰ�?
	ObjectID_t	m_LastKiller;
};

#endif
