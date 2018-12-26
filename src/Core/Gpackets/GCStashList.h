//////////////////////////////////////////////////////////////////////////////
// Filename    : GCStashList.h 
// Written By  : �輺��
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_STASH_LIST_H__
#define __GC_STASH_LIST_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "SubItemInfo.h"
#include <list>

typedef struct _STASHITEM
{
	int getPacketSize() const
	{ 
		return szObjectID + 
				szBYTE + 
				szItemType + 
				szBYTE + optionType.size() +
				szBYTE + optionType2.size() +   // ������ �ɼ�
				szDurability +
				szItemNum +
				szSilver +
				szGrade +
				szEnchantLevel +
				szEnchantLevel + // ������ ��æƮ ����
				szEnchantLevel; // ������ ��æƮ ����
	}

	static int getPacketMaxSize() 
	{ 
		return szObjectID + 
				szBYTE + 
				szItemType + 
				szBYTE + 255 +
				szBYTE + 255 +
				szDurability +
				szItemNum +
				szSilver +
				szGrade +
				szEnchantLevel +
				szEnchantLevel + // ������ ��æƮ ����
				szEnchantLevel; // ������ ��æƮ ����
	}

	ObjectID_t     		objectID;
	BYTE           		itemClass;
	ItemType_t     		itemType;
	list<OptionType_t>  optionType;
	list<OptionType_t>  optionType2;
	Durability_t   		durability;
	ItemNum_t      		num;
	Silver_t       		silver;
	Grade_t       		grade;
	EnchantLevel_t 		enchantLevel;
	EnchantLevel_t 		HeroOption; // ��æƮ ����
	EnchantLevel_t		HeroOptionAttr; // ��æƮ ����
} STASHITEM;

//////////////////////////////////////////////////////////////////////////////
// class GCStashList;
//////////////////////////////////////////////////////////////////////////////

class Item;

class GCStashList : public Packet 
{
public:
	GCStashList() ;
	virtual ~GCStashList() ;

	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_STASH_LIST; }
	PacketSize_t getPacketSize() ;
	string getPacketName()  { return "GCStashList"; }
	string toString() ;

public:
	bool isExist(BYTE rack, BYTE index) ;

	STASHITEM getStashItem(BYTE rack, BYTE index) ;
	void setStashItem(BYTE rack, BYTE index, Item* pItem) ;

	list<SubItemInfo*>& getSubItems(BYTE rack, BYTE index) ;

	BYTE getSubItemCount(BYTE rack, BYTE index) ;

	Gold_t getStashGold()  { return m_StashGold; }
	void setStashGold(Gold_t gold) throw() { m_StashGold = gold; }

	BYTE getStashNum()  { return m_StashNum; }
	void setStashNum(BYTE num) throw() { m_StashNum = num; }
	
private:
	bool               m_bExist[STASH_RACK_MAX][STASH_INDEX_MAX];
	STASHITEM          m_pItems[STASH_RACK_MAX][STASH_INDEX_MAX];
	list<SubItemInfo*> m_pSubItems[STASH_RACK_MAX][STASH_INDEX_MAX];
	BYTE               m_SubItemsCount[STASH_RACK_MAX][STASH_INDEX_MAX];
	Gold_t             m_StashGold;
	BYTE               m_StashNum;
};


//////////////////////////////////////////////////////////////////////////////
// class GCStashListFactory;
//////////////////////////////////////////////////////////////////////////////

class GCStashListFactory : public PacketFactory 
{
public :
	Packet* createPacket() throw() { return new GCStashList(); }
	string getPacketName()  { return "GCStashList"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_STASH_LIST; }
	PacketSize_t getPacketMaxSize()  
	{ 
		PacketSize_t size = 0;
		PacketSize_t unit_size = 
			szBYTE*2 +                  // rack�� �ε���
			//sizeof(STASHITEM) +         // ���� ����
			STASHITEM::getPacketMaxSize() +
			szBYTE +                    // ��Ʈ�� ����ִ� �������� ����
			SubItemInfo::getSize()* 8; // ��Ʈ ������(8���� �ƽ�)
		
		size += szBYTE; // �������� ����
		size += szBYTE; // �� �������� ����
		size += unit_size* STASH_RACK_MAX* STASH_INDEX_MAX; // �������� �� �� �ִٸ�...
		size += szGold; // ��

		return size;
	}

};


//////////////////////////////////////////////////////////////////////////////
// class GCStashListHandler;
//////////////////////////////////////////////////////////////////////////////

class GCStashListHandler 
{
public :
	static void execute(GCStashList* pPacket, Player* pPlayer) ;

};

#endif
