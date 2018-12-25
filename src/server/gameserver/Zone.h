//////////////////////////////////////////////////////////////////////////////
// FileName 	: Zone.h
// Written By	: Reiot
// Description	:
//////////////////////////////////////////////////////////////////////////////

#ifndef __ZONE_H__
#define __ZONE_H__

#include "Types.h"
#include "Exception.h"
#include "Tile.h"
#include "Sector.h"
#include "ObjectRegistry.h"
#include "Mutex.h"
#include "Effect.h"
#include "Party.h"
#include "PCManager.h"
#include "Encrypter.h"
#include <queue>
#include <vector>
#include <hash_map>

//////////////////////////////////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////////////////////////////////
class ZoneGroup;
class NPC;
class NPCManager;
class MonsterManager;
class PCManager;
class Slayer;

class MasterLairManager;
class WarScheduler;
//class EventMonsterManager;

class EffectManager;
class NPCInfo;
class WeatherManager;
class Creature;
class Vampire;
class Monster;
class Item;
class VampirePortalItem;
class EffectVampirePortal;
class EffectScheduleManager;
class TradeManager;
class Motorcycle;
class LevelWarManager;
class DynamicZone;

//////////////////////////////////////////////////////////////////////////////
// ���� Ÿ��
//////////////////////////////////////////////////////////////////////////////
enum ZoneType 
{
	ZONE_NORMAL_FIELD,           // �Ϲ� �ʵ�
	ZONE_NORMAL_DUNGEON,         // �Ϲ� ����
	ZONE_SLAYER_GUILD,           // �����̾� ���
	ZONE_RESERVED_SLAYER_GUILD,  // ...
	ZONE_PC_VAMPIRE_LAIR,        // PC �����̾� ����
	ZONE_NPC_VAMPIRE_LAIR,       // NPC �����̾� ����
	ZONE_NPC_HOME,               // ...
	ZONE_NPC_SHOP,               // ...
	ZONE_RANDOM_MAP,             // -_-;
	ZONE_CASTLE,               	 // ��
};

//////////////////////////////////////////////////////////////////////////////
// ���� ���ٸ��
//////////////////////////////////////////////////////////////////////////////
enum ZoneAccessMode 
{
	PUBLIC = 0, 	// �ƹ��� ���� �� �ִ� ���̴�.
	PRIVATE			// ������ ������� ���� �� �ִ� ���̴�.(�����,���� ��)
};

//////////////////////////////////////////////////////////////////////////////
// Move type for darkness
//////////////////////////////////////////////////////////////////////////////
#define INTO_DARKNESS   0
#define OUTER_DARKNESS  1
#define IN_DARKNESS     2
#define OUT_DARKNESS    3




//////////////////////////////////////////////////////////////////////////////
//
// class Zone;
//
//////////////////////////////////////////////////////////////////////////////

class Zone 
{
public: // constructor & destructor
	Zone(ZoneID_t zoneID) throw();
	Zone(ZoneID_t zoneID, ZoneCoord_t width, ZoneCoord_t height) throw();
	~Zone() throw();

public:
	void init() throw(Error);
	void load(bool bOutput=false) throw(Error);
	void reload(bool bOutput=false) throw(Error);
	void loadItem() throw(Error);
	void loadTriggeredPortal() throw(Error);
	void initSpriteCount() throw(Error);
	void save() throw(Error);

public:
	void pushPC(Creature* pCreature) throw(Error);
	void addPC(Creature* pCreature, ZoneCoord_t cx, ZoneCoord_t cy, Dir_t dir) throw(EmptyTileNotExistException, Error);
	void addPC(Creature* pCreature) throw(Error);
	void addCreature(Creature* pCreature, ZoneCoord_t cx, ZoneCoord_t cy, Dir_t dir) throw(EmptyTileNotExistException, Error);
	TPOINT addItem(Item* pItem, ZoneCoord_t cx, ZoneCoord_t cy, bool bAllowCreature=true, Turn_t decayTurn=0, ObjectID_t DropPetOID=0) throw(EmptyTileNotExistException, Error); 
	Item* getItem(ObjectID_t id) ;
	void addEffect(Effect* pEffect) throw(Error);	
	void deleteEffect(ObjectID_t id) throw(Error);	
	Effect* findEffect(Effect::EffectClass eid) throw(Error);	

	// by sigi. 2002.5.4
	void addEffect_LOCKING(Effect* pEffect) throw(Error);	
	void deleteEffect_LOCKING(ObjectID_t id) throw(Error);	

	void deletePC(Creature* pCreature) throw();//NoSuchElementException, Error);
	void deleteQueuePC(Creature* pCreature) throw(NoSuchElementException, Error);
	void deleteCreature(Creature* pCreature, ZoneCoord_t x, ZoneCoord_t y) throw(NoSuchElementException, Error);
	void deleteObject(Object* pObject, ZoneCoord_t x, ZoneCoord_t y) throw(NoSuchElementException, Error);
	void deleteItem(Object* pObject, ZoneCoord_t x, ZoneCoord_t y) throw(NoSuchElementException, Error);

	bool deleteNPC(Creature* pCreature) throw(Error);//NoSuchElementException, Error);
	void deleteNPCs(Race_t race) throw(Error);//NoSuchElementException, Error);
	void loadNPCs(Race_t race) throw(Error);//NoSuchElementException, Error);
	void sendNPCInfo() throw(Error);

	void loadEffect() throw(Error);


public:
	void movePC(Creature* pCreature, ZoneCoord_t nx, ZoneCoord_t ny, Dir_t dir) ;
	void moveCreature(Creature* pCreature, ZoneCoord_t nx, ZoneCoord_t ny, Dir_t dir) ;

	// ���Ͱ� �ֺ��� ��ĵ�Ѵ�.
	void monsterScan(Monster* pMonster, ZoneCoord_t x, ZoneCoord_t y, Dir_t dir) throw(Error);

	void broadcastPacket(Packet* pPacket, Creature* owner = NULL) ;
	void broadcastPacket(ZoneCoord_t x, ZoneCoord_t y, Packet* pPacket, Creature* owner = NULL, bool Plus = false, Range_t Range = 0) ;
	void broadcastPacket(ZoneCoord_t x, ZoneCoord_t y, Packet* pPacket, const list<Creature *> & creatureList, bool Plus = false, Range_t Range = 0) ;
	void broadcastDarkLightPacket(Packet* pPacket1, Packet* pPacket2, Creature* owner = NULL) ;
	void broadcastSayPacket(ZoneCoord_t x, ZoneCoord_t y, Packet* pPacket, Creature* owner = NULL, bool isVampire = false) ;
	void broadcastLevelWarBonusPacket(Packet* pPacket, Creature* owner = NULL) ;
	list<Creature*> broadcastSkillPacket(ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, Packet* pPacket, list<Creature*> creatureList, bool bConcernDarkness = true) ;

	//(x,y) Ÿ�� ���� �ִ� PC ���� �ֺ� ������ �о �����Ѵ�. pPacket �� NULL �� �ƴ϶��, ���ÿ� ��ε�ĳ��Ʈ�� ����Ѵ�.
	void scan(Creature* pPC, ZoneCoord_t x, ZoneCoord_t y, Packet* pPacket) ;
	
	// ���ڸ����� �þ߰� ����� ��� �ֺ� ������ �ٽ� �����ش�.
	void updateScan(Creature* pPC, Sight_t oldSight, Sight_t newSight) ;

	// �װ��� �� �� �ִ� �ѵ�(Player)�� list�� �����ش�.�
	list<Creature*>  getWatcherList(ZoneCoord_t, ZoneCoord_t, Creature* pTargetCreature = NULL) throw(Error);

	// ������ ���Ͱ� �ֺ��� PC �鿡�� GCAddXXX ��Ŷ�� ��ε�ĳ��Ʈ�ϸ鼭���ÿ� �׵��� �������� ������ �ν��ϵ��� �Ѵ�.
	void scanPC(Creature* pCreature) ;

	// ���ڸ����� hidden creature�� ���� update�� �ʿ��� ���.
	void updateHiddenScan(Creature* pCreature) ;
	
	// ���ڸ����� install mine�� ���� update�� �ʿ��� ���.
	void updateMineScan(Creature* pCreature) ;
	
    // ���ڸ����� invisible creature�� ���� update�� �ʿ��� ���.
	void updateInvisibleScan(Creature* pCreature) ;

    // ���ڸ����� hide,invisible creature�� ���� update�� �ʿ��� ���.
	void updateDetectScan(Creature* pCreature) ;

	// PC �� P(x1,y1)���� Q(x2,y2)�� �̵������� �ֺ��� ��ε�ĳ��Ʈ�Ѵ�.
	void movePCBroadcast(Creature* pPC, ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, bool bSendMove = true, bool bKnockback=false) ;

	// !PC �� P(x1,y1)���� Q(x2,y2)�� �̵������� �ֺ��� ��ε�ĳ��Ʈ�Ѵ�.
	void moveCreatureBroadcast(Creature* pCreature, ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, bool bSendMove = true, bool bKnockback=false) ;
	
	// PC �� P(x1,y1)���� Q(x2,y2)�� �̵������� �ֺ��� ��ε�ĳ��Ʈ�Ѵ�.
	bool moveFastPC(Creature* pPC, ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, SkillType_t skillType) ;
	bool moveFastMonster(Monster* pMonster, ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, SkillType_t skillType) ;

	// ����� �� ���� �������밡 �Ǿ��ٰ� ���Ҵٰ� �Ѵ�. ���� ���������� �ƴϰ� ����ų� ���󺹱���Ų��.
	void releaseSafeZone() throw();
	void resetSafeZone() throw();

	// ������Ʈ ���
	void registerObject( Object* pObject ) throw() { getObjectRegistry().registerObject( pObject ); }

public:
	void heartbeat() throw(Error);

	// �̸�, ũ��ó Ŭ����, OID ���� �̿��ؼ� ���� �����ϴ� ũ���� ��ü�� ����
	Creature* getCreature(const string& Name) ;//NoSuchElementException, Error);
	Creature* getCreature(ObjectID_t objectID) ;//NoSuchElementException, Error);
	Creature* getCreature(Creature::CreatureClass creatureClass, ObjectID_t objectID) ;


public:
	void lock() throw(Error) { m_Mutex.lock(); }
	void unlock() throw(Error) { m_Mutex.unlock(); }

	// get debug string
	string toString() ;

public:
	ObjectRegistry & getObjectRegistry() throw() { return m_ObjectRegistry; }

	const Tile & getTile(ZoneCoord_t x, ZoneCoord_t y) ;
	Tile & getTile(ZoneCoord_t x, ZoneCoord_t y) throw(OutOfBoundException);

	Sector* getSector(ZoneCoord_t x, ZoneCoord_t y) throw(OutOfBoundException);

	ZoneID_t getZoneID()  { return m_ZoneID; }
	void setZoneID(ZoneID_t zoneID) throw() { m_ZoneID = zoneID; }
	
	ZoneGroup* getZoneGroup()  { return m_pZoneGroup; }
	void setZoneGroup(ZoneGroup* pZoneGroup) throw() { m_pZoneGroup = pZoneGroup; }

	ZoneType getZoneType()  { return m_ZoneType; }
	void setZoneType(ZoneType zoneType) throw() { m_ZoneType = zoneType; }

	ZoneLevel_t getZoneLevel()  { return m_ZoneLevel; }
	void setZoneLevel(ZoneLevel_t zoneLevel) throw() { m_ZoneLevel = zoneLevel; }
    ZoneLevel_t getZoneLevel(ZoneCoord_t x, ZoneCoord_t y) ;

	ZoneAccessMode getZoneAccessMode()  { return m_ZoneAccessMode; }
	void setZoneAccessMode(ZoneAccessMode zoneAccessMode) throw() { m_ZoneAccessMode = zoneAccessMode; }

	string getOwnerID()  { return m_OwnerID; }
	void setOwnerID(const string & ownerID) throw() { m_OwnerID = ownerID; }

	DarkLevel_t getDarkLevel()  { return m_DarkLevel; }
	void setDarkLevel(DarkLevel_t darkLevel) throw() { m_DarkLevel = darkLevel; }

	LightLevel_t getLightLevel()  { return m_LightLevel; }
	void setLightLevel(LightLevel_t lightLevel) throw() { m_LightLevel = lightLevel; }

	const WeatherManager* getWeatherManager()  { return m_pWeatherManager; }

	uint getNPCCount()  { return m_NPCCount; }
	void setNPCCount(uint n) throw(Error) { Assert(n <= maxNPCPerZone); m_NPCCount = n; }

	NPCType_t getNPCType(uint n)  { Assert(n < maxNPCPerZone); return m_NPCTypes[n]; }
	void setNPCType(uint n, NPCType_t npcType) throw() { Assert(n < maxNPCPerZone); m_NPCTypes[n] = npcType; }

	uint getMonsterCount()  { return m_MonsterCount; }
	void setMonsterCount(uint n) throw(Error) { Assert(n <= maxMonsterPerZone); m_MonsterCount = n; }

	MonsterType_t getMonsterType(uint n)  { Assert(n < maxMonsterPerZone); return m_MonsterTypes[n]; }
	void setMonsterType(uint n, MonsterType_t npcType) throw() { Assert(n < maxMonsterPerZone); m_MonsterTypes[n] = npcType; }

	ZoneCoord_t getWidth()  { return m_Width; }
	ZoneCoord_t getHeight()  { return m_Height; }

	uint getTimeband() const { return m_Timeband; }
	void setTimeband( uint timeband ) { m_Timeband = timeband; }

	bool isTimeStop() { return m_bTimeStop; }
	void stopTime() { m_bTimeStop = true; }
	void resumeTime() { m_bTimeStop = false; }

	void resetDarkLightInfo() throw();

	// ABCD add item to item hash map
	void addToItemList(Item* pItem) throw();
	void deleteFromItemList(ObjectID_t id) throw();
	hash_map<ObjectID_t, Item*> getItems(void) throw() { return m_Items; }

	EffectManager* getEffectManager() throw() { return m_pEffectManager; }
	EffectManager* getVampirePortalManager() throw() { return m_pVampirePortalManager; }
	EffectScheduleManager* getEffectScheduleManager(void) throw() { return m_pEffectScheduleManager; }

	VSRect* getOuterRect(void) { return &m_OuterRect; }
	VSRect* getInnerRect(void) { return &m_InnerRect; }
	VSRect* getCoreRect(void) { return &m_CoreRect; }

	list<NPCInfo*>* getNPCInfos(void);
	void addNPCInfo(NPCInfo* pInfo);
	bool removeNPCInfo(NPC* pNPC);

	// �� ��ü�� NPC���� MarketCondition�� �����Ѵ�. default(100, 25)
	//void setNPCMarketCondition(MarketCond_t NPCSell, MarketCond_t NPCBuy) throw (Error);

	void addVampirePortal(ZoneCoord_t cx, ZoneCoord_t cy, Vampire* pVampire, const ZONE_COORD& ZoneCoord) throw();
	void deleteMotorcycle(ZoneCoord_t cx, ZoneCoord_t cy, Motorcycle* pMotorcycle) throw(Error);

	void addItemDelayed(Item* pItem, ZoneCoord_t cx, ZoneCoord_t cy, bool bAllowCreature=true) throw(Error);
	void addItemToCorpseDelayed(Item* pItem, ObjectID_t corpseObjectID) throw(Error);
	void deleteItemDelayed(Object* pObject, ZoneCoord_t x, ZoneCoord_t y) throw(Error);
	void transportItem(ZoneCoord_t x, ZoneCoord_t y, Item* pItem, Zone* pZone, ZoneCoord_t cx, ZoneCoord_t y) throw(Error);
	void transportItemToCorpse(Item* pItem, Zone* pTargetZone, ObjectID_t corpseObjectID) throw(Error);

	LocalPartyManager* getLocalPartyManager(void) const { return m_pLocalPartyManager; }
	PartyInviteInfoManager* getPartyInviteInfoManager(void) const { return m_pPartyInviteInfoManager; }
	
	TradeManager* getTradeManager(void) const { return m_pTradeManager; }


	// pPC�� pMonster�� ���� Monster�� � packet���� add�Ǵ°�?
	// pPC�� NULL�� ��� �� ���̴� ���¶�� �����Ѵ�.
	Packet*	createMonsterAddPacket(Monster* pMonster, Creature* pPC) ;

	// �� ���� ��ǥ
	const BPOINT& getRandomMonsterRegenPosition() const;
	const BPOINT& getRandomEmptyTilePosition() const;

	MonsterManager* getMonsterManager(void) const { return m_pMonsterManager; }
	MasterLairManager* getMasterLairManager(void) const { return m_pMasterLairManager; }
	WarScheduler* getWarScheduler(void) const { return m_pWarScheduler; }
	LevelWarManager* getLevelWarManager() const { return m_pLevelWarManager; }

	void	killAllMonsters() throw (Error);
	void	killAllMonsters_UNLOCK() throw (Error);

	void	killAllPCs() throw(Error);

	const PCManager*  getPCManager() const		{ return m_pPCManager; }             // PC Manager 
	WORD getPCCount(void)  { return m_pPCManager->getSize(); }

#ifdef __USE_ENCRYPTER__
	// get zone's encrypt code
	uchar getEncryptCode() const { return m_EncryptCode; }
#endif

public :
	// ����ȭ
	bool isPayPlay()  { return m_bPayPlay; }
    void setPayPlay(bool bPayPlay=true) throw() { m_bPayPlay = bPayPlay; }

	bool isPremiumZone()  { return m_bPremiumZone; }
	void setPremiumZone(bool bPremiumZone=true) throw() { m_bPremiumZone = bPremiumZone; }

	bool isPKZone()  { return m_bPKZone; }
	void setPKZone(bool bPKZone=true) throw() { m_bPKZone = bPKZone; }

	bool isNoPortalZone()  { return m_bNoPortalZone; }
	void setNoPortalZone(bool bNoPortalZone=true) throw() { m_bNoPortalZone = bNoPortalZone; }

	bool isMasterLair()  { return m_bMasterLair; }
	void setMasterLair(bool bMasterLair=true) throw() { m_bMasterLair = bMasterLair; }

	bool isCastle()  { return m_bCastle; }
	void setCastle(bool bCastle=true) throw() { m_bCastle = bCastle; }

	bool isHolyLand()  { return m_bHolyLand; }
	void setHolyLand(bool bHolyLand=true) throw() { m_bHolyLand = bHolyLand; }

	bool isCastleZone()  { return m_bCastleZone; }
	void setCastleZone(bool bCastleZone=true) throw() { m_bCastleZone = bCastleZone; }

	// Relic�����븦 ���� �ֳ�?
	bool hasRelicTable()  { return m_bHasRelicTable; }
    void setRelicTable(bool bHasRelicTable=true) throw() { m_bHasRelicTable = bHasRelicTable; }

	bool addRelicItem(int relicIndex) throw(Error); 
	bool deleteRelicItem() throw(Error); 

	// Holy Land Race Bonus ��ȭ�� ���� �÷��̾� refresh
	void setRefreshHolyLandPlayer( bool bRefresh ) { m_pPCManager->setRefreshHolyLandPlayer( bRefresh ); }
//	void setRefreshLevelWarBonusZonePlayer( bool bRefresh ) { m_pPCManager->setRefreshLevelWarBonusZonePlayer( bRefresh ); }

	void    remainRaceWarPlayers() throw(Error);

	void    remainPayPlayer() throw(Error);

	bool isLevelWarZone() const;

public :
	void   initLoadValue();
	DWORD  getLoadValue() const;

public:
	bool			isDynamicZone() const { return m_pDynamicZone != NULL; }
	void			setDynamicZone( DynamicZone* pDynamicZone ) { m_pDynamicZone = pDynamicZone; }
	DynamicZone*	getDynamicZone() const { return m_pDynamicZone; }

////////////////////////////////////////////////////////////
// member data
////////////////////////////////////////////////////////////
private:
	// ���� �⺻ ���� ����
	ZoneID_t       m_ZoneID;           // zone id
	ZoneGroup*     m_pZoneGroup;       // parent zone group
	ZoneType       m_ZoneType;         // �� Ÿ��(�� Ÿ���� �ٲ�� DB�� ����Ǿ�� �Ѵ�.)
	ZoneLevel_t    m_ZoneLevel;        // ���� ����.
	ZoneAccessMode m_ZoneAccessMode;   // ���� ���� ���� ��� { PUBLIC | PRIVATE }
	string         m_OwnerID;          // �� ������ ���̵�(�����̾� ��� ���̵� Ȥ�� �����̾� ������ ���̵�)
	DarkLevel_t    m_DarkLevel;        // ���� ��ӱ�
	LightLevel_t   m_LightLevel;       // ���� ���� ũ��
	ZoneCoord_t    m_Width;            // ���� ���� ũ��
	ZoneCoord_t    m_Height;           // ���� ���� ũ��
	Tile**         m_pTiles;           // Ÿ���� ������ �迭
	ZoneLevel_t**  m_ppLevel;          // �� ������ ������ �迭
	Sector**       m_pSectors;          // ������ ������ �迭
	int            m_SectorWidth;      // ������ ũ��
	int            m_SectorHeight;     // ������ ũ��
	
	// ���� �Ŵ�����
	PCManager*             m_pPCManager;             // PC Manager 
	NPCManager*            m_pNPCManager;            // NPC Manager
	MonsterManager*        m_pMonsterManager;        // Monster Manager

//	EventMonsterManager*   m_pEventMonsterManager;

	EffectManager*         m_pEffectManager;         // effect manager
	EffectManager*         m_pVampirePortalManager;  // effect manager
	EffectManager*         m_pLockedEffectManager;   // effect manager
	EffectScheduleManager* m_pEffectScheduleManager;
	list<NPCInfo*>         m_NPCInfos;               // npc infos
	WeatherManager*        m_pWeatherManager;        // ���� ����

	// ���� �����ϴ� NPC ��������Ʈ Ÿ���� ����Ʈ
	BYTE m_NPCCount;
	NPCType_t m_NPCTypes[ maxNPCPerZone ];

	// ���� �����ϴ� ���� ��������Ʈ Ÿ���� ����Ʈ
	BYTE m_MonsterCount;
	MonsterType_t m_MonsterTypes[ maxMonsterPerZone ];

	// object registery
	ObjectRegistry m_ObjectRegistry;

	// ���� ���� �� PC���� ť
	queue< Creature* > m_PCQueue;
	list< Creature* > m_PCListQueue;

	// zone�ٴڿ� ������ item hashmap
	hash_map<ObjectID_t, Item*> m_Items;
	
	// Monster AI�� ���� ���� ������ �������� ���� �簢����...
	VSRect m_OuterRect;
	VSRect m_InnerRect;
	VSRect m_CoreRect;

	LocalPartyManager* m_pLocalPartyManager;
	PartyInviteInfoManager* m_pPartyInviteInfoManager;
	TradeManager* m_pTradeManager;
	
	// �� ���� ��ǥ�� ���� ����.
	vector<BPOINT> m_MonsterRegenPositions;
	vector<BPOINT> m_EmptyTilePositions;

	// mutex
	mutable Mutex m_Mutex;
	mutable Mutex m_MutexEffect;

	// ����ȭ ����
	bool m_bPayPlay;
	bool m_bPremiumZone;

	// ��Ÿ ����
	bool m_bPKZone;
	bool m_bNoPortalZone;
	bool m_bMasterLair;
	bool m_bCastle;
	bool m_bHolyLand;
	bool m_bCastleZone;

	// ���� ��?
	bool m_bHasRelicTable;

	// Relic Table ���� ����
	ObjectID_t m_RelicTableOID;
	ZoneCoord_t m_RelicTableX;
	ZoneCoord_t m_RelicTableY;

	Timeval	m_LoadValueStartTime;
	DWORD  m_LoadValue;

	// ������ ����. by sigi.2002.9.2
	MasterLairManager* 	m_pMasterLairManager;

	// ���� ���� by sigi. 2003.1.24
	WarScheduler* 		m_pWarScheduler;

	LevelWarManager*	m_pLevelWarManager;

	// by sigi. for debugging. 2002.12.23
	int m_LastItemClass;

	// Zone Timeband
	uint m_Timeband;

	bool m_bTimeStop;

	Timeval m_UpdateTimebandTime;

#ifdef __USE_ENCRYPTER__
	// zone's encrypt code
	uchar	m_EncryptCode;
#endif

	DynamicZone*	m_pDynamicZone;		// �δ� ����
};	

#endif
