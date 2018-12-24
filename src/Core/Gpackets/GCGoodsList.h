//////////////////////////////////////////////////////////////////////////////
// Filename    : GCGoodsList.h 
// Written By  : 김성민
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_GOODS_LIST_H__
#define __GC_GOODS_LIST_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "SubItemInfo.h"
#include <list>

#define MAX_GOODS_LIST 20

typedef struct _GoodsInfo
{
	int getPacketSize() const
	{ 
		return szObjectID + 
				szBYTE + 
				szItemType + 
				szGrade +
				szBYTE + optionType.size() +
				szBYTE + optionType2.size() +
				szItemNum +
				szDWORD + 
				szSilver +
				szEnchantLevel +
				szEnchantLevel + // 아이템 인챈트 레벨
				szEnchantLevel; // 아이템 인챈트 레벨;
	}

	static int getPacketMaxSize() 
	{ 
		return szObjectID + 
				szBYTE + 
				szItemType + 
				szGrade +
				szBYTE + 255 +
				szBYTE + 255 +
				szItemNum +
				szDWORD+
				szSilver +
				szEnchantLevel +
				szEnchantLevel + // 아이템 인챈트 레벨
				szEnchantLevel; // 아이템 인챈트 레벨
	}

	string toString() const
	{
		StringStream msg;
		msg << "Good( "
			<< "ObjectID : " << objectID
			<< ", ItemClass : " << (int)itemClass
			<< ", ItemType : " << itemType
			<< ", Grade : " << grade
			<< ", Options : (";

		list<OptionType_t>::const_iterator itr = optionType.begin();
		list<OptionType_t>::const_iterator endItr = optionType.end();

		for ( ; itr != endItr ; ++itr )
		{
			msg << *itr << ", ";
		}

			msg  << "), Options2 : (";

		list<OptionType_t>::const_iterator itr2 = optionType2.begin();
		list<OptionType_t>::const_iterator endItr2 = optionType2.end();

		for ( ; itr2 != endItr2 ; ++itr2 )
		{
			msg << *itr2 << ", ";
		}


		msg << "), Num : " << num
			<< ", TimeLimit : " << timeLimit;

		return msg.toString();
	}

	ObjectID_t     		objectID;
	BYTE           		itemClass;
	ItemType_t     		itemType;
	Grade_t				grade;
	list<OptionType_t>  optionType;
	list<OptionType_t>  optionType2;
	ItemNum_t      		num;
	Silver_t silver;
	EnchantLevel_t enchantLevel;
	EnchantLevel_t HeroOption;
	EnchantLevel_t HeroOptionAttr;
	DWORD				timeLimit;
} GoodsInfo;

//////////////////////////////////////////////////////////////////////////////
// class GCGoodsList;
//////////////////////////////////////////////////////////////////////////////

class Item;

class GCGoodsList : public Packet 
{
public:
	GCGoodsList() throw();
	virtual ~GCGoodsList() throw();

	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_GOODS_LIST; }
	PacketSize_t getPacketSize() const throw();
	string getPacketName() const throw() { return "GCGoodsList"; }
	string toString() const throw();

public:
	void		addGoodsInfo( GoodsInfo* pGI ) { m_GoodsList.push_back( pGI ); }
	GoodsInfo*	popGoodsInfo( ) { GoodsInfo* pRet = m_GoodsList.front(); if ( pRet ) m_GoodsList.pop_front(); return pRet; }

private:
	list<GoodsInfo*> m_GoodsList;
};


//////////////////////////////////////////////////////////////////////////////
// class GCGoodsListFactory;
//////////////////////////////////////////////////////////////////////////////

class GCGoodsListFactory : public PacketFactory 
{
public :
	Packet* createPacket() throw() { return new GCGoodsList(); }
	string getPacketName() const throw() { return "GCGoodsList"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_GOODS_LIST; }
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		PacketSize_t size = szBYTE;
		size += GoodsInfo::getPacketMaxSize() * MAX_GOODS_LIST;

		return size;
	}
};


//////////////////////////////////////////////////////////////////////////////
// class GCGoodsListHandler;
//////////////////////////////////////////////////////////////////////////////

class GCGoodsListHandler 
{
public :
	static void execute(GCGoodsList* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
