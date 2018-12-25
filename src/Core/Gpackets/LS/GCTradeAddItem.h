////////////////////////////////////////////////////////////////////////////////
// Filename    : GCTradeAddItem.h 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __GC_TRADE_ADD_ITEM_H__
#define __GC_TRADE_ADD_ITEM_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "SubItemInfo.h"
#include <list>

////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeAddItem;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeAddItem : public Packet 
{
public:
	GCTradeAddItem() throw();
	~GCTradeAddItem() throw();
	
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_GC_TRADE_ADD_ITEM; }
	PacketSize_t getPacketSize()  
	{ 
		PacketSize_t size = 0;
		size += szObjectID;                           // m_TargetObjectID
		size += szCoordInven;                         // m_X
		size += szCoordInven;                         // m_Y
		size += szObjectID;                           // m_ItemObjectID
		size += szBYTE;                               // m_ItemClass
		size += szItemType;                           // m_ItemType
		size += szBYTE + m_OptionType.size();         // m_OptionType
		size += szBYTE + m_OptionType2.size();         // m_OptionType
		size += szDurability;                         // m_Durability
		size += szItemNum;                            // m_ItemNum
		size += szSilver;                             // silver coating amount
		size += szGrade;                             // ������ ���
		size += szEnchantLevel;                       // enchant level
		size += szEnchantLevel;                       // enchant level
		size += szEnchantLevel;                       // enchant level
		size += szBYTE;                               // m_ListNum
		size +=(SubItemInfo::getSize()* m_ListNum); // list<SubItemInfo*> m_InfoList;
		return size;
	}
	string getPacketName()  { return "GCTradeAddItem"; }
	string toString() ;

public:
	ObjectID_t getTargetObjectID()  { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id) throw() { m_TargetObjectID = id; }

	CoordInven_t getX()  { return m_X; }
	void setX(CoordInven_t x) throw() { m_X = x; }

	CoordInven_t getY()  { return m_Y; }
	void setY(CoordInven_t y) throw() { m_Y = y; }

	ObjectID_t getItemObjectID()  { return m_ItemObjectID; }
	void setItemObjectID(ObjectID_t id) throw() { m_ItemObjectID = id; }

	BYTE getItemClass()  { return m_ItemClass; }
	void setItemClass(BYTE IClass) throw() { m_ItemClass = IClass; }

	ItemType_t getItemType()  { return m_ItemType; }
	void setItemType(ItemType_t itemType) { m_ItemType = itemType; }

	int getOptionTypeSize()  { return m_OptionType.size(); }
	const list<OptionType_t>& getOptionType()  { return m_OptionType; }
	OptionType_t popOptionType() throw()
	{
		if (m_OptionType.empty()) return 0;
		OptionType_t optionType = m_OptionType.front();
		m_OptionType.pop_front();
		return optionType;
	}
	void addOptionType(OptionType_t otype) { m_OptionType.push_back( otype ); }
	void setOptionType(const list<OptionType_t>& OptionTypes) throw() { m_OptionType = OptionTypes; }

	int getOptionTypeSize2()  { return m_OptionType2.size(); }
	const list<OptionType_t>& getOptionType2()  { return m_OptionType2; }
	OptionType_t popOptionType2() throw()
	{
		if (m_OptionType2.empty()) return 0;
		OptionType_t optionType2 = m_OptionType2.front();
		m_OptionType2.pop_front();
		return optionType2;
	}
	void addOptionType2(OptionType_t otype) { m_OptionType2.push_back( otype ); }
	void setOptionType2(const list<OptionType_t>& OptionTypes) throw() { m_OptionType2 = OptionTypes; }

	Durability_t getDurability()  { return m_Durability; }
	void setDurability(Durability_t dur) throw() { m_Durability = dur; }

	ItemNum_t getItemNum()  { return m_ItemNum; }
	void setItemNum(ItemNum_t itemNum) { m_ItemNum = itemNum; }

	Silver_t getSilver()  { return m_Silver; }
	void setSilver(Silver_t amount) throw() { m_Silver = amount; }

	Grade_t getGrade()  { return m_Grade; }
	void setGrade(Grade_t grade) throw() { m_Grade = grade; }

	EnchantLevel_t getEnchantLevel()  { return m_EnchantLevel; }
	void setEnchantLevel(EnchantLevel_t level) throw() { m_EnchantLevel = level; }

	EnchantLevel_t getHeroOption()  { return m_HeroOption; }
	void setHeroOption(EnchantLevel_t level) throw() { m_HeroOption= level; }

	EnchantLevel_t getHeroOptionAttr()  { return m_HeroOptionAttr; }
	void setHeroOptionAttr(EnchantLevel_t level) throw() { m_HeroOptionAttr = level; }

	BYTE getListNum()  { return m_ListNum; }
	void setListNum(BYTE num) throw() { m_ListNum = num; }

	void addListElement(SubItemInfo* pInfo) throw() { m_InfoList.push_back(pInfo); }
	void clearList() throw() { m_InfoList.clear(); m_ListNum = 0; }

	SubItemInfo* popListElement() throw() 
	{
		SubItemInfo* pInfo = m_InfoList.front();
		m_InfoList.pop_front();
		return pInfo;
	}

private:
	ObjectID_t         m_TargetObjectID;  // ��ȯ�� �ϰ� �ִ� ������ OID
	ObjectID_t         m_ItemObjectID;    // ������ OID
	CoordInven_t       m_X;               // �κ��丮������ X ��ǥ
	CoordInven_t       m_Y;               // �κ��丮������ Y ��ǥ
	BYTE               m_ItemClass;       // ������ Ŭ����
	ItemType_t         m_ItemType;        // ������ Ÿ��
	list<OptionType_t> m_OptionType;      // �ɼ� Ÿ��
	list<OptionType_t> m_OptionType2;      // �ɼ� Ÿ��
	Durability_t       m_Durability;      // ������
	ItemNum_t          m_ItemNum;         // ������ ����
	Silver_t           m_Silver;          // silver coating amount
	Grade_t           m_Grade;          // ������ ���
	EnchantLevel_t     m_EnchantLevel;    // enchant level
	EnchantLevel_t 		m_HeroOption; // ��æƮ ����
	EnchantLevel_t		m_HeroOptionAttr; // ��æƮ ����
	BYTE               m_ListNum;         // ��Ʈ�� ���, �ȿ� �ִ� �������� ����
	list<SubItemInfo*> m_InfoList;        // ��Ʈ�� ���, �ȿ� �ִ� �������� ����

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeAddItemFactory;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeAddItemFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCTradeAddItem(); }
	string getPacketName()  { return "GCTradeAddItem"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_TRADE_ADD_ITEM; }
	PacketSize_t getPacketMaxSize()  
	{ 
		PacketSize_t size = 0;
		size += szObjectID;                   // m_TargetObjectID
		size += szCoordInven;                 // m_X
		size += szCoordInven;                 // m_Y
		size += szObjectID;                   // m_ItemObjectID
		size += szBYTE;                       // m_ItemClass
		size += szItemType;                   // m_ItemType
		size += szBYTE + 255;                 // m_OptionType
		size += szBYTE + 255;                 // m_OptionType
		size += szDurability;                 // m_Durability
		size += szItemNum;                    // m_ItemNum
		size += szSilver;                     // silver coating amount
		size += szGrade;                             // ������ ���
		size += szEnchantLevel;               // enchant level
		size += szEnchantLevel;                       // enchant level
		size += szEnchantLevel;                       // enchant level
		size += szBYTE;                       // m_ListNum
		size +=(SubItemInfo::getSize()* 8); // list<SubItemInfo*> m_InfoList;
		return size;
	}
};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeAddItemHandler;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeAddItemHandler 
{
public:
	static void execute(GCTradeAddItem* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
