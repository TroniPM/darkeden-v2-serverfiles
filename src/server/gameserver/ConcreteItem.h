#ifndef __CONCRETE_ITEM_H__
#define __CONCRETE_ITEM_H__

#include "Item.h"
#include "ItemInfo.h"
#include "ItemInfoManager.h"
#include "DB.h"
#include "ItemPolicies.h"

/*#define InitTableNameClass(C, S) \
class C { public: \
	static const string& getObjectTableName() { static string theString(string(S) + "Object"); return theString; } \
	static const string& getInfoTableName() { static string theString(string(S) + "Info"); return theString; } \
};*/

template <Item::ItemClass IClass,
	typename StackPolicy = NoStack, typename DurabilityPolicy = NoDurability, typename OptionPolicy = NoOption, typename GradePolicy = NoGrade,
	typename AttackingStatPolicy = NoAttacking, typename EnchantLevelPolicy = HasEnchantLevel, typename OptionPolicy2 = NoOption2, typename HeroItemPolicy = NoHeroOption,typename HeroItemAttrPolicy = NoHeroOptionAttr>
class ConcreteItem : public Item
{
public:
	// 가상 함수 구체화
	ItemClass	getItemClass()  { return IClass; }
	string		getObjectTableName()  { return ItemObjectTableName[getItemClass()]; }
	ItemInfo*	getItemInfo() const { return g_pItemInfoManager->getItemInfo( getItemClass(), getItemType() ); }

	ItemType_t	getItemType()  { return m_ItemType; }
	void		setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	VolumeWidth_t	getVolumeWidth()  { return getItemInfo()->getVolumeWidth(); }
	VolumeHeight_t	getVolumeHeight()  { return getItemInfo()->getVolumeHeight(); }
	Weight_t		getWeight()  { return getItemInfo()->getWeight(); }

public:
	// 아이템 쌓기 관련
	bool	isStackable()  { return m_Stack.hasValue(); }

	ItemNum_t	getNum()  { return m_Stack.getValue(); }
	void		setNum(ItemNum_t Num) throw() { m_Stack.setValue(Num); }

public:
	// 내구도 관련
	Durability_t	getDurability()  { return m_Durability.getValue(); }
	void			setDurability(Durability_t durability) throw(Error) { m_Durability.setValue(durability); }
	Durability_t	getMaxDurability() const {
		if ( m_Durability.hasValue() )
		{
			Durability_t baseDur = getItemInfo()->getDurability();
//			return max(1000,((int)baseDur) + min((int)m_Grade.getDurabilityOffset(), 65000-baseDur));
			return max(1000,(int)baseDur + m_Grade.getDurabilityOffset());
		}
		else
			return getItemInfo()->getDurability();
	}

public:
	// 옵션 관련
	bool						hasOptionType()  { return m_Option.hasOptionType(); }
	int							getOptionTypeSize()  { return m_Option.getOptionTypeSize(); }
	int							getRandomOptionType()  { return m_Option.getRandomOptionType(); }
	const list<OptionType_t>&	getOptionTypeList()  { return m_Option.getOptionTypeList(); }
	OptionType_t				getFirstOptionType()  { return m_Option.getFirstOptionType(); }
	void						removeOptionType(OptionType_t OptionType) throw() { m_Option.removeOptionType(OptionType); }
	void						changeOptionType(OptionType_t currentOptionType, OptionType_t newOptionType) throw() { m_Option.changeOptionType(currentOptionType, newOptionType); }
	void						addOptionType(OptionType_t OptionType) throw() { m_Option.addOptionType(OptionType); }
	void						setOptionType(const list<OptionType_t>& OptionType) throw() { m_Option.setOptionType(OptionType); }

public:
	// 아이템 등급 관련
	Grade_t	getGrade() const { return m_Grade.getValue(); }
	void	setGrade(Grade_t Grade) { m_Grade.setValue(Grade); }

	Luck_t	getLuck() const { return m_Grade.getLuck(); }

public:
	// 공격력 관련 속성
	Damage_t	getMinDamage()  { return max(1,((int)getItemInfo()->getMinDamage()) + ((int)getBonusDamage()) + m_Grade.getDamageOffset()); }
	Damage_t	getMaxDamage()  { return max(1,((int)getItemInfo()->getMaxDamage()) + ((int)getBonusDamage()) + m_Grade.getDamageOffset()); }
	Range_t		getRange()  { return getItemInfo()->getRange(); }
	ToHit_t		getToHitBonus()  { return getItemInfo()->getToHitBonus(); }
	Speed_t		getSpeed()  { return getItemInfo()->getSpeed(); }
	int			getCriticalBonus()  { return max(0,getItemInfo()->getCriticalBonus() + m_Grade.getCriticalOffset()); }

	BYTE		getBulletCount()  { return m_AttackingStat.getBulletCount(); }
	void		setBulletCount(BYTE bulletCount) throw() { m_AttackingStat.setBulletCount(bulletCount); }

	bool		isSilverWeapon()  { return m_AttackingStat.isSilverWeapon(); }
	Silver_t	getSilver()  { return m_AttackingStat.getSilver(); }
	void		setSilver(Silver_t amount) throw() { m_AttackingStat.setSilver(amount); }

	bool		isGun()  { return m_AttackingStat.isGun(); }

	Damage_t	getBonusDamage()  { return m_AttackingStat.getBonusDamage(); }
	void		setBonusDamage(Damage_t BonusDamage) throw() { m_AttackingStat.setBonusDamage(BonusDamage); }

public:
	// 방어력 관련 속성
	Defense_t	getDefenseBonus()  { return max(0,((int)getItemInfo()->getDefenseBonus()) + m_Grade.getDefenseOffset()); }
	Protection_t	getProtectionBonus()  { return max(0,((int)getItemInfo()->getProtectionBonus()) + m_Grade.getProtectionOffset()); }

public:
	// 인챈트 레벨
	EnchantLevel_t	getEnchantLevel()  { return m_EnchantLevel.getValue(); }
	void			setEnchantLevel(EnchantLevel_t level) throw() { m_EnchantLevel.setValue(level); }

public:
	// 옵션 관련
	bool						hasOptionType2()  { return m_Option2.hasOptionType2(); }
	int							getOptionTypeSize2()  { return m_Option2.getOptionTypeSize2(); }
	int							getRandomOptionType2()  { return m_Option2.getRandomOptionType2(); }
	const list<OptionType_t>&	getOptionTypeList2()  { return m_Option2.getOptionTypeList2(); }
	OptionType_t				getFirstOptionType2()  { return m_Option2.getFirstOptionType2(); }
	void						removeOptionType2(OptionType_t OptionType) throw() { m_Option2.removeOptionType2(OptionType); }
	void						changeOptionType2(OptionType_t currentOptionType, OptionType_t newOptionType) throw() { m_Option2.changeOptionType2(currentOptionType, newOptionType); }
	void						addOptionType2(OptionType_t OptionType) throw() { m_Option2.addOptionType2(OptionType); }
	void						setOptionType2(const list<OptionType_t>& OptionType) throw() { m_Option2.setOptionType2(OptionType); }

public:

	EnchantLevel_t	getHeroOption()  { return m_HeroOption.getValue(); }
	void			setHeroOption(EnchantLevel_t level) throw() { m_HeroOption.setValue(level); }

	EnchantLevel_t	getHeroOptionAttr()  { return m_HeroOptionAttr.getValue(); }
	void			setHeroOptionAttr(EnchantLevel_t level) throw() { m_HeroOptionAttr.setValue(level); }

private:
	ItemType_t			m_ItemType;

	StackPolicy			m_Stack;
	DurabilityPolicy	m_Durability;
	OptionPolicy		m_Option;
	OptionPolicy2		m_Option2;
	GradePolicy			m_Grade;

	AttackingStatPolicy	m_AttackingStat;
	EnchantLevelPolicy	m_EnchantLevel;

	HeroItemPolicy	m_HeroOption;
	HeroItemAttrPolicy	m_HeroOptionAttr;
};

#endif
