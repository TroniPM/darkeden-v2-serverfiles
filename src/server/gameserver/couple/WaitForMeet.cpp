#include "Assert.h"
#include "Player.h"
#include "GamePlayer.h"
#include "Slayer.h"
#include "Vampire.h"
#include "PacketUtil.h"
#include "PlayerCreature.h"
#include "ItemNameInfo.h"
#include "FlagSet.h"
#include "StringStream.h"
#include "StringPool.h"

#include "WaitForMeet.h"
#include "CoupleManager.h"
#include "OptionInfo.h"
#include "VariableManager.h"

#include "item/CoupleRing.h"
#include "item/VampireCoupleRing.h"
#include "ItemFactoryManager.h"

#include "Gpackets/GCCreateItem.h"
//#include "Gpackets/GCItemNameInfoList.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCModifyInformation.h"

#include <stdio.h>

const int CoupleRingOptionNum = 4;
static const char* CoupleRingOptions[2][4] =
{	{ "STR+4", "DEX+4", "DAM+3", "HP+4" },
	{ "STR+4", "DEX+4", "DAM+3", "ASPD+4" } };

uint WaitForMeet::waitPartner( PlayerCreature* pTargetPC )
	
{
	__BEGIN_TRY

	if ( pTargetPC == NULL )
		return COUPLE_MESSAGE_LOGOFF;		// �� �̸޽��� ����. ���� ���⼭ ���ϵǴ� ���� ������

	PlayerCreature* pWaitingPC = getWaitingPC();
	if ( pWaitingPC == NULL )
		return COUPLE_MESSAGE_LOGOFF;

	uint result = canMakeCouple( pWaitingPC, pTargetPC );
	if ( result != 0 )
		return result;

	GCSystemMessage gcSystemMessage;
//	StringStream msg;
//	msg << pWaitingPC->getName() << "�����κ��� Ŀ�� ��û�� �Խ��ϴ�.";

	char msg[100];
	sprintf( msg, g_pStringPool->c_str( STRID_REQUEST_MEET ), pWaitingPC->getName().c_str() );
	gcSystemMessage.setMessage( msg );

	pTargetPC->getPlayer()->sendPacket( &gcSystemMessage );

	return 0;
	
	__END_CATCH
}

uint WaitForMeet::acceptPartner( PlayerCreature* pRequestedPC )
	
{
	__BEGIN_TRY

	Assert( pRequestedPC != NULL );

	PlayerCreature* pWaitingPC = getWaitingPC();
	if ( pWaitingPC == NULL )
		return COUPLE_MESSAGE_LOGOFF;

	// ������ �ٸ��ų� ������ ������ �ȵȴ�.
	// ���� ���ѿ� �ɸ��ų� ���� ���ڶ� �ȵȴ�.
	// �� �� �Ѹ��� �̹� Ŀ���̶� �ȵȴ�.
	uint result = canMakeCouple( pRequestedPC, pWaitingPC );
	if ( result != 0 )
		return result;

	// Ŀ�ø��� �ش�.
	_TPOINT pt1;
	_TPOINT pt2;

	// �Ѹ� �޴� ��츦 �����ϱ� ���� �̸� ���� �� �ִ����� Ȯ���Ѵ�.
	// �ٴڿ� �������� ��������.
	if ( !(canGetCoupleRing( pRequestedPC, pt1 ) && canGetCoupleRing( pWaitingPC, pt2 )) ) return COUPLE_MESSAGE_INVENTORY_FULL;

	// Ŀ�ø��� �ش�.
	CoupleRingBase* pNewItem1 = giveCoupleRing( pRequestedPC, pWaitingPC->getName(), &pt1 );
	CoupleRingBase* pNewItem2 = giveCoupleRing( pWaitingPC, pRequestedPC->getName(), &pt2 );

	// ������ Ȯ�������Ƿ� ���⼭ ��縮���� �����尡 �����ų� �� ������ �ִ�.
	Assert( pNewItem1 != NULL );
	Assert( pNewItem2 != NULL );

	// Ŀ�ø��� ���� ����� ������ID�� ����صд�. ���߿� ���ﶧ ���� ������ �Ǵϱ�.
	pNewItem1->setPartnerItemID( pNewItem2->getItemID() );
	pNewItem2->setPartnerItemID( pNewItem1->getItemID() );

//	ItemNameInfo *pRequestedPCItemNameInfo = new ItemNameInfo( pNewItem1->getObjectID(), pWaitingPC->getName() );
//	ItemNameInfo *pWaitingPCItemNameInfo = new ItemNameInfo( pNewItem2->getObjectID(), pRequestedPC->getName() );

//	pRequestedPC->addItemNameInfoList( pRequestedPCItemNameInfo );
//	pWaitingPC->addItemNameInfoList( pWaitingPCItemNameInfo );

	// Ŀ�øŴ����� ����Ѵ�.
	g_pCoupleManager->makeCouple( pWaitingPC, pRequestedPC );

	// Ŀ�� ��ϱ��� �޾Ƴ���.
	receiveCoupleRegisterFee( pWaitingPC );
	receiveCoupleRegisterFee( pRequestedPC );

	// ���� �������� Ŀ������ �����մϴ�.
	pRequestedPC->getFlagSet()->turnOn( FLAGSET_IS_COUPLE );
	pWaitingPC->getFlagSet()->turnOn( FLAGSET_IS_COUPLE );
	pRequestedPC->getFlagSet()->turnOn( FLAGSET_WAS_COUPLE );
	pWaitingPC->getFlagSet()->turnOn( FLAGSET_WAS_COUPLE );

	pRequestedPC->getFlagSet()->save( pRequestedPC->getName() );
	pWaitingPC->getFlagSet()->save( pWaitingPC->getName() );
	
	// �� �� �� ����.....
	// �̸����� ������ ����Ʈ ����� �����ؼ� �����ش�.
	// �� �����ش�. -_- - 2003.2.24
/*	if ( !pRequestedPC->isEmptyItemNameInfoList()
		&& !pWaitingPC->isEmptyItemNameInfoList() )
	{
		GCItemNameInfoList  gcRequestedPCItemNamInfoList;
		GCItemNameInfoList  gcWaitingPCItemNamInfoList;

		makeGCItemNameInfoList( &gcRequestedPCItemNamInfoList, pRequestedPC );
		makeGCItemNameInfoList( &gcWaitingPCItemNamInfoList, pWaitingPC );

		pRequestedPC->getPlayer()->sendPacket( &gcRequestedPCItemNamInfoList );
		pWaitingPC->getPlayer()->sendPacket( &gcWaitingPCItemNamInfoList );
	}
	else 
	{
		Assert(false);
	}*/

	return 0;
	
	__END_CATCH
}

void WaitForMeet::timeExpired()
	
{
	__BEGIN_TRY

	// ��ٸ��� ������� �ȵǼ̽��ϴ�..��� �޽����� �����ش�.
	GCNPCResponse gcNPCResponse;
	gcNPCResponse.setCode( NPC_RESPONSE_MEET_WAIT_TIME_EXPIRED );

	PlayerCreature* pPC = getWaitingPC();
	if ( pPC != NULL )
		pPC->getPlayer()->sendPacket( &gcNPCResponse );
	
	__END_CATCH
}

Gold_t WaitForMeet::getCoupleRegisterFee( PlayerCreature* pPC )
	
{
	__BEGIN_TRY

	Assert( pPC != NULL );

	Gold_t ret = 0;

	switch( pPC->getRace() )
	{
		case RACE_SLAYER:
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>( pPC );
				Assert( pSlayer != NULL );

				ret = 100000 * ( pSlayer->getTotalAttr( ATTR_BASIC ) / 3 );
			}
			break;
		case RACE_VAMPIRE:
			{
				Vampire* pVampire = dynamic_cast<Vampire*>( pPC );
				Assert( pVampire != NULL );

				ret = 100000 * pVampire->getLevel();
			}
			break;
		default:
			return 0;
	}

	return ret;

	__END_CATCH
}

void WaitForMeet::receiveCoupleRegisterFee( PlayerCreature* pPC ) 
	
{ 
	__BEGIN_TRY

	pPC->decreaseGoldEx( getCoupleRegisterFee( pPC ) ); 
	GCModifyInformation gcMI;

	gcMI.addLongData( MODIFY_GOLD, pPC->getGold() );
	pPC->getPlayer()->sendPacket( &gcMI );


	__END_CATCH
}

uint WaitForMeet::canMakeCouple( PlayerCreature* pPC1, PlayerCreature* pPC2 )
{
	if ( pPC1->getRace() != pPC2->getRace() ) return COUPLE_MESSAGE_DIFFERENT_RACE;
	if ( pPC1->getSex() == pPC2->getSex() ) return COUPLE_MESSAGE_SAME_SEX;

	uint result = canHavePartner( pPC1 );
	if ( result != 0 )
		return result;

	result = canHavePartner( pPC2 );
	if ( result != 0 )
		return result;

	return 0;
}

OptionType_t WaitForMeet::getRandomOptionType( PlayerCreature* pPC )
{
	int op = rand() % 4;
	return g_pOptionInfoManager->getOptionType( CoupleRingOptions[(int)pPC->getRace()][op] );
}

CoupleRingBase* WaitForMeet::giveCoupleRing( PlayerCreature* pPC, string partnerName, _TPOINT* pPt )
	
{
	__BEGIN_TRY

	list<OptionType_t> optionList;
	optionList.push_back( getRandomOptionType( pPC ) );
	
	Item* 		pNewItem 		= g_pItemFactoryManager->createItem(getItemClass( pPC ), getItemType( pPC ), optionList);
	CoupleRingBase* pCoupleItem 	= dynamic_cast<CoupleRingBase*>(pNewItem);
	Assert(pCoupleItem != NULL);
	pCoupleItem->setName( partnerName );
	pPC->getZone()->registerObject( pCoupleItem );

	Inventory* pPCInven = pPC->getInventory();

	_TPOINT pt;

	if ( pPt == NULL )
	{
		if ( !canGetCoupleRing( pPC, pt ) ) return NULL;
	}
	else
	{
		pt = *pPt;
	}

	Assert(pPCInven->addItem(pt.x, pt.y, pCoupleItem));
	pCoupleItem->create( pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y );

	GCCreateItem	gcCreateItem;
	makeGCCreateItem( &gcCreateItem, pCoupleItem, pt.x, pt.y );
	pPC->getPlayer()->sendPacket(&gcCreateItem);

	return pCoupleItem;

	__END_CATCH
}

bool WaitForMeet::canGetCoupleRing( PlayerCreature* pPC, _TPOINT& pt )
{
	ItemInfo* pCoupleItemInfo = CoupleRingBase::getItemInfo( getItemType( pPC ), pPC->getRace() );//g_pCoupleItemInfoManager->getItemInfo(0);
	return pPC->getInventory()->getEmptySlot( pCoupleItemInfo->getVolumeWidth(), pCoupleItemInfo->getVolumeHeight(), pt );
}

uint WaitForMeet::canHavePartner( PlayerCreature* pPC )
	
{
	__BEGIN_TRY

	Assert( pPC != NULL );

	GamePlayer* pGP = dynamic_cast<GamePlayer*>(pPC->getPlayer());
	Assert( pGP != NULL );

	if ( !pGP->isPayPlaying() ) return COUPLE_MESSAGE_NOT_PAY_PLAYER;
	if ( pPC->getFlagSet()->isOn( FLAGSET_IS_COUPLE ) ) return COUPLE_MESSAGE_ALREADY_COUPLE;
	if ( !g_pVariableManager->canRecouple() )
		if ( pPC->getFlagSet()->isOn( FLAGSET_WAS_COUPLE ) ) return COUPLE_MESSAGE_WAS_COUPLE;
	if ( pPC->getGold() < getCoupleRegisterFee( pPC ) ) return COUPLE_MESSAGE_NOT_ENOUGH_GOLD;

	switch( pPC->getRace() )
	{
		case RACE_SLAYER:
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
				Assert( pSlayer != NULL );
				Attr_t totalAttr = pSlayer->getTotalAttr( ATTR_BASIC );
				if ( totalAttr < 65 )
					return COUPLE_MESSAGE_NOT_ENOUGH_ATTR;
			}
			break;
		case RACE_VAMPIRE:
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
				Assert( pVampire != NULL );
				if ( pVampire->getLevel() < 20 )
					return COUPLE_MESSAGE_NOT_ENOUGH_LEVEL;
			}
			break;

		default:
			Assert( false );
	}

	return 0;

	__END_CATCH
}

