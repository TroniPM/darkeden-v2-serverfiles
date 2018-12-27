////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveEventItem.cpp
// Written By  : ��ȫâ
// Description :
////////////////////////////////////////////////////////////////////////////////
#include "ActionGiveEventItem.h"
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
#include "Gpackets/GCNPCResponse.h"

#include "VariableManager.h"

////////////////////////////////////////////////////////////////////////////////
// ActionGiveEventItem
////////////////////////////////////////////////////////////////////////////////
ActionGiveEventItem::ActionGiveEventItem()
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
ActionGiveEventItem::~ActionGiveEventItem()
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
void ActionGiveEventItem::load()
    
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
void ActionGiveEventItem::read(PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try
	{
		// read script id
		m_FlagSetType = (FlagSetType)propertyBuffer.getPropertyInt("FlagSetType");
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
void ActionGiveEventItem::execute(Creature * pCreature1 , Creature * pCreature2) 
	
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
	OptionType_t	OptionType2;

	Item*			pItem;

	// �̺�Ʈ ���� �Ⱓ�� �ƴ� ���
	if (!g_pVariableManager->isActiveGiveEventItem())
	{
		GCNPCResponse response;
		response.setCode( NPC_RESPONSE_GIVE_EVENT_ITEM_FAIL_NOW );
		pPlayer->sendPacket( &response );

		GCNPCResponse quit;
		quit.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
		pPlayer->sendPacket( &quit );

		return;
	}

	// �� ���� �����ؼ�
	// ĳ���� �����ÿ� FlagSet�� �ٲ�����Ѵ�. (default ON ����)
	// �̹� ������ ��ȯ�� ���ٸ�
	if ( pFlagSet->isOn( m_FlagSetType ) )
	{
		GCNPCResponse response;
		response.setCode( NPC_RESPONSE_GIVE_EVENT_ITEM_FAIL );
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
	OptionType2	= pLuaSelectItem->getOptionType2();

	pLuaSelectItem->clear();

	if( ItemClass >= Item::ITEM_CLASS_MAX )
	//||  ItemType  >= ITEM_TYPE_MAX || ItemType  < 0
	//	|| OptionType == 0)
	{
		filelog( "GiveEventItemError.txt", "[ ItemInfo Error ] : ItemClass = %d , ItemType = %d , OptionType = %d", ItemClass, ItemType, OptionType );

		GCNPCResponse quit;
		quit.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
		pPlayer->sendPacket( &quit );

		return;
	}

	// ����(Item)�� �����.
	list<OptionType_t> optionTypeList;
	if ( OptionType != 0 ) optionTypeList.push_back( OptionType );
	if ( OptionType2 != 0 ) optionTypeList.push_back( OptionType2 );

	pItem = g_pItemFactoryManager->createItem( ItemClass, ItemType, optionTypeList );
	Assert( pItem != NULL );

	_TPOINT pt;
	if (!pInventory->getEmptySlot(pItem, pt))
	{
		SAFE_DELETE(pItem);

		GCNPCResponse response;
		response.setCode( NPC_RESPONSE_NO_EMPTY_SLOT );
		pPlayer->sendPacket( &response );

		GCNPCResponse quit;
		quit.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
		pPlayer->sendPacket( &quit );

		return;
	}
	 
	CoordInven_t X = pt.x;
	CoordInven_t Y = pt.y;

	// ������ �κ��丮�� �߰��Ѵ�.
	pZone->getObjectRegistry().registerObject( pItem );
	pInventory->addItem( X, Y, pItem );
	pItem->create( pPC->getName(), STORAGE_INVENTORY, 0, X, Y );

	// ItemTraceLog �� �����
	if ( pItem != NULL && pItem->isTraceItem() )
	{
		remainTraceLog( pItem, pCreature1->getName(), pCreature2->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);

		remainTraceLogNew( pItem, pCreature2->getName(), ITL_GET, ITLD_EVENTNPC, pCreature1->getZone()->getZoneID(), pCreature1->getX(), pCreature1->getY() );
	}

	// Ŭ���̾�Ʈ�� ������ �߰��Ǿ����� �˸���.
	GCCreateItem gcCreateItem;
	makeGCCreateItem( &gcCreateItem, pItem, X, Y );
	pPlayer->sendPacket(&gcCreateItem);

	// Flag�� �Ҵ�.
	pFlagSet->turnOn( m_FlagSetType );

	// Flag�� �����Ѵ�.
	pFlagSet->save( pPC->getName() );

	// ������ ��ȯ�� �̷�� ���ٰ� Ŭ���̾�Ʈ�� �˸���.
	GCNPCResponse response;
	response.setCode( NPC_RESPONSE_GIVE_EVENT_ITEM_OK );
	pPlayer->sendPacket( &response );

	GCNPCResponse quit;
	quit.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
	pPlayer->sendPacket( &quit );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionGiveEventItem::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionGiveEventItem("
	    << ")";
	return msg.toString();

	__END_CATCH
}
