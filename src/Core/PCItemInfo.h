//////////////////////////////////////////////////////////////////////////////
// Filename    : PCItemInfo.h
// Written By  : elca
// Description :
// ������ �ϳ��� ���� ������ ������ �ִ� ��Ŷ�̴�.
// ��ǥ�����, ����Ʈ�� ���� ������ ������ ���� �ʴ�.
// �κ��丮�� ���õ� ���� �������� ��ӵǾ� ���ȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __SLAYER_ITEM_INFO_H__
#define __SLAYER_ITEM_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "SubItemInfo.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
// class PCItemInfo
//////////////////////////////////////////////////////////////////////////////

class PCItemInfo 
{
public:
	PCItemInfo() ;
	virtual ~PCItemInfo() ;

public:
	void read (SocketInputStream & iStream);
	void write (SocketOutputStream & oStream) ;

	string toString() ;

public:
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }
	ObjectID_t getObjectID()  { return m_ObjectID; }

	void setItemClass (BYTE IClass) throw() { m_IClass = IClass; }
	BYTE getItemClass ()  { return m_IClass; }

	void setItemType (ItemType_t ItemType) throw() { m_ItemType = ItemType; }
	ItemType_t getItemType()  { return m_ItemType; }

	void addOptionType(OptionType_t OptionType) throw() { m_OptionType.push_back( OptionType ); }
	void setOptionType(const list<OptionType_t>& OptionType) throw() { m_OptionType = OptionType; }
	int getOptionTypeSize()  { return m_OptionType.size(); }
	const list<OptionType_t>& getOptionType()  { return m_OptionType; }
	OptionType_t popOptionType() throw() 
	{ 
		if (m_OptionType.empty()) return 0;
		OptionType_t optionType = m_OptionType.front(); 
		m_OptionType.pop_front(); 
		return optionType; 
	}

	void addOptionType2(OptionType_t OptionType) throw() { m_OptionType2.push_back( OptionType ); }
	void setOptionType2(const list<OptionType_t>& OptionType) throw() { m_OptionType2 = OptionType; }
	int getOptionTypeSize2()  { return m_OptionType2.size(); }
	const list<OptionType_t>& getOptionType2()  { return m_OptionType2; }
	OptionType_t popOptionType2() throw() 
	{ 
		if (m_OptionType2.empty()) return 0;
		OptionType_t optionType2 = m_OptionType2.front(); 
		m_OptionType2.pop_front(); 
		return optionType2; 
	}

	void setSilver(Silver_t amount) throw() { m_Silver = amount; }
	Silver_t getSilver()  { return m_Silver; }

	void setGrade(Grade_t grade) throw() { m_Grade = grade; }
	Grade_t getGrade()  { return m_Grade; }

	void setDurability(Durability_t Durability) throw() { m_Durability = Durability; }
	Durability_t getDurability()  { return m_Durability; }

	void setEnchantLevel(EnchantLevel_t level) throw() { m_EnchantLevel = level; }
	EnchantLevel_t getEnchantLevel() throw() { return m_EnchantLevel; }

	void setHeroOption(EnchantLevel_t level) throw() { m_HeroOption = level; }
	EnchantLevel_t getHeroOption() throw() { return m_HeroOption; }

	void setHeroOptionAttr(EnchantLevel_t level) throw() { m_HeroOptionAttr = level; }
	EnchantLevel_t getHeroOptionAttr() throw() { return m_HeroOptionAttr; }

	void setItemNum(ItemNum_t ItemNum) throw() { m_ItemNum = ItemNum; }
	ItemNum_t getItemNum()  { return m_ItemNum; }

	void setMainColor(WORD MainColor) throw() { m_MainColor = MainColor; }
	WORD getMainColor()  { return m_MainColor; }

	BYTE getListNum()  { return m_ListNum; }
	void setListNum(BYTE ListNum) throw() { m_ListNum = ListNum; }

	void addListElement(SubItemInfo* pSubItemInfo) throw() 
	{ 
		m_SubItemInfoList.push_back(pSubItemInfo); 
		m_ListNum++;
	}

	void clearList() throw() { m_SubItemInfoList.clear(); m_ListNum = 0; }

	SubItemInfo* popFrontListElement() throw() 
	{ 
		SubItemInfo* TempSubItemInfo = m_SubItemInfoList.front(); 
		m_SubItemInfoList.pop_front(); 
		return TempSubItemInfo; 
	}

public:
	uint getSize() 
	{
		return szObjectID +
			szBYTE +
			szItemType + 
			szBYTE + m_OptionType.size() +
			szDurability +
			szSilver + 
			szGrade +
			szEnchantLevel +
			szItemNum +
			szWORD +
			szBYTE +
			SubItemInfo::getMaxSize()*m_ListNum +
			szBYTE + m_OptionType2.size() +
			szEnchantLevel +
			szEnchantLevel;
	}

	static uint getMaxSize() throw()
	{
		return szObjectID +
			szBYTE +
			szItemType + 
			szBYTE + 255 +
			szDurability +
			szSilver + 
			szGrade +
			szEnchantLevel +
			szItemNum +
			szWORD +
			szBYTE +
			SubItemInfo::getMaxSize()*8 +
			szBYTE + 255 +
			szEnchantLevel +
			szEnchantLevel;
	}


protected:
	ObjectID_t         m_ObjectID;         // item object id
	BYTE               m_IClass;           // item class
	ItemType_t         m_ItemType;         // item type
	list<OptionType_t> m_OptionType;       // item option type
	list<OptionType_t> m_OptionType2;       // item option type
	Durability_t       m_Durability;       // item durability
	Silver_t           m_Silver;           // silver coating amount
	Grade_t				m_Grade;			// ������ ���
	EnchantLevel_t     m_EnchantLevel;     // item enchant level
	EnchantLevel_t     m_HeroOption;     // item enchant level
	EnchantLevel_t     m_HeroOptionAttr;     // item enchant level
	ItemNum_t          m_ItemNum;          // number of item
	WORD               m_MainColor;        // item color
	BYTE               m_ListNum;          // number of sub item
	list<SubItemInfo*> m_SubItemInfoList;  // actual sub item info

};

#endif
