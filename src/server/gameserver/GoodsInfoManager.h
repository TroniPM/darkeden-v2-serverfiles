//////////////////////////////////////////////////////////////////////////////
// Filename    : GoodsInfo.h
// Written By  : bezz
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GOODS_INFO_H__
#define __GOODS_INFO_H__

#include "Exception.h"
#include "Types.h"
#include "Item.h"

#include <list>
#include <hash_map>

//////////////////////////////////////////////////////////////////////////////
// Class GoodsInfo
//////////////////////////////////////////////////////////////////////////////

class GoodsInfo 
{
public:
	GoodsInfo();
	~GoodsInfo();

public:
	DWORD getID() const { return m_ID; }
	void setID(DWORD id) { m_ID = id; }

	string getName() const { return m_Name ; }
	void setName(string name) { m_Name = name ; }

	Item::ItemClass getItemClass() const { return m_ItemClass; }
	void setItemClass( Item::ItemClass itemClass ) { m_ItemClass = itemClass; }

	ItemType_t getItemType() const { return m_ItemType; }
	void setItemType( ItemType_t itemType ) { m_ItemType = itemType; }

	Grade_t getGrade() const { return m_Grade; }
	void setGrade( Grade_t grade ) { m_Grade = grade; }

	Silver_t getSilver()  { return m_Silver; }
	void setSilver(Silver_t amount) throw() { m_Silver = amount;}

	const list<OptionType_t>& getOptionTypeList() const { return m_OptionTypes; }
	void setOptionTypeList( const list<OptionType_t>& optionTypes ) { m_OptionTypes = optionTypes; }

	const list<OptionType_t>& getOptionTypeList2() const { return m_OptionTypes2; }
	void setOptionTypeList2( const list<OptionType_t>& optionTypes ) { m_OptionTypes2 = optionTypes; }

	EnchantLevel_t getHeroOption()  { return m_HeroOption;}
	void setHeroOption(EnchantLevel_t HeroOption) throw() { m_HeroOption = HeroOption; }

	EnchantLevel_t getHeroOptionAttr()  { return m_HeroOptionAttr;}
	void setHeroOptionAttr(EnchantLevel_t HeroOptionAttr) throw() { m_HeroOptionAttr = HeroOptionAttr; }

	EnchantLevel_t getEnchantLevel()  { return m_EnchantLevel;}
	void setEnchantLevel(EnchantLevel_t level) throw() { m_EnchantLevel = level; }

	int getNum() const { return m_Num; }
	void setNum( int num ) { m_Num = num; }

	bool isTimeLimit() const { return m_bTimeLimit; }
	void setTimeLimit( bool bTimeLimit = true ) { m_bTimeLimit = bTimeLimit; }

	int getHour() const { return m_Hour; }
	void setHour( int hour ) { m_Hour = hour; }

	// toString
	string toString() const ;

private:
	DWORD					m_ID;			// Type
	string					m_Name;			// Name
	Item::ItemClass			m_ItemClass;	// ItemClass
	ItemType_t				m_ItemType;		// ItemType
	Grade_t					m_Grade;		// Grade
	list<OptionType_t>		m_OptionTypes;	// OptionType list
	list<OptionType_t>		m_OptionTypes2;	// OptionType list
	int 					m_Num;
	Silver_t	m_Silver;
	EnchantLevel_t	m_EnchantLevel;
	EnchantLevel_t	m_HeroOption;
	EnchantLevel_t	m_HeroOptionAttr;
	bool					m_bTimeLimit;	// 시간제한 아이템인가?
	int						m_Hour;			// 사용 제한 시간
};

//////////////////////////////////////////////////////////////////////////////
// Class GoodsInfoManager
//////////////////////////////////////////////////////////////////////////////

class GoodsInfoManager 
{
public:
	typedef hash_map<DWORD, GoodsInfo*>			HashMapGoodsInfo;
	typedef HashMapGoodsInfo::iterator			HashMapGoodsInfoItr;
	typedef HashMapGoodsInfo::const_iterator	HashMapGoodsInfoConstItr;

public:
	GoodsInfoManager() ;
	~GoodsInfoManager() ;

public:

	// initialize Manager
	void init();

	// void load() ;
	void load();
	
	// clear list
	void clear() ;

	// add GoodsInfo
	void addGoodsInfo(GoodsInfo* pGoodsInfo) throw(DuplicatedException, Error);

	// get GoodsInfo
	GoodsInfo* getGoodsInfo( DWORD id ) ;

	// toString for Debug
	string toString() ;

private:
	HashMapGoodsInfo		m_GoodsInfos;

};

// Global Variable Definition
extern GoodsInfoManager* g_pGoodsInfoManager;

#endif	// __SKILL_INFO_MANAGER_H__
