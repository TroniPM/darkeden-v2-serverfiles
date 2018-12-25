//////////////////////////////////////////////////////////////////////////////
// Filename    : PlayerCreature.h
// Written by  : excel96
// Description : 
// Slayer �� Vampire Ŭ������ �������̽� �� ����Ǵ� �κ��� ��Ƴ��� 
// Ŭ������. abstract Ŭ�����̹Ƿ�, �ٷ� �����ϸ� �� �� ���̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __PLAYER_CREATURE_H__
#define __PLAYER_CREATURE_H__

#include "Creature.h"
#include "ObjectRegistry.h"
#include "InventorySlot.h"
#include "Garbage.h"
#include "RankBonus.h"
#include "ExpFwd.h"
//#include "RankExpTable.h"
//#include "ItemNameInfo.h"
//#include "quest/Squest/QuestManager.h"
#include "Gpackets/GCMonsterKillQuestInfo.h"
#include "OptionInfo.h"

#include <hash_map>
#include <bitset>
#include <slist>
#include <vector>

static const GuildID_t SlayerCommon	=99;
static const GuildID_t VampireCommon=0;
static const GuildID_t OustersCommon=66;


//////////////////////////////////////////////////////////////////////////////
// class PlayerCreature
//////////////////////////////////////////////////////////////////////////////

class Inventory;
class InventorySlot;
class Stash;
class Player;
class FlagSet;
class QuestManager;
class TimeLimitItemManager;
class GoodsInventory;
class PetInfo;
class PetItem;
class Pet;
class SMSAddressBook;
class NicknameBook;
class NicknameInfo;
class GQuestManager;
class BloodBibleSignInfo;
class Store;
//class GCMonsterKillQuestInfo;
//struct GCMonsterKillQuestInfo::QuestInfo;

typedef hash_map<DWORD, RankBonus*> HashMapRankBonus;
typedef HashMapRankBonus::iterator HashMapRankBonusItor;
typedef HashMapRankBonus::const_iterator HashMapRankBonusConstItor;


class PlayerCreature : public Creature
{
////////////////////////////////////////////////////////////
// ������ �� �Ҹ���
////////////////////////////////////////////////////////////
public:
	PlayerCreature(ObjectID_t objectID = 0, Player* pPlayer = NULL) throw();
	virtual ~PlayerCreature() throw();

	virtual bool load() throw (InvalidProtocolException, Error);
	virtual void tinysave(const string & field)  = 0;
//	virtual void tinysave(const char* field)  = 0;

////////////////////////////////////////////////////////////
// OID ��� ���� �޽��
////////////////////////////////////////////////////////////
public:
	virtual void registerItem(Item* pItem, ObjectRegistry& OR) throw();
	virtual void registerInventory(ObjectRegistry& OR) throw();
	virtual void registerInitInventory(ObjectRegistry& OR) throw();
	virtual void registerStash(void) throw();

	virtual void registerGoodsInventory(ObjectRegistry& OR) throw();

//////////////////////////////////////////////////////////////
// �ð����� ������ ���� �Լ�
//////////////////////////////////////////////////////////////
public:
	bool wasteIfTimeLimitExpired(Item* pItem);
	virtual void checkItemTimeLimit() throw (Error) = 0;
	void sendTimeLimitItemInfo();
	void addTimeLimitItem(Item* pItem, DWORD time);
	void sellItem( Item* pItem );
	void deleteItemByMorph( Item* pItem );
	void updateItemTimeLimit( Item* pItem, DWORD time );
	virtual void updateEventItemTime( DWORD time ) throw(Error) = 0;
	void loadTimeLimitItem();

//////////////////////////////////////////////////////////////
// ���� ��ǰ ������ ���� �Լ�
//////////////////////////////////////////////////////////////
public:
	void loadGoods();

//////////////////////////////////////////////////////////////
// ����Ʈ �Ŵ��� ���� �Լ�
//////////////////////////////////////////////////////////////
public:
	QuestManager*	getQuestManager() const { return m_pQuestManager; }
	void			sendCurrentQuestInfo() ;

	int findEffection(int EffectClass) ;

	virtual	int		getQuestLevel() const = 0;
	virtual void	whenQuestLevelUpgrade();

////////////////////////////////////////////////////////////
// �κ��丮 ���� �޽��
////////////////////////////////////////////////////////////
public:
	virtual Inventory* getInventory()  { return m_pInventory; }
	virtual void setInventory(Inventory* pInventory) throw() { m_pInventory = pInventory; }

	virtual InventorySlot* getExtraInventorySlot() throw() { return m_pExtraInventorySlot; }
	virtual Item* getExtraInventorySlotItem() throw(Error) { return m_pExtraInventorySlot->getItem(); }
	virtual void deleteItemFromExtraInventorySlot() throw(Error) { m_pExtraInventorySlot->deleteItem(); }
	virtual void addItemToExtraInventorySlot(Item* pItem) throw(Error) { m_pExtraInventorySlot->addItem(pItem); }

	// 2003.04.04. by Sequoia
	virtual void loadItem() throw (InvalidProtocolException, Error);

	virtual GoodsInventory* getGoodsInventory()  { return m_pGoodsInventory; }

////////////////////////////////////////////////////////////
// ������ ���� �޽��
////////////////////////////////////////////////////////////
public:
	virtual Stash* getStash(void)  { return m_pStash; }
	virtual void setStash(Stash* pStash) throw() { m_pStash = pStash; }

	virtual BYTE getStashNum(void)  { return m_StashNum; }
	virtual void setStashNum(BYTE num) throw() { m_StashNum = num; }
	virtual void setStashNumEx(BYTE num) throw();

	virtual Gold_t getStashGold(void)  { return m_StashGold; }
	virtual void setStashGold(Gold_t gold) throw() { m_StashGold = gold; }
	virtual void setStashGoldEx(Gold_t gold) throw();
	virtual void increaseStashGoldEx(Gold_t gold) throw();
	virtual void decreaseStashGoldEx(Gold_t gold) throw();
	virtual bool checkStashGoldIntegrity() = 0;

	virtual bool getStashStatus(void)  { return m_bStashStatus; }
	virtual void setStashStatus(bool s) throw() { m_bStashStatus = s; }

	virtual void deleteStash(void) throw();


////////////////////////////////////////////////////////////
// ������ ���� �޽��
////////////////////////////////////////////////////////////
public:
	void addItemToGarbage(Item* pItem) { m_Garbage.addItem(pItem); }
	void addItemToGarbageEx(Item* pItem) { m_Garbage.addItemEx(pItem, getName()); }
	Item* popItemFromGarbage(void) { return m_Garbage.popItem(); }
	void saveGarbage(void) { m_Garbage.save(getName()); }
	int getGarbageSize(void) { return m_Garbage.size(); }

////////////////////////////////////////////////////////////
// ������ �˻� �Լ�
////////////////////////////////////////////////////////////
public:
	virtual Item* findItemOID(ObjectID_t id) throw() = 0;
	virtual Item* findItemOID(ObjectID_t id, int& storage, int& x, int& y) throw() = 0;

	virtual Item* findItemIID(ItemID_t id) throw() = 0;
	virtual Item* findItemIID(ItemID_t id, int& storage, int& x, int& y) throw() = 0;

	virtual Item* findBeltOID(ObjectID_t id) throw() = 0;
	virtual Item* findBeltOID(ObjectID_t id, int& storage, int& x, int& y) throw() = 0;

	virtual Item* findBeltIID(ItemID_t id) throw() = 0;
	virtual Item* findBeltIID(ItemID_t id, int& storage, int& x, int& y) throw() = 0;

	virtual Item* findSubInventoryID(ItemID_t id) throw() = 0;
	virtual Item* findSubInventoryID(ItemID_t id, int& storage, int& x, int& y) throw() = 0;


////////////////////////////////////////////////////////////
// �÷��� �� ���� �Լ�
////////////////////////////////////////////////////////////
public:
	FlagSet* getFlagSet(void)  { return m_pFlagSet; }
	void setFlagSet(FlagSet* pSet) throw() { m_pFlagSet = pSet; } 
	void deleteFlagSet(void) throw();


////////////////////////////////////////////////////////////
// ��Ÿ �Լ�
////////////////////////////////////////////////////////////
public:
	virtual Fame_t getFame()  = 0;
	virtual void setFame(Fame_t fame) throw() = 0;

	virtual Gold_t getGold()  = 0;
	virtual void setGold(Gold_t gold) throw() = 0;
	virtual void setGoldEx(Gold_t gold) throw() = 0;
	virtual void   increaseGoldEx(Gold_t gold) throw() = 0;
    virtual void   decreaseGoldEx(Gold_t gold) throw() = 0;
	virtual bool checkGoldIntegrity() = 0;
	bool checkDBGold( Gold_t gold )
	{
		Gold_t temp = getGold();
		setGold(gold);
		bool ret = checkGoldIntegrity();
		setGold(temp);
		return ret;
	}

	virtual Fame_t getKillPoint()  = 0;
	virtual void setKillPoint(Fame_t fame) throw() = 0;

	virtual Color_t getShopColor()  = 0;
	virtual void setShopColor(Color_t ShopColor) throw() = 0;

	virtual Sex	getSex()  = 0;

	virtual ZoneID_t getResurrectZoneID(void)  = 0;
	virtual void setResurrectZoneID(ZoneID_t id) throw() = 0;
	virtual void setResurrectZoneIDEx(ZoneID_t id) throw() = 0;

	//virtual Race_t getRace() const = 0; - Creature�� �÷ȴ�.
	virtual GuildID_t getCommonGuildID() const = 0;

	virtual IP_t getIP(void) const = 0;


////////////////////////////////////////////////////////////
// ���� �ý��� ����
////////////////////////////////////////////////////////////
	// enemy specific methods
	void addEnemy(const string& Name);
	void deleteEnemy(const string& Name) throw(NoSuchElementException, Error);

	// �� Ư�� ����ڰ� �̹� ������ �Ͽ��°�?
	bool hasEnemy(const string& Name) ;
	uint getMaxEnemies() ;

	list<string>& getEnemies(void) throw() { return m_Enemies;}

	bool isPK() throw() { return m_isPK; }

	void setPK(bool isPK) throw() { m_isPK = isPK; }

	void setGuildID( GuildID_t GuildID ) throw() { m_GuildID = GuildID; }
	GuildID_t getGuildID()  { return m_GuildID; }

	string getGuildName() ;
	GuildMemberRank_t getGuildMemberRank() ;

	Rank_t  	getRank() ;
	RankExp_t   getRankExp() ;
	RankExp_t   getRankGoalExp() ;

//	virtual Rank_t getRank()  = 0;
	void increaseRankExp(RankExp_t Point);

	WORD getRankExpSaveCount(void) const { return m_RankExpSaveCount; }
	void setRankExpSaveCount(WORD count) { m_RankExpSaveCount = count; }

	virtual Alignment_t getAlignment() =0;
	virtual void setAlignment(Alignment_t Alignment) throw()=0;

////////////////////////////////////////////////////////////
// Rank Bonus ����
////////////////////////////////////////////////////////////
	void loadRankBonus() throw();
	bool hasRankBonus( RankBonus::RankBonusType type ) throw() { return m_RankBonusFlag.test(type); }
	RankBonus* getRankBonus( RankBonus::RankBonusType type ) ;
	RankBonus* getRankBonusByRank( Rank_t rank ) ;
	bool learnRankBonus( DWORD type ) throw();
	void clearRankBonus() throw();
	void clearRankBonus( Rank_t rank ) throw();
	HashMapRankBonus& getRankBonuses() { return m_RankBonuses; }

	void sendRankBonusInfo() throw();

protected:
	void addRankBonus( RankBonus* rankBonus ) throw();

public :
	// by sigi. 2002.11.19
	bool isBillingPlayAvaiable();
	virtual bool isPayPlayAvaiable();
	virtual bool canPlayFree();

public:
	Item*	getQuestItem() const { return m_pQuestItem; }
	void	setQuestItem( Item* pItem ) { m_pQuestItem = pItem; }

public :
	// by sigi. 2002.12.3
/*	void	loadQuest();
	bool 	hasQuest() const 	{ return m_pQuestManager!=NULL && !m_pQuestManager->isEmpty(); }
	bool 	addQuest(Quest* pQuest);
	bool 	checkEvent(QuestEvent* pQuest);
	Quest* 	removeCompleteQuest();
	void 	removeAllQuest() throw (Error)	{ if (m_pQuestManager!=NULL) m_pQuestManager->release(); }*/

	virtual void initAllStatAndSend() = 0;
	virtual void initAllStat(int numPartyMember) throw() = 0;

	virtual void computeStatOffset(void) throw() = 0;
	virtual void computeItemStat(Item* pItem) throw() = 0;
	virtual void computeOptionStat(Item* pItem) throw() = 0;
	virtual void computeOptionStat(OptionType_t optionType) throw() = 0;
	virtual void computeOptionClassStat( OptionClass OClass, int PlusPoint ) = 0;

	void heartbeat(const Timeval& currentTime) throw();

	virtual bool canSee( Object* pObject ) const;

////////////////////////////////////////////////////////////
// ��� ������
////////////////////////////////////////////////////////////
protected:
	Inventory*     m_pInventory;          // �κ��丮 ������
	InventorySlot* m_pExtraInventorySlot; // ���콺 ������

	GoodsInventory* m_pGoodsInventory;    // ���� ������ �κ��丮

	Stash*         m_pStash;              // ������ ������
	BYTE           m_StashNum;            // �������� ����
	Gold_t         m_StashGold;           // ������ ���� �� �׼�
	bool           m_bStashStatus;        // ������ ������ OID ��� ����

	Garbage        m_Garbage;             // ������...

	FlagSet*       m_pFlagSet;            // �÷��� ����

	// ���� ������ ������� �̸��� �����Ѵ�.
	// ObjectID�� ������ ���� ������, �׾ �ٽ� ���� ��������� �������� �ʱ� ������ �̸����� �������ش�.
    list<string> m_Enemies;

	// PK�� ���ߴ��� �ƴϳĸ� �����Ѵ�.
	bool m_isPK;

	// GuildID
	GuildID_t		m_GuildID;

	// Rank Bonus map
	HashMapRankBonus m_RankBonuses;
	bitset<RankBonus::RANK_BONUS_MAX> m_RankBonusFlag;

	Rank*	m_pRank;
	WORD	m_RankExpSaveCount;

//	QuestManager*	m_pQuestManager;
	QuestManager*			m_pQuestManager;
	TimeLimitItemManager*	m_pTimeLimitItemManager;

	Item*					m_pQuestItem;
	vector<Item*>			m_PetStash;		// pet ������

public:
	/////////////////////////////////////////////////////////
	// pet �����Ͽ� ���õ� method
	/////////////////////////////////////////////////////////
	Item*				getPetStashItem(int idx);	
	void				addPetStashItem(int idx, Item* pPetItem);

	/////////////////////////////////////////////////////////
	// BloodBible ���� ���ʽ� ��ġ��
	/////////////////////////////////////////////////////////
public:
	int					getConsumeMPRatio() const { return m_ConsumeMPRatio; }
	void				setConsumeMPRatio( int ratio ) { m_ConsumeMPRatio = ratio; }

	int					getGamblePriceRatio() const { return m_GamblePriceRatio; }
	void				setGamblePriceRatio( int ratio ) { m_GamblePriceRatio = ratio; }

	int					getPotionPriceRatio() const { return m_PotionPriceRatio; }
	void				setPotionPriceRatio( int ratio ) { m_PotionPriceRatio = ratio; }

	Damage_t			getMagicBonusDamage() const { return m_MagicBonusDamage; }
	void				setMagicBonusDamage( Damage_t damage ) { m_MagicBonusDamage = damage; }

	Damage_t			getPhysicBonusDamage() const { return m_PhysicBonusDamage; }
	void				setPhysicBonusDamage( Damage_t damage ) { m_PhysicBonusDamage = damage; }

	Damage_t			getMagicDamageReduce() const { return m_MagicDamageReduce; }
	void				setMagicDamageReduce( Damage_t damage ) { m_MagicDamageReduce = damage; }

	Damage_t			getPhysicDamageReduce() const { return m_PhysicDamageReduce; }
	void				setPhysicDamageReduce( Damage_t damage ) { m_PhysicDamageReduce = damage; }

	int			getCriticalAddDamage() const { return m_CriticalAddDamage; }
	void				setCriticalAddDamage( int CriticalAddDamage) { m_CriticalAddDamage = CriticalAddDamage; }

	int			getHitAddGold() const { return m_HitAddGold; }
	void				setHitAddGold( int HitAddGold) { m_HitAddGold = HitAddGold; }

	int			getHitAddExp() const { return m_HitAddExp; }
	void				setHitAddExp( int HitAddExp) { m_HitAddExp = HitAddExp; }

	int			getHitSleep() const { return m_HitSleep; }
	void				setHitSleep( int HitSleep) { m_HitSleep = HitSleep; }

	int			getHitIce() const { return m_HitIce; }
	void				setHitIce( int HitIce) { m_HitIce = HitIce; }

	int			getHitAddAttack() const { return m_HitAddAttack; }
	void				setHitAddAttack( int HitAddAttack) { m_HitAddAttack = HitAddAttack; }

	int			getHitAddMagic() const { return m_HitAddMagic; }
	void				setHitAddMagic( int HitAddMagic) { m_HitAddMagic = HitAddMagic; }

	int			getYouReg() const { return m_YouReg; }
	void				setYouReg( int YouReg) { m_YouReg = YouReg; }

	int			getAddPlayerDamage() const { return m_AddPlayerDamage; }
	void				setAddPlayerDamage( int AddPlayerDamage) { m_AddPlayerDamage = AddPlayerDamage; }

	int			getMagicDefense() const { return m_MagicDefense; }
	void				setMagicDefense( int MagicDefense) { m_MagicDefense = MagicDefense; }

	int			getDropMagic() const { return m_DropMagic; }
	void				setDropMagic( int DropMagic) { m_DropMagic = DropMagic; }

/*	bool				isEmptyItemNameInfoList() { return m_ItemNameInfoList.empty(); }
	void				clearItemNameInfoList() { m_ItemNameInfoList.clear(); }
	const list<ItemNameInfo*>& getItemNameInfoList() const { return m_ItemNameInfoList; }
	void				addItemNameInfoList( ItemNameInfo* itemNameInfo ) { m_ItemNameInfoList.push_back(itemNameInfo); }
	bool				deleteItemNameInfoList( ObjectID_t objectID );
	string				getItemName( ObjectID_t objectID );*/

protected:
	int						m_ConsumeMPRatio;
	int						m_GamblePriceRatio;
	int						m_PotionPriceRatio;
	Damage_t				m_MagicBonusDamage;
	Damage_t				m_PhysicBonusDamage;

	Damage_t				m_MagicDamageReduce;
	Damage_t				m_PhysicDamageReduce;

	int			m_CriticalAddDamage;
	int			m_HitAddGold;
	int			m_HitAddExp;
	int			m_HitSleep;
	int			m_HitIce;
	int			m_HitAddAttack;
	int			m_HitAddMagic;
	int			m_YouReg;
	int			m_AddPlayerDamage;
	int			m_MagicDefense;
	int			m_DropMagic;

//	list<ItemNameInfo*> 	m_ItemNameInfoList;

// ������� ��÷ ���θ� ����ϱ� ���� ��¿ �� ���� ���� �߰��ؾ� �ɵ�

public:
	DWORD				getLottoRewardID() const { return m_LottoRewardID; }
	void				setLottoRewardID( DWORD lottoRewardID ) { m_LottoRewardID = lottoRewardID; }

	DWORD				getLottoQuestLevel() const { return m_LottoQuestLevel; }
	void 				setLottoQuestLevel( DWORD lottoQuestLevel ) { m_LottoQuestLevel = lottoQuestLevel; }

	bool				isLotto() const { return m_bLotto; }
	void				setLotto( bool lotto ) { m_bLotto = lotto; }

protected:
	DWORD				m_LottoRewardID;
	DWORD				m_LottoQuestLevel;
	bool				m_bLotto;

	//////////////////////////////////////////////
	// Default Option Set Info
	//////////////////////////////////////////////
public:
	void	addDefaultOptionSet( DefaultOptionSetType_t type ) throw();
	void	removeDefaultOptionSet( DefaultOptionSetType_t type ) throw();

protected:
	slist<DefaultOptionSetType_t>		m_DefaultOptionSet;

public:
	PetInfo*	getPetInfo() const;
	void		setPetInfo(PetInfo* pPetInfo);

	list<PetItem*>& getPetItems() { return m_PetItems; }
	const list<PetItem*>& getPetItems() const { return m_PetItems; }

	Pet*		getPet() const { return m_pPet; }

protected:
	PetInfo* m_pPetInfo;
	list<PetItem*> m_PetItems;
	Pet*	m_pPet;

	// 2�� �� ����Ʈ ���� 
public:
	SpriteType_t	getTargetMonsterSType() const { return m_TargetMonster; }
	virtual void	initPetQuestTarget() = 0;
	GCMonsterKillQuestInfo::QuestInfo*	getPetQuestInfo() const;

protected:
	SpriteType_t	m_TargetMonster;
	DWORD			m_TargetNum;
	DWORD			m_TimeLimit;

	// SMS ����
public:
	SMSAddressBook*	getAddressBook() const { return m_pSMSAddressBook; }
	uint			getSMSCharge() const { return m_SMSCharge; }
	void			setSMSCharge(uint charge) { m_SMSCharge = charge; }

	NicknameBook*	getNicknameBook() const { return m_pNicknameBook; }

	NicknameInfo*	getNickname() const { return m_pNickname; }
	void			setNickname(NicknameInfo* pNickname) { m_pNickname = pNickname; }
	
	GQuestManager*	getGQuestManager() const { return m_pGQuestManager; }

	BloodBibleSignInfo* getBloodBibleSign() const { return m_pBloodBibleSign; }

	virtual int		getBloodBibleSignOpenNum() const = 0;
	void			applyBloodBibleSign();

private:
	SMSAddressBook*	m_pSMSAddressBook;
	uint			m_SMSCharge;

	NicknameBook*	m_pNicknameBook;
	NicknameInfo*	m_pNickname;

	GQuestManager*	m_pGQuestManager;
	BloodBibleSignInfo*	m_pBloodBibleSign;

public:
	void			setBaseLuck(Luck_t luck) { m_BaseLuck = luck; }
	Luck_t			getBaseLuck() const { return m_BaseLuck; }
protected:
	Luck_t			m_BaseLuck;

public:
	Store*			getStore() const { return m_pStore; }

protected:
	Store*			m_pStore;

public:
    // get / set PowerPoint
    int getPowerPoint() const { return m_PowerPoint; }
    void setPowerPoint( int powerpoint ) { m_PowerPoint = powerpoint; }

protected:
    // �Ŀ�¯ ����Ʈ
    int             m_PowerPoint;

public:
	bool			isAdvanced() const { return m_bAdvanced; }
	
	Level_t			getAdvancementClassLevel() const;
	Exp_t			getAdvancementClassGoalExp() const;
	bool			increaseAdvancementClassExp(Exp_t exp, bool bApplyExpBount = true);

protected:
	bool				m_bAdvanced;
	AdvancementClass*	m_pAdvancementClass;
	WORD				m_AdvancementClassExpSaveCount;

public:
	Attr_t				getAdvancedAttrBonus() const { return m_AdvancedAttrBonus; }
	Attr_t				getAdvancedBonusToSTR()  const { return m_AdvancedSTR; }
	Attr_t				getAdvancedBonusToDEX()  const { return m_AdvancedDEX; }
	Attr_t				getAdvancedBonusToINT()  const { return m_AdvancedINT; }
	bool				putAdvancedBonusToSTR();
	bool				putAdvancedBonusToDEX();
	bool				putAdvancedBonusToINT();
	bool				deputAdvancedBonusToSTR();
	bool				deputAdvancedBonusToDEX();
	bool				deputAdvancedBonusToINT();

	virtual Bonus_t getBonus()  = 0;
	virtual void    setBonus(Bonus_t bonus) throw() = 0;

protected:
	Attr_t				m_AdvancedSTR;
	Attr_t				m_AdvancedDEX;
	Attr_t				m_AdvancedINT;
	Attr_t				m_AdvancedAttrBonus;

public:
	BYTE				getMasterEffectColor() const { return m_MasterEffectColor; }
	void				setMasterEffectColor(BYTE color) { m_MasterEffectColor = color; }
	// add by sonic 2006.10.29
	bool				canChangeMasterEffectColor();

protected:
	BYTE				m_MasterEffectColor;
};

#endif
