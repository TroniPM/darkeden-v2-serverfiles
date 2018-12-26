//////////////////////////////////////////////////////////////////////////////
// Filename    : Slayer.h
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __SLAYER_H__
#define __SLAYER_H__

#include "PlayerCreature.h"
#include "Zone.h"
#include "Assert.h"
#include "Inventory.h"
#include "PCSlayerInfo.h"
#include "PCSlayerInfo2.h"
#include "PCSlayerInfo3.h"
#include "InventoryInfo.h"
#include "ItemLoaderManager.h"
#include "GearInfo.h"
#include "ExtraInfo.h"
#include "OptionInfo.h"
#include "RideMotorcycleInfo.h"
#include "SlayerSkillInfo.h"
#include "CreatureUtil.h"
#include "ModifyInfo.h"
#include "Mutex.h"
#include <hash_map>
//#include "RankExpTable.h"
#include "SlayerAttrExpTable.h"

#include "skill/Skill.h"
#include "skill/SkillSlot.h"

#include "Gpackets/GCModifyInformation.h"

#ifdef __CHINA_SERVER__
#define	SLAYER_BOUND_LEVEL			100
#define SLAYER_BOUND_ATTR			200
#define	SLAYER_BOUND_ATTR_SUM		300
#define SLAYER_BOUND_ONE_EXP_ATTR	200
#define SLAYER_BOUND_SUB_ATTR		50
#define SLAYER_MAX_LEVEL			150
#define SLAYER_MAX_ATTR				295
#define	SLAYER_MAX_ATTR_SUM			435
#define SLAYER_ONE_EXP_ATTR			400
#define	SLAYER_MAX_DOMAIN_LEVEL		150
#define SLAYER_MAX_SUB_ATTR			70

#define SLAYER_MAX_RANK	50
#else
// �����̾�� ������ ������ BOUND_LEVEL�� �����ϱ� ��������
// �ɷ�ġ�� BOUND_ATTR ���Ϸ�, �ɷ�ġ ������ BOUND_ATTR_SUM ���Ϸ� ���ѵȴ�.
// BOUND_LEVEL�� ���� �ڿ��� MAX_ATTR�� MAX_ATTR_SUM���� ���ѵȴ�.
#define	SLAYER_BOUND_LEVEL			100
#define SLAYER_BOUND_ATTR			210
#define	SLAYER_BOUND_ATTR_SUM		330
#define SLAYER_BOUND_ONE_EXP_ATTR	210
#define SLAYER_BOUND_SUB_ATTR		60
#define SLAYER_MAX_LEVEL			150
//#define SLAYER_MAX_ATTR				295
#define SLAYER_MAX_ATTR				315
//#define	SLAYER_MAX_ATTR_SUM			435
#define	SLAYER_MAX_ATTR_SUM			475
#define SLAYER_ONE_EXP_ATTR			400
#define	SLAYER_MAX_DOMAIN_LEVEL		150
#define SLAYER_MAX_SUB_ATTR			80

#define SLAYER_MAX_RANK	50
#endif

////////////////////////////////////////////////////////////////////////////////
// ��� �԰� ���� �� ��� �԰� ���� ���� �ɷ�ġ�� 
// ������ �α� ���� ����(?) Ŭ����.
////////////////////////////////////////////////////////////////////////////////

class SLAYER_RECORD
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
// Class Slayer;
//
// Creature �� ���� Ŭ������ �÷��̾ �����ϴ� PC �̴�.
//
////////////////////////////////////////////////////////////////////////////////
	
class Motorcycle;

class Slayer : public PlayerCreature 
{

//////////////////////////////////////////////////////////////
// Ŭ���� ���� ��� ����
//////////////////////////////////////////////////////////////
public:

	enum WearPart 
	{ 
		WEAR_HEAD, 
		WEAR_NECK, 
		WEAR_BODY, 
		WEAR_LEFTHAND, 
		WEAR_RIGHTHAND,
		WEAR_HAND3,
		WEAR_BELT,
		WEAR_LEG,
		WEAR_WRIST1, 
		WEAR_WRIST2, 				
		WEAR_FINGER1, 
		WEAR_FINGER2, 
		WEAR_FINGER3, 
		WEAR_FINGER4,
		WEAR_FOOT,
		WEAR_ZAP1,
		WEAR_ZAP2,
		WEAR_ZAP3,
		WEAR_ZAP4,
		WEAR_PDA,
		WEAR_SHOULDER,
		WEAR_BRACELET_ZAP1,
		WEAR_BRACELET_ZAP2,
		WEAR_NECKLACE_ZAP,
		WEAR_COAT_ZAP,
		WEAR_LEG_ZAP,
		WEAR_LEFTHAND_ZAP, 
		WEAR_HEAD_ZAP, 
		WEAR_BELT_ZAP,
		WEAR_HAND3_ZAP,
		WEAR_FOOT_ZAP,
		WEAR_MAX 
	};

//////////////////////////////////////////////////////////////
// ������/�Ҹ���
//////////////////////////////////////////////////////////////
public:
	Slayer() ;
	virtual ~Slayer();
	
//////////////////////////////////////////////////////////////
// ���� Ŭ���� ��� �Լ�
//////////////////////////////////////////////////////////////
public:
	virtual CreatureClass getCreatureClass()  { return CREATURE_CLASS_SLAYER; }
	virtual string getCreatureClassString()  { return "CREATURE_CLASS_SLAYER"; }

	virtual void registerObject();
	virtual void registerInitObject();

	virtual bool load() ;
	void loadItem( bool checkTimeLimit = false ) ;

	virtual void save() ;
	virtual void tinysave(const string & field) ;
//	virtual void tinysave(const char* field) ;
	void saveSkills(void) ;
	void saveGears(void) ;
	void saveExps(void) ;

	virtual void act(const Timeval& currentTime)  {}

	virtual string toString() ;

	virtual Race_t getRace() const { return RACE_SLAYER; }
	virtual GuildID_t getCommonGuildID() const { return SlayerCommon; }

//////////////////////////////////////////////////////////////
// �ð����� ������ ���� �Լ�
//////////////////////////////////////////////////////////////
public:
	void checkItemTimeLimit();
	void updateEventItemTime( DWORD time );

//////////////////////////////////////////////////////////////
// ���� ���� �Լ�(dead or alive)
//////////////////////////////////////////////////////////////
public:
	virtual bool isDead()  { return m_HP[ATTR_CURRENT] == 0; }
	virtual bool isAlive()  { return m_HP[ATTR_CURRENT] != 0; }

//////////////////////////////////////////////////////////////
// �Ѹ�� ���� �Լ�(�̸�, ����, ����, �Ӹ�, �Ǻ�, ��ȭ��ȣ)
//////////////////////////////////////////////////////////////
public:
	const string& getName()  { return m_Name; }
	void setName(const string & name) throw() { m_Name = name; m_Owner = name; }

	BYTE getCompetence()  { return m_Competence; }
	void setCompetence(BYTE Competence) { m_Competence = Competence; }

	BYTE getCompetenceShape()  { return m_CompetenceShape; }
	void setCompetenceShape(BYTE CompetenceShape) { m_CompetenceShape = CompetenceShape; }

	Sex getSex()  { return m_Sex; }
	void setSex(Sex sex) throw() { m_Sex = sex; m_SlayerInfo.setSex(sex); }
	void setSex(const string & sex) throw(InvalidProtocolException)
	{
		if(sex == Sex2String[MALE]) setSex(MALE);
		else if(sex == Sex2String[FEMALE]) setSex(FEMALE);
		else throw InvalidProtocolException("invalid sex value");
	}

	HairStyle getHairStyle()  { return m_HairStyle; }
	void setHairStyle(HairStyle hairStyle) throw() { m_HairStyle = hairStyle; }
	void setHairStyle(const string& hairStyle) throw(InvalidProtocolException)
	{
		if(hairStyle == HairStyle2String[HAIR_STYLE1])      m_HairStyle = HAIR_STYLE1;
		else if(hairStyle == HairStyle2String[HAIR_STYLE2]) m_HairStyle = HAIR_STYLE2;
		else if(hairStyle == HairStyle2String[HAIR_STYLE3]) m_HairStyle = HAIR_STYLE3;
		else throw InvalidProtocolException("invalid hairstyle value");
	}

	Color_t getHairColor()  { return m_HairColor; }
	void setHairColor(Color_t hairColor) throw() { m_HairColor = hairColor; }

	Color_t getSkinColor()  { return m_SkinColor; }
	void setSkinColor(Color_t skinColor) throw() { m_SkinColor = skinColor; }

	virtual Color_t getShopColor()  { return m_ShopColor; }
	virtual void setShopColor(Color_t ShopColor) throw() { m_ShopColor = ShopColor; }

	virtual ItemType_t getJacketItemType()  { return m_JacketItemType; }
	virtual void setJacketItemType(ItemType_t ItemType)  throw() { m_JacketItemType = ItemType; }

//////////////////////////////////////////////////////////////
// ��ȭ ���� �Լ�
//////////////////////////////////////////////////////////////
public:
	PhoneNumber_t getPhoneNumber()  { return m_PhoneNumber; }
	void setPhoneNumber(PhoneNumber_t PhoneNumber) throw() { m_PhoneNumber = PhoneNumber; }
	
	PhoneNumber_t getPhoneSlotNumber(SlotID_t SlotID) ;
	void setPhoneSlotNumber(SlotID_t SlotID, PhoneNumber_t PhoneNumber) ;
	SlotID_t getSlotWithPhoneNumber(PhoneNumber_t PhoneNumber) ;
	SlotID_t findEmptyPhoneSlot() ;
	bool isEmptyPhoneSlot() ;
	bool isSlotByPhoneNumber(PhoneNumber_t PhoneNumber) ;

//////////////////////////////////////////////////////////////
// �ɷ�ġ ���� �Լ�(STR, DEX, INT)
//////////////////////////////////////////////////////////////
public:

	Bonus_t getBonus()  { return m_AdvancedAttrBonus; }
	void    setBonus(Bonus_t bonus) throw() { m_AdvancedAttrBonus = bonus; }

	// ����
	Alignment_t getAlignment()  { return m_Alignment; }
	void setAlignment(Alignment_t Alignment) throw() { m_Alignment = Alignment; }
	void saveAlignment(Alignment_t alignment) ;

	Attr_t  getSTR(AttrType attrType = ATTR_CURRENT)  { return m_STR[attrType]; }
	void    setSTR(Attr_t attr, AttrType attrType = ATTR_CURRENT) throw() { m_STR[attrType] = attr; }
	Exp_t   getSTRGoalExp()  { return m_pAttrs[ATTR_KIND_STR]->getGoalExp(); }

	Attr_t  getDEX(AttrType attrType = ATTR_CURRENT)  { return m_DEX[attrType]; }
	void    setDEX(Attr_t attr, AttrType attrType = ATTR_CURRENT) throw() { m_DEX[attrType] = attr; }
	Exp_t   getDEXGoalExp()  { return m_pAttrs[ATTR_KIND_DEX]->getGoalExp(); }

	Attr_t  getINT(AttrType attrType = ATTR_CURRENT)  { return m_INT[attrType]; }
	void    setINT(Attr_t attr, AttrType attrType = ATTR_CURRENT) throw() { m_INT[attrType] = attr; }
	Exp_t   getINTGoalExp()  { return m_pAttrs[ATTR_KIND_INT]->getGoalExp(); }

	Attr_t	getTotalAttr( AttrType attrType = ATTR_CURRENT )  { return getSTR( attrType ) + getDEX( attrType ) + getINT( attrType ); }
	QuestGrade_t getQuestGrade() ;

	void divideAttrExp(AttrKind kind, Damage_t damage, ModifyInfo& ModifyInfo);

	// ��� �߰�. by sigi. 2002.8.30
	// PlayerCreature�� �ű�. 2004.1 by Sequoia

	// �ʺ����ΰ�? ���� �ɷ�??���� 40 ����
	bool	isNovice() const;

//////////////////////////////////////////////////////////////
// �ɷ�ġ ���� �Լ�(HP, MP)
//////////////////////////////////////////////////////////////
public:
	HP_t getHP(AttrType attrType = ATTR_CURRENT)  { return m_HP[attrType]; }
	void setHP(HP_t hp, AttrType attrType = ATTR_CURRENT) throw() { m_HP[attrType] = hp; }
	void setHP(HP_t current, HP_t max) throw() { m_HP[ATTR_CURRENT] = current; m_HP[ATTR_MAX] = max; }

	MP_t getMP(AttrType attrType = ATTR_CURRENT)  { return m_MP[attrType]; }
	void setMP(MP_t hp, AttrType attrType = ATTR_CURRENT) throw() { m_MP[attrType] = hp; }
	void setMP(MP_t current, MP_t max) throw() { m_MP[ATTR_CURRENT] = current; m_MP[ATTR_MAX] = max; }


//////////////////////////////////////////////////////////////
// �ɷ�ġ ���� �Լ�(Damage, CC, Defense, ToHit)
//////////////////////////////////////////////////////////////
public:
	Damage_t     getDamage(AttrType attrType = ATTR_CURRENT)  { return m_Damage[attrType]; }
	Protection_t getProtection(void)  { return m_Protection[ATTR_CURRENT]; }
	Defense_t    getDefense(void)  { return m_Defense[ATTR_CURRENT]; }
	ToHit_t      getToHit(void)  { return m_ToHit[ATTR_CURRENT]; }
	Speed_t      getAttackSpeed(void)  { return m_AttackSpeed[ATTR_CURRENT]; }

	
//////////////////////////////////////////////////////////////
// ��ų ���� �Լ�
//////////////////////////////////////////////////////////////
public:
	Exp_t getGoalExp(SkillDomainType_t Domain)  { return m_GoalExp[Domain]; }
	void  setGoalExp(SkillDomainType_t Domain, Exp_t GoalExp) throw() { m_GoalExp[Domain] = GoalExp; }

	SkillLevel_t getSkillDomainLevel(SkillDomainType_t skillDomain)  { return m_SkillDomainLevels[skillDomain]; }
	void         setSkillDomainLevel(SkillDomainType_t skillDomain, SkillLevel_t skillLevel) throw() { m_SkillDomainLevels[skillDomain] = skillLevel; }
	SkillLevel_t getHighestSkillDomainLevel() ;
	SkillDomainType_t getHighestSkillDomain() ;

//	SkillExp_t getSkillDomainExp(SkillDomainType_t skillDomain)  { return m_SkillDomainExps[skillDomain]; }
//	void       setSkillDomainExp(SkillDomainType_t skillDomain, SkillExp_t skillExp) throw() { m_SkillDomainExps[skillDomain] = skillExp; }

//	void setSkillDomain(SkillDomainType_t skillDomain, SkillLevel_t skillLevel, SkillExp_t skillExp) throw() { m_SkillDomainLevels[skillDomain] = skillLevel; m_SkillDomainExps[skillDomain] = skillExp; }

	SkillLevel_t getSkillDomainLevelSum() ;
	Level_t getLevel()  { return (Level_t)getHighestSkillDomainLevel(); }

	int getQuestLevel() const { return getHighestSkillDomainLevel(); }

	void addSkill(SkillSlot* pSkillSlot) ;
	void addSkill(SkillType_t SkillType) ;
	void removeCastleSkill(SkillType_t SkillType) ;
	void removeAllCastleSkill() ;
	SkillSlot* hasSkill(SkillType_t SkillType)  { return getSkill(SkillType); }
	SkillSlot* getSkill(SkillType_t SkillType) ;

	Exp_t getGunBonusExp()  { return m_GunBonusExp; }
	void setGunBonusExp(Exp_t GunBonusExp) throw() { m_GunBonusExp = GunBonusExp; }

	Exp_t getRifleBonusExp()  { return m_RifleBonusExp; }
	void setRifleBonusExp(Exp_t RifleBonusExp) throw() { m_RifleBonusExp = RifleBonusExp; }
	
	// ������ domain���� ���� ���� level�� ����� Ÿ���� �ǵ�����.
	//SkillType_t getMaxLevelSkillType(SkillDomainType_t domain) ;
//	void setHotKey(BYTE pos, SkillType_t SkillType) throw() { m_HotKey[pos] = SkillType; }
//	SkillType_t getHotKey(BYTE pos)  { return m_HotKey[pos]; }


//////////////////////////////////////////////////////////////
// ������ ��/Ż ���� �Լ�
//////////////////////////////////////////////////////////////
public:
	bool  isWear(WearPart Part) throw() { return m_pWearItem[Part] != NULL ? true : false; }
	void  addWearItem(WearPart Part, Item* pItem) throw() { Assert(m_pWearItem[Part] = NULL); m_pWearItem[Part] = pItem;}
	void  deleteWearItem(WearPart Part)  { Assert(m_pWearItem[Part] != NULL); m_pWearItem[Part] = NULL; }
	Item* getWearItem(WearPart Part) throw() { return m_pWearItem[Part]; }
	void  wearItem(WearPart Part);
	void  wearItem(WearPart Part, Item* pItem);
	void  takeOffItem(WearPart Part, bool bAddOnMouse, bool bSendModifyInfo);
	WearPart getWearPart(Item::ItemClass IClass) const;
	bool 	changeShape(Item* pItem, Color_t color, bool bSendPacket=true);
	bool 	addShape(Item::ItemClass IClass, ItemType_t IType, Color_t color);
	bool 	removeShape(Item::ItemClass IClass, bool bSendPacket=true);
	Color_t getItemShapeColor(Item* pItem, OptionInfo* pOptionInfo=NULL) const;


	void  destroyGears() ;

	bool  isRealWearing(WearPart part) ;
	bool  isRealWearing(Item* pItem) ;
	bool  isRealWearingEx(WearPart part) const;
	DWORD sendRealWearingInfo(void) ;
	void  getShapeInfo (DWORD& flag, Color_t color[PCSlayerInfo::SLAYER_COLOR_MAX]) const;

//////////////////////////////////////////////////////////////
// ������ ��/Ż �� �ɷ�ġ ���� ���� �Լ�
//////////////////////////////////////////////////////////////
public:
	void initAllStat(int numPartyMember=-1) ;
	void initCastleSkill() ;
	void addModifyInfo(const SLAYER_RECORD& previous, ModifyInfo& pkt) ;
	void sendModifyInfo(const SLAYER_RECORD& previous) ;
	void initAllStatAndSend();

private:
	void computeStatOffset(void) ;
	void computeItemStat(Item* pItem) ;
	void computeSetItemStat(Item* pItem) ;
	void computePetItemOptionTypeStat(PetInfo* pPetInfo) ;
	void computeOptionStat(Item* pItem) ;
	void computeOptionStat(OptionType_t optionType) ;
	void computeOptionClassStat( OptionClass OClass, int PlusPoint );

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

//////////////////////////////////////////////////////////////
// ���� ����Ŭ ���� �Լ�
//////////////////////////////////////////////////////////////
public:
	Motorcycle* getMotorcycle()  { return m_pMotorcycle; }
	void setMotorcycle(Motorcycle* pMotorcycle) ;
	void getOffMotorcycle();

	RideMotorcycleInfo* getRideMotorcycleInfo() ;
	bool hasRideMotorcycle()  { return((m_pMotorcycle != NULL) ? true : false);}


//////////////////////////////////////////////////////////////
// ���� ���� �Լ�
//////////////////////////////////////////////////////////////
public:
	PCSlayerInfo2* getSlayerInfo2() ;
	PCSlayerInfo3  getSlayerInfo3() ;
	GearInfo*      getGearInfo() ;
	InventoryInfo* getInventoryInfo() ;
	InventoryInfo* getInventoryInfo2() ;
	ExtraInfo*     getExtraInfo() ;
	void sendSlayerSkillInfo() ;

	// get/set EffectInfo
    EffectInfo* getEffectInfo() ;

//////////////////////////////////////////////////////////////
// ��Ÿ �Լ�
//////////////////////////////////////////////////////////////
public:

	virtual Fame_t getFame()  { return m_Fame; }
	virtual void   setFame(Fame_t fame) throw() { m_Fame = fame; }

	virtual Fame_t getKillPoint()  { return m_KillPoint; }
	virtual void   setKillPoint(Fame_t Kill) throw() { m_KillPoint = Kill; }

	virtual Gold_t getGold()  { return m_Gold; }
	virtual void   setGold(Gold_t gold) ;
	virtual void   setGoldEx(Gold_t gold) ;
	virtual void   increaseGoldEx(Gold_t gold) ;
	virtual void   decreaseGoldEx(Gold_t gold) ;
	virtual bool checkGoldIntegrity();
	virtual bool checkStashGoldIntegrity();

	virtual Attr_t getAttackBloodBurstPoint() const { return m_AttackBloodBurstPoint; }
	virtual void setAttackBloodBurstPoint( Attr_t point ) { m_AttackBloodBurstPoint = point; }

	virtual Attr_t getDefenseBloodBurstPoint() const { return m_DefenseBloodBurstPoint; }
	virtual void setDefenseBloodBurstPoint( Attr_t point ) { m_DefenseBloodBurstPoint = point; }

	virtual Attr_t getPartyBloodBurstPoint() const { return m_PartyBloodBurstPoint; }
	virtual void setPartyBloodBurstPoin( Attr_t point ) { m_PartyBloodBurstPoint = point; }

	void setInMagics(const string & blob) throw() {}

	void heartbeat(const Timeval& currentTime) ;

	void getSlayerRecord(SLAYER_RECORD& record) ;

	virtual ZoneID_t getResurrectZoneID(void)  { return m_ResurrectZoneID; }
	virtual void setResurrectZoneID(ZoneID_t id) throw() { m_ResurrectZoneID = id; }
	virtual void setResurrectZoneIDEx(ZoneID_t id) ;

	virtual Steal_t getHPStealAmount(void) const { return m_HPStealAmount; }
	virtual void setHPStealAmount(Steal_t steal) { m_HPStealAmount = steal; }

	virtual Steal_t getMPStealAmount(void) const { return m_MPStealAmount; }
	virtual void setMPStealAmount(Steal_t steal) { m_MPStealAmount = steal; }

	virtual Steal_t getHPStealRatio(void) const { return m_HPStealRatio; }
	virtual void setHPStealRatio(Steal_t steal) { m_HPStealRatio = steal; }

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

	uint getSlayerLevel(void) ;
	void saveInitialRank(void) ;

	virtual IP_t getIP(void) const;

	WORD getDomainExpSaveCount(void) const { return m_DomainExpSaveCount; }
	void setDomainExpSaveCount(WORD count) { m_DomainExpSaveCount = count; }

	WORD getAttrExpSaveCount(void) const { return m_AttrExpSaveCount; }
	void setAttrExpSaveCount(WORD count) { m_AttrExpSaveCount = count; }

	WORD getSkillExpSaveCount(void) const { return m_SkillExpSaveCount; }
	void setSkillExpSaveCount(WORD count) { m_SkillExpSaveCount = count; }

	WORD getFameSaveCount(void) const { return m_FameSaveCount; }
	void setFameSaveCount(WORD count) { m_FameSaveCount = count; }

	WORD getAlignmentSaveCount(void) const { return m_AlignmentSaveCount; }
	void setAlignmentSaveCount(WORD count) { m_AlignmentSaveCount = count; }

//	WORD getRankExpSaveCount(void) const { return m_RankExpSaveCount; }
//	void setRankExpSaveCount(WORD count) { m_RankExpSaveCount = count; }

//	void increaseRankExp(RankExp_t Point);

public :
	// by sigi. 2002.11.19
	virtual bool isPayPlayAvaiable();
	virtual bool canPlayFree();

	virtual void setLastTarget(ObjectID_t value);

	void	initPetQuestTarget();
	int		getBloodBibleSignOpenNum() const;

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
private:

	// PC name
	string m_Name;

	// ����
	BYTE m_Competence;
	BYTE m_CompetenceShape;

	// Sex(1bit), HairStyle(2bit)
	// ���߿��� bit ������ �ؼ� �޸𸮸� ���̵��� ����.
	Sex m_Sex;
	HairStyle m_HairStyle;	

	// HairColor(8bit), SkinColor(8bit)
	Color_t m_HairColor;
	Color_t m_SkinColor;
	Color_t m_ShopColor;

    // Phone Number
	PhoneNumber_t m_PhoneNumber;
	
	// Phone Slot
	PhoneNumber_t m_PhoneSlot[3];

	// Alignment
	Alignment_t m_Alignment;

	// STR/DEX/INT
	Attr_t m_STR[3];
	Attr_t m_DEX[3];
	Attr_t m_INT[3];

	Attr* m_pAttrs[ATTR_KIND_MAX];

	// STR/DEX/INT exp
//	Exp_t m_STRExp;
//	Exp_t m_STRGoalExp;
//	Exp_t m_DEXExp;
//	Exp_t m_DEXGoalExp;
//	Exp_t m_INTExp;
//	Exp_t m_INTGoalExp;

	// Rank
//	Rank_t 		m_Rank;
//	RankExp_t 	m_RankExp;
//	RankExp_t 	m_RankGoalExp;

//	Rank*		m_pRank;

	// HP/MP
	HP_t m_HP[3];
	MP_t m_MP[3];

	Damage_t     m_Damage[3];
	ToHit_t      m_ToHit[2];
	Defense_t    m_Defense[2];
	Protection_t m_Protection[2];
	Speed_t      m_AttackSpeed[2];
	int          m_CriticalRatio[2];

	// Vision / SkillPoint
	Vision_t     m_Vision[2];
	SkillPoint_t m_SkillPoint;
	
	// Fame/Gold
	Fame_t m_Fame;
	Fame_t m_KillPoint;
	Gold_t m_Gold;

	// SkillLevel, SkillExp
	SkillLevel_t m_SkillDomainLevels[SKILL_DOMAIN_VAMPIRE];
//	SkillExp_t m_SkillDomainExps[SKILL_DOMAIN_VAMPIRE];

	// Goal Exp
	Exp_t m_GoalExp[SKILL_DOMAIN_VAMPIRE];

	// Gun, Rifle Bonus Exp
	Exp_t m_GunBonusExp;
	Exp_t m_RifleBonusExp;

	// SkillSlot
	//SkillSlot* m_pSkillSlot[MAX_SLAYER_SKILL_SLOT];
	hash_map<SkillType_t, SkillSlot*> m_SkillSlot;

	// WearItem Field
	Item* m_pWearItem[WEAR_MAX];
	bool  m_pRealWearingCheck[WEAR_MAX];

	// Motorcycle Pointer
	Motorcycle* m_pMotorcycle;

	// outlook information
	mutable PCSlayerInfo3 m_SlayerInfo;

	// Hot Key Set
//	SkillType_t m_HotKey[4];

	mutable Mutex m_Mutex;

	// �����̾��� ���� �ɷ�ġ�� ������ �δ� ���� ����ü
	SLAYER_RECORD m_Record;

	// ��Ȱ�� ����
	ZoneID_t m_ResurrectZoneID;

	// HP, MP ��ƿ
	Steal_t m_HPStealAmount;
	Steal_t m_MPStealAmount;
	Steal_t m_HPStealRatio;
	Steal_t m_MPStealRatio;

	// HP, MP ���
	Regen_t m_HPRegen;
	Regen_t m_MPRegen;
	
	// luck
	Luck_t  m_Luck;
	ItemType_t m_JacketItemType;

	// Prayer�� Meditation�� ���õ� timer
	Timeval m_MPRegenTime;

	// ���� ����ġ ���̺� ī��Ʈ
	WORD m_DomainExpSaveCount;
	WORD m_AttrExpSaveCount;
	WORD m_SkillExpSaveCount;
	WORD m_FameSaveCount;
	WORD m_AlignmentSaveCount;
//	WORD m_RankExpSaveCount;

	Attr_t	m_AttackBloodBurstPoint;
	Attr_t	m_DefenseBloodBurstPoint;
	Attr_t	m_PartyBloodBurstPoint;

};

#endif // __SLAYER_H__
