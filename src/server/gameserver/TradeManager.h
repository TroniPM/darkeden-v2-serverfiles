////////////////////////////////////////////////////////////////////////////////
// Filename    : TradeManager.h
// Written by  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __TRADE_MANAGER__
#define __TRADE_MANAGER__

#include "Types.h"
#include "Exception.h"
#include "Timeval.h"
#include <list>
#include <hash_map>

////////////////////////////////////////////////////////////////////////////////
// ��ȯ ���� �÷���
////////////////////////////////////////////////////////////////////////////////

enum
{
	// �������� �ű�� �ִ� ����
	TRADE_TRADING,

	// �������� �� �ű��, ��ȯ�� ��ٸ��� �ִ� ����
	TRADE_FINISH,

	TRADE_MAX
};

////////////////////////////////////////////////////////////////////////////////
// class TradeInfo
////////////////////////////////////////////////////////////////////////////////

class Item;

class TradeInfo
{
///// Member methods /////
public:
	TradeInfo() ;
	~TradeInfo() ;

public:
	const string getMainName(void)  { return m_MainName; }
	void setMainName(const string & Name)  { m_MainName = Name; }

	const string getTargetName(void)  { return m_TargetName; }
	void setTargetName(const string & Name)  { m_TargetName = Name; }

	list<Item*> getItemList(void)  { return m_ItemList; }
	void setItemList(list<Item*> itemList)  { m_ItemList = itemList; }

	Gold_t getGold(void)  { return m_Gold; }
	void setGold(Gold_t gold) { m_Gold = gold; }

	int getStatus(void)  { return m_Status; }
	void setStatus(int status)  { m_Status = status; }

	bool hasItem(Item* pItem) ;
	bool addItem(Item* pItem) ;
	bool removeItem(Item* pItem) ;

	void clearAll(void) ;

	Timeval getLastOKTime(void) const { return m_LastOKTime; }
	void setLastOKTime(const Timeval& lastOKTime) { m_LastOKTime = lastOKTime; }
	void setNextTime(const Timeval& currentTime);
	bool isValidOKTime(const Timeval& currentTime);

protected:
	string 		m_MainName;
	string 		m_TargetName;
	list<Item*> m_ItemList;
	Gold_t      m_Gold;
	int         m_Status;
	Timeval     m_LastOKTime;
};


////////////////////////////////////////////////////////////////////////////////
// class TradeManager
////////////////////////////////////////////////////////////////////////////////

class Creature;

class TradeManager
{
///// Member methods /////
public:
	TradeManager() ;
	~TradeManager() ;

public:
	void init() ;

	bool hasTradeInfo(const string & Name) ;

	TradeInfo* getTradeInfo(const string & Name) ;

	void addTradeInfo(TradeInfo* pInfo) ;

	void removeTradeInfo(const string & Name) ;

public:

	void initTrade(Creature* pCreature1, Creature* pCreature2) ;
	// Ʈ���̵� �� �� ������ 0, ���� ���� ���� ������ ���ϸ� 2, �� �� ������ 1
	int canTrade(Creature* pCreature1, Creature* pCreature2) ;
	void processTrade(Creature* pCreature1, Creature* pCreature2) ;
	void cancelTrade(Creature* pCreature1, Creature* pCreature2) ;
	void cancelTrade(Creature* pCreature1) ;
	bool isTrading(Creature* pCreature1, Creature* pCreature2) ;

///// Member data /////
protected:
	hash_map<string, TradeInfo*> m_InfoMap;
};

#endif

