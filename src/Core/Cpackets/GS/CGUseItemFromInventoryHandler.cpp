//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUseItemFromInventoryHandler.cpp
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGUseItemFromInventory.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "PlayerCreature.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Monster.h"
	#include "Inventory.h"
	#include "Item.h"
	#include "ItemInfo.h"
	#include "ItemInfoManager.h"
	#include "ItemFactoryManager.h"
	#include "ItemUtil.h"
	#include "ItemMineInfo.h"
	#include "skill/Skill.h"
	#include "SkillInfo.h"
	#include "skill/SkillUtil.h"
	#include "CreatureUtil.h"
    #include "EffectHPRecovery.h"
    #include "EffectMPRecovery.h"
	#include "Effect.h"
	#include "EffectReloadTimer.h"
	#include "EffectManager.h"
	#include "EffectAftermath.h"
	#include "EffectTranslation.h"
	#include "SimpleCreatureEffect.h"
	#include "EffectHasPet.h"
	#include "skill/EffectSummonSylph.h"
	#include "ZoneUtil.h"
	#include "Treasure.h"
	#include "StringPool.h"
	#include "MonsterDropSetup.h"
	#include "MonsterItemDrop.h"
	#include "MonsterItemDropOption.h"
	#include "VariableManager.h"
	#include "ItemGradeManager.h"
	#include <math.h>
	#include <stdio.h>
	#include "SkillInfo.h"
	#include "ctf/FlagManager.h"

	#include "ParkingCenter.h"
	#include "VariableManager.h"
	#include "DB.h"
	#include "GQuestManager.h"
	#include "EffectSevenFoldStone.h"
	#include "item/Potion.h"
	#include "item/DyePotion.h"
	#include "item/Serum.h"
	#include "item/SlayerPortalItem.h"
	#include "item/Key.h"
	#include "item/ResurrectItem.h"
	#include "item/OustersSummonItem.h"
	#include "item/EffectItem.h"
	#include "item/PetItem.h"
	#include "item/PetFood.h"
	#include "item/SlayerPortalItem.h"
	#include "item/VampirePortalItem.h"
	#include "item/OustersSummonItem.h"
	#include "item/OustersWingItem.h"
	#include "item/SMSItem.h"
	#include "item/TrapItem.h"
	#include "item/EventETC.h"
	#include "item/SubInventory.h"
	#include "item/SkillBook.h"
	#include "Gpackets/GCCannotUse.h"
	#include "Gpackets/GCUseOK.h"
	#include "Gpackets/GCHPRecoveryStartToSelf.h"
	#include "Gpackets/GCHPRecoveryStartToOthers.h"
	#include "Gpackets/GCMPRecoveryStart.h"
	#include "Gpackets/GCAddHelicopter.h"
	#include "Gpackets/GCAddEffectToTile.h"
	#include "Gpackets/GCAddEffect.h"
	#include "Gpackets/GCDeleteObject.h"
	#include "Gpackets/GCAddSlayer.h"
	#include "Gpackets/GCAddSylph.h"
	#include "Gpackets/GCAddVampire.h"
	#include "Gpackets/GCAddOusters.h"
	#include "Gpackets/GCCreateItem.h"
	#include "Gpackets/GCUseBonusPointOK.h"
	#include "Gpackets/GCRemoveEffect.h"
	#include "Gpackets/GCStatusCurrentHP.h"
	#include "Gpackets/GCModifyInformation.h"
	#include "Gpackets/GCAddressListVerify.h"
	#include "Gpackets/GCLearnSkillFailed.h"
	#include "Gpackets/GCLearnSkillOK.h"
	#include "PacketUtil.h"
	#include "PetTypeInfo.h"
	#include "GDRLairManager.h"
	#include "MonsterItemDrop.h" 
	#include "EffectAutoTurret.h"
	#include "EffectTurretLaser.h"
	#include "EffectKillTimer.h"
	#include "SiegeManager.h"
	#include "Store.h"
	#include "DynamicZone.h"

	#include "Gpackets/GCMyStoreInfo.h"
	#include "Gpackets/GCSubInventoryInfo.h"
	#include "Gpackets/GCSystemMessage.h"

	bool changeHairColorEx( PlayerCreature* pPC, Color_t color );
	bool changeBatColorEx( PlayerCreature* pPC, Color_t color );
	bool changeMasterEffectColorEx( PlayerCreature* pPC, BYTE color );
	bool changeSkinColorEx( PlayerCreature* pPC, Color_t color );
	inline bool sendCannotUse( CGUseItemFromInventory* pPacket, Player* pPlayer );
	void SlayerStatus(PlayerCreature* pPC, int Case,CGUseItemFromInventory* pPacket);
	void VampireStatus(PlayerCreature* pPC, int Case,CGUseItemFromInventory* pPacket);
	void OustersStatus(PlayerCreature* pPC, int Case,CGUseItemFromInventory* pPacket);
	void AllSlayerStatus(PlayerCreature* pPC, int Case,CGUseItemFromInventory* pPacket);
	void AllVampireStatus(PlayerCreature* pPC, int Case,CGUseItemFromInventory* pPacket);
	void AllOustersStatus(PlayerCreature* pPC, int Case,CGUseItemFromInventory* pPacket);
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUseItemFromInventoryHandler::execute(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

//	cout << "CGUseItemFromInventoryHandler " << endl;
	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	Creature* pCreature = pGamePlayer->getCreature();
	Assert(pCreature != NULL);
	Assert(pCreature->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert(pPC != NULL);

	Inventory* pInventory = pPC->getInventory();
	Zone*      pZone      = pPC->getZone();

	Storage_t Storage = STORAGE_INVENTORY;
	StorageID_t StorageID = 0;

	bool SubInventoryTrue = false;

	if(pPacket->getInventoryItemObjectID() != 0){
		Item*           pInvenItem        = NULL;
		pInvenItem        = pInventory->getItemWithObjectID(pPacket->getInventoryItemObjectID());
		SubInventory* pSubInventory = dynamic_cast<SubInventory*>(pInvenItem);
		SubInventoryTrue = true;
		Storage = STORAGE_BOX;
		StorageID = pInvenItem->getItemID();
		pInventory = ((SubInventory*)pSubInventory)->getInventory();
	}

	Assert(pInventory != NULL);
	Assert(pZone != NULL);

	CoordInven_t InvenX = pPacket->getX();
	CoordInven_t InvenY = pPacket->getY();

	//cout << "��Ŷ����� : " << pPacket->toString() << endl;

	// �κ��丮 ��ǥ�� �Ѿ�� �����̶�� �� �ȴ�.
	if (InvenX >= pInventory->getWidth() || InvenY >= pInventory->getHeight())
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	// �κ��丮�� �� �������� ���ٸ� ������.
	Item* pItem = pInventory->getItem(InvenX, InvenY);
	if (pItem == NULL)
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	// �κ��丮�� �ִ� �������� Object�� �޴´�.
	ObjectID_t ItemObjectID = pItem->getObjectID();

	// OID�� ��ġ���� �ʰų�, ����� �� ���� �������̶�� ������.
	if (ItemObjectID != pPacket->getObjectID() || !isUsableItem(pItem, pCreature))
	{
		//cout << "���� ��� �Ұ�. ����Ʈ �Ƶ� �� �´���..." << endl;
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}


	// ������Ʒ�����̵���
	// �������ܿ����̵�?�����ʹ��BUG
	if (pItem->getItemType() >=5 && pItem->getItemType() <=7)
	{
		BYTE bIndex=pPC->getStore()->getItemIndex(pItem);
		if (bIndex != 0xff)
		{
			pPC->getStore()->removeStoreItem(bIndex);
			GCMyStoreInfo gcInfo;
			gcInfo.setStoreInfo( &(pPC->getStore()->getStoreInfo()) );
			pGamePlayer->sendPacket( &gcInfo );
		}
		
	}
	if ( pPC->getStore()->getItemIndex(pItem) != 0xff )
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	// �������� ������ ����, ó�� �Լ��� �б���� �ش�.
	////cout << pItem->getItemClass() << endl;

	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_POTION:
			Assert(false);
			break;
		case Item::ITEM_CLASS_MAGAZINE:
			Assert(false);
			break;
		case Item::ITEM_CLASS_ETC:
			Assert(pItem->getItemType() != 0);
			executeTranslator(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_SERUM:
			Assert(false);
			break;
		case Item::ITEM_CLASS_VAMPIRE_ETC:
			Assert(pItem->getItemType() > 1);
			executeTranslator(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_SLAYER_PORTAL_ITEM:
			executeSlayerPortalItem(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM:
			executeOustersSummonItem(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_KEY:
			executeKeyItem(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_EVENT_ETC:
			executeFirecraker(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_DYE_POTION:
			executeDyePotion(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_RESURRECT_ITEM:
			executeResurrectItem(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_EFFECT_ITEM:
			executeEffectItem(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_PET_ITEM:
			executePetItem(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_PET_FOOD:
			executePetFood(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_EVENT_GIFT_BOX:
			executeEventGiftBox(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_SMS_ITEM:
			{
				SMSItemInfo* pItemInfo = dynamic_cast<SMSItemInfo*>(g_pItemInfoManager->getItemInfo( pItem->getItemClass(), pItem->getItemType() ));
				Assert( pItemInfo != NULL );

				uint charge = pItemInfo->getCharge();
				pPC->setSMSCharge( pPC->getSMSCharge() + charge );

				GCUseOK _GCUseOK;
				pGamePlayer->sendPacket(&_GCUseOK);

				GCAddressListVerify gcVerify;
				gcVerify.setCode( GCAddressListVerify::SMS_CHARGE_OK );
				gcVerify.setParameter( pPC->getSMSCharge() );
				pGamePlayer->sendPacket( &gcVerify );

				char buffer[100];
				sprintf( buffer, "SMSCharge=%u", pPC->getSMSCharge() );
				pPC->tinysave( buffer );

				// ������ �ʴ� �������� �ٷιٷ� �������ش�.
				pInventory->deleteItem(InvenX, InvenY);
				pItem->destroy();
				SAFE_DELETE(pItem);
			}
			break;

		case Item::ITEM_CLASS_TRAP_ITEM:
			executeTrapItem(pPacket, pPlayer);
			break;
			// add by Coffee 2007-6-9 �����¼��ܿ��۳�����
		case Item::ITEM_CLASS_MOON_CARD:
			if (pItem->getItemType() >=5 && pItem->getItemType() <=7)
			{
				GCUseOK _GCUseOK;
				pGamePlayer->sendPacket(&_GCUseOK);
				decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);

			}
			break;
			// add end by Coffee 2007-6-9

		case Item::ITEM_CLASS_SUB_INVENTORY:
			executeSubInventory(pPacket, pPlayer);
			break;

		case Item::ITEM_CLASS_SKILLBOOK:
			executeSkillBook(pPacket, pPlayer);
			break;

		case Item::ITEM_CLASS_OUSTERSWING_ITEM:
			executeOustersWingItem(pPacket, pPlayer);
			break;

		default:
			Assert(false);
			break;
	}

#endif

    __END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUseItemFromInventoryHandler::executePotion(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// ���� �Լ����� ���� üũ�� ���� �߱� ������,
	// ���� üũ�� ���� ����Ѵ�.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	//ObjectID_t      ItemObjectID = pItem->getObjectID();

	Storage_t Storage = STORAGE_INVENTORY;
	StorageID_t StorageID = 0;

	bool SubInventoryTrue = false;

	if(pPacket->getInventoryItemObjectID() != 0){
		Item*           pInvenItem        = NULL;
		pInvenItem        = pInventory->getItemWithObjectID(pPacket->getInventoryItemObjectID());
		SubInventory* pSubInventory = dynamic_cast<SubInventory*>(pInvenItem);
		SubInventoryTrue = true;
		Storage = STORAGE_BOX;
		StorageID = pInvenItem->getItemID();
		pInventory = ((SubInventory*)pSubInventory)->getInventory();
	}

	Item*           pItem        = pInventory->getItem(InvenX, InvenY);

	Assert(pCreature->isSlayer());

	Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

	// �ڸ� ���¶�� ����� �� ����.
	if (pSlayer->isFlag(Effect::EFFECT_CLASS_COMA)
		// ������ ���� ���� ����ڰ� �ƴϸ� ����� �� ����.
		|| pItem->getItemType()==11 && !pGamePlayer->isPayPlaying() && !pGamePlayer->isPremiumPlay())
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	HP_t	MaxHP     = pSlayer->getHP(ATTR_MAX);
	HP_t	CurrentHP = pSlayer->getHP(ATTR_CURRENT);
	MP_t	MaxMP     = pSlayer->getMP(ATTR_MAX);
	MP_t	CurrentMP = pSlayer->getMP(ATTR_CURRENT);
	Potion* pPotion   = dynamic_cast<Potion*>(pItem);

	int HPQuantity = pPotion->getHPQuantity();
	int MPQuantity = pPotion->getMPQuantity();

	int HPDelayProvider = pPotion->getHPDelay();
	int MPDelayProvider = pPotion->getMPDelay();

	// Activation Effect�� �ɷ��ִٸ� ȸ���ӵ��� 2�谡 �ȴ�.
	if (pSlayer->isFlag(Effect::EFFECT_CLASS_ACTIVATION))
	{
		if ( pPotion->getItemType() >= 14 && pPotion->getItemType() <= 17 )
		{
			// �� ���� �ִ�.
		}
		else
		{
			HPDelayProvider = (HPDelayProvider>>1);
			MPDelayProvider = (MPDelayProvider>>1);

			HPDelayProvider = max(HPDelayProvider, 1);
			MPDelayProvider = max(MPDelayProvider, 1);
		}
	}

	Attr_t INT = pSlayer->getINT();

	int PotionHPAmount=0, PotionMPAmount=0;

	// ���� �ٸ� ������ Relic�� �����ߴٸ�, ��û/������ ȿ���� 50%�� ��������.
	PotionHPAmount = pPotion->getHPAmount();
	PotionMPAmount = pPotion->getMPAmount();
	
	int HPAmount = min(MaxHP - CurrentHP , PotionHPAmount);
	int MPAmount = min(MaxMP - CurrentMP , (int)(PotionMPAmount* (double)(1 + (double)((double)INT / 300.0))));

	bool notRecoverHP = false;
	bool notRecoverMP = false;

	// HP ȸ������ �����Ѵٸ�...
	if (HPAmount != 0 && HPQuantity != 0)
	{
		if (CurrentHP < MaxHP) 
		{
			EffectManager* pEffectManager = pSlayer->getEffectManager();

			double temp     = (double)((double)HPAmount/(double)HPQuantity);
			int    Period   = (uint)ceil(temp);
			Turn_t Deadline = Period* HPDelayProvider;

			if (pSlayer->isFlag(Effect::EFFECT_CLASS_HP_RECOVERY)) 
			{
				Effect* pEffect = pEffectManager->findEffect(Effect::EFFECT_CLASS_HP_RECOVERY);
				EffectHPRecovery* pEffectHPRecoveryEffect = dynamic_cast<EffectHPRecovery*>(pEffect);

				// ������ ������� Ƚ���� ä��� HP���� ����Ѵ�.
				// �װ��� ���� ȸ���翡 ���Ѵ�.
				int PrevHPAmount = pEffectHPRecoveryEffect->getHPQuantity()* pEffectHPRecoveryEffect->getPeriod();
				HPAmount = min((int)(HPAmount + PrevHPAmount), MaxHP - CurrentHP);

				// �� �߿� ū ����ȸ����� ���� �����̸� ����.
				HPQuantity      = max(HPQuantity,      (int)(pEffectHPRecoveryEffect->getHPQuantity()));
				HPDelayProvider = min(HPDelayProvider, (int)(pEffectHPRecoveryEffect->getDelay()));

				// ���� ȸ������ ������, �󸶾� ����� ȸ���� ���ΰ��� �����Ѵ�.
				temp     = (double)((double)HPAmount/(double)HPQuantity);
				Period   = (uint)ceil(temp);
				Deadline = Period* HPDelayProvider;

				// HP Recovery effect�� �����Ѵ�.
				pEffectHPRecoveryEffect->setDeadline(Deadline);
				pEffectHPRecoveryEffect->setDelay(HPDelayProvider);
				pEffectHPRecoveryEffect->setHPQuantity(HPQuantity);
				pEffectHPRecoveryEffect->setPeriod(Period);

				// ȸ�� �����϶�� ��Ŷ�� �ڽſ��� ������.
				GCHPRecoveryStartToSelf gcHPRecoveryStartToSelf;
				gcHPRecoveryStartToSelf.setPeriod(pEffectHPRecoveryEffect->getPeriod());
				gcHPRecoveryStartToSelf.setDelay(pEffectHPRecoveryEffect->getDelay());
				gcHPRecoveryStartToSelf.setQuantity(pEffectHPRecoveryEffect->getHPQuantity());

				pGamePlayer->sendPacket(&gcHPRecoveryStartToSelf);

				// ȸ�� �����϶�� ��Ŷ�� �ٸ��̵鿡�� ������.
				// ȸ�� ���� ��Ŷ, ���۰� �� ���� ��Ŷ�� ������.
				GCHPRecoveryStartToOthers gcHPRecoveryStartToOthers;
				gcHPRecoveryStartToOthers.setObjectID(pSlayer->getObjectID());
				gcHPRecoveryStartToOthers.setPeriod(pEffectHPRecoveryEffect->getPeriod());
				gcHPRecoveryStartToOthers.setDelay(pEffectHPRecoveryEffect->getDelay());
				gcHPRecoveryStartToOthers.setQuantity(pEffectHPRecoveryEffect->getHPQuantity());

				pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcHPRecoveryStartToOthers, pSlayer);
				GCUseOK _GCUseOK;
				pGamePlayer->sendPacket(&_GCUseOK);
			} 
			else 
			{
				EffectHPRecovery* pEffectHPRecovery = new EffectHPRecovery();

				pEffectHPRecovery->setTarget(pSlayer);
				pEffectHPRecovery->setDeadline(Deadline);
				pEffectHPRecovery->setDelay(HPDelayProvider);
				pEffectHPRecovery->setNextTime(0);
				pEffectHPRecovery->setHPQuantity(HPQuantity);
				pEffectHPRecovery->setPeriod(Period);

				pEffectManager->addEffect(pEffectHPRecovery);

				// ȸ�� �����϶�� ��Ŷ�� �ڽſ��� ������.
				GCHPRecoveryStartToSelf gcHPRecoveryStartToSelf;
				gcHPRecoveryStartToSelf.setPeriod(Period);
				gcHPRecoveryStartToSelf.setDelay(HPDelayProvider);
				gcHPRecoveryStartToSelf.setQuantity(HPQuantity);

				pGamePlayer->sendPacket(&gcHPRecoveryStartToSelf);

				// ȸ�� �����϶�� ��Ŷ�� �����̵鿡�� ������.
				GCHPRecoveryStartToOthers gcHPRecoveryStartToOthers;
				gcHPRecoveryStartToOthers.setObjectID(pSlayer->getObjectID());
				gcHPRecoveryStartToOthers.setPeriod(Period);
				gcHPRecoveryStartToOthers.setDelay(HPDelayProvider);
				gcHPRecoveryStartToOthers.setQuantity(HPQuantity);

				pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcHPRecoveryStartToOthers, pSlayer);
				GCUseOK _GCUseOK;
				pGamePlayer->sendPacket(&_GCUseOK);
			}

			if(!SubInventoryTrue)
				decreaseItemNum(pItem, pInventory, pSlayer->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);	
			else
				decreaseItemNum(pItem, pInventory, pSlayer->getName(), STORAGE_BOX, StorageID, InvenX, InvenY);
	
		} 
		else 
		{
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pGamePlayer->sendPacket(&_GCCannotUse);
			return;
		}
	} 
	else 
	{
		notRecoverHP = true;
	}

	// MP ȸ������ �����Ѵٸ�...
	if (MPAmount != 0 && MPQuantity != 0)
	{
		if (CurrentMP < MaxMP) 
		{
			EffectManager* pEffectManager = pSlayer->getEffectManager();

			double temp     = (double)((double)MPAmount/(double)MPQuantity);
			uint   Period   = (uint)ceil(temp);
			Turn_t Deadline = Period* MPDelayProvider;

			if (pSlayer->isFlag(Effect::EFFECT_CLASS_MP_RECOVERY)) 
			{
				Effect* pEffect = pEffectManager->findEffect(Effect::EFFECT_CLASS_MP_RECOVERY);
				EffectMPRecovery* pEffectMPRecoveryEffect = dynamic_cast<EffectMPRecovery*>(pEffect);

				// ������ ������� Ƚ���� ä��� MP���� ����Ѵ�.
				// �װ��� ���� ȸ���翡 ���Ѵ�.
				int PrevMPAmount = pEffectMPRecoveryEffect->getMPQuantity()* pEffectMPRecoveryEffect->getPeriod();
				MPAmount = min((int)(MPAmount + PrevMPAmount), MaxMP - CurrentMP);

				// �� �߿� ū ����ȸ����� ���� �����̸� ����.
				MPQuantity      = max(MPQuantity,      (int)(pEffectMPRecoveryEffect->getMPQuantity()));
				MPDelayProvider = min(MPDelayProvider, (int)(pEffectMPRecoveryEffect->getDelay()));

				// ���� ȸ������ ������, �󸶾� ����� ȸ���� ���ΰ��� �����Ѵ�.
				temp     = (double)((double)MPAmount/(double)MPQuantity);
				Period   = (uint)ceil(temp);
				Deadline = Period* MPDelayProvider;

				// MP Recovery effect�� �����Ѵ�.
				pEffectMPRecoveryEffect->setDeadline(Deadline);
				pEffectMPRecoveryEffect->setDelay(MPDelayProvider);
				pEffectMPRecoveryEffect->setMPQuantity(MPQuantity);
				pEffectMPRecoveryEffect->setPeriod(Period);

				// ȸ�� �����϶�� ��Ŷ�� �ڽſ��� ������.
				GCMPRecoveryStart gcMPRecoveryStart;
				gcMPRecoveryStart.setPeriod(pEffectMPRecoveryEffect->getPeriod());
				gcMPRecoveryStart.setDelay(pEffectMPRecoveryEffect->getDelay());
				gcMPRecoveryStart.setQuantity(pEffectMPRecoveryEffect->getMPQuantity());

				pGamePlayer->sendPacket(&gcMPRecoveryStart);

				GCUseOK _GCUseOK;
				pGamePlayer->sendPacket(&_GCUseOK);
			} 
			else 
			{
				EffectMPRecovery* pEffectMPRecovery = new EffectMPRecovery();

				pEffectMPRecovery->setTarget(pSlayer);
				pEffectMPRecovery->setDeadline(Deadline);
				pEffectMPRecovery->setDelay(MPDelayProvider);
				pEffectMPRecovery->setNextTime(0);
				pEffectMPRecovery->setMPQuantity(MPQuantity);
				pEffectMPRecovery->setPeriod(Period);

				pEffectManager->addEffect(pEffectMPRecovery);

				// ȸ�� �����϶�� ��Ŷ�� �ڽſ��� ������.
				GCMPRecoveryStart gcMPRecoveryStart;
				gcMPRecoveryStart.setPeriod(Period);
				gcMPRecoveryStart.setDelay(MPDelayProvider);
				gcMPRecoveryStart.setQuantity(MPQuantity);

				pGamePlayer->sendPacket(&gcMPRecoveryStart);

				GCUseOK _GCUseOK;
				pGamePlayer->sendPacket(&_GCUseOK);

			}

			if(!SubInventoryTrue)
				decreaseItemNum(pItem, pInventory, pSlayer->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);	
			else
				decreaseItemNum(pItem, pInventory, pSlayer->getName(), STORAGE_BOX, StorageID, InvenX, InvenY);
		} 
		else 
		{
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pGamePlayer->sendPacket(&_GCCannotUse);
			return;
		}
	} 
	else 
	{
		notRecoverMP = true;
	}

	if (notRecoverHP && notRecoverMP)
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

#endif

    __END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUseItemFromInventoryHandler::executeMagazine(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// ���� �Լ����� ���� üũ�� ���� �߱� ������,
	// ���� üũ�� ���� ����Ѵ�.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	//Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	ObjectID_t      ItemObjectID = pItem->getObjectID();

	Assert(pCreature->isSlayer());

	Slayer*      pSlayer     = dynamic_cast<Slayer*>(pCreature);
	Item*        pArmsItem   = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
	bool         bSuccess    = false;

	if (pArmsItem != NULL) 
	{
		if (isArmsWeapon(pArmsItem))
		{
			SkillSlot*	pVivid = pSlayer->getSkill( SKILL_VIVID_MAGAZINE );
			bool		hasVivid = (pVivid != NULL) && pVivid->canUse();

			if (isSuitableMagazine(pArmsItem, pItem, hasVivid)) bSuccess = true;
		}
	} 

	// reload delay�� �����Ƿ� effect�� ��� ��Ų��.
	EffectManager* pEffectManager = pSlayer->getEffectManager();
	if (pEffectManager == NULL) return;

	if (bSuccess && !pSlayer->isFlag(Effect::EFFECT_CLASS_RELOAD_TIMER)) 
	{
		EffectReloadTimer* pEffect = new EffectReloadTimer(pSlayer);
		
		pEffect->setFromInventory(true);
		pEffect->setObjectID(ItemObjectID);
		pEffect->setInventoryXY(InvenX, InvenY);
		
		// by sigi. 2002.12.3.  1�� --> 0.7��
		if (pSlayer->hasSkill(SKILL_FAST_RELOAD)) pEffect->setDeadline(7); // ���� reload(0.7??
		else                                      pEffect->setDeadline(2*10); // ���� reload(2sec)

		pSlayer->setFlag(Effect::EFFECT_CLASS_RELOAD_TIMER);
		pEffectManager->addEffect(pEffect);

		if ( pSlayer->isFlag( Effect::EFFECT_CLASS_INSTALL_TURRET ) ){
		pSlayer->removeFlag(Effect::EFFECT_CLASS_INSTALL_TURRET );
		}
	} 
	else 
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotUse);
	}

#endif

    __END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUseItemFromInventoryHandler::executeETC(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// ���� �Լ����� ���� üũ�� ���� �߱� ������,
	// ���� üũ�� ���� ����Ѵ�.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	//Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	//ObjectID_t      ItemObjectID = pItem->getObjectID();

	Storage_t Storage = STORAGE_INVENTORY;
	StorageID_t StorageID = 0;

	bool SubInventoryTrue = false;

	if(pPacket->getInventoryItemObjectID() != 0){
		Item*           pInvenItem        = NULL;
		pInvenItem        = pInventory->getItemWithObjectID(pPacket->getInventoryItemObjectID());
		SubInventory* pSubInventory = dynamic_cast<SubInventory*>(pInvenItem);
		SubInventoryTrue = true;
		Storage = STORAGE_BOX;
		StorageID = pInvenItem->getItemID();
		pInventory = ((SubInventory*)pSubInventory)->getInventory();
	}

	Item*           pItem        = pInventory->getItem(InvenX, InvenY);

	// �������� ���̴� ������ �������̶��, 
	// ����� ������ �׸�ŭ ������ �� �ش�.
	if (isStackable(pItem))
	{
		if(!SubInventoryTrue)
		decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_INVENTORY, StorageID, InvenX, InvenY);
		else
		decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_BOX, StorageID, InvenX, InvenY);
	}
	else 
	{
		// ������ �ʴ� �������� �ٷιٷ� �������ش�.
		pInventory->deleteItem(InvenX, InvenY);
		pItem->destroy();
		SAFE_DELETE(pItem);
	}

#endif

    __END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUseItemFromInventoryHandler::executeSerum(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__


	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// ���� �Լ����� ���� üũ�� ���� �߱� ������,
	// ���� üũ�� ���� ����Ѵ�.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	//ObjectID_t      ItemObjectID = pItem->getObjectID();

	Storage_t Storage = STORAGE_INVENTORY;
	StorageID_t StorageID = 0;

	bool SubInventoryTrue = false;

	if(pPacket->getInventoryItemObjectID() != 0){
		Item*           pInvenItem        = NULL;
		pInvenItem        = pInventory->getItemWithObjectID(pPacket->getInventoryItemObjectID());
		SubInventory* pSubInventory = dynamic_cast<SubInventory*>(pInvenItem);
		SubInventoryTrue = true;
		Storage = STORAGE_BOX;
		StorageID = pInvenItem->getItemID();
		pInventory = ((SubInventory*)pSubInventory)->getInventory();
	}

	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	Assert(pCreature->isVampire());

	Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

	// �ڸ� ���¶�� ����� �� ����.
	if (pVampire->isFlag(Effect::EFFECT_CLASS_COMA)
		// ������ ���� ���� ����ڰ� �ƴϸ� ����� �� ����.
		|| pItem->getItemType()==5 && !pGamePlayer->isPayPlaying() && !pGamePlayer->isPremiumPlay())
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	HP_t   MaxHP       = pVampire->getHP(ATTR_MAX);
	HP_t   CurrentHP   = pVampire->getHP(ATTR_CURRENT);
	Serum* pSerum      = dynamic_cast<Serum*>(pItem);
	int    RegenHP     = 0;

	RegenHP = pSerum->getHPAmount();

	int    RegenPeriod = pSerum->getPeriod()*10; // ���� �ð��� �ֱ�
	int    RegenCount  = pSerum->getCount();     // ��� ���� �ð��� �ݺ��� ���ΰ�?

	int    RegenHPUnit = (int)((float)MaxHP* (float)RegenHP* 0.01); // �ѹ��� ȸ���ϴ� HP�� ��
	int    HPAmount    = min(MaxHP - CurrentHP , RegenHPUnit* RegenCount);

	// HP ȸ������ �����Ѵٸ�...
	if (HPAmount != 0)
	{
		// �󸶾� ��� ���ʸ���.
		if (CurrentHP < MaxHP) 
		{
			EffectManager* pEffectManager = pVampire->getEffectManager(); 
			Turn_t 	       Period         = RegenCount; // ��� ȸ����Ű��?
			Turn_t	       Deadline       = RegenPeriod* Period;   // ���� ������?

			if (pVampire->isFlag(Effect::EFFECT_CLASS_HP_RECOVERY)) 
			{
				Effect*     pEffect           = pEffectManager->findEffect(Effect::EFFECT_CLASS_HP_RECOVERY);
				EffectHPRecovery* pEffectHPRecoveryEffect = dynamic_cast<EffectHPRecovery*>(pEffect);

				// ��� �� �ؾ� �Ѵٴ� ���� ������ �ش�.
				Turn_t OldCount  = pEffectHPRecoveryEffect->getPeriod();
				Turn_t NewPeriod = OldCount + Period;
				pEffectHPRecoveryEffect->setPeriod(NewPeriod);
				pEffectHPRecoveryEffect->setDeadline(NewPeriod* RegenPeriod);

				// ȸ�� �����϶�� ��Ŷ�� �ڽſ��� ������.
				GCHPRecoveryStartToSelf gcHPRecoveryStartToSelf;
				gcHPRecoveryStartToSelf.setPeriod(NewPeriod); // ��� ȸ���ϳ�?
				gcHPRecoveryStartToSelf.setDelay(RegenPeriod); // �� �� ������ �ϳ�?
				gcHPRecoveryStartToSelf.setQuantity(RegenHPUnit); // �ѹ��� �󸶳� ȸ���ϳ�?

				pGamePlayer->sendPacket(&gcHPRecoveryStartToSelf);

				// ȸ�� �����϶�� ��Ŷ�� �ٸ��̵鿡�� ������.
				// ȸ�� ���� ��Ŷ, ���۰� �� ���� ��Ŷ�� ������.
				GCHPRecoveryStartToOthers gcHPRecoveryStartToOthers;
				gcHPRecoveryStartToOthers.setObjectID(pVampire->getObjectID());
				gcHPRecoveryStartToOthers.setPeriod(NewPeriod);
				gcHPRecoveryStartToOthers.setDelay(RegenPeriod );
				gcHPRecoveryStartToOthers.setQuantity(RegenHPUnit);

				pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcHPRecoveryStartToOthers, pVampire);
				GCUseOK _GCUseOK;
				pGamePlayer->sendPacket(&_GCUseOK);
			} 
			else 
			{
				EffectHPRecovery* pEffectHPRecovery = new EffectHPRecovery();

				pEffectHPRecovery->setTarget(pVampire);
				pEffectHPRecovery->setDeadline(Deadline);
				pEffectHPRecovery->setDelay(RegenPeriod);
				pEffectHPRecovery->setNextTime(0);
				pEffectHPRecovery->setHPQuantity(RegenHPUnit);
				pEffectHPRecovery->setPeriod(Period);

				pEffectManager->addEffect(pEffectHPRecovery);

				// ȸ�� ������?�?��Ŷ�� �ڽſ��� ������.
				GCHPRecoveryStartToSelf gcHPRecoveryStartToSelf;
				gcHPRecoveryStartToSelf.setPeriod(Period);
				gcHPRecoveryStartToSelf.setDelay(RegenPeriod);
				gcHPRecoveryStartToSelf.setQuantity(RegenHPUnit);

				pGamePlayer->sendPacket(&gcHPRecoveryStartToSelf);

				// ȸ�� �����϶�� ��Ŷ�� �����̵鿡�� ������.
				GCHPRecoveryStartToOthers gcHPRecoveryStartToOthers;
				gcHPRecoveryStartToOthers.setObjectID(pVampire->getObjectID());
				gcHPRecoveryStartToOthers.setPeriod(Period);
				gcHPRecoveryStartToOthers.setDelay(RegenPeriod);
				gcHPRecoveryStartToOthers.setQuantity(RegenHPUnit);

				pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcHPRecoveryStartToOthers, pVampire);

				GCUseOK _GCUseOK;
				pGamePlayer->sendPacket(&_GCUseOK);
			}
		} 
		else 
		{
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pGamePlayer->sendPacket(&_GCCannotUse);
			return;
		}
	}
	else
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}
	if(!SubInventoryTrue)
	decreaseItemNum(pItem, pInventory, pVampire->getName(), STORAGE_INVENTORY, StorageID, InvenX, InvenY);
	else
	decreaseItemNum(pItem, pInventory, pVampire->getName(), STORAGE_BOX, StorageID, InvenX, InvenY);
#endif

    __END_DEBUG_EX __END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUseItemFromInventoryHandler::executeVampireETC(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	/*
	// ���� �Լ����� ���� üũ�� ���� �߱� ������,
	// ���� üũ�� ���� ����Ѵ�.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();

	Storage_t Storage = STORAGE_INVENTORY;
	StorageID_t StorageID = 0;

	bool SubInventoryTrue = false;

	if(pPacket->getInventoryItemObjectID() != 0){
		Item*           pInvenItem        = NULL;
		pInvenItem        = pInventory->getItemWithObjectID(pPacket->getInventoryItemObjectID());
		SubInventory* pSubInventory = dynamic_cast<SubInventory*>(pInvenItem);
		SubInventoryTrue = true;
		Storage = STORAGE_BOX;
		StorageID = pInvenItem->getItemID();
		pInventory = ((SubInventory*)pSubInventory)->getInventory();
	}

	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	ObjectID_t      ItemObjectID = pItem->getObjectID();

	// �������� ���̴� ������ �������̶��, 
	// ����� ������ �׸�ŭ ������ �� �ش�.
	if (isStackable(pItem))
	{
		if(!SubInventoryTrue)
		decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_INVENTORY, StorageID, InvenX, InvenY);
		else
		decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_BOX, StorageID, InvenX, InvenY);
	}
	else 
	{
		// ������ �ʴ� �������� �ٷιٷ� �������ش�.
		pInventory->deleteItem(InvenX, InvenY);
		pItem->destroy();
		SAFE_DELETE(pItem);
	}
	*/

#endif

    __END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUseItemFromInventoryHandler::executeSlayerPortalItem(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// ���� �Լ����� ���� üũ�� ���� �߱� ������,
	// ���� üũ�� ���� ����Ѵ�.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	//ObjectID_t      ItemObjectID = pItem->getObjectID();

	Storage_t Storage = STORAGE_INVENTORY;
	StorageID_t StorageID = 0;

	bool SubInventoryTrue = false;

	if(pPacket->getInventoryItemObjectID() != 0){
		Item*           pInvenItem        = NULL;
		pInvenItem        = pInventory->getItemWithObjectID(pPacket->getInventoryItemObjectID());
		SubInventory* pSubInventory = dynamic_cast<SubInventory*>(pInvenItem);
		SubInventoryTrue = true;
		Storage = STORAGE_BOX;
		StorageID = pInvenItem->getItemID();
		pInventory = ((SubInventory*)pSubInventory)->getInventory();
	}

	Item*           pItem        = pInventory->getItem(InvenX, InvenY);

	Assert(pCreature->isSlayer());

	Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
	SlayerPortalItem* pPortalItem = dynamic_cast<SlayerPortalItem*>(pItem);

	Assert(pSlayer != NULL);
	Assert(pPortalItem != NULL);

	Store* pStore = pSlayer->getStore();
	if ( pStore->isOpen() )
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	// ���� Relic�� �����ϰ� �ִٸ�,��⸦ �θ� �� ����.
	bool bHasRelic        = false;
	if (pSlayer->hasRelicItem() || pSlayer->isFlag( Effect::EFFECT_CLASS_HAS_FLAG ) || pSlayer->isFlag( Effect::EFFECT_CLASS_HAS_SWEEPER) )
	{
		bHasRelic         = true;
	}

	// ��ȭ�Ǿ� �ִٸ� ��⸦ �θ� �� ����.
	bool bParalyze = pSlayer->isFlag( Effect::EFFECT_CLASS_PARALYZE ) ? true : false;

	bool bZoneTypeCheck   = (pZone->getZoneType() == ZONE_NORMAL_FIELD) ? true : false;
	bool bCanUseCheck     = pSlayer->isRealWearing(pPortalItem);
	bool bChargeCheck     = (pPortalItem->getCharge() > 0) ? true : false;
	//bool bMotorcycleCheck = pSlayer->hasRideMotorcycle();
	bool bZoneCheck		= pZone->isNoPortalZone();

	//if (bZoneTypeCheck && bCanUseCheck && bChargeCheck && !bMotorcycleCheck)
	if (bZoneTypeCheck && bCanUseCheck && bChargeCheck && !bHasRelic && !bParalyze && !bZoneCheck)
	{
		// �����ۿ� ������ ���̰�, �����̾�� ����Ʈ�� �ɾ��ش�.
		pPortalItem->setCharge(pPortalItem->getCharge()-1);
		//pPortalItem->save(pSlayer->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY); // ������ ������ �����Ѵ�.
        // ������ ���� ����ȭ. by sigi. 2002.5.13
        char pField[80];
	    sprintf(pField, "Charge=%d", pPortalItem->getCharge());
		pPortalItem->tinysave(pField);

		pSlayer->setFlag(Effect::EFFECT_CLASS_SLAYER_PORTAL);

		// �ֺ����ٰ� ��� ���϶�� ��Ŷ�� �Ѹ���.
		GCAddHelicopter gcAddHelicopter;
		gcAddHelicopter.setObjectID(pSlayer->getObjectID());
		gcAddHelicopter.setCode(0);
		pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcAddHelicopter);

		// ���� ��Ŷ�� �����ش�.
		GCUseOK gcUseOK;
		pPlayer->sendPacket(&gcUseOK);
	}
	else
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
	}

#endif

    __END_DEBUG_EX __END_CATCH
}

void CGUseItemFromInventoryHandler::executeOustersSummonItem(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_DEBUG_EX __BEGIN_TRY

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// ���� �Լ����� ���� üũ�� ���� �߱� ������,
	// ���� üũ�� ���� ����Ѵ�.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	//ObjectID_t      ItemObjectID = pItem->getObjectID();

	Storage_t Storage = STORAGE_INVENTORY;
	StorageID_t StorageID = 0;

	bool SubInventoryTrue = false;

	if(pPacket->getInventoryItemObjectID() != 0){
		Item*           pInvenItem        = NULL;
		pInvenItem        = pInventory->getItemWithObjectID(pPacket->getInventoryItemObjectID());
		SubInventory* pSubInventory = dynamic_cast<SubInventory*>(pInvenItem);
		SubInventoryTrue = true;
		Storage = STORAGE_BOX;
		StorageID = pInvenItem->getItemID();
		pInventory = ((SubInventory*)pSubInventory)->getInventory();
	}

	Item*           pItem        = pInventory->getItem(InvenX, InvenY);

	if ( SiegeManager::Instance().isSiegeZone(pPC->getZoneID()) || pZone->isNoPortalZone() )
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	Assert(pCreature->isOusters());

	Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
	pOusters->setWingSylphType(1);
	pOusters->setWingItemType(0);
	pOusters->setWingColor(0);
	pOusters->setWingEffectColor(0);
	OustersSummonItem* pSummonItem = dynamic_cast<OustersSummonItem*>(pItem);

	Assert(pOusters != NULL);
	Assert(pSummonItem != NULL);

	// ���� Relic�� �����ϰ� �ִٸ�,��⸦ �θ� �� ����.
	bool bHasRelic        = false;
	if (pOusters->hasRelicItem()||pOusters->isFlag(Effect::EFFECT_CLASS_REFINIUM_TICKET)
		||pOusters->isFlag( Effect::EFFECT_CLASS_SUMMON_SYLPH )
		|| GDRLairManager::Instance().isGDRLairZone( pZone->getZoneID() )
		|| (pZone->isDynamicZone() && pZone->getDynamicZone()->getTemplateZoneID() == 4002)
	)
	{
		bHasRelic         = true;
	}

	// ��ȭ�Ǿ� �ִٸ� ��⸦ �θ� �� ����.
	bool bParalyze = pOusters->isFlag( Effect::EFFECT_CLASS_PARALYZE ) ? true : false;

	bool bCanUseCheck     = pOusters->isRealWearing(pSummonItem);
	bool bChargeCheck     = (pSummonItem->getCharge() > 0) ? true : false;
	//bool bMotorcycleCheck = pOusters->hasRideMotorcycle();

	SkillType_t       SkillType  = SKILL_SUMMON_SYLPH;
	SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
	OustersSummonItemInfo*	pItemInfo	 = dynamic_cast<OustersSummonItemInfo*>(g_pItemInfoManager->getItemInfo( pItem->getItemClass(), pItem->getItemType() ));
	Assert( pItemInfo != NULL );

	int RequireMP	= (int)pSkillInfo->getConsumeMP();
	bool bManaCheck	= hasEnoughMana(pOusters, RequireMP);
	bool bTileCheck = checkZoneLevelToUseSkill(pOusters);
	bool bEffect	= pOusters->isFlag( Effect::EFFECT_CLASS_SUMMON_SYLPH );
	bool bSatisfyRequire = pOusters->satisfySkillRequire( pSkillInfo );
	bool bRangeCheck = checkZoneLevelToUseSkill(pOusters);

	if (bCanUseCheck && bChargeCheck && !bHasRelic && !bParalyze && bTileCheck
		&& bManaCheck && !bEffect && bSatisfyRequire && bRangeCheck)
	{
		GCModifyInformation gcMI;

		decreaseMana(pOusters, RequireMP, gcMI);
		// �����ۿ� ������ ���̰�, �����̾�� ����Ʈ�� �ɾ��ش�.
		pSummonItem->setCharge(pSummonItem->getCharge()-1);
		//pSummonItem->save(pOusters->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY); // ������ ������ �����Ѵ�.
        // ������ ���� ����ȭ. by sigi. 2002.5.13
        char pField[80];
	    sprintf(pField, "Charge=%d", pSummonItem->getCharge());
		pSummonItem->tinysave(pField);

		// ����Ʈ Ŭ������ ����� ���δ�.
		EffectSummonSylph* pEffect = new EffectSummonSylph(pOusters);
		pEffect->setEClass( (Effect::EffectClass)pItemInfo->getEffectID() );
		pOusters->addEffect(pEffect);
		pOusters->setFlag( Effect::EFFECT_CLASS_SUMMON_SYLPH );

		OUSTERS_RECORD prev;
		pOusters->getOustersRecord(prev);
		pOusters->initAllStat();
		pOusters->addModifyInfo(prev, gcMI);

		// ���� ��Ŷ�� �����ش�.
		GCUseOK gcUseOK;
		pPlayer->sendPacket(&gcUseOK);
		pPlayer->sendPacket(&gcMI);

		GCAddEffect gcAddEffect;
		gcAddEffect.setObjectID( pOusters->getObjectID() );
		gcAddEffect.setEffectID( pEffect->getSendEffectClass() );
		gcAddEffect.setDuration( pEffect->getRemainDuration() );

		pZone->broadcastPacket( pOusters->getX(), pOusters->getY(), &gcAddEffect, pOusters );
		pPlayer->sendPacket( &gcAddEffect );

		if ( pOusters->getPetInfo() != NULL )
		{
			pOusters->setPetInfo( NULL );
			sendPetInfo( pGamePlayer, true );
		}

		pOusters->getGQuestManager()->rideMotorcycle();
	}
	else
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
	}

	

#endif

	__END_DEBUG_EX __END_CATCH
}

void CGUseItemFromInventoryHandler::executeOustersWingItem(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_DEBUG_EX __BEGIN_TRY

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// ���� �Լ����� ���� üũ�� ���� �߱� ������,
	// ���� üũ�� ���� ����Ѵ�.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	//ObjectID_t      ItemObjectID = pItem->getObjectID();

	Storage_t Storage = STORAGE_INVENTORY;
	StorageID_t StorageID = 0;

	bool SubInventoryTrue = false;

	if(pPacket->getInventoryItemObjectID() != 0){
		Item*           pInvenItem        = NULL;
		pInvenItem        = pInventory->getItemWithObjectID(pPacket->getInventoryItemObjectID());
		SubInventory* pSubInventory = dynamic_cast<SubInventory*>(pInvenItem);
		SubInventoryTrue = true;
		Storage = STORAGE_BOX;
		StorageID = pInvenItem->getItemID();
		pInventory = ((SubInventory*)pSubInventory)->getInventory();
	}

	Item*           pItem        = pInventory->getItem(InvenX, InvenY);

	if ( SiegeManager::Instance().isSiegeZone(pPC->getZoneID()) || pZone->isNoPortalZone() )
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	Assert(pCreature->isOusters());

	Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
	OustersWingItem* pSummonItem = dynamic_cast<OustersWingItem*>(pItem);

	Assert(pOusters != NULL);
	Assert(pSummonItem != NULL);

	// ���� Relic�� �����ϰ� �ִٸ�,��⸦ �θ� �� ����.
	bool bHasRelic        = false;
	if (pOusters->hasRelicItem()||pOusters->isFlag(Effect::EFFECT_CLASS_REFINIUM_TICKET)
		||pOusters->isFlag( Effect::EFFECT_CLASS_SUMMON_SYLPH )
		|| GDRLairManager::Instance().isGDRLairZone( pZone->getZoneID() )
		|| (pZone->isDynamicZone() && pZone->getDynamicZone()->getTemplateZoneID() == 4002)
	)
	{
		bHasRelic         = true;
	}

	// ��ȭ�Ǿ� �ִٸ� ��⸦ �θ� �� ����.
	bool bParalyze = pOusters->isFlag( Effect::EFFECT_CLASS_PARALYZE ) ? true : false;

	bool bCanUseCheck     = pOusters->isRealWearing(pSummonItem);
	//bool bMotorcycleCheck = pOusters->hasRideMotorcycle();

	SkillType_t       SkillType  = SKILL_SUMMON_SYLPH;
	SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
	OustersWingItemInfo*	pItemInfo	 = dynamic_cast<OustersWingItemInfo*>(g_pItemInfoManager->getItemInfo( pItem->getItemClass(), pItem->getItemType() ));

	pOusters->setWingSylphType(2);
	pOusters->setWingItemType(pItem->getItemType());
	pOusters->setWingColor(pItemInfo->getDefaulBodyColor());
	pOusters->setWingEffectColor(pItemInfo->getDefaulEffectColor());
	Assert( pItemInfo != NULL );

	int RequireMP	= (int)pSkillInfo->getConsumeMP();
	bool bManaCheck	= hasEnoughMana(pOusters, RequireMP);
	bool bTileCheck = checkZoneLevelToUseSkill(pOusters);
	bool bEffect	= pOusters->isFlag( Effect::EFFECT_CLASS_SUMMON_SYLPH );
	bool bSatisfyRequire = pOusters->satisfySkillRequire( pSkillInfo );
	bool bRangeCheck = checkZoneLevelToUseSkill(pOusters);

	if (bCanUseCheck && !bHasRelic && !bParalyze && bTileCheck
		&& bManaCheck && !bEffect && bSatisfyRequire && bRangeCheck)
	{
		GCModifyInformation gcMI;

		decreaseMana(pOusters, RequireMP, gcMI);

		// ����Ʈ Ŭ������ ����� ���δ�.
		EffectSummonSylph* pEffect = new EffectSummonSylph(pOusters);
		pEffect->setEClass( (Effect::EffectClass)245 );

		pOusters->addEffect(pEffect);
		pOusters->setFlag( Effect::EFFECT_CLASS_SUMMON_SYLPH );

		OUSTERS_RECORD prev;
		pOusters->getOustersRecord(prev);
		pOusters->initAllStat();
		pOusters->addModifyInfo(prev, gcMI);

		// ���� ��Ŷ�� �����ش�.
		GCUseOK gcUseOK;
		pPlayer->sendPacket(&gcUseOK);
		pPlayer->sendPacket(&gcMI);

		GCAddSylph gcAddSylph;
		gcAddSylph.setObjectID( pOusters->getObjectID() );
		gcAddSylph.setSylphType( pOusters->getWingSylphType() );
		gcAddSylph.setWingItemType( pItem->getItemType() );
		gcAddSylph.setWingBodyColor( pItemInfo->getDefaulBodyColor() );
		gcAddSylph.setWingEffectColor( pItemInfo->getDefaulEffectColor() );
		pPlayer->sendPacket(&gcAddSylph);
		pZone->broadcastPacket( pOusters->getX(), pOusters->getY(), &gcAddSylph, pOusters );

		/*GCAddEffect gcAddEffect;
		gcAddEffect.setObjectID( pOusters->getObjectID() );
		gcAddEffect.setEffectID( 556 );
		gcAddEffect.setDuration( pEffect->getRemainDuration() );

		pZone->broadcastPacket( pOusters->getX(), pOusters->getY(), &gcAddEffect, pOusters );
		pPlayer->sendPacket( &gcAddEffect );*/

		if ( pOusters->getPetInfo() != NULL )
		{
			pOusters->setPetInfo( NULL );
			sendPetInfo( pGamePlayer, true );
		}

		pOusters->getGQuestManager()->rideMotorcycle();
	}
	else
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
	}

	

#endif

	__END_DEBUG_EX __END_CATCH
}

void CGUseItemFromInventoryHandler::executeKeyItem(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	////cout << pPacket->toString().c_str() << endl;

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// ���� �Լ����� ���� üũ�� ���� �߱� ������,
	// ���� üũ�� ���� ����Ѵ�.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	//ObjectID_t      ItemObjectID = pItem->getObjectID();

	Storage_t Storage = STORAGE_INVENTORY;
	StorageID_t StorageID = 0;

	bool SubInventoryTrue = false;

	if(pPacket->getInventoryItemObjectID() != 0){
		Item*           pInvenItem        = NULL;
		pInvenItem        = pInventory->getItemWithObjectID(pPacket->getInventoryItemObjectID());
		SubInventory* pSubInventory = dynamic_cast<SubInventory*>(pInvenItem);
		SubInventoryTrue = true;
		Storage = STORAGE_BOX;
		StorageID = pInvenItem->getItemID();
		pInventory = ((SubInventory*)pSubInventory)->getInventory();
	}

	Item*           pItem        = pInventory->getItem(InvenX, InvenY);

	//
	if ( SiegeManager::Instance().isSiegeZone(pPC->getZoneID()) )
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	// SLAYER�� �ƴ϶�� ������̸� ȣ���� �� ����.
	Assert(pCreature->isSlayer());

	Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
	
	// ��ȯ ���� ���� ������ �Ǿ��־�� �Ѵ�.
	// �ڸ� ���¶�� ����� �� ����.
	// ?������?���� �������� �ƴ϶��, ������̸� ȣ���� �� ����.
	// ������ ��� ��Ż ��� �Ұ� ������ ������� ��ȯ �Ұ�
	// premium ����ڸ� ȣ�Ⱑ���ϴ�.
	if (!g_pVariableManager->isSummonMotorcycle()
		|| pSlayer->hasRideMotorcycle()
		|| pItem->getItemClass() != Item::ITEM_CLASS_KEY
		|| pSlayer->isFlag(Effect::EFFECT_CLASS_COMA)
		|| (pZone->getZoneLevel(pCreature->getX(), pCreature->getY()) & SAFE_ZONE)
		|| pZone->isMasterLair() || pZone->isNoPortalZone()
		|| (!pGamePlayer->isPremiumPlay() && !pGamePlayer->isPayPlaying())
		|| g_pFlagManager->isInPoleField( ZONE_COORD( pZone->getZoneID(), pCreature->getX(), pCreature->getY() ) )
		|| GDRLairManager::Instance().isGDRLairZone( pZone->getZoneID() )
	)
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	// ������ �������� �����Ǿ� �ִ����� Ȯ���Ѵ�.
	ItemID_t targetID = dynamic_cast<Key*>(pItem)->getTarget();

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	// targetID�� 0�� ����.. targetID(motorcycleObject�� ItemID)�� ������ �ȵ� ����.
	// �� ���� �ӽ÷� targetID�� key�� ItemID�� ���� �ϸ� �ȴ�...�� ����.
	// targetID�� motorcycle�� itemID�� ���� ������..
	// broadcasting ���.. Assert()�� ���ؼ� �ٿ�Ǿ���...�� ��������.  - -;
	// by sigi. 2002.12.25 x-mas T_T;
	if (targetID==0)
	{
		Key* pKey = dynamic_cast<Key*>(pItem);
		Assert( pKey != NULL );

		targetID = pKey->setNewMotorcycle(pSlayer);
/*		// (!) MotorcycleObject�� �����ϰ� MotorcycleItemID==Target�� �޾ƾ� �Ѵ�.
		// �� �ڵ� ���� �Լ��� ���⸦.. -_-; by sigi
		Key* pKey = dynamic_cast<Key*>(pItem);

		KeyInfo* pKeyInfo = dynamic_cast<KeyInfo*>(g_pItemInfoManager->getItemInfo( pKey->getItemClass(), pKey->getItemType() ));
		Assert( pKeyInfo != NULL );

		list<OptionType_t> option;
		ItemType_t motorcycleType = pKeyInfo->getTargetType();

		if ( pKeyInfo->getOptionType() != 0 ) option.push_back( pKeyInfo->getOptionType() );

		Item* pMotorcycle = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_MOTORCYCLE, motorcycleType, option);
		Assert(pMotorcycle != NULL);
		(pZone->getObjectRegistry()).registerObject(pMotorcycle);

		pMotorcycle->create(pSlayer->getName(), STORAGE_ZONE, pZone->getZoneID(), pSlayer->getX(), pSlayer->getY());
		pKey->setTarget(pMotorcycle->getItemID());

		targetID = pMotorcycle->getItemID();

		// targetID�� DB���� update���Ѿ� �Ѵ�.
		BEGIN_DB
		{
			pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pResult = pStmt->executeQuery(
						"UPDATE KeyObject SET Target=%lu WHERE ItemID=%lu", 
									targetID, pKey->getItemID());

			SAFE_DELETE(pStmt);
		}
		END_DB(pStmt)

		// log
		filelog("motorcycle.txt", "[SetTargetID] Owner = %s, KeyID = %lu, Key's targetID = %lu, MotorcycleID = %lu", pSlayer->getName().c_str(), pKey->getItemID(), pKey->getTarget(), pMotorcycle->getItemID() );

		// �ؿ��� pMotorcycle�� ����ص� �ǰ�����, ���� �ڵ� �� �ǵ帱���� ���⼭ �����. 
		SAFE_DELETE(pMotorcycle);*/
	}
	else
	{
		// �ѹ� ���ͻ���Ŭ�̶� Ű�� ����ƴµ� ���ͻ���Ŭ�� ���� �ڲ� ���쳪����.
		// Ű�� ����� ���ͻ���Ŭ�� ������ ��� �ִ��� üũ�ϰ� ������ ���� ���� �־��ش�.
		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pResult = pStmt->executeQuery("SELECT ItemID FROM MotorcycleObject WHERE ItemID=%lu", targetID);
			
			if ( !pResult->next() )
			{
				Key* pKey = dynamic_cast<Key*>(pItem);
				Assert( pKey != NULL );

				targetID = pKey->setNewMotorcycle(pSlayer);
			}

			SAFE_DELETE(pStmt);
		}
		END_DB(pStmt);
	}

	
	// �ʻ� ��� �ڵ� -_-;
	if (targetID==0)
	{
		filelog("errorLog.txt", "[ActionRedeemMotorcycle] itemID=%lu, motorItemID=%lu", (int)pItem->getItemID(), (int)targetID);
		return;
	}


	if (g_pParkingCenter->hasMotorcycleBox(targetID)) 
	{
		////cout << "������ �ҷ��� ������̰� �ֽ��ϴ�" << endl;

		MotorcycleBox* pMotorcycleBox = g_pParkingCenter->getMotorcycleBox(targetID);

		if (pMotorcycleBox!=NULL
			&& !pMotorcycleBox->isTransport())
		{
			Zone* pMotorZone = pMotorcycleBox->getZone();
			ZoneCoord_t motorX = pMotorcycleBox->getX();
			ZoneCoord_t motorY = pMotorcycleBox->getY();
			Motorcycle* pMotorcycle = pMotorcycleBox->getMotorcycle();

			// ���� ���� �ִ� ���
			// �Ÿ��� �ʹ� ������ �θ��� ����~
			if (pMotorZone!=pZone
				|| pSlayer->getDistance(motorX, motorY) > 15)
			{
				// �ٸ� zone���� �̵����̶�� ǥ���Ѵ�.
				pMotorcycleBox->setTransport();

				// motorcycle�� slayer�� zone���� �ű��.
				pMotorZone->transportItem( motorX, motorY, pMotorcycle, 
											pZone, pSlayer->getX(), pSlayer->getY() );

				// Use OK ����̴�.
				// Use�ϸ� �������� ��������� �׷��� �ʹ�. - -;
				/*
				GCCannotUse _GCCannotUse;
				_GCCannotUse.setObjectID(pPacket->getObjectID());
				pGamePlayer->sendPacket(&_GCCannotUse);
				*/

				// �ѵ��� delay�� ����ϴµ�..
			}
		}

		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);

		return;
	}

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT ItemID, ItemType, OptionType, Durability FROM MotorcycleObject WHERE ItemID=%lu", targetID);

		ItemID_t     itemID;
		ItemType_t   itemType;
		list<OptionType_t> optionTypes;
		Durability_t durability;

		bool bFound = false;

		if (pResult->next())
		{
			bFound = true;

			itemID     = pResult->getInt(1);
			itemType   = pResult->getInt(2);

			string optionField = pResult->getString(3);
			setOptionTypeFromField(optionTypes, optionField);

			durability = pResult->getInt(4);
		}
		else
		{
			itemID     = targetID;
			itemType   = 0;
			durability = 300;
		}

		// ���ο� ������� ��ü�� �����Ѵ�.
		Motorcycle* pMotorcycle = new Motorcycle(itemType, optionTypes);

		Assert(pMotorcycle != NULL);

		pMotorcycle->setItemID(itemID);
		pMotorcycle->setDurability(durability);

		// Object ID �Ҵ�ޱ�
		(pZone->getObjectRegistry()).registerObject(pMotorcycle);


		// ������̸� ���� �߰��Ѵ�.
		////cout << "������̸� ���� �߰��մϴ�" << pSlayer->getX() << " " << pSlayer->getY() << endl;
		TPOINT pt = pZone->addItem(pMotorcycle, pSlayer->getX(), pSlayer->getY(), false);

		if(pt.x == -1)
		{
			StringStream msg;
			msg << "������̸� ���� ���� �� �����ϴ�: "
				<< "ZoneID=" << (int)pZone->getZoneID()
				<< ", X=" << (int)pSlayer->getX()
				<< ", Y=" << (int)pSlayer->getY();

			filelog("motorError.txt", "%s", msg.toString().c_str());
			//throw Error("������̸� ���� ���� �� �����ϴ�");

			SAFE_DELETE(pMotorcycle);
		}
		else
		{
			if (!bFound)
			{
				// by sigi. 2002.10.14
				pStmt->executeQuery(
				"INSERT INTO MotorcycleObject (ItemID, ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, OptionType, Durability) Values (%d, %d, %d, '', %d, %d, %d, %d, '', %d)",
					itemID, pMotorcycle->getObjectID(), itemType, STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y, durability);
			}

			// ������̸� Parking Center�� ����Ѵ�.
			MotorcycleBox* pBox = new MotorcycleBox(pMotorcycle, pZone, pt.x, pt.y);
			Assert(pBox != NULL);
			g_pParkingCenter->addMotorcycleBox(pBox);
		}


		// ���� ��Ŷ�̴�.
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		//}
			/*
		else
		{
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pGamePlayer->sendPacket(&_GCCannotUse);

			SAFE_DELETE(pStmt);
			return;
		}
		*/

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt);
#endif
    __END_DEBUG_EX __END_CATCH
}

#ifdef __GAME_SERVER__

static const Effect::EffectClass FirecrackerEffects[] =
{
	Effect::EFFECT_CLASS_FIRE_CRACKER_1,				// 0
	Effect::EFFECT_CLASS_FIRE_CRACKER_2,				// 1
	Effect::EFFECT_CLASS_FIRE_CRACKER_3,				// 2
	Effect::EFFECT_CLASS_DRAGON_FIRE_CRACKER,			// 3
	Effect::EFFECT_CLASS_FIRE_CRACKER_4,				// 4
	Effect::EFFECT_CLASS_FIRE_CRACKER_VOLLEY_1,			// 5
	Effect::EFFECT_CLASS_FIRE_CRACKER_VOLLEY_2,			// 6
	Effect::EFFECT_CLASS_FIRE_CRACKER_VOLLEY_3,			// 7
	Effect::EFFECT_CLASS_FIRE_CRACKER_VOLLEY_4,			// 8
	Effect::EFFECT_CLASS_FIRE_CRACKER_WIDE_VOLLEY_1,	// 9
	Effect::EFFECT_CLASS_FIRE_CRACKER_WIDE_VOLLEY_2,	// 10
	Effect::EFFECT_CLASS_FIRE_CRACKER_WIDE_VOLLEY_3,	// 11
	Effect::EFFECT_CLASS_FIRE_CRACKER_WIDE_VOLLEY_4,	// 12
	Effect::EFFECT_CLASS_FIRE_CRACKER_STORM				// 13
};

#endif

void CGUseItemFromInventoryHandler::executeFirecraker(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	////cout << pPacket->toString().c_str() << endl;

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// ���� �Լ����� ���� üũ�� ���� �߱� ������,
	// ���� üũ�� ���� ����Ѵ�.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	Storage_t Storage = STORAGE_INVENTORY;
	StorageID_t StorageID = 0;

	bool SubInventoryTrue = false;

	if(pPacket->getInventoryItemObjectID() != 0){
		Item*           pInvenItem        = NULL;
		pInvenItem        = pInventory->getItemWithObjectID(pPacket->getInventoryItemObjectID());
		SubInventory* pSubInventory = dynamic_cast<SubInventory*>(pInvenItem);
		SubInventoryTrue = true;
		Storage = STORAGE_BOX;
		StorageID = pInvenItem->getItemID();
		pInventory = ((SubInventory*)pSubInventory)->getInventory();
	}

	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	ObjectID_t      ItemObjectID = pItem->getObjectID();


	if ( pItem->getItemType() >= 14 )
	{
		EventETCInfo* pInfo = dynamic_cast<EventETCInfo*>(g_pItemInfoManager->getItemInfo( pItem->getItemClass(), pItem->getItemType() ));
		Assert( pInfo != NULL );

		int amount = pInfo->getFunction();

		GCModifyInformation gcMI;
		bool HPRegen=false, MPRegen=false;
		HP_t CurrentHP = 0, MaxHP = 0;
		if ( pPC->isSlayer() )
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
			CurrentHP = pSlayer->getHP();
			MaxHP = pSlayer->getHP(ATTR_MAX);
		}
		else if ( pPC->isVampire() )
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
			CurrentHP = pVampire->getHP();
			MaxHP = pVampire->getHP(ATTR_MAX);
		}
		else if ( pPC->isOusters() )
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
			CurrentHP = pOusters->getHP();
			MaxHP = pOusters->getHP(ATTR_MAX);
		}

		if ( CurrentHP < MaxHP )
		{
			CurrentHP += min(amount, MaxHP-CurrentHP);
			GCStatusCurrentHP gcHP;
			gcHP.setObjectID(pPC->getObjectID());
			gcHP.setCurrentHP(CurrentHP);
			pZone->broadcastPacket( pPC->getX(), pPC->getY(), &gcHP );

			gcMI.addLongData(MODIFY_CURRENT_HP, CurrentHP);
			HPRegen = true;

			if ( pPC->isSlayer() )
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
				pSlayer->setHP(CurrentHP);
			}
			else if ( pPC->isVampire() )
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
				pVampire->setHP(CurrentHP);
			}
			else if ( pPC->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
				pOusters->setHP(CurrentHP);
			}
		}

		MP_t CurrentMP = 0, MaxMP = 0;
		if ( pPC->isSlayer() )
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
			CurrentMP = pSlayer->getMP();
			MaxMP = pSlayer->getMP(ATTR_MAX);
		}
		else if ( pPC->isOusters() )
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
			CurrentMP = pOusters->getMP();
			MaxMP = pOusters->getMP(ATTR_MAX);
		}

		if ( CurrentMP < MaxMP )
		{
			CurrentMP += min(amount, MaxMP-CurrentMP);
			gcMI.addLongData(MODIFY_CURRENT_MP, CurrentMP);
			MPRegen = true;

			if ( pPC->isSlayer() )
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
				pSlayer->setMP(CurrentMP);
			}
			else if ( pPC->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
				pOusters->setMP(CurrentMP);
			}
		}

		if ( !HPRegen && !MPRegen )
		{
			sendCannotUse( pPacket, pPlayer );
			return;
		}
		else
		{
			pPlayer->sendPacket( &gcMI );
		}
	}
	else
	{
		// Ÿ�Ͽ� ��ų�� ���� ���̶�� ���� �� �� �ִ����� üũ�Ѵ�.
		// �������뿡���� ����� �� ����.
		if ( !isAbleToUseTileSkill( pCreature )
			|| (pZone->getZoneLevel(pCreature->getX(), pCreature->getY()) & COMPLETE_SAFE_ZONE)
			|| ItemObjectID != pPacket->getObjectID()
			)
		{
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pGamePlayer->sendPacket(&_GCCannotUse);
			return;
		}

		Effect::EffectClass effectClass = FirecrackerEffects[ pItem->getItemType() ];

	/*	switch ( pItem->getItemType() )
		{
			case 0:
				effectClass = Effect::EFFECT_CLASS_FIRE_CRACKER_1;
				break;

			case 1:
				effectClass = Effect::EFFECT_CLASS_FIRE_CRACKER_2;
				break;

			case 2:
				effectClass = Effect::EFFECT_CLASS_FIRE_CRACKER_3;
				break;

			case 3:
				effectClass = Effect::EFFECT_CLASS_DRAGON_FIRE_CRACKER;
				break;

			case 4:
				effectClass = Effect::EFFECT_CLASS_FIRE_CRACKER_4;
				break;

			default:
				Assert(false);
				break;
		}*/
		// ����Ʈ�� ���� ��ε�ĳ���� �Ѵ�.
		GCAddEffectToTile gcAddEffectToTile;
		gcAddEffectToTile.setObjectID( pCreature->getObjectID() );
		gcAddEffectToTile.setEffectID( effectClass );
		gcAddEffectToTile.setXY( pCreature->getX(), pCreature->getY() );
		gcAddEffectToTile.setDuration( 10 );  // �� �ǹ� ���� �׳� 1��

		pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcAddEffectToTile );
	}

	if (isStackable(pItem))
	{
		if(!SubInventoryTrue)
		decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_INVENTORY, StorageID, InvenX, InvenY);
		else
		decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_BOX, StorageID, InvenX, InvenY);
	}
	else 
	{
		// ������ �ʴ� �������� �ٷιٷ� �������ش�.
		pInventory->deleteItem(InvenX, InvenY);
		pItem->destroy();
		SAFE_DELETE(pItem);
	}

	// �������� ����ߴٰ� Ŭ���̾�Ʈ�� �˸���.
	GCUseOK gcUseOK;
	pGamePlayer->sendPacket( &gcUseOK );

#endif
    __END_DEBUG_EX __END_CATCH
}

void CGUseItemFromInventoryHandler::executeDyePotion(CGUseItemFromInventory* pPacket, Player* pPlayer) 
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// ���� �Լ����� ���� üũ�� ���� �߱� ������,
	// ���� üũ�� ���� ����Ѵ�.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();

	Storage_t Storage = STORAGE_INVENTORY;
	StorageID_t StorageID = 0;

	bool SubInventoryTrue = false;

	if(pPacket->getInventoryItemObjectID() != 0){
		Item*           pInvenItem        = NULL;
		pInvenItem        = pInventory->getItemWithObjectID(pPacket->getInventoryItemObjectID());
		SubInventory* pSubInventory = dynamic_cast<SubInventory*>(pInvenItem);
		SubInventoryTrue = true;
		Storage = STORAGE_BOX;
		StorageID = pInvenItem->getItemID();
		pInventory = ((SubInventory*)pSubInventory)->getInventory();
	}

	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	DyePotionInfo*	pItemInfo	 = dynamic_cast<DyePotionInfo*>(g_pItemInfoManager->getItemInfo( pItem->getItemClass(), pItem->getItemType() ));
	bool			bInitAllStat = false;
	bool			bRefresh = true;


	if ( pItem->getObjectID() != pPacket->getObjectID() ||
		pItemInfo == NULL )
	{
		sendCannotUse( pPacket, pPlayer );
		return;
	}

	BYTE func = pItemInfo->getFunctionFlag();
	int funcv = pItemInfo->getFunctionValue();

	if ( func == DyePotionInfo::FUNCTION_HAIR && pPC->isVampire() )
	{
		sendCannotUse( pPacket, pPlayer );
		return;
	}

	if ( func == DyePotionInfo::FUNCTION_SKIN && pPC->isOusters() )
	{
		sendCannotUse( pPacket, pPlayer );
		return;
	}

	switch ( func )
	{
		case DyePotionInfo::FUNCTION_HAIR:
			{
				if ( !changeHairColorEx( pPC, funcv ) )
				{
					sendCannotUse( pPacket, pPlayer );
					return;
				}
			}
			break;
		case DyePotionInfo::FUNCTION_SKIN:
			{
				if ( !changeSkinColorEx( pPC, funcv ) )
				{
					sendCannotUse( pPacket, pPlayer );
					return;
				}
			}
			break;
		case DyePotionInfo::FUNCTION_SEX:
			{
				int code = changeSexEx( pPC );
				if ( code != 0 )
				{
					// -_-; ����ȯ �����۸� ������Ʈ ���̵𿡴ٰ� �����ڵ� �־��ش�. ��.��
					GCCannotUse _GCCannotUse;
					_GCCannotUse.setObjectID((ObjectID_t)code);
					pPlayer->sendPacket(&_GCCannotUse);

					return;
				}
				else bInitAllStat = true;
			}
			break;
		case DyePotionInfo::FUNCTION_BAT:
			{
				if ( !changeBatColorEx( pPC, funcv ) )
				{
					sendCannotUse( pPacket, pPlayer );
					return;
				}
			}
			break;
		case DyePotionInfo::FUNCTION_MASTER_EFFECT:
			{
				if ( !changeMasterEffectColorEx( pPC, (BYTE)funcv ) )
				{
					sendCannotUse( pPacket, pPlayer );
					return;
				}
			}
			break;
		case DyePotionInfo::FUNCTION_STATUSPOINT:
		{

			if(pCreature->isSlayer()){
				SlayerStatus(pPC, funcv,pPacket);
			}else if(pCreature->isVampire()){
				VampireStatus(pPC, funcv,pPacket);
			}else if(pCreature->isOusters()){
				OustersStatus(pPC, funcv,pPacket);
			}
			break;
		}
		case DyePotionInfo::FUNCTION_CLEARRANK:
		{
			pPC->clearRankBonus();
			bInitAllStat = true;
			pPC->sendRankBonusInfo();
			break;
		}
		case DyePotionInfo::FUNCTION_ALLSTATUSPOINT:
		{

			if(pCreature->isSlayer()){
				AllSlayerStatus(pPC, funcv,pPacket);
			}else if(pCreature->isVampire()){
				AllVampireStatus(pPC, funcv,pPacket);
			}else if(pCreature->isOusters()){
				AllOustersStatus(pPC, funcv,pPacket);
			}
			break;
		}
		case DyePotionInfo::FUNCTION_ITEM_BOX:
		{
			TreasureList* pTreasureList = NULL;
			Item* pItem1 = NULL;

			Creature::CreatureClass ownerCreatureClass;
			ownerCreatureClass = pCreature->getCreatureClass();

			MonsterDropSetup* pMonsterItemDrop = g_pMonsterDropSetupManager->getMonsterDropSetup(funcv);

			if ( pMonsterItemDrop != NULL && pMonsterItemDrop->IsDrop() )
			{
				if (ownerCreatureClass == Creature::CREATURE_CLASS_SLAYER)
				{
					pTreasureList = g_pMonsterItemDropManager->getMonsterItemDrop(pMonsterItemDrop->getSlayerRandomDrop1())->getSlayerTreasureList();
				}
				else if (ownerCreatureClass == Creature::CREATURE_CLASS_VAMPIRE)
				{
					pTreasureList = g_pMonsterItemDropManager->getMonsterItemDrop(pMonsterItemDrop->getSlayerRandomDrop1())->getVampireTreasureList();
				}
				else if (ownerCreatureClass == Creature::CREATURE_CLASS_OUSTERS)
				{
					pTreasureList = g_pMonsterItemDropManager->getMonsterItemDrop(pMonsterItemDrop->getSlayerRandomDrop1())->getOustersTreasureList();
				}
			}

		if ( pTreasureList != NULL )
		{

			const list<Treasure*>& treasures = pTreasureList->getTreasures();
			list<Treasure*>::const_iterator itr = treasures.begin();

			ITEM_TEMPLATE it;

			for (; itr != treasures.end(); itr++)
			{

				Treasure* pTreasure = (*itr);
				ITEM_TEMPLATE it;

				it.ItemClass  = Item::ITEM_CLASS_MAX;
				it.ItemType   = 0;

				it.NextOptionRatio = g_pVariableManager->getChiefMonsterRareItemPercent();
				it.NextOptionRatio += pMonsterItemDrop->getItemRareOptionBounsRatio();

				pTreasure->setRndItemOptionMax(g_pMonsterItemDropManager->getMonsterItemDrop(pMonsterItemDrop->getSlayerRandomDrop1())->getOptionCount());

				if ( pTreasure->getRandomItem(&it) )
				{
					pItem1 = g_pItemFactoryManager->createItem(it.ItemClass, it.ItemType, it.OptionType);
					pItem1->setGrade( ItemGradeManager::Instance().getRandomGrade() );
						
						if(pMonsterItemDrop->getItemSetOptionSetup() && pMonsterItemDrop->getItemSetOptionRatio() > rand()%100000)
						{
						pItem1->setOptionType2( it.OptionType2 );
						}
					
					pItem1->setHeroOption( 0 );
					pItem1->setHeroOptionAttr( 0 );
						
						if(pMonsterItemDrop->getItemSetHeroOptionSetup() && pMonsterItemDrop->getItemSetHeroOptionRatio() > rand()%100000){
							int HeroOptionSetting = rand()%13;
							int HeroOption = g_pMonsterItemDropOptionManager->getRandomOption(HeroOptionSetting);
							int HeroOptionAttrSetting = g_pMonsterItemDropOptionManager->getRandomItem(HeroOptionSetting);
							if(HeroOptionAttrSetting != 0 )
							{
								pItem1->setHeroOption( HeroOption+1 );
								pItem1->setHeroOptionAttr( HeroOptionAttrSetting );
							}
						}

					Assert(pItem1 != NULL);
				}
			}
		}
	
		if (pItem1 != NULL)
		{
			TPOINT pt;
			pZone->registerObject(pItem1);

			if(pInventory->addItem(pItem1, pt))
			{

				pItem1->create(pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y);
				GCCreateItem gcCreateItem;
				makeGCCreateItem( &gcCreateItem, pItem1, pt.x, pt.y );

				pPlayer->sendPacket(&gcCreateItem);

				// ItemTraceLog �� �����
				if ( pItem1 != NULL && pItem1->isTraceItem() )
				{
					remainTraceLog( pItem1, pCreature->getName(), pCreature->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
				}

				GCSystemMessage gcSystemMessage;
				gcSystemMessage.setMessage( g_pStringPool->getString( STRID_TRADE_SUCCESS ) );
				pPlayer->sendPacket(&gcSystemMessage);
			}
			else
			{
				GCSystemMessage gcSystemMessage;
				gcSystemMessage.setMessage( g_pStringPool->getString( STRID_NOT_ENOUGH_INVENTORY_SPACE ) );
				pPlayer->sendPacket(&gcSystemMessage);

				sendCannotUse( pPacket, pPlayer );
				return;
			}
		}

		break;
		}
		case DyePotionInfo::FUNCTION_KILLPOINT:
		{
			if(pCreature->isSlayer()){
				Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
				pSlayer->setKillPoint(pSlayer->getKillPoint()+funcv);

				GCModifyInformation gcFameMI;
				gcFameMI.addLongData( MODIFY_KILL_POINT, pSlayer->getKillPoint() );
				pCreature->getPlayer()->sendPacket( &gcFameMI );
			}else if(pCreature->isVampire()){
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
				pVampire->setKillPoint(pVampire->getKillPoint()+funcv);

				GCModifyInformation gcFameMI;
				gcFameMI.addLongData( MODIFY_KILL_POINT, pVampire->getKillPoint() );
				pCreature->getPlayer()->sendPacket( &gcFameMI );
			}else if(pCreature->isOusters()){
				Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
				pOusters->setKillPoint(pOusters->getKillPoint()+funcv);

				GCModifyInformation gcFameMI;
				gcFameMI.addLongData( MODIFY_KILL_POINT, pOusters->getKillPoint() );
				pCreature->getPlayer()->sendPacket( &gcFameMI );
			}
			break;
		}
		case DyePotionInfo::FUNCTION_ADVANCE_COLOR:
		{
			if(pCreature->isVampire()){

			Vampire* pSlayer = dynamic_cast<Vampire*>(pPC);
			Assert( pSlayer != NULL );

			if ( pSlayer->getAdvanceBatColor() == funcv )
			{
					sendCannotUse( pPacket, pPlayer );
					return;
			}

			pSlayer->setAdvanceBatColor( funcv );

			char query[25];
			sprintf( query, "AdvBatColor=%u", funcv);

			pSlayer->tinysave( query );

			}else{
					sendCannotUse( pPacket, pPlayer );
					return;
			}
		break;
		}
		case DyePotionInfo::FUNCTION_COLOR_PAINT:
		{
			if(pCreature->isSlayer()){
			Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
			Assert( pSlayer != NULL );

			if ( pSlayer->getShopColor() == funcv )
			{
					sendCannotUse( pPacket, pPlayer );
					return;
			}

			pSlayer->setShopColor( funcv );

			char query[25];
			sprintf( query, "ShopColor=%u", funcv);

			pSlayer->tinysave( query );
			}else if(pCreature->isVampire()){
			Vampire* pSlayer = dynamic_cast<Vampire*>(pPC);
			Assert( pSlayer != NULL );

			if ( pSlayer->getShopColor() == funcv )
			{
					sendCannotUse( pPacket, pPlayer );
					return;
			}

			pSlayer->setShopColor( funcv );

			char query[25];
			sprintf( query, "ShopColor=%u", funcv);

			pSlayer->tinysave( query );
			}
			else if(pCreature->isOusters()){
			Ousters* pSlayer = dynamic_cast<Ousters*>(pPC);
			Assert( pSlayer != NULL );

			if ( pSlayer->getShopColor() == funcv )
			{
					sendCannotUse( pPacket, pPlayer );
					return;
			}

			pSlayer->setShopColor( funcv );

			char query[25];
			sprintf( query, "ShopColor=%u", funcv);

			pSlayer->tinysave( query );
			}

		break;
		}
		case DyePotionInfo::FUNCTION_REGEN:
			{
				GCModifyInformation gcMI;
				bool HPRegen=false, MPRegen=false;
				HP_t CurrentHP = 0, MaxHP = 0;
				if ( pPC->isSlayer() )
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
					CurrentHP = pSlayer->getHP();
					MaxHP = pSlayer->getHP(ATTR_MAX);
				}
				else if ( pPC->isVampire() )
				{
					Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
					CurrentHP = pVampire->getHP();
					MaxHP = pVampire->getHP(ATTR_MAX);
				}
				else if ( pPC->isOusters() )
				{
					Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
					CurrentHP = pOusters->getHP();
					MaxHP = pOusters->getHP(ATTR_MAX);
				}

				if ( CurrentHP < MaxHP )
				{
					CurrentHP += min(1000, MaxHP-CurrentHP);
					GCStatusCurrentHP gcHP;
					gcHP.setObjectID(pPC->getObjectID());
					gcHP.setCurrentHP(CurrentHP);
					pZone->broadcastPacket( pPC->getX(), pPC->getY(), &gcHP );

					gcMI.addLongData(MODIFY_CURRENT_HP, CurrentHP);
					HPRegen = true;

					if ( pPC->isSlayer() )
					{
						Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
						pSlayer->setHP(CurrentHP);
					}
					else if ( pPC->isVampire() )
					{
						Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
						pVampire->setHP(CurrentHP);
					}
					else if ( pPC->isOusters() )
					{
						Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
						pOusters->setHP(CurrentHP);
					}
				}

				MP_t CurrentMP = 0, MaxMP = 0;
				if ( pPC->isSlayer() )
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
					CurrentMP = pSlayer->getMP();
					MaxMP = pSlayer->getMP(ATTR_MAX);
				}
				else if ( pPC->isOusters() )
				{
					Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
					CurrentMP = pOusters->getMP();
					MaxMP = pOusters->getMP(ATTR_MAX);
				}

				if ( CurrentMP < MaxMP )
				{
					CurrentMP += min(1000, MaxMP-CurrentMP);
					gcMI.addLongData(MODIFY_CURRENT_MP, CurrentMP);
					MPRegen = true;

					if ( pPC->isSlayer() )
					{
						Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
						pSlayer->setMP(CurrentMP);
					}
					else if ( pPC->isOusters() )
					{
						Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
						pOusters->setMP(CurrentMP);
					}
				}

				if ( !HPRegen && !MPRegen )
				{
					sendCannotUse( pPacket, pPlayer );
					return;
				}
				else
				{
					pPlayer->sendPacket( &gcMI );
				}

				bRefresh = false;
			}
			break;
		default:
			{
				sendCannotUse( pPacket, pPlayer );
				return;
			}
	}

	GCUseOK gcUseOK;
	pPlayer->sendPacket( &gcUseOK );

	if (isStackable(pItem))
	{
		if(!SubInventoryTrue)
		decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_INVENTORY, StorageID, InvenX, InvenY);
		else
		decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_BOX, StorageID, InvenX, InvenY);
	}
	else 
	{
		// ������ �ʴ� �������� �ٷιٷ� �������ش�.
		pInventory->deleteItem(InvenX, InvenY);
		pItem->destroy();
		SAFE_DELETE(pItem);
	}

	if ( bInitAllStat )
	{
	//	initAllStatAndSendChange( pPC );
		pPC->setFlag( Effect::EFFECT_CLASS_INIT_ALL_STAT );
		transportCreature( pPC, pPC->getZoneID(), pPC->getX(), pPC->getY(), false );
	}
	else if ( bRefresh )
	{
		GCDeleteObject gcDeleteObject;
		gcDeleteObject.setObjectID( pPC->getObjectID() );
		pZone->broadcastPacket( pPC->getX(), pPC->getY(), &gcDeleteObject, pPC );

		if ( pPC->isSlayer() )
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
			Assert( pSlayer != NULL );

			GCAddSlayer gcAddSlayer;
			makeGCAddSlayer( &gcAddSlayer, pSlayer );
			pZone->broadcastPacket( pPC->getX(), pPC->getY(), &gcAddSlayer, pPC );
		}
		else if ( pPC->isVampire() )
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
			Assert( pVampire != NULL );

			GCAddVampire gcAddVampire;
			makeGCAddVampire( &gcAddVampire, pVampire );
			pZone->broadcastPacket( pPC->getX(), pPC->getY(), &gcAddVampire, pPC );
		}
		else if ( pPC->isOusters() )
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
			Assert( pOusters != NULL );

			GCAddOusters gcAddOusters;
			makeGCAddOusters( &gcAddOusters, pOusters );
			pZone->broadcastPacket( pPC->getX(), pPC->getY(), &gcAddOusters, pPC );
		}
		else
		{
			Assert( false );
		}
	}

	return;

#endif

    __END_DEBUG_EX __END_CATCH
}

#ifdef __GAME_SERVER__

bool changeHairColorEx( PlayerCreature* pPC, Color_t color )
{
	if ( pPC->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		Assert( pSlayer != NULL );

		if ( pSlayer->getHairColor() == color ) return false;

		pSlayer->setHairColor( color );
		
		char query[25];
		sprintf( query, "HairColor=%u", color );

		pSlayer->tinysave( query );

		return true;
	}
	else if ( pPC->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
		Assert( pOusters != NULL );

		if ( pOusters->getHairColor() == color ) return false;

		pOusters->setHairColor( color );
		
		char query[25];
		sprintf( query, "HairColor=%u", color );

		pOusters->tinysave( query );

		return true;
	}

	return false;
}

bool changeBatColorEx( PlayerCreature* pPC, Color_t color )
{
	if ( pPC->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
		Assert( pVampire != NULL );

		if ( pVampire->getBatColor() == color ) return false;
		if ( pVampire->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT) ) return false;

		pVampire->setBatColor( color );
		
		char query[25];
		sprintf( query, "BatColor=%u", color );

		pVampire->tinysave( query );

		return true;
	}

	return false;
}

bool changeMasterEffectColorEx( PlayerCreature* pPC, BYTE color )
{
	if ( pPC->getLevel()>=100 || pPC->isAdvanced() )
	{
		if ( pPC->getMasterEffectColor() == color ) return false;

		pPC->setMasterEffectColor( color );
		
		char query[25];
		sprintf( query, "MasterEffectColor=%u", color );

		pPC->tinysave( query );

		return true;
	}


	return false;
}

bool changeSkinColorEx( PlayerCreature* pPC, Color_t color )
{
	if ( pPC->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		Assert( pSlayer != NULL );

		if ( pSlayer->getSkinColor() == color ) return false;

		pSlayer->setSkinColor( color );

		char query[25];
		sprintf( query, "SkinColor=%u", color );

		pSlayer->tinysave( query );

		return true;
	}
	else if ( pPC->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
		Assert( pVampire != NULL );

		if ( pVampire->getSkinColor() == color ) return false;

		pVampire->setSkinColor( color );

		char query[25];
		sprintf( query, "SkinColor=%u", color );

		pVampire->tinysave( query );

		return true;
	}

	return false;
}
void OustersStatus(PlayerCreature* pPC, int Case, CGUseItemFromInventory* pPacket){
		GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPC->getPlayer());
		Ousters* pVampire = dynamic_cast<Ousters*>(pPC);
		StringStream  ssts;
		Attr_t	Ability = 0;

		OUSTERS_RECORD oldRecord;
		pVampire->getOustersRecord(oldRecord);

		// ���̽��� ���� �ɷ�ġ���� ������ �ش�.
		if(Case == 0){Ability = pVampire->getSTR(ATTR_BASIC);}
		else if(Case == 1){Ability = pVampire->getDEX(ATTR_BASIC);}
		else if(Case == 2){Ability = pVampire->getINT(ATTR_BASIC);}

		if(Ability >= 30){
					
			pVampire->setBonus(pVampire->getBonus() + 10);

				if(Case == 0){
					pVampire->setSTR(pVampire->getSTR(ATTR_BASIC)-10, ATTR_BASIC);
					ssts << "Bonus = " << (int)(pVampire->getBonus()) << ",STR = " << (int)pVampire->getSTR(ATTR_BASIC);
				}
				else if(Case == 1){
					pVampire->setDEX(pVampire->getDEX(ATTR_BASIC)-10, ATTR_BASIC);
					ssts << "Bonus = " << (int)(pVampire->getBonus()) << ",DEX = " << (int)pVampire->getDEX(ATTR_BASIC);
				}
				else if(Case == 2){
					pVampire->setINT(pVampire->getINT(ATTR_BASIC)-10, ATTR_BASIC);
					ssts << "Bonus = " << (int)(pVampire->getBonus()) << ",INTE = " << (int)pVampire->getINT(ATTR_BASIC);
				}
			pVampire->tinysave(ssts.toString());

			}else if(Ability >= 20 && Ability < 30){ // ĳ������ ������ 20 �̸��ϰ��.
					
			pVampire->setBonus(pVampire->getBonus() + (Ability - 10));
				if(Case == 0){
					pVampire->setSTR(pVampire->getSTR(ATTR_BASIC) - (pVampire->getSTR(ATTR_BASIC) - 20), ATTR_BASIC);
					ssts << "Bonus = " << (int)(pVampire->getBonus()) << ",STR = " << (int)pVampire->getSTR(ATTR_BASIC);
				}
				else if(Case == 1){
					pVampire->setDEX(pVampire->getDEX(ATTR_BASIC) - (pVampire->getDEX(ATTR_BASIC) - 20), ATTR_BASIC);
					ssts << "Bonus = " << (int)(pVampire->getBonus()) << ",DEX = " << (int)pVampire->getDEX(ATTR_BASIC);
				}
				else if(Case == 2){
					pVampire->setINT(pVampire->getINT(ATTR_BASIC) - (pVampire->getINT(ATTR_BASIC) - 20), ATTR_BASIC);
					ssts << "Bonus = " << (int)(pVampire->getBonus()) << ",INTE = " << (int)pVampire->getINT(ATTR_BASIC);
				}
			pVampire->tinysave(ssts.toString());
	
			}else{
				sendCannotUse( pPacket, pPC->getPlayer() );
			return;
		}

				GCUseBonusPointOK okpkt;
				pGamePlayer->sendPacket(&okpkt);

				pVampire->initAllStat();
				pVampire->sendModifyInfo(oldRecord);
				pVampire->sendRealWearingInfo();

				GCModifyInformation gcMI;
				gcMI.addLongData(MODIFY_BONUS_POINT, pVampire->getBonus());
				pPC->getPlayer()->sendPacket( &gcMI );

}
void SlayerStatus(PlayerCreature* pPC, int Case, CGUseItemFromInventory* pPacket){

		GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPC->getPlayer());
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		SLAYER_RECORD oldRecord;
		int	is = 0;
	
			if(Case == 0){
				if(pSlayer->getAdvancedBonusToSTR() > 0){
					while(is < 10){
						pSlayer->deputAdvancedBonusToSTR();
						is++;
					}
				}else{
					sendCannotUse( pPacket, pPC->getPlayer());
					return;
				}
			}else if(Case == 1){
				if(pSlayer->getAdvancedBonusToDEX() > 0){
					while(is < 10){
						pSlayer->deputAdvancedBonusToDEX();
						is++;
					}
				}else{
					sendCannotUse( pPacket, pPC->getPlayer());
					return;
				}
			}else if(Case == 2){
				if(pSlayer->getAdvancedBonusToINT() > 0){
					while(is < 10){
						pSlayer->deputAdvancedBonusToINT();
						is++;
					}
				}else{
					sendCannotUse( pPacket, pPC->getPlayer());
					return;
				}
			}

				GCUseBonusPointOK okpkt;
				pGamePlayer->sendPacket(&okpkt);

				pSlayer->initAllStat();
				pSlayer->sendModifyInfo(oldRecord);
				pSlayer->sendRealWearingInfo();

				GCModifyInformation gcMI;
				gcMI.addLongData(MODIFY_BONUS_POINT, pSlayer->getBonus());
				pPC->getPlayer()->sendPacket( &gcMI );
}
void VampireStatus(PlayerCreature* pPC, int Case, CGUseItemFromInventory* pPacket){

		GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPC->getPlayer());
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
		StringStream  ssts;
		Attr_t	Ability = 0;

		VAMPIRE_RECORD oldRecord;
		pVampire->getVampireRecord(oldRecord);

		// ���̽��� ���� �ɷ�ġ���� ������ �ش�.
		if(Case == 0){Ability = pVampire->getSTR(ATTR_BASIC);}
		else if(Case == 1){Ability = pVampire->getDEX(ATTR_BASIC);}
		else if(Case == 2){Ability = pVampire->getINT(ATTR_BASIC);}

		if(Ability >= 30){
					
			pVampire->setBonus(pVampire->getBonus() + 10);

				if(Case == 0){
					pVampire->setSTR(pVampire->getSTR(ATTR_BASIC)-10, ATTR_BASIC);
					ssts << "Bonus = " << (int)(pVampire->getBonus()) << ",STR = " << (int)pVampire->getSTR(ATTR_BASIC);
				}
				else if(Case == 1){
					pVampire->setDEX(pVampire->getDEX(ATTR_BASIC)-10, ATTR_BASIC);
					ssts << "Bonus = " << (int)(pVampire->getBonus()) << ",DEX = " << (int)pVampire->getDEX(ATTR_BASIC);
				}
				else if(Case == 2){
					pVampire->setINT(pVampire->getINT(ATTR_BASIC)-10, ATTR_BASIC);
					ssts << "Bonus = " << (int)(pVampire->getBonus()) << ",INTE = " << (int)pVampire->getINT(ATTR_BASIC);
				}
			pVampire->tinysave(ssts.toString());

			}else if(Ability >= 21 && Ability < 30){ // ĳ������ ������ 20 �̸��ϰ��.
					
			pVampire->setBonus(pVampire->getBonus() + (Ability - 20));
				if(Case == 0){
					pVampire->setSTR(pVampire->getSTR(ATTR_BASIC) - (pVampire->getSTR(ATTR_BASIC) - 20), ATTR_BASIC);
					ssts << "Bonus = " << (int)(pVampire->getBonus()) << ",STR = " << (int)pVampire->getSTR(ATTR_BASIC);
				}
				else if(Case == 1){
					pVampire->setDEX(pVampire->getDEX(ATTR_BASIC) - (pVampire->getDEX(ATTR_BASIC) - 20), ATTR_BASIC);
					ssts << "Bonus = " << (int)(pVampire->getBonus()) << ",DEX = " << (int)pVampire->getDEX(ATTR_BASIC);
				}
				else if(Case == 2){
					pVampire->setINT(pVampire->getINT(ATTR_BASIC) - (pVampire->getINT(ATTR_BASIC) - 20), ATTR_BASIC);
					ssts << "Bonus = " << (int)(pVampire->getBonus()) << ",INTE = " << (int)pVampire->getINT(ATTR_BASIC);
				}
			pVampire->tinysave(ssts.toString());
	
			}else{
				sendCannotUse( pPacket, pPC->getPlayer() );
			return;
		}

				GCUseBonusPointOK okpkt;
				pGamePlayer->sendPacket(&okpkt);

				pVampire->initAllStat();
				pVampire->sendModifyInfo(oldRecord);
				pVampire->sendRealWearingInfo();

				GCModifyInformation gcMI;
				gcMI.addLongData(MODIFY_BONUS_POINT, pVampire->getBonus());
				pPC->getPlayer()->sendPacket( &gcMI );
}

void AllOustersStatus(PlayerCreature* pPC, int Case, CGUseItemFromInventory* pPacket){
		GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPC->getPlayer());
		Ousters* pVampire = dynamic_cast<Ousters*>(pPC);
		StringStream  ssts;
		Attr_t	Ability = 0;

		OUSTERS_RECORD oldRecord;
		pVampire->getOustersRecord(oldRecord);

		// ���̽��� ���� �ɷ�ġ���� ������ �ش�.
		if(Case == 0){Ability = pVampire->getSTR(ATTR_BASIC);}
		else if(Case == 1){Ability = pVampire->getDEX(ATTR_BASIC);}
		else if(Case == 2){Ability = pVampire->getINT(ATTR_BASIC);}

		if(Ability > 20){
					
			pVampire->setBonus(pVampire->getBonus() + Ability-20);

				if(Case == 0){
					pVampire->setSTR(20, ATTR_BASIC);
					ssts << "Bonus = " << (int)(pVampire->getBonus()) << ",STR = " << (int)pVampire->getSTR(ATTR_BASIC);
				}
				else if(Case == 1){
					pVampire->setDEX(20, ATTR_BASIC);
					ssts << "Bonus = " << (int)(pVampire->getBonus()) << ",DEX = " << (int)pVampire->getDEX(ATTR_BASIC);
				}
				else if(Case == 2){
					pVampire->setINT(20, ATTR_BASIC);
					ssts << "Bonus = " << (int)(pVampire->getBonus()) << ",INTE = " << (int)pVampire->getINT(ATTR_BASIC);
				}
			pVampire->tinysave(ssts.toString());
	
			}else{
				sendCannotUse( pPacket, pPC->getPlayer() );
			return;
		}

				GCUseBonusPointOK okpkt;
				pGamePlayer->sendPacket(&okpkt);

				pVampire->initAllStat();
				pVampire->sendModifyInfo(oldRecord);
				pVampire->sendRealWearingInfo();

				GCModifyInformation gcMI;
				gcMI.addLongData(MODIFY_BONUS_POINT, pVampire->getBonus());
				pPC->getPlayer()->sendPacket( &gcMI );

}
void AllSlayerStatus(PlayerCreature* pPC, int Case, CGUseItemFromInventory* pPacket){

		GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPC->getPlayer());
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		SLAYER_RECORD oldRecord;
		int	is = 0;
	
			if(Case == 0){
				if(pSlayer->getAdvancedBonusToSTR() > 0){
					while(pSlayer->getAdvancedBonusToSTR()){
						pSlayer->deputAdvancedBonusToSTR();
					}
				}else{
					sendCannotUse( pPacket, pPC->getPlayer());
					return;
				}
			}else if(Case == 1){
				if(pSlayer->getAdvancedBonusToDEX() > 0){
					while(pSlayer->getAdvancedBonusToDEX()){
						pSlayer->deputAdvancedBonusToDEX();
					}
				}else{
					sendCannotUse( pPacket, pPC->getPlayer());
					return;
				}
			}else if(Case == 2){
				if(pSlayer->getAdvancedBonusToINT() > 0){
					while(pSlayer->getAdvancedBonusToINT()){
						pSlayer->deputAdvancedBonusToINT();
					}
				}else{
					sendCannotUse( pPacket, pPC->getPlayer());
					return;
				}
			}

				GCUseBonusPointOK okpkt;
				pGamePlayer->sendPacket(&okpkt);

				pSlayer->initAllStat();
				pSlayer->sendModifyInfo(oldRecord);
				pSlayer->sendRealWearingInfo();

				GCModifyInformation gcMI;
				gcMI.addLongData(MODIFY_BONUS_POINT, pSlayer->getBonus());
				pPC->getPlayer()->sendPacket( &gcMI );
}
void AllVampireStatus(PlayerCreature* pPC, int Case, CGUseItemFromInventory* pPacket){

		GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPC->getPlayer());
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
		StringStream  ssts;
		Attr_t	Ability = 0;

		VAMPIRE_RECORD oldRecord;
		pVampire->getVampireRecord(oldRecord);

		// ���̽��� ���� �ɷ�ġ���� ������ �ش�.
		if(Case == 0){Ability = pVampire->getSTR(ATTR_BASIC);}
		else if(Case == 1){Ability = pVampire->getDEX(ATTR_BASIC);}
		else if(Case == 2){Ability = pVampire->getINT(ATTR_BASIC);}

		if(Ability > 20){
					
			pVampire->setBonus(pVampire->getBonus() + Ability-20);

				if(Case == 0){
					pVampire->setSTR(20, ATTR_BASIC);
					ssts << "Bonus = " << (int)(pVampire->getBonus()) << ",STR = " << (int)pVampire->getSTR(ATTR_BASIC);
				}
				else if(Case == 1){
					pVampire->setDEX(20, ATTR_BASIC);
					ssts << "Bonus = " << (int)(pVampire->getBonus()) << ",DEX = " << (int)pVampire->getDEX(ATTR_BASIC);
				}
				else if(Case == 2){
					pVampire->setINT(20, ATTR_BASIC);
					ssts << "Bonus = " << (int)(pVampire->getBonus()) << ",INTE = " << (int)pVampire->getINT(ATTR_BASIC);
				}
			pVampire->tinysave(ssts.toString());
	
			}else{
				sendCannotUse( pPacket, pPC->getPlayer() );
			return;
			}

				GCUseBonusPointOK okpkt;
				pGamePlayer->sendPacket(&okpkt);

				pVampire->initAllStat();
				pVampire->sendModifyInfo(oldRecord);
				pVampire->sendRealWearingInfo();

				GCModifyInformation gcMI;
				gcMI.addLongData(MODIFY_BONUS_POINT, pVampire->getBonus());
				pPC->getPlayer()->sendPacket( &gcMI );
}


bool sendCannotUse( CGUseItemFromInventory* pPacket, Player* pPlayer )
{
	GCCannotUse _GCCannotUse;
	_GCCannotUse.setObjectID(pPacket->getObjectID());
	pPlayer->sendPacket(&_GCCannotUse);

	return true;
}

#endif

void CGUseItemFromInventoryHandler::executeResurrectItem(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// ���� �Լ����� ���� üũ�� ���� �߱� ������,
	// ���� üũ�� ���� ����Ѵ�.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	ResurrectItemInfo*	pItemInfo	 = dynamic_cast<ResurrectItemInfo*>(g_pItemInfoManager->getItemInfo( pItem->getItemClass(), pItem->getItemType() ));

	//cout << "Resurrection �������� ����� : " << pPC->getName() << " : " << pItem->getItemType() << endl;

	if ( pItem->getObjectID() != pPacket->getObjectID() ||
		pItemInfo == NULL )
	{
		//cout << "���� ������Ʈ �Ƶ� Ʋ��" << endl;
		sendCannotUse( pPacket, pPlayer );
		return;
	}

	if ( !pPC->isFlag(Effect::EFFECT_CLASS_COMA) )
	{
		//cout << "���� ���°� �ƴ�" << endl;
		sendCannotUse( pPacket, pPlayer );
		return;
	}

	Slayer* pSlayer = NULL;
	Vampire* pVampire = NULL;
	Ousters* pOusters = NULL;

	if ( pPC->isSlayer() ) pSlayer = dynamic_cast<Slayer*>(pPC);
	else if ( pPC->isVampire() ) pVampire = dynamic_cast<Vampire*>(pPC);
	else if ( pPC->isOusters() ) pOusters = dynamic_cast<Ousters*>(pPC);

	ResurrectItemInfo::ResurrectType type = pItemInfo->getResurrectType();
	HP_t hp = 0;
	GCModifyInformation gcMI;
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID( pPC->getObjectID() );

	switch ( type )
	{
		case ResurrectItemInfo::HP_1:
			{
				if ( pPC->isSlayer() )
				{
					Assert( pSlayer != NULL );
					pSlayer->setHP(1);
					hp = 1;
					gcMI.addShortData(MODIFY_CURRENT_HP,hp);
				}
				else if ( pPC->isVampire() )
				{
					Assert( pVampire != NULL );
					pVampire->setHP(1);
					hp = 1;
					gcMI.addShortData(MODIFY_CURRENT_HP,hp);
				}
				else if ( pPC->isOusters() )
				{
					Assert( pOusters != NULL );
					pOusters->setHP(1);
					hp = 1;
					gcMI.addShortData(MODIFY_CURRENT_HP,hp);
				}
				else
				{
					sendCannotUse( pPacket, pPlayer );
					return;
				}

				if ( GDRLairManager::Instance().isGDRLairZone(pPC->getZoneID()) )
				{
					filelog("GDRLair.log", "%s�� %d������ ��Ȱ ��ũ���� ����߽��ϴ�.",
							pPC->getName().c_str(),
							pPC->getZoneID() );
				}
			}
			break;
		case ResurrectItemInfo::HP_FULL:
			{
				if ( pPC->isSlayer() )
				{
					Assert( pSlayer != NULL );
					pSlayer->setHP( pSlayer->getHP(ATTR_MAX) );
					hp = pSlayer->getHP();

					gcMI.addShortData(MODIFY_CURRENT_HP,hp);

					if ( pSlayer->getMP() < pSlayer->getMP(ATTR_MAX) )
					{
						pSlayer->setMP(pSlayer->getMP(ATTR_MAX));
						gcMI.addShortData(MODIFY_CURRENT_MP,pSlayer->getMP());
					}

					Effect* pEffect = pSlayer->getEffectManager()->findEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN);
					if ( pEffect != NULL )
					{
						pEffect->destroy(pSlayer->getName());
						pSlayer->getEffectManager()->deleteEffect(pSlayer, Effect::EFFECT_CLASS_BLOOD_DRAIN);

						gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_BLOOD_DRAIN);

						// ���� �Ƹ�����Ʈ�� �����ϱ� ���� ������ ����Ʈ�� �ٿ��ش�.
						if (pSlayer->isFlag(Effect::EFFECT_CLASS_AFTERMATH))
						{
							Effect* pEffect = pSlayer->getEffectManager()->findEffect(Effect::EFFECT_CLASS_AFTERMATH);
							EffectAftermath* pEffectAftermath = dynamic_cast<EffectAftermath*>(pEffect);
							pEffectAftermath->setDeadline(5*600); // 5�� ���� ���ӵȴ�.
						}
						else
						{
							EffectAftermath* pEffectAftermath = new EffectAftermath(pSlayer);
							pEffectAftermath->setDeadline(5*600); // 5�� ���� ���ӵȴ�.
							pSlayer->getEffectManager()->addEffect(pEffectAftermath);
							pSlayer->setFlag(Effect::EFFECT_CLASS_AFTERMATH);
							pEffectAftermath->create(pSlayer->getName());
						}

						// ������ ġ���ϸ� �ɷ�ġ�� ��ȭ�ϰ� �ȴ�.
						SLAYER_RECORD prev;
						pSlayer->getSlayerRecord(prev);
						pSlayer->initAllStat();
						pSlayer->addModifyInfo(prev, gcMI);
						pSlayer->sendRealWearingInfo();
					}
				}
				else if ( pPC->isVampire() )
				{
					Assert( pVampire != NULL );
					pVampire->setSilverDamage(0);
					pVampire->setHP( pVampire->getHP(ATTR_MAX) );
					hp = pVampire->getHP();
					gcMI.addShortData(MODIFY_CURRENT_HP,hp);
					gcMI.addShortData(MODIFY_SILVER_DAMAGE,0);
				}
				else if ( pPC->isOusters() )
				{
					Assert( pOusters != NULL );
					pOusters->setSilverDamage(0);
					pOusters->setHP( pOusters->getHP(ATTR_MAX) );
					hp = pOusters->getHP();
					gcMI.addShortData(MODIFY_CURRENT_HP,hp);
				}
				else
				{
					sendCannotUse( pPacket, pPlayer );
					return;
				}

				if ( GDRLairManager::Instance().isGDRLairZone(pPC->getZoneID()) )
				{
					filelog("GDRLair.log", "%s�� %d������ ������ ��ũ���� ����߽��ϴ�.",
							pPC->getName().c_str(),
							pPC->getZoneID() );
				}
			}
			break;

		default:
			sendCannotUse( pPacket, pPlayer );
			return;
	}

	pPC->deleteEffect(Effect::EFFECT_CLASS_COMA);
	pPC->removeFlag(Effect::EFFECT_CLASS_COMA);
	
	gcRemoveEffect.addEffectList( (EffectID_t)Effect::EFFECT_CLASS_COMA );
	pZone->broadcastPacket( pPC->getX(), pPC->getY(), &gcRemoveEffect );

	pPC->getEffectManager()->sendEffectInfo( pPC, pZone, pPC->getX(), pPC->getY() );

	GCStatusCurrentHP gcHP;
	gcHP.setObjectID( pPC->getObjectID() );
	gcHP.setCurrentHP( hp );
	pZone->broadcastPacket( pPC->getX(), pPC->getY(), &gcHP, pPC );

	pPlayer->sendPacket( &gcMI );

	GCUseOK gcUseOK;
	pPlayer->sendPacket( &gcUseOK );

	if (isStackable(pItem))
	{
		decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
	}
	else 
	{
		// ������ �ʴ� �������� �ٷιٷ� �������ش�.
		pInventory->deleteItem(InvenX, InvenY);
		pItem->destroy();
		SAFE_DELETE(pItem);
	}

#endif

    __END_DEBUG_EX __END_CATCH
}


void CGUseItemFromInventoryHandler::executeTranslator(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// ���� �Լ����� ���� üũ�� ���� �߱� ������,
	// ���� üũ�� ���� ����Ѵ�.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();

	Storage_t Storage = STORAGE_INVENTORY;
	StorageID_t StorageID = 0;

	bool SubInventoryTrue = false;

	if(pPacket->getInventoryItemObjectID() != 0){
		Item*           pInvenItem        = NULL;
		pInvenItem        = pInventory->getItemWithObjectID(pPacket->getInventoryItemObjectID());
		SubInventory* pSubInventory = dynamic_cast<SubInventory*>(pInvenItem);
		SubInventoryTrue = true;
		Storage = STORAGE_BOX;
		StorageID = pInvenItem->getItemID();
		pInventory = ((SubInventory*)pSubInventory)->getInventory();
	}

	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	ItemInfo*		pItemInfo	 = g_pItemInfoManager->getItemInfo( pItem->getItemClass(), pItem->getItemType() );
	
	if ( pItem->getObjectID() != pPacket->getObjectID() ||
		pItemInfo == NULL ||
		pPC->isFlag( Effect::EFFECT_CLASS_TRANSLATION ) )
	{
		////cout << "���� ������Ʈ �Ƶ� Ʋ��" << endl;
		sendCannotUse( pPacket, pPlayer );
		return;
	}

	EffectTranslation* pEffect = new EffectTranslation(pPC);
	Assert( pEffect != NULL );

	pEffect->setDeadline( 6000 );	// 10��
	pPC->addEffect(pEffect);
	pPC->setFlag( Effect::EFFECT_CLASS_TRANSLATION );

	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID( pPC->getObjectID() );
	gcAddEffect.setEffectID( pEffect->getSendEffectClass() );
	gcAddEffect.setDuration( 6000 );
	pZone->broadcastPacket( pPC->getX(), pPC->getY(), &gcAddEffect );

	GCUseOK gcUseOK;
	pPlayer->sendPacket( &gcUseOK );

	if (isStackable(pItem))
	{
		if(!SubInventoryTrue)
		decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_INVENTORY, StorageID, InvenX, InvenY);
		else
		decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_BOX, StorageID, InvenX, InvenY);
	}
	else 
	{
		// ������ �ʴ� �������� �ٷιٷ� �������ش�.
		pInventory->deleteItem(InvenX, InvenY);
		pItem->destroy();
		SAFE_DELETE(pItem);
	}

#endif

    __END_DEBUG_EX __END_CATCH
}

void CGUseItemFromInventoryHandler::executeEffectItem(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// ���� �Լ����� ���� üũ�� ���� �߱� ������,
	// ���� üũ�� ���� ����Ѵ�.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();

	Storage_t Storage = STORAGE_INVENTORY;
	StorageID_t StorageID = 0;

	bool SubInventoryTrue = false;

	if(pPacket->getInventoryItemObjectID() != 0){
		Item*           pInvenItem        = NULL;
		pInvenItem        = pInventory->getItemWithObjectID(pPacket->getInventoryItemObjectID());
		SubInventory* pSubInventory = dynamic_cast<SubInventory*>(pInvenItem);
		SubInventoryTrue = true;
		Storage = STORAGE_BOX;
		StorageID = pInvenItem->getItemID();
		pInventory = ((SubInventory*)pSubInventory)->getInventory();
	}

	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	EffectItemInfo*	pItemInfo	 = dynamic_cast<EffectItemInfo*>(g_pItemInfoManager->getItemInfo( pItem->getItemClass(), pItem->getItemType() ));

	if ( pItem->getObjectID() != pPacket->getObjectID() || pItemInfo == NULL ||
		pPC->isFlag( pItemInfo->getEffectClass() )
	)
	{
		sendCannotUse( pPacket, pPlayer );
		return;
	}
	if(pItemInfo->getEffectClass() < 521){
	SimpleCreatureEffect* pEffect = new SimpleCreatureEffect( pItemInfo->getEffectClass(), pPC );
	Assert( pEffect != NULL );

	//VSDateTime MagiccurrentTime = VSDateTime::currentDateTime();
	//int diffSecs = MagiccurrentTime.secsTo( MagiccurrentTimeWait );

	pEffect->setDeadline( (WORD)pItemInfo->getDuration()*10 );
	//pEffect->setFeedTime( (WORD)pItemInfo->getDuration()*10 );
	pPC->addEffect( pEffect );
	pPC->setFlag( pEffect->getEffectClass() );

	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID( pPC->getObjectID() );
	gcAddEffect.setEffectID( pEffect->getSendEffectClass() );
	gcAddEffect.setDuration( (WORD)pItemInfo->getDuration()*10 );
	pZone->broadcastPacket( pPC->getX(), pPC->getY(), &gcAddEffect );
	}else{
	
	if(pPC->isFlag((Effect::EffectClass)pItemInfo->getEffectClass())){
	sendCannotUse( pPacket, pPlayer );
	return;
	}


	//if (pItemInfo->getNotEffectClass().size() < 1) return;
	if(pItemInfo->getNotEffectClass() != ""){
	uint a = 0 , b = 0 , c = 0;

	while (c < pItemInfo->getNotEffectClass().size() - 1)
	{
		///////////////////////////////////////////////////////
		// (HP,1)(DAMAGE,1)...
		// a  b ca
		///////////////////////////////////////////////////////
		a = pItemInfo->getNotEffectClass().find_first_of('(',c);
		c = pItemInfo->getNotEffectClass().find_first_of(')',a+1);

		if (a > c || a > c) break;

		//string part  = pItemInfo->getNotEffectClass().substr(a+1, b-a-1);
		int    value = atoi(pItemInfo->getNotEffectClass().substr(a+1, c-1).c_str());

		if (pPC->isFlag((Effect::EffectClass)value)){
		sendCannotUse( pPacket, pPlayer );
		return;
		}
	}

	}
	EffectSevenFoldStone* pEffect = new EffectSevenFoldStone( pPC );

	VSDateTime current = VSDateTime::currentDateTime().addSecs(pItemInfo->getDuration());

	VSDateTime MagiccurrentTime = VSDateTime::currentDateTime();
	int diffSecs = MagiccurrentTime.secsTo( current );

	pEffect->setDeadline( (DWORD)diffSecs*10 );
	pEffect->setFeedTime( current );

	//pEffect->setDeadline( (DWORD)pItemInfo->getDuration()*10 );
	pEffect->setLevel( pItemInfo->getEffectClass() );
	pEffect->setEffectType( pItemInfo->getEffectClass() );
	pEffect->setHeroOption(pItem->getHeroOption());
	pPC->addEffect( pEffect );
	pEffect->create(pPC->getName());
	pPC->setFlag( pEffect->getEffectClass() );

	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID( pPC->getObjectID() );
	gcAddEffect.setEffectID( pEffect->getSendEffectClass() );
	gcAddEffect.setDuration( (DWORD)diffSecs*10 );
	pZone->broadcastPacket( pPC->getX(), pPC->getY(), &gcAddEffect );
	}

		pPC->initAllStatAndSend();

	GCUseOK gcUseOK;
	pPlayer->sendPacket( &gcUseOK );

	if (isStackable(pItem))
	{
		if(!SubInventoryTrue)
		decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_INVENTORY, StorageID, InvenX, InvenY);
		else
		decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_BOX, StorageID, InvenX, InvenY);
	}
	else 
	{
		// ������ �ʴ� ��?����?�ٷιٷ� �������ش�.
		pInventory->deleteItem(InvenX, InvenY);
		pItem->destroy();
		SAFE_DELETE(pItem);
	}
	
#endif

	__END_DEBUG_EX __END_CATCH
}

void CGUseItemFromInventoryHandler::executePetItem(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__
	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// ���� �Լ����� ���� üũ�� ���� �߱� ������,
	// ���� üũ�� ���� ����Ѵ�.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
//	Zone*			pZone		 = pPC->getZone();
	Inventory*      pInventory   = pPC->getInventory();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();

	Storage_t Storage = STORAGE_INVENTORY;
	StorageID_t StorageID = 0;

	bool SubInventoryTrue = false;

	if(pPacket->getInventoryItemObjectID() != 0){
		Item*           pInvenItem        = NULL;
		pInvenItem        = pInventory->getItemWithObjectID(pPacket->getInventoryItemObjectID());
		SubInventory* pSubInventory = dynamic_cast<SubInventory*>(pInvenItem);
		SubInventoryTrue = true;
		Storage = STORAGE_BOX;
		StorageID = pInvenItem->getItemID();
		pInventory = ((SubInventory*)pSubInventory)->getInventory();
	}

	Item*           pItem        = pInventory->getItem(InvenX, InvenY);

	if ( pPC == NULL )
	{
		sendCannotUse( pPacket, pPlayer );
		return;
	}

	if ( pPC != NULL && pPC->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		if ( pSlayer->hasRideMotorcycle() )
		{
			sendCannotUse( pPacket, pPlayer );
			return;
		}
	}

	if ( pPC != NULL &&
		(pPC->isFlag( Effect::EFFECT_CLASS_TRANSFORM_TO_BAT ) || pPC->isFlag( Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF )
		 || pPC->isFlag( Effect::EFFECT_CLASS_SUMMON_SYLPH ))
	)
	{
		sendCannotUse( pPacket, pPlayer );
		return;
	}

	PetItem* pPetItem = dynamic_cast<PetItem*>(pItem);
	if ( pPetItem != NULL )
	{
		PetInfo* pTargetPetInfo = pPetItem->getPetInfo();
		if ( pTargetPetInfo->getPetHP() == 0 )
		{
//			cout << pPC->getName() << " ���� �� �θ��� ����" << endl;
			sendCannotUse( pPacket, pPlayer );
			return;
		}

		if ( pTargetPetInfo->getPetType() >= PET_CENTAURO && pPC->getQuestLevel() < 40 )
		{
			filelog("Pet.log", "���� �ȵǴ� ���� 2���� �θ���� �׷��� : [%s:%s]", pGamePlayer->getID().c_str(), pPC->getName().c_str());
			sendCannotUse( pPacket, pPlayer );
			return;
		}

		PetInfo* pPetInfo = pPC->getPetInfo();
		if ( pPetInfo == NULL || pPetInfo->getPetItem() != pPetItem )
		{
			pPC->setPetInfo( pTargetPetInfo );
			//cout << pPetItem->getObjectID() << " �������� ���� �ҷ����ϴ�." << endl;
		}
		else
		{
			//cout << "���� �������ϴ�." << endl;
			pPC->setPetInfo( NULL );
		}

		pPC->initAllStatAndSend();
		sendPetInfo( pGamePlayer, true, true );
		GCUseOK gcUseOK;
		pGamePlayer->sendPacket(&gcUseOK);
	}
#endif

	__END_CATCH
}
	
void CGUseItemFromInventoryHandler::executePetFood(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__
	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// ���� �Լ����� ���� üũ�� ���� �߱� ������,
	// ���� üũ�� ���� ����Ѵ�.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();

	Storage_t Storage = STORAGE_INVENTORY;
	StorageID_t StorageID = 0;

	bool SubInventoryTrue = false;

	if(pPacket->getInventoryItemObjectID() != 0){
		Item*           pInvenItem        = NULL;
		pInvenItem        = pInventory->getItemWithObjectID(pPacket->getInventoryItemObjectID());
		SubInventory* pSubInventory = dynamic_cast<SubInventory*>(pInvenItem);
		SubInventoryTrue = true;
		Storage = STORAGE_BOX;
		StorageID = pInvenItem->getItemID();
		pInventory = ((SubInventory*)pSubInventory)->getInventory();
	}

	Item*           pItem        = pInventory->getItem(InvenX, InvenY);

	PetFood* pPetFood = dynamic_cast<PetFood*>(pItem);
	PetFoodInfo* pInfo = dynamic_cast<PetFoodInfo*>(g_pItemInfoManager->getItemInfo( pPetFood->getItemClass(), pPetFood->getItemType() ));

	if ( pPetFood != NULL && pInfo != NULL )
	{
		PetInfo* pPetInfo = pPC->getPetInfo();
		if ( pPetInfo == NULL || pPetInfo->getPetHP() == 0 )
		{
			sendCannotUse( pPacket, pPlayer );
			return;
		}

		PetTypeInfo* pPetTypeInfo = PetTypeInfoManager::getInstance()->getPetTypeInfo( pPetInfo->getPetType() );

		if ( pPetTypeInfo == NULL || pPetTypeInfo->getFoodType() != pInfo->getTarget() )
		{
			sendCannotUse( pPacket, pPlayer );
			return;
		}
		else
		{
			pPetInfo->setPetHP( pInfo->getPetHP() );
			pPetInfo->setFoodType( pPetFood->getItemType() );
			
			if(!SubInventoryTrue)
			decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_INVENTORY, StorageID, InvenX, InvenY);
			else
			decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_BOX, StorageID, InvenX, InvenY);


//			pInventory->deleteItem( pPetFood->getObjectID() );
//			pPetFood->destroy();
			
//			SAFE_DELETE( pPetFood );

//			GCModifyInformation gcMI;
//			gcMI.addShortData( MODIFY_PET_HP, pPetInfo->getPetHP() );
//			pGamePlayer->sendPacket(&gcMI);

			sendPetInfo( pGamePlayer, true );

			GCUseOK gcUseOK;
			pGamePlayer->sendPacket(&gcUseOK);

			char query[100];
			sprintf( query, "PetHP=%u, FoodType=%u", pPetInfo->getPetHP(), pPetInfo->getFoodType() );

			Item* pItem = pPetInfo->getPetItem();
			if ( pItem != NULL ) pItem->tinysave( query );
		}
	}
#endif

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUseItemFromInventoryHandler::executeEventGiftBox(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// ���� �Լ����� ���� üũ�� ���� �߱� ������,
	// ���� üũ�� ���� ����Ѵ�.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	//ObjectID_t      ItemObjectID = pItem->getObjectID();
	cout << "Check Name : " << pCreature->getName() << " , GiftBoxType : " << pItem->getItemType() << endl;
	// ������ ���� ���ڰ� �ƴ϶�� ����� �� ���� 
	/*if ( pItem->getItemType() < 6 || ( pItem->getItemType() >= 16 && pItem->getItemType() <= 18 ) || pItem->getItemType() > 26)
	{
		filelog("GiftBoxErrorLog.txt", "[Name] : %s , [ItemType] : %d : �߸��� ������ Ÿ��\n", pCreature->getName().c_str(), pItem->getItemType());
		return;
	}*/

	// DEBUG
	cout << "Name : " << pCreature->getName() << " , GiftBoxType : " << pItem->getItemType() << endl;

	if ( pItem->getItemType() >= 22 && pItem->getItemType() <= 26 )
	{
		sendCannotUse( pPacket, pPlayer );
		return;
	}

/*	if ( pItem->getItemType() == 23 )
	{
		if ( pCreature->isFlag( Effect::EFFECT_CLASS_CAN_MODIFY_PET_NICKNAME ) )
		{
			sendCannotUse( pPacket, pPlayer );
			return;
		}
		else
		{
			pCreature->setFlag( Effect::EFFECT_CLASS_CAN_MODIFY_PET_NICKNAME );

			GCUseOK gcUseOK;
			pGamePlayer->sendPacket(&gcUseOK);

			pInventory->deleteItem(InvenX, InvenY);
			pItem->destroy();
			SAFE_DELETE(pItem);
			return;
		}
	}
*/
	// �������ڰ� ��?ϴ?�������� 2*2 �� �� ���� ũ���̹Ƿ� Inventory �˻�� ����
	// (���� ���� ���� ����� ���� �� ���� ��Ȳ �߻��ϸ� ����Ϲ�??
	Item*	pResultItem	= NULL;
	bool	bFullStack = true;

	if ( pItem->getItemType() == 6 )
	{
		if ( pCreature->isSlayer() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 113, 122 );
		}
		else if ( pCreature->isVampire() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 123, 132 );
		}
		else if ( pCreature->isOusters() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 133, 142 );
		}
	}
	else if ( pItem->getItemType() == 7 )
	{
		if ( pCreature->isSlayer() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 143, 152 );
		}
		else if ( pCreature->isVampire() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 153, 162 );
		}
		else if ( pCreature->isOusters() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 163, 172 );
		}
	}
	else if ( pItem->getItemType() == 8 )
	{
		if ( pCreature->isSlayer() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 173, 182 );
		}
		else if ( pCreature->isVampire() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 183, 192 );
		}
		else if ( pCreature->isOusters() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 193, 202 );
		}
	}
	else if ( pItem->getItemType() == 9 )
	{
		if ( pCreature->isSlayer() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 203, 212 );
		}
		else if ( pCreature->isVampire() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 213, 222 );
		}
		else if ( pCreature->isOusters() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 223, 232 );
		}
	}
	else if ( pItem->getItemType() == 10 )
	{
		if ( pCreature->isSlayer() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 233, 242 );
		}
		else if ( pCreature->isVampire() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 243, 252 );
		}
		else if ( pCreature->isOusters() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 253, 262 );
		}
	}
	else if ( pItem->getItemType() == 11 )
	{
		if ( pCreature->isSlayer() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 263, 272 );
		}
		else if ( pCreature->isVampire() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 273, 282 );
		}
		else if ( pCreature->isOusters() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 283, 292 );
		}
	}
	else if ( pItem->getItemType() == 12 )
	{
		if ( pCreature->isSlayer() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 293, 302 );
		}
		else if ( pCreature->isVampire() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 303, 312 );
		}
		else if ( pCreature->isOusters() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 313, 322 );
		}
	}
	else if ( pItem->getItemType() == 13 )
	{
		if ( pCreature->isSlayer() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 323, 332 );
		}
		else if ( pCreature->isVampire() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 333, 342 );
		}
		else if ( pCreature->isOusters() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 343, 352 );
		}
	}
	else if ( pItem->getItemType() == 14 )
	{
		if ( pCreature->isSlayer() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 353, 362 );
		}
		else if ( pCreature->isVampire() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 363, 372 );
		}
		else if ( pCreature->isOusters() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 373, 382 );
		}
	}
	else if ( pItem->getItemType() == 15 )
	{
		if ( pCreature->isSlayer() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 383, 392 );
		}
		else if ( pCreature->isVampire() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 393, 402 );
		}
		else if ( pCreature->isOusters() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem( 403, 412 );
		}
	}
	else if ( pItem->getItemType() == 19 )
	{
		int value = rand()%100;
		bFullStack = false;

		if ( value < 70 )
		{
			// ������ ��ũ��
			pResultItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_RESURRECT_ITEM, 1, list<OptionType_t>() );
		}
		else if ( value < 95 )
		{
			// ���� ����
			pResultItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_STAR, 8, list<OptionType_t>() );
		}
		else if ( value < 99 )
		{
			// ������ ��ũ�� ����
			pResultItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_RESURRECT_ITEM, 1, list<OptionType_t>() );
			pResultItem->setNum(9);
		}
		else
		{
			// �Ǽ��縮 �ͽ����� A��
			pResultItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_MIXING_ITEM, 6, list<OptionType_t>() );
		}
	}
	else if ( pItem->getItemType() == 20 )
	{
		int value = rand()%100;
		bFullStack = false;

		if ( value < 70 )
		{
			// ��Ȱ ��ũ��
			pResultItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_RESURRECT_ITEM, 0, list<OptionType_t>() );
		}
		else if ( value < 95 )
		{
			// �Ķ� ����
			pResultItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_STAR, 10, list<OptionType_t>() );
		}
		else if ( value < 99 )
		{
			// ������ 50��
			pResultItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_STAR, 12, list<OptionType_t>() );
			pResultItem->setNum(50);
		}
		else
		{
			// �Ƹ� �ͽ����� A��
			pResultItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_MIXING_ITEM, 3, list<OptionType_t>() );
		}
	}

	else if ( pItem->getItemType() == 21 )
	{
		int value = rand()%100;
		bFullStack = false;

		if ( value < 70 )
		{
			// ��Ȱ ��ũ��
			pResultItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_RESURRECT_ITEM, 0, list<OptionType_t>() );
		}
		else if ( value < 95 )
		{
			// ��� ����
			pResultItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_STAR, 9, list<OptionType_t>() );
		}
		else if ( value < 99 )
		{
			// �˸��� 3
			pResultItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_TREE, 28, list<OptionType_t>() );
		}
		else
		{
			// Ǫ�� 4��
			pResultItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_PET_FOOD, 4, list<OptionType_t>() );
			pResultItem->setNum(4);
		}
	}else if ( pItem->getItemType() == 27 )
	{
		bFullStack = false;
		pResultItem = g_pItemMineInfoManager->getRandomItem( 437, 459 );
	}else if ( pItem->getItemType() == 29 )
	{
		bFullStack = false;

		/*if ( pCreature->isSlayer() )
		{
		pResultItem = g_pMonsterItemDropManager->getPayItemRace( 1900, 1924, 0 );
		}
		if ( pCreature->isVampire() )
		{
		pResultItem = g_pMonsterItemDropManager->getPayItemRace( 1925, 1936, 1 );
		}
		if ( pCreature->isOusters() )
		{
		pResultItem = g_pMonsterItemDropManager->getPayItemRace( 1937, 1951, 1 );
		}*/
	}

	if ( pResultItem == NULL )
	{
		filelog("GiftBoxErrorLog.txt", "[Name] : %s : �� �� �ִ� �������� ����\n", pCreature->getName().c_str());
		return;
	}

	// ���� �� �ִ� �������̸� �� ä���ش�
	if ( pResultItem->isStackable() && bFullStack )
	{
		int MaxStack = ItemMaxStack[pResultItem->getItemClass()];
		pResultItem->setNum( MaxStack );
	}

	bool isChargingItem = false;
	int chargeNum = 0;
	// Charging �����۵� �� ä���ش�
	if ( pResultItem->getItemClass() == Item::ITEM_CLASS_SLAYER_PORTAL_ITEM ) 
	{
		SlayerPortalItem* pSlayerPortalItem = dynamic_cast<SlayerPortalItem*>(pResultItem);
		pSlayerPortalItem->setCharge( pSlayerPortalItem->getMaxCharge() );
		isChargingItem = true;
		chargeNum = pSlayerPortalItem->getMaxCharge();
	}
	else if ( pResultItem->getItemClass() == Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM )
	{
		VampirePortalItem* pVampirePortalItem = dynamic_cast<VampirePortalItem*>(pResultItem);
		pVampirePortalItem->setCharge( pVampirePortalItem->getMaxCharge() );
		isChargingItem = true;
		chargeNum = pVampirePortalItem->getMaxCharge();
	}
	else if ( pResultItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM )
	{
		OustersSummonItem* pOustersSummonItem = dynamic_cast<OustersSummonItem*>(pResultItem);
		pOustersSummonItem->setCharge( pOustersSummonItem->getMaxCharge() );
		isChargingItem = true;
		chargeNum = pOustersSummonItem->getMaxCharge();
	}

	pZone->registerObject(pResultItem);

	GCUseOK gcUseOK;
	pGamePlayer->sendPacket(&gcUseOK);
	// ������ ���� ���ڸ� ����� �� �ڸ��� �������� �ִ´�
	pInventory->deleteItem(InvenX, InvenY);
	pItem->destroy();
	SAFE_DELETE(pItem);

	// inventory�� �ִ´�.
	if(pInventory->addItem(InvenX, InvenY, pResultItem))
	{
		pResultItem->create(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);

		GCCreateItem gcCreateItem;
/*		gcCreateItem.setObjectID(pResultItem->getObjectID());
		gcCreateItem.setItemClass(pResultItem->getItemClass());
		gcCreateItem.setItemType(pResultItem->getItemType());
		gcCreateItem.setOptionType(pResultItem->getOptionTypeList());
		gcCreateItem.setDurability(pResultItem->getDurability());
		gcCreateItem.setItemNum(pResultItem->getNum());

		if ( isChargingItem )
			gcCreateItem.setEnchantLevel( chargeNum );

		gcCreateItem.setInvenX(InvenX);
		gcCreateItem.setInvenY(InvenY);*/
		makeGCCreateItem( &gcCreateItem, pResultItem, InvenX, InvenY );

		pGamePlayer->sendPacket(&gcCreateItem);

		// ItemTraceLog �� �����
		if ( pResultItem != NULL && pResultItem->isTraceItem() )
		{
			remainTraceLog( pResultItem, "BLACK BOX", pCreature->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
		}

	}
	else
	{
		filelog("GiftBoxErrorLog.txt", "[Name] : %s : �κ��丮�� �������� ���� �� ����. Item : %s\n", pCreature->getName().c_str(), pResultItem->toString().c_str());
		return;
	}



#endif

    __END_DEBUG_EX __END_CATCH
}

void CGUseItemFromInventoryHandler::executeTrapItem(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
#ifdef __GAME_SERVER__
	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// ���� �Լ����� ���� üũ�� ���� �߱� ������,
	// ���� üũ�� ���� ��????
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	Item*           pItem        = pInventory->getItem(InvenX, InvenY);

	TrapItem*		pTrapItem	= dynamic_cast<TrapItem*>(pItem);
	TrapItemInfo*	pInfo		= dynamic_cast<TrapItemInfo*>(g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType() ));

	/*if ( !SiegeManager::Instance().isSiegeZone(pPC->getZoneID()) )
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}*/

	if ( pTrapItem != NULL && pInfo != NULL )
	{
		/*if ( pTrapItem->getItemType() <= 3 )
		{
			// Ʈ��
			if (
					( pCreature->getX() < 97 || pCreature->getX() > 121 )
				||	( pCreature->getY() < 135 || pCreature->getY() > 170 )
			   )
			{
				GCCannotUse _GCCannotUse;
				_GCCannotUse.setObjectID(pPacket->getObjectID());
				pGamePlayer->sendPacket(&_GCCannotUse);
				return;
			}
		}
		else
		{
			// ��ֹ�
			if (
					( pCreature->getX() < 132 || pCreature->getX() > 152 )
				||	( pCreature->getY() < 105 || pCreature->getY() > 135 )
			   )
			{
				GCCannotUse _GCCannotUse;
				_GCCannotUse.setObjectID(pPacket->getObjectID());
				pGamePlayer->sendPacket(&_GCCannotUse);
				return;
			}
		}*/

		switch ( pInfo->getFunction() )
		{
			case TrapItemInfo::SUMMON_MONSTER :
			case TrapItemInfo::SUMMON_TRAP :
				{
					Monster* pMonster = new Monster( pInfo->getParameter() );
					pCreature->getZone()->addCreature( pMonster, pCreature->getX(), pCreature->getY(), 2 );
					if ( pInfo->getFunction() == TrapItemInfo::SUMMON_TRAP )
						addSimpleCreatureEffect( pMonster, Effect::EFFECT_CLASS_HIDE_TO_ATTACKER );
				}
				break;
			case TrapItemInfo::MAKE_EFFECT :
				{
					Zone* pZone = pPC->getZone();

					ZoneCoord_t sx = pPC->getX();
					ZoneCoord_t sy = pPC->getY();

					Monster* pMonster = new Monster( pInfo->getParameter() );
					pMonster->setBrain(NULL);
					EffectKillTimer* pTimer = new EffectKillTimer( pMonster );
					pTimer->setDeadline(65000);
					pMonster->setFlag( Effect::EFFECT_CLASS_NO_DAMAGE );
					pMonster->addEffect( pTimer );

					pCreature->getZone()->addCreature( pMonster, sx, sy, 2 );
					addSimpleCreatureEffect( pMonster, Effect::EFFECT_CLASS_HIDE_TO_ATTACKER );
					sx = pMonster->getX();
					sy = pMonster->getY();

					GCAddEffectToTile gcAE;
					gcAE.setDuration( 65000 );
					gcAE.setXY( sx, sy );

					for ( int i=1; i<=7; ++i )
					{
						ZoneCoord_t tx = sx+i;
						ZoneCoord_t ty = sy+i;
						if ( !isValidZoneCoord( pZone, tx, ty ) ) continue;
						if ( !pZone->getTile(tx, ty).canAddEffect() ) continue;

						EffectTurretLaser* pTurretLaser = new EffectTurretLaser( pZone, tx, ty );
						pTurretLaser->setDeadline(65000);
						pTurretLaser->setNextTime(0);
						pZone->registerObject( pTurretLaser );
						pZone->addEffect( pTurretLaser );
						pZone->getTile(tx, ty).addEffect( pTurretLaser );

						gcAE.setEffectID( pTurretLaser->getSendEffectClass() );
						gcAE.setObjectID( pTurretLaser->getObjectID() );
						gcAE.setXY( tx, ty );
						pZone->broadcastPacket( tx, ty, &gcAE );
					}
				}
				break;
		}

		GCUseOK _GCUseOK;
		pGamePlayer->sendPacket(&_GCUseOK);

		pInventory->deleteItem(InvenX, InvenY);
		pItem->destroy();
		SAFE_DELETE(pItem);
	}

#endif

}
void CGUseItemFromInventoryHandler::executeSubInventory(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__
	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// ���� �Լ����� ��??üũ�� ���� �߱� ������,
	// ���� üũ�� ���� ����Ѵ�.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	Item*           pItem        = pInventory->getItem(InvenX, InvenY);

	SubInventory* pSubInventory = dynamic_cast<SubInventory*>(pItem);
	Inventory*      pSubInventoryInven   = ((SubInventory*)pSubInventory)->getInventory();
	SubInventoryInfo* pInfo = dynamic_cast<SubInventoryInfo*>(g_pItemInfoManager->getItemInfo( pSubInventory->getItemClass(), pSubInventory->getItemType() ));

	BYTE ItemCount = 0;
	int	ItemCount2 = 0;

	if ( pItem->getObjectID() != pPacket->getObjectID() ||
		pInfo == NULL )
	{
		////cout << "���� ������Ʈ �Ƶ� Ʋ��" << endl;
		sendCannotUse( pPacket, pPlayer );
		return;
	}

	InventoryInfo* pInventoryInfo = new InventoryInfo();
	list<Item*> ItemList;
	VolumeHeight_t Height = pSubInventoryInven->getHeight();
	VolumeWidth_t Width = pSubInventoryInven->getWidth();

	for (int j = 0; j < Height; j++) 
	{
		for (int i = 0 ; i < Width ; i ++) 
		{
			if (pSubInventoryInven->hasItem(i, j)) 
			{
				Item* pItems = pSubInventoryInven->getItem(i , j);
				VolumeWidth_t ItemWidth = pItems->getVolumeWidth();
				list<Item*>::iterator itr = find(ItemList.begin() , ItemList.end() , pItems);

				if (itr == ItemList.end()) 
				{
					ItemList.push_back(pItems);

					// InventorySlotInfo�� ����
					InventorySlotInfo* pInventorySlotInfo = new InventorySlotInfo();
					pItems->makePCItemInfo( *pInventorySlotInfo );
					pInventorySlotInfo->setInvenX(i);
					pInventorySlotInfo->setInvenY(j);
					pInventoryInfo->addListElement(pInventorySlotInfo);
					ItemCount++;
					ItemCount2++;
					i = i + ItemWidth - 1;
				}
			}
		}
	}
	pInventoryInfo->setListNum(ItemCount);

	cout << "LIST : " << ItemCount2 << ", SIZE :  " << (int)pSubInventoryInven->getHeight() <<  (int)pSubInventoryInven->getWidth() << endl;

	GCSubInventoryInfo gcSubInventoryInfo;
	gcSubInventoryInfo.setObjectID(pItem->getObjectID());
	gcSubInventoryInfo.setInventoryInfo(pInventoryInfo);	
	pGamePlayer->sendPacket(&gcSubInventoryInfo);

	pPC->loadTimeLimitItem();
	pPC->sendTimeLimitItemInfo();
	
#endif

	__END_CATCH
}
void CGUseItemFromInventoryHandler::executeSkillBook(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__
	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// ���� �Լ����� ���� üũ�� ���� �߱� ������,
	// ���� üũ�� ���� ����Ѵ�.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();

	Storage_t Storage = STORAGE_INVENTORY;
	StorageID_t StorageID = 0;

	bool SubInventoryTrue = false;

	if(pPacket->getInventoryItemObjectID() != 0){
		Item*           pInvenItem        = NULL;
		pInvenItem        = pInventory->getItemWithObjectID(pPacket->getInventoryItemObjectID());
		SubInventory* pSubInventory = dynamic_cast<SubInventory*>(pInvenItem);
		SubInventoryTrue = true;
		Storage = STORAGE_BOX;
		StorageID = pInvenItem->getItemID();
		pInventory = ((SubInventory*)pSubInventory)->getInventory();
	}

	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	
	SkillBookInfo* pInfo = dynamic_cast<SkillBookInfo*>(g_pItemInfoManager->getItemInfo( pItem->getItemClass(), pItem->getItemType() ));
	SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(pInfo->getFunctionValue());
	SkillDomainType_t DomainType = pSkillInfo->getDomainType();
	bool Succes = false;

	if ( pItem->getObjectID() != pPacket->getObjectID() ||
		pInfo == NULL )
	{
		////cout << "���� ������Ʈ �Ƶ� Ʋ��" << endl;
		sendCannotUse( pPacket, pPlayer );
		return;
	}

	if(pInfo->getRaceValue() != pCreature->getCreatureClass() && pInfo->getRaceValue() != 7){
		//cout << "������ ��?? << endl;
		sendCannotUse( pPacket, pPlayer );
		return;
	}

	switch(pCreature->getCreatureClass()){
		
		// �����̾� �� ���.
		case 0 :
		{

			Slayer* pSlayer          = dynamic_cast<Slayer*>(pCreature);
		
			// ���� �ִ� ���� �� �ɷ�ġ ������ �ȵ�.
			if(!pSlayer->isRealWearing(pItem)){
			GCLearnSkillFailed failpkt; 
			failpkt.setSkillType(pInfo->getFunctionValue());
			failpkt.setDesc(1);
			pPlayer->sendPacket(&failpkt);
			sendCannotUse( pPacket, pPlayer );
			return;
			break;
			}

			if(pInfo->getFunctionValue() == 404 || pInfo->getFunctionValue() == 405){
				if(pSlayer->getHighestSkillDomain() != 3 && pSlayer->getHighestSkillDomain() != 4){

					GCLearnSkillFailed failpkt; 
					failpkt.setSkillType(pInfo->getFunctionValue());
					failpkt.setDesc(1);
		
					pPlayer->sendPacket(&failpkt);
		
					sendCannotUse( pPacket, pPlayer );
					return;
				
					break;
				}
			}

			SkillSlot* pSkillSlot = pSlayer->hasSkill( pInfo->getFunctionValue() );
			// �̹� ��ų�� ���
			if(pSkillSlot != NULL){ 
			GCLearnSkillFailed failpkt; 
			failpkt.setSkillType(pInfo->getFunctionValue());;
			failpkt.setDesc(2);
			pPlayer->sendPacket(&failpkt);
			sendCannotUse( pPacket, pPlayer );
			return;
			break;
			}

			pSlayer->addSkill(pInfo->getFunctionValue());

			GCLearnSkillOK okpkt;
			okpkt.setSkillType(pInfo->getFunctionValue());
			okpkt.setSkillDomainType(DomainType);
			pPlayer->sendPacket (&okpkt);

				SLAYER_RECORD prev;

				pSlayer->getSlayerRecord(prev);
				pSlayer->initAllStat();
				pSlayer->sendRealWearingInfo();
				pSlayer->sendModifyInfo(prev);
			Succes = true;
				break;
		}

		// �����̾� �� ��??
		case 1 :
		{

			Vampire* pSlayer          = dynamic_cast<Vampire*>(pCreature);
		
			// ���� �ִ� ���� �� �ɷ�ġ ������ �ȵ�.
			if(!pSlayer->isRealWearing(pItem)){
			GCLearnSkillFailed failpkt; 
			failpkt.setSkillType(pInfo->getFunctionValue());
			failpkt.setDesc(1);
			pPlayer->sendPacket(&failpkt);
			sendCannotUse( pPacket, pPlayer );
			return;
			break;
			}

			VampireSkillSlot* pSkillSlot = pSlayer->hasSkill( pInfo->getFunctionValue() );
			// �̹� ��ų�� ���
			if(pSkillSlot != NULL){ 
			GCLearnSkillFailed failpkt; 
			failpkt.setSkillType(pInfo->getFunctionValue());;
			failpkt.setDesc(2);
			pPlayer->sendPacket(&failpkt);
			sendCannotUse( pPacket, pPlayer );
			return;
			break;
			}

			pSlayer->addSkill(pInfo->getFunctionValue());

			GCLearnSkillOK okpkt;
			okpkt.setSkillType(pInfo->getFunctionValue());
			okpkt.setSkillDomainType(DomainType);
			pPlayer->sendPacket (&okpkt);

			VAMPIRE_RECORD prev;

			pSlayer->getVampireRecord( prev );
			pSlayer->initAllStat();
			pSlayer->sendRealWearingInfo();
			pSlayer->sendModifyInfo( prev );
			Succes = true;
				break;
		}

		// �����̾� �� ���.
		case 4 :
		{

			Ousters* pSlayer          = dynamic_cast<Ousters*>(pCreature);
		
			// ���� �ִ� ���� �� �ɷ�ġ ������ �ȵ�.
			if(!pSlayer->isRealWearing(pItem)){
			GCLearnSkillFailed failpkt; 
			failpkt.setSkillType(pInfo->getFunctionValue());
			failpkt.setDesc(1);
			pPlayer->sendPacket(&failpkt);
			sendCannotUse( pPacket, pPlayer );
			return;
			break;
			}

			OustersSkillSlot* pSkillSlot = pSlayer->hasSkill( pInfo->getFunctionValue() );
			// �̹� ��ų�� ���
			if(pSkillSlot != NULL){ 
			GCLearnSkillFailed failpkt; 
			failpkt.setSkillType(pInfo->getFunctionValue());;
			failpkt.setDesc(2);
			pPlayer->sendPacket(&failpkt);
			sendCannotUse( pPacket, pPlayer );
			return;
			break;
			}

			pSlayer->addSkill(pInfo->getFunctionValue());

			GCLearnSkillOK okpkt;
			okpkt.setSkillType(pInfo->getFunctionValue());
			okpkt.setSkillDomainType(DomainType);
			pPlayer->sendPacket (&okpkt);

				OUSTERS_RECORD prev;

				pSlayer->getOustersRecord( prev );
				pSlayer->initAllStat();
				pSlayer->sendRealWearingInfo();
				pSlayer->sendModifyInfo( prev );
			Succes = true;
				break;
		}
		default :
		{
				return;
				break;
		}
		
	}

	if(Succes){
	pInventory->deleteItem(pItem->getObjectID());
	pItem->destroy();
	SAFE_DELETE(pItem);

	GCUseOK _GCUseOK;
	pGamePlayer->sendPacket(&_GCUseOK);
	}

	
#endif

	__END_CATCH
}
