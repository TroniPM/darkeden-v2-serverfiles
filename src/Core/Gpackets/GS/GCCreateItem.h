//////////////////////////////////////////////////////////////////////////////
// Filename    : GCCreateItem.h 
// Written By  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_CREATE_ITEM_H__
#define __GC_CREATE_ITEM_H__

#include "Packet.h"
#include "PacketFactory.h"
#include <list>

//////////////////////////////////////////////////////////////////////////////
// class GCCreateItem;
//////////////////////////////////////////////////////////////////////////////

class GCCreateItem : public Packet 
{
public:
	GCCreateItem() ;

public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_CREATE_ITEM; }
	PacketSize_t getPacketSize()  
	{ 
		return szObjectID +  // 아이템 오브젝트 ID
			szBYTE +         // 아이템 클래스
			szItemType +     // 아이템 타입
			szBYTE + m_OptionType.size() +   // 아이템 옵션
			szBYTE + m_OptionType2.size() +   // 아이템 옵션
			szDurability +   // 아이템 내구도
			szSilver +       // 아이템 은 도금량
			szGrade +       // 아이템 등급
			szEnchantLevel + // 아이템 인챈트 레벨
			szEnchantLevel + // 아이템 인챈트 레벨
			szEnchantLevel + // 아이템 인챈트 레벨
			szItemNum +      // 아이템 숫자
			szCoordInven +   // 아이템 X 좌표
			szCoordInven;    // 아이템 Y 좌표
	}
	string getPacketName()  { return "GCCreateItem"; }
	string toString() ;

public:
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	BYTE getItemClass()  { return m_ItemClass; }
	void setItemClass(BYTE ItemClass)  { m_ItemClass = ItemClass; }

	ItemType_t getItemType()  { return m_ItemType; }
	void setItemType(ItemType_t ItemType)  { m_ItemType = ItemType; }

	int getOptionTypeSize()  { return m_OptionType.size(); }
	const list<OptionType_t>& getOptionType()  { return m_OptionType; }
	OptionType_t popOptionType() 
	{
		if (m_OptionType.empty()) return 0;
		OptionType_t optionType = m_OptionType.front();
		m_OptionType.pop_front();
		return optionType;
	}
	void addOptionType(OptionType_t OptionType)  { m_OptionType.push_back( OptionType ); }
	void setOptionType(const list<OptionType_t>& OptionTypes)  { m_OptionType = OptionTypes; }

	int getOptionTypeSize2()  { return m_OptionType2.size(); }
	const list<OptionType_t>& getOptionType2()  { return m_OptionType2; }
	OptionType_t popOptionType2() 
	{
		if (m_OptionType2.empty()) return 0;
		OptionType_t optionType2 = m_OptionType2.front();
		m_OptionType2.pop_front();
		return optionType2;
	}
	void addOptionType2(OptionType_t OptionType)  { m_OptionType2.push_back( OptionType ); }
	void setOptionType2(const list<OptionType_t>& OptionTypes)  { m_OptionType2 = OptionTypes; }

	Durability_t getDurability()  { return m_Durability; }
	void setDurability(Durability_t Durability)  { m_Durability = Durability; }

	Silver_t getSilver()  { return m_Silver; }
	void setSilver(Silver_t silver)  { m_Silver = silver; }

	Grade_t getGrade()  { return m_Grade; }
	void setGrade(Grade_t silver)  { m_Grade = silver; }

	EnchantLevel_t getEnchantLevel()  { return m_EnchantLevel; }
	void setEnchantLevel(EnchantLevel_t level)  { m_EnchantLevel = level; }

	EnchantLevel_t getHeroOption()  { return m_HeroOption; }
	void setHeroOption(EnchantLevel_t level)  { m_HeroOption= level; }

	EnchantLevel_t getHeroOptionAttr()  { return m_HeroOptionAttr; }
	void setHeroOptionAttr(EnchantLevel_t level)  { m_HeroOptionAttr = level; }

	ItemNum_t getItemNum()  { return m_ItemNum; }
	void setItemNum(ItemNum_t num)  { m_ItemNum = num; }

	CoordInven_t getInvenX()  { return m_InvenX; }
	void setInvenX(CoordInven_t InvenX)  { m_InvenX = InvenX; }

	CoordInven_t getInvenY()  { return m_InvenY; }
	void setInvenY(CoordInven_t InvenY)  { m_InvenY = InvenY; }

private:
	ObjectID_t     		m_ObjectID;     // 오브젝트 ID
	BYTE           		m_ItemClass;    // 아이템 클래스
	ItemType_t     		m_ItemType;     // 아이템 타입
	list<OptionType_t>  m_OptionType;   // 옵션 타입
	list<OptionType_t>  m_OptionType2;   // 옵션 타입
	Durability_t   		m_Durability;   // 내구성
	Silver_t       		m_Silver;       // 은 도금량
	Grade_t       		m_Grade;       // 아이템 등급
	EnchantLevel_t 		m_EnchantLevel; // 인챈트 레벨
	EnchantLevel_t 		m_HeroOption; // 인챈트 레벨
	EnchantLevel_t		m_HeroOptionAttr; // 인챈트 레벨
	ItemNum_t      		m_ItemNum;      // 아이템의 숫자
	CoordInven_t   		m_InvenX;       // 인벤토리 X 좌표
	CoordInven_t   		m_InvenY;       // 인벤토리 Y 좌표
	
};


//////////////////////////////////////////////////////////////////////////////
// class GCCreateItemFactory;
//////////////////////////////////////////////////////////////////////////////

class GCCreateItemFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCCreateItem(); }
	string getPacketName()  { return "GCCreateItem"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_CREATE_ITEM; }
	PacketSize_t getPacketMaxSize()  
	{ 
		return szObjectID +  // 아이템 오브젝트 ID
			szBYTE +         // 아이템 클래스
			szItemType +     // 아이템 타입
			szBYTE + 255 +   // 아이템 옵션
			szBYTE + 255 +   // 아이템 옵션
			szDurability +   // 아이템 내구도
			szSilver +       // 아이템 은 도금량
			szGrade +       // 아이템 등급
			szEnchantLevel + // 아이템 인챈트 레벨
			szEnchantLevel + // 아이템 인챈트 레벨
			szEnchantLevel + // 아이템 인챈트 레벨
			szItemNum +      // 아이템 숫자
			szCoordInven +   // 아이템 X 좌표
			szCoordInven;    // 아이템 Y 좌표
	}
};


//////////////////////////////////////////////////////////////////////////////
// class GCCreateItemHandler;
//////////////////////////////////////////////////////////////////////////////

class GCCreateItemHandler 
{
public:
	static void execute(GCCreateItem* pPacket, Player* pPlayer);

};

#endif
