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
	GCCreateItem() throw();

public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_CREATE_ITEM; }
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szObjectID +  // ������ ������Ʈ ID
			szBYTE +         // ������ Ŭ����
			szItemType +     // ������ Ÿ��
			szBYTE + m_OptionType.size() +   // ������ �ɼ�
			szBYTE + m_OptionType2.size() +   // ������ �ɼ�
			szDurability +   // ������ ������
			szSilver +       // ������ �� ���ݷ�
			szGrade +       // ������ ���
			szEnchantLevel + // ������ ��æƮ ����
			szEnchantLevel + // ������ ��æƮ ����
			szEnchantLevel + // ������ ��æƮ ����
			szItemNum +      // ������ ����
			szCoordInven +   // ������ X ��ǥ
			szCoordInven;    // ������ Y ��ǥ
	}
	string getPacketName() const throw() { return "GCCreateItem"; }
	string toString() const throw();

public:
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	BYTE getItemClass() const throw() { return m_ItemClass; }
	void setItemClass(BYTE ItemClass) throw() { m_ItemClass = ItemClass; }

	ItemType_t getItemType() const throw() { return m_ItemType; }
	void setItemType(ItemType_t ItemType) throw() { m_ItemType = ItemType; }

	int getOptionTypeSize() const throw() { return m_OptionType.size(); }
	const list<OptionType_t>& getOptionType() const throw() { return m_OptionType; }
	OptionType_t popOptionType() throw()
	{
		if (m_OptionType.empty()) return 0;
		OptionType_t optionType = m_OptionType.front();
		m_OptionType.pop_front();
		return optionType;
	}
	void addOptionType(OptionType_t OptionType) throw() { m_OptionType.push_back( OptionType ); }
	void setOptionType(const list<OptionType_t>& OptionTypes) throw() { m_OptionType = OptionTypes; }

	int getOptionTypeSize2() const throw() { return m_OptionType2.size(); }
	const list<OptionType_t>& getOptionType2() const throw() { return m_OptionType2; }
	OptionType_t popOptionType2() throw()
	{
		if (m_OptionType2.empty()) return 0;
		OptionType_t optionType2 = m_OptionType2.front();
		m_OptionType2.pop_front();
		return optionType2;
	}
	void addOptionType2(OptionType_t OptionType) throw() { m_OptionType2.push_back( OptionType ); }
	void setOptionType2(const list<OptionType_t>& OptionTypes) throw() { m_OptionType2 = OptionTypes; }

	Durability_t getDurability() const throw() { return m_Durability; }
	void setDurability(Durability_t Durability) throw() { m_Durability = Durability; }

	Silver_t getSilver() const throw() { return m_Silver; }
	void setSilver(Silver_t silver) throw() { m_Silver = silver; }

	Grade_t getGrade() const throw() { return m_Grade; }
	void setGrade(Grade_t silver) throw() { m_Grade = silver; }

	EnchantLevel_t getEnchantLevel() const throw() { return m_EnchantLevel; }
	void setEnchantLevel(EnchantLevel_t level) throw() { m_EnchantLevel = level; }

	EnchantLevel_t getHeroOption() const throw() { return m_HeroOption; }
	void setHeroOption(EnchantLevel_t level) throw() { m_HeroOption= level; }

	EnchantLevel_t getHeroOptionAttr() const throw() { return m_HeroOptionAttr; }
	void setHeroOptionAttr(EnchantLevel_t level) throw() { m_HeroOptionAttr = level; }

	ItemNum_t getItemNum() const throw() { return m_ItemNum; }
	void setItemNum(ItemNum_t num) throw() { m_ItemNum = num; }

	CoordInven_t getInvenX() const throw() { return m_InvenX; }
	void setInvenX(CoordInven_t InvenX) throw() { m_InvenX = InvenX; }

	CoordInven_t getInvenY() const throw() { return m_InvenY; }
	void setInvenY(CoordInven_t InvenY) throw() { m_InvenY = InvenY; }

private:
	ObjectID_t     		m_ObjectID;     // ������Ʈ ID
	BYTE           		m_ItemClass;    // ������ Ŭ����
	ItemType_t     		m_ItemType;     // ������ Ÿ��
	list<OptionType_t>  m_OptionType;   // �ɼ� Ÿ��
	list<OptionType_t>  m_OptionType2;   // �ɼ� Ÿ��
	Durability_t   		m_Durability;   // ������
	Silver_t       		m_Silver;       // �� ���ݷ�
	Grade_t       		m_Grade;       // ������ ���
	EnchantLevel_t 		m_EnchantLevel; // ��æƮ ����
	EnchantLevel_t 		m_HeroOption; // ��æƮ ����
	EnchantLevel_t 		m_HeroOptionAttr; // ��æƮ ����
	ItemNum_t      		m_ItemNum;      // �������� ����
	CoordInven_t   		m_InvenX;       // �κ��丮 X ��ǥ
	CoordInven_t   		m_InvenY;       // �κ��丮 Y ��ǥ
	
};


//////////////////////////////////////////////////////////////////////////////
// class GCCreateItemFactory;
//////////////////////////////////////////////////////////////////////////////

class GCCreateItemFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCCreateItem(); }
	string getPacketName() const throw() { return "GCCreateItem"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_CREATE_ITEM; }
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szObjectID +  // ������ ������Ʈ ID
			szBYTE +         // ������ Ŭ����
			szItemType +     // ������ Ÿ��
			szBYTE + 255 +   // ������ �ɼ�
			szBYTE + 255 +   // ������ �ɼ�
			szDurability +   // ������ ������
			szSilver +       // ������ �� ���ݷ�
			szGrade +       // ������ ���
			szEnchantLevel + // ������ ��æƮ ����
			szEnchantLevel + // ������ ��æƮ ����
			szEnchantLevel + // ������ ��æƮ ����
			szItemNum +      // ������ ����
			szCoordInven +   // ������ X ��ǥ
			szCoordInven;    // ������ Y ��ǥ
	}
};


//////////////////////////////////////////////////////////////////////////////
// class GCCreateItemHandler;
//////////////////////////////////////////////////////////////////////////////

class GCCreateItemHandler 
{
public:
	static void execute(GCCreateItem* pPacket, Player* pPlayer) throw(Error);

};

#endif
