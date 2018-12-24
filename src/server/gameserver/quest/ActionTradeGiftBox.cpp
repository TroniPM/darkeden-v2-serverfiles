////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTradeGiftBox.cpp
// Written By  : ��ȫâ
// Description :
////////////////////////////////////////////////////////////////////////////////
#include "ActionTradeGiftBox.h"
#include "PlayerCreature.h"
#include "GamePlayer.h"
#include "Item.h"
#include "ItemUtil.h"
#include "OptionInfo.h"
#include "Inventory.h"
#include "Zone.h"
#include "ItemFactoryManager.h"
#include "DB.h"
#include "Thread.h"
#include "Slayer.h"
#include "Vampire.h"
#include "FlagSet.h"
#include <list>

#include "PacketUtil.h"
#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCDeleteInventoryItem.h"
#include "Gpackets/GCNPCResponse.h"

#include "PriceManager.h"

////////////////////////////////////////////////////////////////////////////////
// ActionTradeGiftBox
////////////////////////////////////////////////////////////////////////////////
ActionTradeGiftBox::ActionTradeGiftBox()
: m_pLuaState(NULL), m_pLuaSlayerItem(NULL), m_pLuaVampireItem(NULL)
{
	m_pLuaState = new LuaState;
	m_pLuaState->init();

	m_pLuaSlayerItem = new LuaTradeEventSlayerItem(m_pLuaState);
	m_pLuaVampireItem = new LuaTradeEventVampireItem(m_pLuaState);
}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
ActionTradeGiftBox::~ActionTradeGiftBox()
{
    __BEGIN_TRY

	SAFE_DELETE(m_pLuaState);
	SAFE_DELETE(m_pLuaSlayerItem);
	SAFE_DELETE(m_pLuaVampireItem);

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//  load
////////////////////////////////////////////////////////////////////////////////
void ActionTradeGiftBox::load()
    throw (Error)
{
    __BEGIN_TRY
	
	Assert(m_pLuaState!=NULL);

	int result = m_pLuaState->dofile(m_CommonFilename);
	LuaState::logError(result);

    __END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionTradeGiftBox::read(PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY

	try
	{
		// read script id
		m_CommonFilename = propertyBuffer.getProperty("CommonFilename");
		m_SlayerFilename = propertyBuffer.getProperty("SlayerFilename");
		m_VampireFilename = propertyBuffer.getProperty("VampireFilename");

		load();
	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// �׼��� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionTradeGiftBox::execute(Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert(pPC != NULL);

	Player* pPlayer = pPC->getPlayer();
	Assert(pPlayer != NULL);

	Inventory* pInventory = pPC->getInventory();
	Assert( pInventory != NULL );

	Zone* pZone = pPC->getZone();
	Assert( pZone != NULL );

	FlagSet* pFlagSet = pPC->getFlagSet();

	Item::ItemClass ItemClass;
	ItemType_t		ItemType;
	OptionType_t	OptionType;

	Item*			pItem;
	Item*			pGiftBoxItem;

	// �̹� ������ ��ȯ�� ���ٸ�
	if ( pFlagSet->isOn( FLAGSET_TRADE_GIFT_BOX_2002_12 ) )
	{
		GCNPCResponse response;
		response.setCode( NPC_RESPONSE_TRADE_GIFT_BOX_ALREADY_TRADE );
		pPlayer->sendPacket( &response );

		GCNPCResponse quit;
		quit.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
		pPlayer->sendPacket( &quit );

		return;
	}

	// ���� ���� ���ڰ� �ִ��� Ȯ���Ѵ�.
	CoordInven_t X,Y;
	pGiftBoxItem = pInventory->findItem( Item::ITEM_CLASS_EVENT_GIFT_BOX, 1, X, Y );
	if ( pGiftBoxItem == NULL )
	{
		GCNPCResponse response;
		response.setCode( NPC_RESPONSE_TRADE_GIFT_BOX_NO_ITEM );
		pPlayer->sendPacket( &response );

		GCNPCResponse quit;
		quit.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
		pPlayer->sendPacket( &quit );

		return;
	}

	LuaSelectItem*	pLuaSelectItem = NULL;
	string			luaFileName;

	if ( pPC->isSlayer() )
	{
		// ��ƿ� �����̾� �ɷ�ġ�� ���� set�Ѵ�.
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		Assert( pSlayer != NULL );

		Attr_t sum = pSlayer->getSTR( ATTR_BASIC )
				   + pSlayer->getDEX( ATTR_BASIC )
				   + pSlayer->getINT( ATTR_BASIC );

		m_pLuaSlayerItem->setSum(sum);
		pLuaSelectItem = m_pLuaSlayerItem;
		luaFileName = m_SlayerFilename;

	}
	else if ( pPC->isVampire() )
	{
		// ��ƿ� �����̾��� ������ set�Ѵ�.
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
		Assert( pVampire != NULL );

		int level = pVampire->getLevel();
		m_pLuaVampireItem->setLevel(level);
		pLuaSelectItem = m_pLuaVampireItem;
		luaFileName = m_VampireFilename;
	}

	//--------------------------------------------------------
	// �ӵ� üũ�� ���ؼ� 1000�� �������� �ڵ�
	// �����.. 0.07�� ���� ���Դ�. ����~ -_-;
	/*
	Timeval beforeTime;
	getCurrentTime(beforeTime);

	for (int i=0; i<1000; i++)
	{
		// ����� ��� ����� �޾� �������� �����Ѵ�.
		pLuaSelectItem->prepare();
		
		int result = pLuaSelectItem->executeFile( luaFileName );
		LuaState::logError(result);
		pLuaSelectItem->clear();
	}

	Timeval afterTime;
	getCurrentTime(afterTime);

	cout << "luaExecute time before : " << beforeTime.tv_sec  << "." << beforeTime.tv_usec << endl;
	cout << "luaExecute time after  : " << afterTime.tv_sec  << "." << afterTime.tv_usec << endl;
	*/
	//--------------------------------------------------------

	// ����� ��� ����� �޾� �������� �����Ѵ�.
	pLuaSelectItem->prepare();
	
	int result = pLuaSelectItem->executeFile( luaFileName );
	LuaState::logError(result);

	ItemClass 	= pLuaSelectItem->getItemClass();
	ItemType  	= pLuaSelectItem->getItemType();
	OptionType	= pLuaSelectItem->getOptionType();

	pLuaSelectItem->clear();

	if( ItemClass >= Item::ITEM_CLASS_MAX )
	//||  ItemType  >= ITEM_TYPE_MAX || ItemType  < 0
	//	|| OptionType == 0)
	{
		filelog( "XMasEventError.txt", "[ ItemInfo Error ] : ItemClass = %d , ItemType = %d , OptionType = %d", ItemClass, ItemType, OptionType );

		GCNPCResponse quit;
		quit.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
		pPlayer->sendPacket( &quit );

		return;
	}

	// Ŭ���̾�Ʈ�� �������ڸ� ���쵵�� �Ѵ�.
	GCDeleteInventoryItem gcDeleteInventoryItem;
	gcDeleteInventoryItem.setObjectID( pGiftBoxItem->getObjectID() );
	pPlayer->sendPacket( &gcDeleteInventoryItem );

	// �������ڸ� �����.
	pInventory->deleteItem( X, Y );
	// ItemTraceLog �� �����
	if ( pGiftBoxItem != NULL && pGiftBoxItem->isTraceItem() )
	{
		remainTraceLog( pGiftBoxItem, pCreature2->getName(), pCreature1->getName(), ITEM_LOG_DELETE, DETAIL_EVENTNPC);
	}
	pGiftBoxItem->destroy();
	SAFE_DELETE( pGiftBoxItem );


	// ����(Item)�� �����.
	list<OptionType_t> optionTypeList;
	if ( OptionType != 0 )
		optionTypeList.push_back( OptionType );

	pItem = g_pItemFactoryManager->createItem( ItemClass, ItemType, optionTypeList );
	Assert( pItem != NULL );


	// ������ �κ��丮�� �߰��Ѵ�.
	pZone->getObjectRegistry().registerObject( pItem );
	pInventory->addItem( X, Y, pItem );
	pItem->create( pPC->getName(), STORAGE_INVENTORY, 0, X, Y );

	// ItemTraceLog �� �����
	if ( pItem != NULL && pItem->isTraceItem() )
	{
		remainTraceLog( pItem, pCreature1->getName(), pCreature2->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
	}

	// Ŭ���̾�Ʈ�� ������ �߰��Ǿ����� �˸���.
	GCCreateItem gcCreateItem;
	makeGCCreateItem( &gcCreateItem, pItem, X, Y );
	pPlayer->sendPacket(&gcCreateItem);

	// Flag�� �Ҵ�.
	pFlagSet->turnOn( FLAGSET_TRADE_GIFT_BOX_2002_12 );

	// Flag�� �����Ѵ�.
	pFlagSet->save( pPC->getName() );

	// ������ ��ȯ�� �̷�� ���ٰ� Ŭ���̾�Ʈ�� �˸���.
	GCNPCResponse response;
	response.setCode( NPC_RESPONSE_TRADE_GIFT_BOX_OK );
	pPlayer->sendPacket( &response );

	GCNPCResponse quit;
	quit.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
	pPlayer->sendPacket( &quit );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionTradeGiftBox::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionTradeGiftBox("
	    << ")";
	return msg.toString();

	__END_CATCH
}
