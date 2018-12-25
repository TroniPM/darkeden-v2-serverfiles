#ifndef __CASTLE_SHRINE_INFO_MANAGER_H__
#define __CASTLE_SHRINE_INFO_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "ShrineInfoManager.h"
#include <hash_map>

class PlayerCreature;
class ZoneItemPosition;
class Zone;
class Item;
class CastleSymbol;
class MonsterCorpse;

class CastleShrineSet
{
public: 
	CastleShrineSet() {}
	~CastleShrineSet() {}

	ItemID_t getCastleSymbolItemID() const			{ return m_ItemID; }
	void	 setCastleSymbolItemID(ItemID_t itemID) 	{ m_ItemID = itemID; }

	string toString() ;

public :
	ShrineID_t		m_ShrineID;				// Shrine ID. ItemType�� ���ƾ� �Ѵ�.
	ShrineInfo		m_GuardShrine;			// �� �ȿ� �ִ� Shrine
	ShrineInfo		m_HolyShrine;			// �ƴ��� ������ �ִ� Shrine
	ItemType_t		m_ItemType;				// ���� ���� ItemType
	ItemID_t		m_ItemID;				// ���� ���� ItemID
};


class CastleShrineInfoManager
{
public:
	typedef hash_map<ShrineID_t, CastleShrineSet*>	HashMapShrineSet;
	typedef HashMapShrineSet::iterator			HashMapShrineSetItor;
	typedef HashMapShrineSet::const_iterator	HashMapShrineSetConstItor;

public:
	CastleShrineInfoManager() {}
	~CastleShrineInfoManager();

public:
	void init();
	void load();
	void clear();

	void addAllShrineToZone();
	Item* addShrineToZone( ShrineInfo& shrineInfo, ItemType_t itemType = 0 );

	void addShrineSet( CastleShrineSet* pShrineSet );
	void deleteShrineSet( ShrineID_t shrineID );
	CastleShrineSet* getShrineSet( ShrineID_t shrineID ) ;
	int  size() const { return m_ShrineSets.size(); }

	string toString() ;

public:
	bool isMatchHolyShrine(Item* pItem, MonsterCorpse* pMonsterCorpse) ;
	bool isDefenderOfGuardShrine( PlayerCreature* pPC, MonsterCorpse* pShrine ) ;
	bool canPickupCastleSymbol( Race_t race, CastleSymbol* pCastleSymbol ) ;
	bool getMatchGuardShrinePosition(Item* pItem, ZoneItemPosition& zip) ;

	bool returnAllCastleSymbol( ZoneID_t castleZoneID ) ;
	bool returnCastleSymbol( ShrineID_t shrineID, bool bLock = true ) ;
	bool returnCastleSymbol( Zone* pZone, CastleSymbol* pCastleSymbol ) ;

	ZoneID_t getGuardShrineZoneID( ZoneID_t castleZoneID ) ;

	bool removeShrineShield( Zone* pZone );
	bool addShrineShield( Zone* pZone );
	bool addShrineShield_LOCKED( Zone* pZone );

	bool putCastleSymbol(PlayerCreature* pPC, Item* pItem, MonsterCorpse* pCorpse) ;

private:
	HashMapShrineSet		m_ShrineSets;
};

extern CastleShrineInfoManager* g_pCastleShrineInfoManager;

#endif // __SHRINE_INFO_MANAGER_H__
