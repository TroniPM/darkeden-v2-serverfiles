//////////////////////////////////////////////////////////////////////////////
// Filename    : Ousters.h
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __OUSTERS_H__
#define __OUSTERS_H__

#include "PlayerCreature.h"
#include "Inventory.h"
#include "Zone.h"
#include "PCOustersInfo.h"
#include "PCOustersInfo2.h"
#include "PCOustersInfo3.h"
#include "InventoryInfo.h"
#include "GearInfo.h"
#include "ExtraInfo.h"
#include "OptionInfo.h"
#include "OustersSkillInfo.h"
#include "Mutex.h"
#include "ModifyInfo.h"
#include "CreatureUtil.h"
#include <hash_map>

#include "skill/OustersSkillSlot.h"

#include "Gpackets/GCModifyInformation.h"

class SkillInfo;

#define OUSTERS_MAX_LEVEL				150		//abcd
#define OUSTERS_MAX_RANK				50		// ��� max
#define OUSTERS_MAX_SUM					492
#define OUSTERS_MAX_ATTR				472
#define BONUS_POINTS_PER_LEVEL1			3		// �������� �־����� �ɷ�ġ point
#define BONUS_POINTS_PER_LEVEL2			2		// �������� �־����� �ɷ�ġ point
#define BONUS_POINTS_PER_LEVEL3			1		// �������� �־����� �ɷ�ġ point

////////////////////////////////////////////////////////////////////////////////
// ��� �԰� ���� �� ��� �԰� ���� ���� �ɷ�ġ�� 
// ������ �α� ���� ����(?) Ŭ����
////////////////////////////////////////////////////////////////////////////////

class OUSTERS_RECORD
{
public:
	Attr_t       pSTR[3];
	Attr_t       pDEX[3];
	Attr_t       pINT[3];
	Rank_t    	 Rank;
	HP_t         pHP[2];
	MP_t         pMP[2];
	Damage_t     pDamage[2];
	Defense_t    Defense;
	Protection_t Protection;
	ToHit_t      ToHit;
	Speed_t      AttackSpeed;
};




////////////////////////////////////////////////////////////////////////////////
//
// Class Ousters;
//
////////////////////////////////////////////////////////////////////////////////

class Ousters : public PlayerCreature 
{

////////////////////////////////////////////////////
// Ŭ���� ���� ��� ����
////////////////////////////////////////////////////
public:
	// ���� ����
	enum WearPart
	{ 
		WEAR_CIRCLET,
		WEAR_COAT,
		WEAR_LEFTHAND,
		WEAR_RIGHTHAND,
		WEAR_BOOTS,
		WEAR_ARMSBAND1,
		WEAR_ARMSBAND2,
		WEAR_RING1,
		WEAR_RING2,
		WEAR_NECKLACE1,
		WEAR_NECKLACE2,
		WEAR_NECKLACE3,
		WEAR_STONE1,
		WEAR_STONE2,
		WEAR_STONE3,
		WEAR_STONE4,
		WEAR_ZAP1,
		WEAR_ZAP2,
		WEAR_ZAP3,
		WEAR_ZAP4,
		WEAR_FASCIA,
		WEAR_MITTEN,
		WEAR_BRACELET_ZAP1,
		WEAR_BRACELET_ZAP2,
		WEAR_NECKLACE_ZAP1,
		WEAR_NECKLACE_ZAP2,
		WEAR_NECKLACE_ZAP3,
		WEAR_COAT_ZAP,
		WEAR_BOOTS_ZAP,
		WEAR_LEFTHAND_ZAP,
		WEAR_CIRCLET_ZAP,
		WEAR_ARMSBAND1_ZAP,
		WEAR_ARMSBAND2_ZAP,
		OUSTERS_WEAR_MAX 
	};

////////////////////////////////////////////////////
// ������/�Ҹ���
////////////////////////////////////////////////////
public:
	Ousters() throw();
	virtual ~Ousters() throw (Error);

////////////////////////////////////////////////////
// ���� Ŭ����(Creature) ��� �Լ�
////////////////////////////////////////////////////
public:
	virtual CreatureClass getCreatureClass()  { return CREATURE_CLASS_OUSTERS; }
	virtual string getCreatureClassString()  { return "CREATURE_CLASS_OUSTERS"; }

	virtual void registerObject() throw(Error);
	virtual void registerInitObject() throw(Error);

	virtual bool load() throw (InvalidProtocolException, Error);
	void loadItem( bool checkTimeLimit = false ) throw (InvalidProtocolException, Error);

	virtual void save() ;
	virtual void tinysave(const string & field) ;
//	virtual void tinysave(const char* field) ;
	void saveSkills(void) ;
	void saveGears(void) ;
	void saveExps(void) ;

	virtual void act(const Timeval& currentTime) throw(Error) {}

	virtual string toString() ;

	virtual Race_t getRace() const { return RACE_OUSTERS; }
	virtual GuildID_t getCommonGuildID() const { return OustersCommon; }

//////////////////////////////////////////////////////////////
// �ð����� ������ ���� �Լ�
//////////////////////////////////////////////////////////////
public:
	void checkItemTimeLimit() throw (Error);
	void updateEventItemTime( DWORD time ) throw(Error);

////////////////////////////////////////////////////
// ���� ���� �Լ�(Dead or Alive!)
////////////////////////////////////////////////////
public:
	bool isAlive()  { return m_HP[ATTR_CURRENT] != 0; }
	bool isDead()  { return m_HP[ATTR_CURRENT] == 0; }


////////////////////////////////////////////////////
// �Ѹ�� ���� �Լ�(�̸�, ����, ����, �Ӹ�, �Ǻ�)
////////////////////////////////////////////////////
public:
	const string& getName()  { return m_Name; }
	void setName(const string & name) throw() { m_Name = name; }

	BYTE getCompetence()  { return m_Competence; }
	void setCompetence(BYTE Competence) { m_Competence = Competence; }

	BYTE getCompetenceShape()  { return m_CompetenceShape; }
	void setCompetenceShape(BYTE CompetenceShape) { m_CompetenceShape = CompetenceShape; }

	Sex getSex()  { return m_Sex; }
	void setSex(Sex sex) throw() { m_Sex = sex; m_OustersInfo.setSex(sex); }
	void setSex(const string & sex) throw(InvalidProtocolException) 
	{
		if(sex == Sex2String[MALE])
			setSex(MALE);
		else if(sex == Sex2String[FEMALE])
			setSex(FEMALE);
		else throw InvalidProtocolException("invalid sex");
	}

	Color_t getHairColor()  { return m_HairColor; }
	void setHairColor(Color_t hairColor) throw() { m_HairColor = hairColor; }

	virtual BYTE getWingSylphType() const throw (){ return m_WingSylphType; }
	virtual void setWingSylphType(BYTE Type) throw (){ m_WingSylphType = Type; }

	virtual ItemType_t getWingItemType() const throw () { return m_WingItemType; }
	virtual void setWingItemType(ItemType_t ItemType) throw() { m_WingItemType = ItemType; }

	virtual Color_t getWingColor() const throw () { return m_WingColor; }
	virtual void	setWingColor(Color_t batColor) throw () { m_WingColor = batColor; }
	
	virtual Color_t getWingEffectColor() const throw () { return m_WingEffectColor; }
	virtual void	setWingEffectColor(Color_t batColor) throw () { m_WingEffectColor = batColor; }

	virtual Color_t getShopColor()  { return m_ShopColor; }
	virtual void setShopColor(Color_t ShopColor) throw() { m_ShopColor = ShopColor; }

////////////////////////////////////////////////////
// �ɷ�ġ ���� �Լ�(STR, DEX, INT)
////////////////////////////////////////////////////
public:

	Alignment_t getAlignment()  { return m_Alignment; }
	void setAlignment(Alignment_t Alignment) throw() { m_Alignment = Alignment; }
	void saveAlignment(Alignment_t alignment) throw();

	Attr_t getSTR(AttrType attrType = ATTR_CURRENT)  { return m_STR[attrType]; }
	void setSTR(Attr_t attr, AttrType attrType = ATTR_CURRENT) throw() { m_STR[attrType] = attr; }
	
	Attr_t getDEX(AttrType attrType = ATTR_CURRENT)  { return m_DEX[attrType]; }
	void setDEX(Attr_t attr, AttrType attrType = ATTR_CURRENT) throw() { m_DEX[attrType] = attr; }

	Attr_t getINT(AttrType attrType = ATTR_CURRENT)  { return m_INT[attrType]; }
	void setINT(Attr_t attr, AttrType attrType = ATTR_CURRENT) throw() { m_INT[attrType] = attr; }

////////////////////////////////////////////////////
// �ɷ�ġ ���� �Լ�(HP)
////////////////////////////////////////////////////
public:
	HP_t getHP(AttrType attrType = ATTR_CURRENT)  { return m_HP[attrType]; }
	void setHP(HP_t hp, AttrType attrType = ATTR_CURRENT) throw() { m_HP[attrType] = hp; }
	void setHP(HP_t current, HP_t max) throw() { m_HP[ATTR_CURRENT] = current; m_HP[ATTR_MAX] = max; }

	MP_t getMP(AttrType attrType = ATTR_CURRENT)  { return m_MP[attrType]; }
	void setMP(MP_t hp, AttrType attrType = ATTR_CURRENT) throw() { m_MP[attrType] = hp; }
	void setMP(MP_t current, MP_t max) throw() { m_MP[ATTR_CURRENT] = current; m_MP[ATTR_MAX] = max; }

////////////////////////////////////////////////////
// �ɷ�ġ ���� �Լ�(Damage, Protect, Defense, ToHit)
////////////////////////////////////////////////////
public:
	Damage_t     getDamage(AttrType attrType = ATTR_CURRENT)  { return m_Damage[attrType]; }
	Protection_t getProtection(void)  { return m_Protection[ATTR_CURRENT]; }
	Defense_t    getDefense(void)  { return m_Defense[ATTR_CURRENT]; }
	ToHit_t      getToHit(void)  { return m_ToHit[ATTR_CURRENT]; }
	Speed_t      getAttackSpeed(void)  { return m_AttackSpeed[ATTR_CURRENT]; }
	
////////////////////////////////////////////////////
// ����ġ ���� �Լ�
////////////////////////////////////////////////////
public:
//	Exp_t getExp()  { return m_Exp; }
//	void  setExp(Exp_t exp) throw() { m_Exp = exp; }

	Exp_t getGoalExp()  { return m_GoalExp; }
	void  setGoalExp(Exp_t GoalExp) throw() { m_GoalExp = GoalExp; }

//	Exp_t getExpOffset()  { return m_ExpOffset; }
//	void  setExpOffset(Exp_t expOffset) throw() { m_ExpOffset = expOffset; }

//	void setExp(Exp_t exp, Exp_t expOffset) throw() { m_Exp = exp; m_ExpOffset = expOffset; }

	Level_t getLevel()  { return m_Level; }
	void    setLevel(Level_t level) throw() { m_Level = level; }

	int		getQuestLevel() const { return getLevel(); }

	// ���. by sigi. 2002.8.30
/*	Rank_t  getRank()  { return m_Rank; }
	void    setRank(Rank_t rank) throw() { m_Rank = rank; }
	RankExp_t   getRankExp()  { return m_RankExp; }
	void    setRankExp(RankExp_t exp) throw() { m_RankExp = exp; }
	RankExp_t   getRankGoalExp()  { return m_RankGoalExp; }
	void    setRankGoalExp(RankExp_t RankGoalExp) throw() { m_RankGoalExp = RankGoalExp; }*/


	Bonus_t getBonus()  { return m_Bonus; }
	void    setBonus(Bonus_t bonus) throw() { m_Bonus = bonus; }

	SkillBonus_t	getSkillBonus()  { return m_SkillBonus; }
	void			setSkillBonus( SkillBonus_t skillBonus ) throw() { m_SkillBonus = skillBonus; }

	SkillBonus_t	getSumOfUsedSkillBonus() ;

////////////////////////////////////////////////////
// ��ų ���� �Լ�
////////////////////////////////////////////////////
public:
	void addSkill(SkillType_t SkillType) throw();
    void addSkill(OustersSkillSlot* pSkillSlot) throw();
	void removeSkill(SkillType_t SkillType) throw();
	void removeCastleSkill(SkillType_t SkillType) throw();
	void removeAllCastleSkill() throw();
	OustersSkillSlot* hasSkill(SkillType_t SkillType)  { return getSkill(SkillType); }
	OustersSkillSlot* getSkill(SkillType_t SkillType) ;


////////////////////////////////////////////////////
// ������ ��/Ż ���� �Լ�
////////////////////////////////////////////////////
public:
	bool  isWear(WearPart Part) throw() { return m_pWearItem[Part] != NULL ? true : false; }
	void  addWearItem(WearPart Part, Item* pItem) throw() { Assert(m_pWearItem[Part] != NULL); m_pWearItem[Part] = pItem; }
	void  deleteWearItem(WearPart Part) throw() { m_pWearItem[Part] = NULL; }
	Item* getWearItem(WearPart Part) throw() { return m_pWearItem[Part]; }

	void wearItem(WearPart Part) throw();
	void wearItem(WearPart Part, Item* pItem) throw();
	void takeOffItem(WearPart Part, bool bAddOnMouse, bool bSendModifyInfo) throw();
	bool    addShape(Item::ItemClass IClass, ItemType_t IType, Color_t color);
    bool    removeShape(Item::ItemClass IClass, bool bSendPacket=true);
	Color_t getItemShapeColor(Item* pItem, OptionInfo* pOptionInfo=NULL) const;


	void destroyGears() throw();

	bool isRealWearing(WearPart Part) ;
	bool isRealWearing(Item* pItem) ;
	bool isRealWearingEx(WearPart Part) const;
	DWORD sendRealWearingInfo(void) ;

	void  getShapeInfo (DWORD& flag, Color_t color[PCOustersInfo::OUSTERS_COLOR_MAX]) const;

////////////////////////////////////////////////////
// ������ ��/Ż�� �ɷ�ġ ���� ���� �Լ�
////////////////////////////////////////////////////
public:
	void initAllStat(int numPartyMember=-1) throw();
	void initCastleSkill() throw();
	void sendModifyInfo(const OUSTERS_RECORD& previous) ;
	void addModifyInfo(const OUSTERS_RECORD& previous, ModifyInfo& pkt) ;
	void initAllStatAndSend();
	
private:
	void computeStatOffset(void) throw();
	void computeItemStat(Item* pItem) throw();
	void computeOptionStat(Item* pItem) throw();
	void computePetItemOptionTypeStat(PetInfo* pPetInfo) throw();
	void computeSetItemStat(Item* pItem) throw();
	void computeOptionStat(OptionType_t optionType) throw();
	void computeOptionClassStat(OptionClass OClass, int PlusPoint);


//////////////////////////////////////////////////////////////
// ������ �˻� �Լ�
//////////////////////////////////////////////////////////////
public:

	virtual Item* findItemOID(ObjectID_t id) throw() { return ::findItemOID(this, id); }
	virtual Item* findItemOID(ObjectID_t id, int& storage, int& x, int& y) throw() { return ::findItemOID(this, id, storage, x, y); }

	virtual Item* findItemIID(ItemID_t id) throw() { return ::findItemIID(this, id); }
	virtual Item* findItemIID(ItemID_t id, int& storage, int& x, int& y) throw() { return ::findItemIID(this, id, storage, x, y); }

	virtual Item* findBeltOID(ObjectID_t id) throw() { return ::findItemOID(this, id, Item::ITEM_CLASS_BELT); }
	virtual Item* findBeltOID(ObjectID_t id, int& storage, int& x, int& y) throw() { return ::findItemOID(this, id, Item::ITEM_CLASS_BELT, storage, x, y); }

	virtual Item* findBeltIID(ItemID_t id) throw(){ return ::findItemIID(this, id, Item::ITEM_CLASS_BELT); }
	virtual Item* findBeltIID(ItemID_t id, int& storage, int& x, int& y) throw(){ return ::findItemIID(this, id, Item::ITEM_CLASS_BELT, storage, x, y); }


	virtual Item* findSubInventoryID(ItemID_t id) throw(){ return ::findItemIID(this, id, Item::ITEM_CLASS_SUB_INVENTORY); }
	virtual Item* findSubInventoryID(ItemID_t id, int& storage, int& x, int& y) throw(){ return ::findItemIID(this, id, Item::ITEM_CLASS_SUB_INVENTORY, storage, x, y); }

////////////////////////////////////////////////////
// ���� ���� �Լ�
////////////////////////////////////////////////////
public:

	PCOustersInfo2* getOustersInfo2() throw();
	PCOustersInfo3  getOustersInfo3() ;
	InventoryInfo*  getInventoryInfo() ;
	InventoryInfo*  getInventoryInfo2() ;
	GearInfo*       getGearInfo() ;
	ExtraInfo*      getExtraInfo() ;
	void sendOustersSkillInfo() throw();


////////////////////////////////////////////////////
// ��Ÿ �Լ�
////////////////////////////////////////////////////
public:

	virtual Gold_t getGold()  { return m_Gold; }
	virtual void setGold(Gold_t gold) throw();
	virtual void setGoldEx(Gold_t gold) throw();
	virtual void   increaseGoldEx(Gold_t gold) throw();
    virtual void   decreaseGoldEx(Gold_t gold) throw();

	virtual bool checkGoldIntegrity();
	virtual bool checkStashGoldIntegrity();

	void heartbeat(const Timeval& currentTime) throw();

	void getOustersRecord(OUSTERS_RECORD& record) ;

	virtual Fame_t getFame()  { return m_Fame; }
	virtual void   setFame(Fame_t fame) throw() { m_Fame = fame; }

	virtual Fame_t getKillPoint()  { return m_KillPoint; }
	virtual void   setKillPoint(Fame_t KillPoint) throw() { m_KillPoint = KillPoint; }

	virtual Attr_t getAttackBloodBurstPoint() const { return m_AttackBloodBurstPoint; }
	virtual void setAttackBloodBurstPoint( Attr_t point ) { m_AttackBloodBurstPoint = point; }

	virtual Attr_t getDefenseBloodBurstPoint() const { return m_DefenseBloodBurstPoint; }
	virtual void setDefenseBloodBurstPoint( Attr_t point ) { m_DefenseBloodBurstPoint = point; }

	virtual Attr_t getPartyBloodBurstPoint() const { return m_PartyBloodBurstPoint; }
	virtual void setPartyBloodBurstPoin( Attr_t point ) { m_PartyBloodBurstPoint = point; }

	virtual ZoneID_t getResurrectZoneID(void)  { return m_ResurrectZoneID; }
	virtual void setResurrectZoneID(ZoneID_t id) throw() { m_ResurrectZoneID = id; }
	virtual void setResurrectZoneIDEx(ZoneID_t id) throw();

	Silver_t getSilverDamage()  { return m_SilverDamage; }
	void setSilverDamage(Silver_t damage) throw() { m_SilverDamage = damage; }
	void saveSilverDamage(Silver_t damage) throw();

	virtual Steal_t getHPStealAmount(void) const { return m_HPStealAmount; }
	virtual void setHPStealAmount(Steal_t steal) { m_HPStealAmount = steal; }

	virtual Steal_t getHPStealRatio(void) const { return m_HPStealRatio; }
	virtual void setHPStealRatio(Steal_t steal) { m_HPStealRatio = steal; }

	virtual Steal_t getMPStealAmount(void) const { return m_MPStealAmount; }
	virtual void setMPStealAmount(Steal_t steal) { m_MPStealAmount = steal; }

	virtual Steal_t getMPStealRatio(void) const { return m_MPStealRatio; }
	virtual void setMPStealRatio(Steal_t steal) { m_MPStealRatio = steal; }

	virtual Regen_t getHPRegen(void) const { return m_HPRegen; }
	virtual void setHPRegen(Regen_t regen) { m_HPRegen = regen; }

	virtual Regen_t getMPRegen(void) const { return m_MPRegen; }
	virtual void setMPRegen(Regen_t regen) { m_MPRegen = regen; }

	virtual Luck_t getLuck(void) const { return m_Luck; }
	virtual void setLuck(Luck_t luck) { m_Luck = luck; }

	virtual int getCriticalRatio(void) const { return m_CriticalRatio[ATTR_CURRENT]; }
	virtual void setCriticalRatio(int ratio) { m_CriticalRatio[ATTR_CURRENT] = ratio; }

	virtual Sight_t getEffectedSight() throw();

	virtual IP_t getIP(void) const;

//	WORD getRankExpSaveCount(void) const { return m_RankExpSaveCount; }
//	void setRankExpSaveCount(WORD count) { m_RankExpSaveCount = count; }

	WORD getExpSaveCount(void) const { return m_ExpSaveCount; }
	void setExpSaveCount(WORD count) { m_ExpSaveCount = count; }

	WORD getFameSaveCount(void) const { return m_FameSaveCount; }
	void setFameSaveCount(WORD count) { m_FameSaveCount = count; }

	WORD getAlignmentSaveCount(void) const { return m_AlignmentSaveCount; }
	void setAlignmentSaveCount(WORD count) { m_AlignmentSaveCount = count; }

//	void increaseOustersExp(Exp_t Point);
//	void increaseRankExp(RankExp_t Point);

	void saveInitialRank(void) throw();

//////////////////////////////
// ���� �Ӽ� ���� �Լ�
//////////////////////////////
	Elemental_t getElementalFire() const { return m_ElementalFire; }
	Elemental_t getElementalWater() const { return m_ElementalWater; }
	Elemental_t getElementalEarth() const { return m_ElementalEarth; }
	Elemental_t getElementalWind() const { return m_ElementalWind; }
	Elemental_t getElementalSum() const { return m_ElementalFire + m_ElementalWater + m_ElementalEarth + m_ElementalWind; }

//////////////////////////////
// ���� ���� ���ʽ�
//////////////////////////////
	Damage_t getFireDamage() const { return m_FireDamage; }
	Damage_t getWaterDamage() const { return m_WaterDamage; }
	Damage_t getEarthDamage() const { return m_EarthDamage; }

	Resist_t getSilverResist() const { return m_SilverResist; }

	bool satisfySkillRequire( SkillInfo* pSkillInfo );

//////////////////////////////
// ���� �Ӽ� ���� �Լ�
//////////////////////////////
	bool isPassiveAvailable(SkillType_t type) { return m_PassiveSkillMap.find(type) != m_PassiveSkillMap.end() && m_PassiveSkillMap[type].first; }
	uint getPassiveBonus(SkillType_t type) { return ( m_PassiveSkillMap.find(type) != m_PassiveSkillMap.end() ) ? m_PassiveSkillMap[type].second : 0; }
	int getPassiveRatio() const { return m_PassiveRatio; }

	SkillBonus_t getSkillPointCount( ElementalDomain eDomain );
	bool canLearnSkill( SkillType_t skill );

public :
	 // by sigi. 2002.11.19
	virtual bool isPayPlayAvaiable() throw(Error);
	virtual bool canPlayFree() throw(Error);

	void	initPetQuestTarget();
	int		getBloodBibleSignOpenNum() const;

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
	
private:

	// PC Name
	string m_Name;

	// ����
	BYTE m_Competence;
	BYTE m_CompetenceShape;

	// Sex, Color
	Sex m_Sex;
	Color_t m_HairColor;

	// Alignment
	Alignment_t m_Alignment;

	// STR/DEX/INT
	Attr_t m_STR[3];
	Attr_t m_DEX[3];
	Attr_t m_INT[3];

	// HP
	HP_t m_HP[3];

	// MP
	MP_t m_MP[3];

	Damage_t     m_Damage[3];
	ToHit_t      m_ToHit[2];
	Defense_t    m_Defense[2];
	Protection_t m_Protection[2];
	Speed_t      m_AttackSpeed[2];
	int          m_CriticalRatio[2];

	// Exp/ExpOffset
//	Exp_t m_Exp;
//	Exp_t m_ExpOffset;

	// Gaol Exp
	Exp_t m_GoalExp;

	// level
	Level_t m_Level;

	// ���. by sigi. 2002.8.30
//	Rank_t 		m_Rank;
//	RankExp_t 	m_RankExp;
//	RankExp_t 	m_RankGoalExp;

	// bonus
	Bonus_t m_Bonus;
	BYTE m_WingSylphType;
	ItemType_t m_WingItemType;
	Color_t m_WingColor;
	Color_t m_WingEffectColor;
	Color_t m_ShopColor;
	// Skill bonus
	SkillBonus_t m_SkillBonus;

	// gold
	Gold_t m_Gold;

	Fame_t m_Fame;
	Fame_t m_KillPoint;

	ZoneCoord_t m_VisionWidth;
	ZoneCoord_t m_VisionHeight;

	// SkillSlot
	//OustersSkillSlot* m_pSkillSlot[MAX_OUSTERS_SKILL_SLOT];
	hash_map<SkillType_t, OustersSkillSlot*> m_SkillSlot;

	// WearItem Field
	Item* m_pWearItem[OUSTERS_WEAR_MAX];
	bool m_pRealWearingCheck[OUSTERS_WEAR_MAX];

	// Ousters Outlook Information
	mutable PCOustersInfo3 m_OustersInfo;

	// mutable Thread Mutex
	mutable Mutex m_Mutex;

	// ��Ȱ�� ����
	ZoneID_t m_ResurrectZoneID;

	// �� ���� ������ ����
	Silver_t m_SilverDamage;

	// HP ��ƿ
	Steal_t m_HPStealAmount;
	Steal_t m_HPStealRatio;

	// MP ��ƿ
	Steal_t m_MPStealAmount;
	Steal_t m_MPStealRatio;

	// HP, MP ���
	Regen_t m_HPRegen;
	Regen_t m_MPRegen;

	Luck_t m_Luck;

	// ���� �Ӽ�
	Elemental_t m_ElementalFire;
	Elemental_t m_ElementalWater;
	Elemental_t m_ElementalEarth;
	Elemental_t m_ElementalWind;

	// ���� ���� ���ʽ� ����Ʈ
	Damage_t m_FireDamage;
	Damage_t m_WaterDamage;
	Damage_t m_EarthDamage;

	// �� ����
	Resist_t m_SilverResist;

	hash_map<SkillType_t, pair<bool, uint> > m_PassiveSkillMap;
	int m_PassiveRatio;

	// ���� ����ġ ���̺� ī��Ʈ
//	WORD m_RankExpSaveCount;
	WORD m_ExpSaveCount;
	WORD m_FameSaveCount;
	WORD m_AlignmentSaveCount;

	Attr_t	m_AttackBloodBurstPoint;
	Attr_t	m_DefenseBloodBurstPoint;
	Attr_t	m_PartyBloodBurstPoint;

	Timeval m_MPRegenTime;
};


#endif // __OUSTERS_H__
