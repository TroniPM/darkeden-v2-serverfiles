#ifndef __ITEM_POLICIES_H__
#define __ITEM_POLICIES_H__

#include "Types.h"
#include <list>

template <typename T>
class OneValuePolicy
{
public:
	OneValuePolicy() { }
	OneValuePolicy(T init) : m_Value(init) { }

	bool	hasValue() const { return true; }
	T		getValue() const { return m_Value; }
	void	setValue(T value) { m_Value = value; }

private:
	T		m_Value;
};

template <typename T, T initValue>
class NoValuePolicy
{
public:
	bool	hasValue() const { return false; }
	T		getValue() const { return initValue; }
	void	setValue(T value) { }
};

typedef NoValuePolicy<ItemNum_t, 1> NoStack;
typedef OneValuePolicy<ItemNum_t> Stackable;

// Stack Policies
/*class NoStack
{
public:
	bool isStackable() const { return false; }
	ItemNum_t getNum() const { return 1; }
	void setNum(ItemNum_t num) { }
};

class Stackable
{
public:
	Stackable() : m_Num(1) { }
	bool isStackable() const { return true; }
	ItemNum_t getNum() const { return m_Num; }
	void setNum(ItemNum_t num) { m_Num = num; }

private:
	ItemNum_t m_Num;
};*/

typedef NoValuePolicy<Durability_t, 1> NoDurability;
typedef OneValuePolicy<Durability_t> HasDurability;

// Durability Policies
/*class NoDurability
{
public:
	bool hasDurability() const { return false; }
	Durability_t getDurability() const { return 1; }
	void setDurability(Durability_t dur) { }
};

class HasDurability
{
public:
	bool hasDurability() const { return true; }
	Durability_t getDurability() const { return m_Durability; }
	void setDurability(Durability_t dur) { m_Durability = dur; }

private:
	Durability_t m_Durability;
};*/

// Option Policies
class NoOption
{
public:
	bool						hasOptionType()  { return false; }
	int							getOptionTypeSize()  { return 0; }
	int							getRandomOptionType()  { return 0; }
	const list<OptionType_t>&	getOptionTypeList()  { static list<OptionType_t> nullList; return nullList; }
	OptionType_t				getFirstOptionType()  { return 0; }
	void						removeOptionType(OptionType_t OptionType) throw() { }
	void						changeOptionType(OptionType_t currentOptionType, OptionType_t newOptionType) throw() { }
	void						addOptionType(OptionType_t OptionType) throw() { }
	void						setOptionType(const list<OptionType_t>& OptionType) throw() { }
};

class HasOption
{
public:
	bool						hasOptionType()  { return !m_OptionType.empty(); }
	int							getOptionTypeSize()  { return m_OptionType.size(); }
	int							getRandomOptionType() 
	{
		if (m_OptionType.empty())
			return 0;
		int pos = rand()%m_OptionType.size();
		list<OptionType_t>::const_iterator itr = m_OptionType.begin();
		for (int i=0; i<pos; i++) itr++;
		return *itr;
	}

	const	list<OptionType_t>& getOptionTypeList()  { return m_OptionType; }
	OptionType_t				getFirstOptionType()  { if (m_OptionType.empty()) return 0; return m_OptionType.front(); }
	void						removeOptionType(OptionType_t OptionType) throw() { list<OptionType_t>::iterator itr = find(m_OptionType.begin(), m_OptionType.end(), OptionType); if (itr!=m_OptionType.end()) m_OptionType.erase(itr); }
	void						changeOptionType(OptionType_t currentOptionType, OptionType_t newOptionType) throw() { list<OptionType_t>::iterator itr = find(m_OptionType.begin(), m_OptionType.end(), currentOptionType); if (itr!=m_OptionType.end()) *itr=newOptionType; }
	void						addOptionType(OptionType_t OptionType) throw() { m_OptionType.push_back(OptionType); }
	void						setOptionType(const list<OptionType_t>& OptionType) throw() { m_OptionType = OptionType; }

private:
	list<OptionType_t>   m_OptionType;
};

// Grade Policies
class NoGrade : public NoValuePolicy<Grade_t, -1>
{
public:
//	Grade_t	getGrade() const { return -1; }
//	void	setGrade(Grade_t Grade) { }

public:
	// �������� �Ӽ��� ��ġ�� ����
	int		getDurabilityOffset() const { return 0; }
	int		getDamageOffset() const { return 0; }
	int		getCriticalOffset() const { return 0; }
	int		getDefenseOffset() const { return 0; }
	int		getProtectionOffset() const { return 0; }
	Luck_t	getLuck() const { return 0; }
};

class HasGrade : public OneValuePolicy<Grade_t>
{
public:
	HasGrade() : OneValuePolicy<Grade_t>(4) { }

//	Grade_t	getGrade() const { return m_Grade; }
//	void	setGrade(Grade_t Grade) { m_Grade = Grade; }

public:
	// �������� �Ӽ��� ��ġ�� ����
	int		getDurabilityOffset() const { return 0; }
	int		getDamageOffset() const { return 0; }
	int		getCriticalOffset() const { return 0; }
	int		getDefenseOffset() const { return 0; }
	int		getProtectionOffset() const { return 0; }
	Luck_t	getLuck() const { return 0; }

private:
	Grade_t	m_Grade;
};

class WeaponGrade : public HasGrade
{
public:
	// �������� �Ӽ��� ��ġ�� ����
	int		getDurabilityOffset() const { return (getValue()-4)*1000; }
	int		getDamageOffset() const { return (getValue()-4); }
	int		getCriticalOffset() const { return (getValue()-4)*2; }
};

template <int DefensePitch, int DefenseGrade, int ProtectionPitch, int ProtectionGrade, int DurabilityPitch>
class ArmorGrade : public HasGrade
{
public:
	// �������� �Ӽ��� ��ġ�� ����
	int		getDurabilityOffset() const { return (getValue()-4)*DurabilityPitch; }
	int		getDefenseOffset() const { return (getValue()-4)/DefenseGrade*DefensePitch; }
	int		getProtectionOffset() const { return (getValue()-4)/ProtectionGrade*ProtectionPitch; }
};

typedef ArmorGrade<2,1,1,1,1000> ClothGrade;
typedef ArmorGrade<1,1,1,2,500> GroceryGrade;

class AccessoryGrade : public HasGrade
{
public:
	// �������� �Ӽ��� ��ġ�� ����
	int		getDurabilityOffset() const { return (getValue()-4)*1000; }
	Luck_t	getLuck() const { return (getValue()-4); }
};

// Attacking Stats Policies
class NoAttacking
{
public:
	BYTE		getBulletCount()  { return 0; }
	void		setBulletCount(BYTE bulletCount) throw() { }

	bool		isSilverWeapon()  { return false; }
	Silver_t	getSilver()  { return 0; }
	void		setSilver(Silver_t amount) throw() { }

	bool		isGun()  { return false; }

	Damage_t	getBonusDamage()  { return 0; }
	void		setBonusDamage(Damage_t BonusDamage) throw() { }
};

class Weapon
{
public:
	Weapon() : m_BonusDamage(0) { }

	BYTE		getBulletCount()  { return 0; }
	void		setBulletCount(BYTE bulletCount) throw() { }

	bool		isGun()  { return false; }

	bool		isSilverWeapon()  { return false; }
	Silver_t	getSilver()  { return 0; }
	void		setSilver(Silver_t amount) throw() { }

	Damage_t	getBonusDamage()  { return m_BonusDamage; }
	void		setBonusDamage(Damage_t BonusDamage) throw() { m_BonusDamage = BonusDamage; }

private:
	Damage_t	m_BonusDamage;
};

class SlayerWeapon : public Weapon
{
public:
	SlayerWeapon() : m_Silver(0) { }

	bool		isSilverWeapon()  { return true; }
	Silver_t	getSilver()  { return m_Silver; }
	void		setSilver(Silver_t amount) throw() { m_Silver = amount; }

private:
	Silver_t	m_Silver;
};

class SlayerGun : public SlayerWeapon
{
public:
	SlayerGun() : m_Bullet(0) { }

	BYTE	getBulletCount()  { return m_Bullet; }
	void	setBulletCount(BYTE bulletCount) throw() { m_Bullet = bulletCount; }

	bool	isGun()  { return true; }

private:
	BYTE	m_Bullet;
};

typedef OneValuePolicy<EnchantLevel_t> HasEnchantLevel;
typedef NoValuePolicy<EnchantLevel_t, 0> NoEnchantLevel;

// Option Policies
class NoOption2
{
public:
	bool						hasOptionType2()  { return false; }
	int							getOptionTypeSize2()  { return 0; }
	int							getRandomOptionType2()  { return 0; }
	const list<OptionType_t>&	getOptionTypeList2()  { static list<OptionType_t> nullList; return nullList; }
	OptionType_t				getFirstOptionType2()  { return 0; }
	void						removeOptionType2(OptionType_t OptionType) throw() { }
	void						changeOptionType2(OptionType_t currentOptionType, OptionType_t newOptionType) throw() { }
	void						addOptionType2(OptionType_t OptionType) throw() { }
	void						setOptionType2(const list<OptionType_t>& OptionType) throw() { }
};

class HasOption2
{
public:
	bool						hasOptionType2()  { return !m_OptionType2.empty(); }
	int							getOptionTypeSize2()  { return m_OptionType2.size(); }
	int							getRandomOptionType2() 
	{
		if (m_OptionType2.empty())
			return 0;
		int pos = rand()%m_OptionType2.size();
		list<OptionType_t>::const_iterator itr = m_OptionType2.begin();
		for (int i=0; i<pos; i++) itr++;
		return *itr;
	}

	const	list<OptionType_t>& getOptionTypeList2()  { return m_OptionType2; }
	OptionType_t				getFirstOptionType2()  { if (m_OptionType2.empty()) return 0; return m_OptionType2.front(); }
	void						removeOptionType2(OptionType_t OptionType) throw() { list<OptionType_t>::iterator itr = find(m_OptionType2.begin(), m_OptionType2.end(), OptionType); if (itr!=m_OptionType2.end()) m_OptionType2.erase(itr); }
	void						changeOptionType2(OptionType_t currentOptionType, OptionType_t newOptionType) throw() { list<OptionType_t>::iterator itr = find(m_OptionType2.begin(), m_OptionType2.end(), currentOptionType); if (itr!=m_OptionType2.end()) *itr=newOptionType; }
	void						addOptionType2(OptionType_t OptionType) throw() { m_OptionType2.push_back(OptionType); }
	void						setOptionType2(const list<OptionType_t>& OptionType) throw() { m_OptionType2 = OptionType; }

private:
	list<OptionType_t>   m_OptionType2;
};

typedef NoValuePolicy<EnchantLevel_t, 0> NoHeroOption;
typedef OneValuePolicy<EnchantLevel_t> HasHeroOption;

typedef NoValuePolicy<EnchantLevel_t, 0> NoHeroOptionAttr;
typedef OneValuePolicy<EnchantLevel_t> HasHeroOptionAttr;
#endif
