//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddItemToItemHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////
/*

// �� �������� �� �ٸ� �����ۿ� �ִ´�.
 [Client]                                               [Server]
           -- CGAddItemToItem
              (mouseItem_ObjectID, invenX, invenY) 
			  =(���콺�� ����ִ� ��, upgrade�� item XY) -->

            <-- GCAddItemToItemVerify(����ڵ�, ���ð�) ---
   
//-------------+---------------------------------------------
// ��� packet | client ó��
//-------------+---------------------------------------------
// �Ұ� packet | �Ұ� message ���
// ���� packet | ���� message ���, �� ����, [������ ����]
// ���� packet | �� ����, option����
//-------------+---------------------------------------------
*/


#include "CGAddItemToItem.h"

#ifdef __GAME_SERVER__
	#include <stdio.h>
	#include "GamePlayer.h"
	#include "ZoneUtil.h"
	#include "PlayerCreature.h"
	#include "Inventory.h"
	#include "Item.h"
	#include "ItemInfoManager.h"
#include "ItemFactoryManager.h"
	#include "OptionInfo.h"
	#include "ItemUtil.h"
	#include "EventStar.h"
	#include "SlayerTuningItem.h"
	#include "VampireTuningItem.h"
	#include "OustersTuningItem.h"
	#include "PetItem.h"
	#include "PetEnchantItem.h"
	#include "PetInfo.h"
	#include "PetAttrInfo.h"
	#include "PetTypeInfo.h"
	#include "CreatureUtil.h"
	#include "MixingItem.h"
	#include "PacketUtil.h"
	#include "Zone.h"
	#include "CrystalOptionLoader.h"

	#include "Gpackets/GCAddItemToItemVerify.h"
	#include "Gpackets/GCDeleteInventoryItem.h"
	#include "Gpackets/GCCreateItem.h"
	#include	"Gpackets/GCUpdateInfo.h"

	#include "SystemAvailabilitiesManager.h"

	void executeUpGrade(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem);
	void executeTypeGrade(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem);
	void executeEnchantOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY);
	void executeEnchantRareOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY);
	void executeEnchantRareThreeOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY);
	void executeEnchantSetOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY);
	void executeEnchantSetRareOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY);
	void executeEnchantSetThreeOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY);
	void executeAddOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, OptionType_t addOptionType);
	void executeAddCoralOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, int addOptionType);
	void executeAddSetOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, OptionType_t addOptionType);
	void executeTransKit(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem);
	void executeRedSunCore(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem);
	void executeVampireTuningItem(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem);
	void executeOustersTuningItem(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem);
	extern bool isPossibleOptionItemClass(Item::ItemClass IClass);

	OptionInfo* getOptionInfo(OptionType_t optionType);

	void    	processUpgradeOptionType(Item* pItem, OptionType_t currentOptionType, OptionInfo* pOptionInfo);
	void    	processUpgradeSetOptionType(Item* pItem, OptionType_t currentOptionType, OptionInfo* pOptionInfo);
	void		crashItem(Item* pItem, Inventory* pInventory, CoordInven_t invenX, CoordInven_t invenY);
	void    	downgradeOptionType(Item* pItem, OptionType_t currentOptionType, OptionInfo* pOptionInfo);
	void    	downgradeSetOptionType(Item* pItem, OptionType_t currentOptionType, OptionInfo* pOptionInfo);
	void		sendEnchantImpossible(GamePlayer* pGamePlayer);
	void		sendEnchantOK(GamePlayer* pGamePlayer, DWORD optionChange);
	void		sendSetEnchantOK(GamePlayer* pGamePlayer, DWORD optionChange);
	// add by sonic �������Է��صķ��
	void		sendEnchantOK(GamePlayer* pGamePlayer, DWORD optionChange, DWORD optionCHange2);

	// PET ���� ��æƮ �������� �����.
	void    	processUpgradePetOptionType(PetInfo* pPetInfo, Item* pItem, OptionType_t currentOptionType, OptionInfo* pOptionInfo);
	void    	downgradePetOptionType(PetInfo* pPetInfo, Item* pItem, OptionType_t currentOptionType, OptionInfo* pOptionInfo);
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAddItemToItemHandler::execute (CGAddItemToItem* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	//cout << pPacket->toString().c_str() << endl;

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	Assert(pGamePlayer != NULL);	// by sigi

	if (pGamePlayer->getPlayerStatus() == GPS_NORMAL) 
	{
		SYSTEM_ASSERT( SYSTEM_ENCHANT );

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);
		ObjectID_t      objectID    = pPacket->getObjectID();
		Inventory* 		pInventory  = pPC->getInventory();
		CoordInven_t 	invenX      = pPacket->getX();
		CoordInven_t 	invenY      = pPacket->getY();

		// �κ��丮�� �������� ������(��ǥüũ�� �ϰ� �ȴ�.)
		if (!pInventory->hasItem(invenX, invenY))
		{
			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );
			return;
		}

		// ���콺 ������
		Item*           pMouseItem  = pPC->getExtraInventorySlotItem();

		// �κ��丮�� �ִ� ��?��?
		Item*      		pItem       = pInventory->getItem(invenX, invenY);

		// �������� ���ų�
		// objectID�� �߸��� ���
		if (pMouseItem==NULL
			|| pItem==NULL
			|| pMouseItem->getObjectID()!=objectID
			|| pMouseItem->getNum() != 1 )
		{
			//cout << "Wrong Item" << endl;

			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );
			return;
		}


		switch (pMouseItem->getItemClass())
		{
			//---------------------------------------------------------
			//
			// 				ITEM_CLASS_EVENT_STAR
			//
			//---------------------------------------------------------
			// �������� �ɼ��� upgrade ��Ų��.
			//---------------------------------------------------------
			case Item::ITEM_CLASS_EVENT_STAR : 
			{
				ItemInfo* pItemInfo = g_pEventStarInfoManager->getItemInfo( pMouseItem->getItemType() );
				Assert(pItemInfo!=NULL);

				EventStarInfo* pEventStarInfo = dynamic_cast<EventStarInfo*>(pItemInfo);
				Assert(pEventStarInfo!=NULL);

				int optionSize = pItem->getOptionTypeSize();
				int optionSize2 = pItem->getOptionTypeSize2();

				if (pEventStarInfo->getFunctionFlag() == 21)
				{
					if(optionSize == 1){
					executeEnchantOption(pGamePlayer, pMouseItem, pItem,  invenX, invenY);
					}else if(optionSize == 2){
					executeEnchantRareOption(pGamePlayer, pMouseItem, pItem, invenX, invenY);
					}else if(optionSize == 3){
					executeEnchantRareThreeOption(pGamePlayer, pMouseItem, pItem, invenX, invenY);
					}
				}
				else if (pEventStarInfo->getFunctionFlag() == 20)
				{
					executeRedSunCore(pGamePlayer, pMouseItem, pItem);
				}else if (pEventStarInfo->getFunctionFlag() == 17)
				{
					int addOptionType = pEventStarInfo->getFunctionValue();
					executeAddSetOption(pGamePlayer, pMouseItem, pItem, addOptionType);
				}
				else if (pEventStarInfo->getFunctionFlag() == 15)
				{
					executeEnchantSetThreeOption(pGamePlayer, pMouseItem, pItem, invenX, invenY);
				}
				else if (pEventStarInfo->getFunctionFlag() == 14)
				{
					executeEnchantSetRareOption(pGamePlayer, pMouseItem, pItem, invenX, invenY);
				}
				else if (pEventStarInfo->getFunctionFlag() == 13)
				{
					executeEnchantSetOption(pGamePlayer, pMouseItem, pItem, invenX, invenY);
				}
				else if (pEventStarInfo->getFunctionFlag() == 12)
				{
					executeTypeGrade(pGamePlayer, pMouseItem, pItem);
				}
				else if (pEventStarInfo->getFunctionFlag() == 11)
				{
					int addOptionType = pEventStarInfo->getFunctionValue();
					executeAddCoralOption(pGamePlayer, pMouseItem, pItem, addOptionType);
				}
				//����װ���ȼ�
				else if ( pEventStarInfo->getFunctionFlag() == 16 )
				{
					executeUpGrade(pGamePlayer, pMouseItem, pItem);
				}
				else if (pEventStarInfo->isFunctionTransKit())
				{
					executeTransKit(pGamePlayer, pMouseItem, pItem);
				}
				// Enchant Option
				else if (optionSize>1)	// by sigi. 2002.10.21
				{
					if (pEventStarInfo->isFunctionEnchantRareOption())
					{
						if(pMouseItem->getItemType()==6 || pMouseItem->getItemType()==47 || pMouseItem->getItemType()==48 || pMouseItem->getItemType()==49)// ��������װ��
							executeEnchantRareThreeOption(pGamePlayer, pMouseItem, pItem, invenX, invenY);
						else
							executeEnchantRareOption(pGamePlayer, pMouseItem, pItem, invenX, invenY);
					}
					else
					{
						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE );
						pGamePlayer->sendPacket( &gcAddItemToItemVerify );
						return;
					}
				}
				else if (pEventStarInfo->isFunctionEnchantOption())
				{
					executeEnchantOption(pGamePlayer, pMouseItem, pItem, invenX, invenY);
				}
				// Add Option
				else if (pEventStarInfo->isFunctionAddOption())
				{
					int addOptionType = pEventStarInfo->getFunctionValue();
					executeAddOption(pGamePlayer, pMouseItem, pItem, addOptionType);
				}
				// Coral Option
			}
			break;

			case Item::ITEM_CLASS_PET_ENCHANT_ITEM :
			{
				//cout << "Trying Pet Enchant... " << endl;
				if ( pItem->getItemClass() != Item::ITEM_CLASS_PET_ITEM )
				{
					//cout << "�� �����ۿ��ٰ� �Ѱ� �ƴԴ�." << endl;
					GCAddItemToItemVerify gcAddItemToItemVerify;
					gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
					pGamePlayer->sendPacket( &gcAddItemToItemVerify );
					return;
				}
				//ItemInfo* pItemInfo2 = g_pPetEnchantItemInfoManager->getItemInfo( pMouseItem->getItemType() );
				//Assert( pItemInfo2 != NULL );

				PetEnchantItemInfo* pItemInfo = dynamic_cast<PetEnchantItemInfo*>(g_pPetEnchantItemInfoManager->getItemInfo( pMouseItem->getItemType() ));
				Assert( pItemInfo != NULL );

				PetItem* pPetItem = dynamic_cast<PetItem*>(pItem);
				PetInfo* pPetInfo = NULL;
				if ( pPetItem == NULL || ( pPetInfo = pPetItem->getPetInfo() ) == NULL )
				{
					//cout << "�� �������� ?ƴϰų?�� �����ۿ� �� ���°� �����ϴ�." << endl;
					GCAddItemToItemVerify gcAddItemToItemVerify;
					gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
					pGamePlayer->sendPacket( &gcAddItemToItemVerify );
					return;
				}

				/*
					ENCHANT_FUNCTION = 0,
					SPEC_OPTION_FUNCTION = 1,
					REVIVAL_FUNCTION = 13,
					RARE_FUNCTION = 14
				*/
				switch ( pItemInfo->getFunction() )
				{
					case PetEnchantItemInfo::ENCHANT_FUNCTION :
					{
						if ( pPetInfo->getPetAttr() != 0xff )
						{
							//cout << "�̹� ��æƮ�� �������Դϴ�." << endl;
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}
						//cout << "ǥ�� ��æƮ �õ����Դϴ�." << endl;
						pPC->deleteItemFromExtraInventorySlot();
						pMouseItem->destroy();
						SAFE_DELETE( pMouseItem );

						if ( PetAttrInfoManager::Instance().enchantRandomAttr( pPetInfo, pItemInfo->getFunctionGrade() ) )
						{
							//cout << "��æ??����." << endl;
							pPetItem->savePetInfo();

							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
							gcAddItemToItemVerify.setParameter( ((uint)pPetInfo->getPetAttr())<<16 | (uint)pPetInfo->getPetAttrLevel() );

							pGamePlayer->sendPacket( &gcAddItemToItemVerify );

							if ( pPC->getPetInfo() == pPetInfo )
							{
								//cout << "�̹� �ҷ����־ ��Ŷ ������ ���Դϴ�." << endl;
								sendPetInfo( pGamePlayer, true );
								pPC->initAllStatAndSend();
							}
							return;
						}
						else
						{
							//cout << "��æƮ ����" << endl;
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}
					}
					break;
					case PetEnchantItemInfo::SPEC_OPTION_FUNCTION :
					{
						if ( pPetInfo->getPetAttr() != 0xff )
						{
							//cout << "�̹� ��æƮ�� �������Դϴ�." << endl;
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}
						pPC->deleteItemFromExtraInventorySlot();
						pMouseItem->destroy();
						SAFE_DELETE( pMouseItem );

						if ( PetAttrInfoManager::Instance().enchantSpecAttr( pPetInfo, (PetAttr_t)pItemInfo->getFunctionGrade() ) )
						{
							pPetItem->savePetInfo();
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
							gcAddItemToItemVerify.setParameter( ((uint)pPetInfo->getPetAttr())<<16 | (uint)pPetInfo->getPetAttrLevel() );
//							gcAddItemToItemVerify.setParameter( pPetInfo->getPetAttr() );

							pGamePlayer->sendPacket( &gcAddItemToItemVerify );

							if ( pPC->getPetInfo() == pPetInfo )
							{
								sendPetInfo( pGamePlayer, true );
								pPC->initAllStatAndSend();
							}
							return;
						}
						else
						{
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}
					}
					break;
					case PetEnchantItemInfo::PET_AMPUL_FUNCTION:
					{
						//cout << "�� ���� ��æƮ ��?Դϴ?" << endl;
						if ( pPetInfo->getPetLevel() < 49 || pPetInfo->getPetVersionOption() != 0)
						{
							//cout << "������ �ȵ� �� ��æƮ���� ����" << endl;
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}

						pPC->deleteItemFromExtraInventorySlot();
						pMouseItem->destroy();
						SAFE_DELETE( pMouseItem );

						/*
						OptionType_t targetOption = rand()%87;
						targetOption++;
						*/

						OptionType_t targetOption = 0;
						int ratio = rand() % 100000;
						const list<PetEnchantOption*>& petEnchantOptions = g_pOptionInfoManager->getPetEnchantOptionList();
						list<PetEnchantOption*>::const_iterator itr = petEnchantOptions.begin();
						list<PetEnchantOption*>::const_iterator endItr = petEnchantOptions.end();

						for ( ; itr != endItr ; itr++ )
						{
							PetEnchantOption* pPetEnchantOption = *itr;
							if ( pPetEnchantOption->getRatio() > ratio )
							{
								targetOption = pPetEnchantOption->getOptionType();
								break;
							}
						}

						pPetInfo->setPetVersionOption( targetOption );
						sendPetInfo( pGamePlayer );

							list<OptionType_t> olist;

							if ( pPetInfo->getPetOption() != 0 ) 
							olist.push_back(pPetInfo->getPetOption());

							if ( pPetInfo->getPetVersionOption() != 0 ) 
							olist.push_back(pPetInfo->getPetVersionOption());
			
							list<OptionType_t> optionList = pPetInfo->getOptionType();
							list<OptionType_t>::const_iterator itr3 = optionList.begin();

							while(itr3 != optionList.end())
							{
							olist.push_back(*itr3);
							itr3++;
							}

						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_THIRD_ENCHANT_OK );
						gcAddItemToItemVerify.setParameter( 0 );
						gcAddItemToItemVerify.setThirdOptionType( olist );
						pGamePlayer->sendPacket( &gcAddItemToItemVerify );

						char query[100];
						sprintf(query, "PetOption2=%u", (uint)targetOption);
						pItem->tinysave(query);
					}
					break;
					case PetEnchantItemInfo::RARE_FUNCTION:
					{
						//cout << "�� ���� ��æƮ ���Դϴ�." << endl;
						if ( pPetInfo->getPetLevel() < 49  || pPetInfo->getPetOption() != 0)
						{
							//cout << "������ �ȵ� �� ��æƮ���� ����" << endl;
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}

						pPC->deleteItemFromExtraInventorySlot();
						pMouseItem->destroy();
						SAFE_DELETE( pMouseItem );

						/*
						OptionType_t targetOption = rand()%87;
						targetOption++;
						*/

						OptionType_t targetOption = 0;
						int ratio = rand() % 100000;
						const list<PetEnchantOption*>& petEnchantOptions = g_pOptionInfoManager->getPetEnchantOptionList();
						list<PetEnchantOption*>::const_iterator itr = petEnchantOptions.begin();
						list<PetEnchantOption*>::const_iterator endItr = petEnchantOptions.end();

						for ( ; itr != endItr ; itr++ )
						{
							PetEnchantOption* pPetEnchantOption = *itr;
							if ( pPetEnchantOption->getRatio() > ratio )
							{
								targetOption = pPetEnchantOption->getOptionType();
								break;
							}
						}

						pPetInfo->setPetOption( targetOption );
						sendPetInfo( pGamePlayer );

							list<OptionType_t> olist;

							if ( pPetInfo->getPetOption() != 0 ) 
							olist.push_back(pPetInfo->getPetOption());

							if ( pPetInfo->getPetVersionOption() != 0 ) 
							olist.push_back(pPetInfo->getPetVersionOption());
			
							list<OptionType_t> optionList = pPetInfo->getOptionType();
							list<OptionType_t>::const_iterator itr3 = optionList.begin();

							while(itr3 != optionList.end())
							{
							olist.push_back(*itr3);
							itr3++;
							}

						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_THIRD_ENCHANT_OK );
						gcAddItemToItemVerify.setParameter( 0 );
						gcAddItemToItemVerify.setThirdOptionType( olist );
						pGamePlayer->sendPacket( &gcAddItemToItemVerify );

						char query[100];
						sprintf(query, "PetOption=%u", (uint)targetOption);
						pItem->tinysave(query);
					}
					break;
					case PetEnchantItemInfo::PET_MIXING_CLEANER_FUNCTION:
					{
						if ( pPetInfo->getMixOptionTypeSize() == 0)
						{
							//cout << "������ �ȵ� �� ��æƮ���� ����" << endl;
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}

						pPC->deleteItemFromExtraInventorySlot();
						pMouseItem->destroy();
						SAFE_DELETE( pMouseItem );

						list<OptionType_t> olist;

						pPetInfo->setMixOptionType( olist );
						sendPetInfo( pGamePlayer );

						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_THIRD_ENCHANT_OK );
						gcAddItemToItemVerify.setParameter( 0 );
						gcAddItemToItemVerify.setThirdOptionType( olist );
						pGamePlayer->sendPacket( &gcAddItemToItemVerify );

						char query[100];
						sprintf(query, "OptionType2=%s", NULL);
						pItem->tinysave(query);
					break;
					}
					case PetEnchantItemInfo::PET_DIET_FUNCTION:
					{
						if(pPetInfo->getMixOptionTypeSize() == 0 || pMouseItem->getNum() != 1){
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}

						bool bFirstSucceed = false;
						uint optionChange = 0;
						uint optionChange2 = 0;
						int  shiftValue = 16;
						int  diceValue = 3500;

						list<OptionType_t> optionList = pPetInfo->getMixOptionType();
						list<OptionType_t>::const_iterator itr = optionList.begin();
		
						OptionType_t thirdOption  = *itr;
						itr++;
						OptionType_t secondOption = *itr;
						itr++;
						OptionType_t firstOption  = *itr;
						itr--;
						itr--;

						OptionInfo* pFirstOptionInfo = getOptionInfo( firstOption );
						OptionInfo* pSecondOptionInfo = getOptionInfo( secondOption );
						OptionInfo* pThirdOptionInfo = getOptionInfo( thirdOption );

		//������Ʒ���Լ��
						if ( pFirstOptionInfo == NULL || pSecondOptionInfo == NULL || pThirdOptionInfo== NULL)
						{
							sendEnchantImpossible( pGamePlayer );
							return;
						}
		//����Ƿ��ǿ�������Ʒ
						bool bFirstUpgradePossible =  pFirstOptionInfo->isUpgradePossible();
						bool bSecondUpgradePossible = pSecondOptionInfo->isUpgradePossible();
						bool bThirdUpgradePossible =  pThirdOptionInfo->isUpgradePossible();
		//���������������
						if ( !bFirstUpgradePossible && !bSecondUpgradePossible && !bThirdUpgradePossible)
						{
							sendEnchantImpossible( pGamePlayer );
							return;
							}

						if ( bFirstUpgradePossible )
						{
							// ù��° �ɼ��� ��æƮ Ȯ���� ����??2�� Ȯ���� ������.
							int succeedRatio = pFirstOptionInfo->getUpgradeSecondRatio() * ( pItemInfo->getUpgradeRatio() +( rand() %50) );
							//succeedRatio += getPercentValue(succeedRatio,pMouseItem->getHeroOption());
							int dice = rand() % diceValue;
							cout << "dice : " << (int)dice <<  endl;
							cout << "diceValue : " << (int)diceValue <<  endl;

							if ( dice < succeedRatio ) //���ͨ����������װ��
							{
								//cout << "��æƮ ����" << endl;
								processUpgradePetOptionType( pPetInfo, pItem, firstOption, pFirstOptionInfo );

								OptionType_t upgradeOptionType = pFirstOptionInfo->getUpgradeType();
								optionChange = (firstOption << (shiftValue+8)) | (upgradeOptionType << shiftValue);

								bFirstSucceed = true;
							goto EnOK;
						}
						else
						{
						if (pFirstOptionInfo->getUpgradeSecondRatio() < 5)
						{
							int noChangeRatio = 33;
							int downgradeRatio = 46;
							dice = rand() % 100;

							cout << "downgradeRatio" << pItemInfo->getName() << " �ɼǶ����� Ȯ�� " << downgradeRatio << endl;

							if ( dice < noChangeRatio )
							{
							// ��ȭ����
							}
							else if ( dice < noChangeRatio + downgradeRatio )
							{
							// �ɼǶ�����
							downgradePetOptionType( pPetInfo, pItem, firstOption, pFirstOptionInfo );

							OptionType_t previousOptionType = pFirstOptionInfo->getPreviousType();
							optionChange = (firstOption << (shiftValue+8)) | (previousOptionType << shiftValue);
						}
					}
				}
			}
			shiftValue -= 16;

			if ( bSecondUpgradePossible )
			{
			// �ι�° �ɼ��� ��æƮ Ȯ���� ù��° �ɼ��� �������ο� ������.

			int succeedRatio= g_pOptionInfoManager->getRareUpgradeRatio( secondOption, bFirstSucceed ) * ( pItemInfo->getUpgradeRatio() +( rand() %50) );
			//succeedRatio += getPercentValue(succeedRatio,pMouseItem->getHeroOption());
			//int dice = rand() %10000;
			int dice = rand() % diceValue;

			//cout << "�ι�° �ɼ� : " << pSecondOptionInfo->getHName() << " ��æƮ Ȯ�� " << succeedRatio << endl;
			//dice =succeedRatio-1;
			if ( dice < succeedRatio )
			{
				//cout << "��æƮ ����" << endl;
								processUpgradePetOptionType( pPetInfo, pItem, firstOption, pFirstOptionInfo );

				OptionType_t upgradeOptionType = pSecondOptionInfo->getUpgradeType();
				optionChange |= (secondOption << (shiftValue+8)) | (upgradeOptionType << shiftValue);

				bFirstSucceed = true;
				goto EnOK;
			}
			else
			{
				if (pSecondOptionInfo->getUpgradeSecondRatio() < 5)
				{
					int noChangeRatio = 33;
					int downgradeRatio = 46;
					dice = rand() % 100;

					cout << "downgradeRatio" << pItemInfo->getName() << " �ɼǶ����� Ȯ�� " << downgradeRatio << endl;

					if ( dice < noChangeRatio )
					{
						// ��ȭ����
					}
					else if ( dice < noChangeRatio + downgradeRatio )
					{
						// �ɼǶ�����
							downgradePetOptionType( pPetInfo, pItem, firstOption, pFirstOptionInfo );

						OptionType_t previousOptionType = pSecondOptionInfo->getPreviousType();
						optionChange = (secondOption << (shiftValue+8)) | (previousOptionType << shiftValue);
					}
				}
			}
		}
			shiftValue=0;
			if ( bThirdUpgradePossible )
			{
			// �ι�° �ɼ��� ��æƮ Ȯ���� ù��° �ɼ��� �������ο� ������.
			int succeedRatio = g_pOptionInfoManager->getRareUpgradeRatio( thirdOption, bFirstSucceed ) * ( pItemInfo->getUpgradeRatio() +( rand() %50) );
			//succeedRatio += getPercentValue(succeedRatio,pMouseItem->getHeroOption());
			//int dice = rand() %10000;

			int dice = rand() % diceValue;
			//cout << "�ι�° �ɼ� : " << pSecondOptionInfo->getHName() << " ��æƮ Ȯ�� " << succeedRatio << endl;
			//dice =succeedRatio-1;
			if ( dice < succeedRatio )
			{
				//cout << "��æƮ ����" << endl;
								processUpgradePetOptionType( pPetInfo, pItem, firstOption, pFirstOptionInfo );

				OptionType_t upgradeOptionType = pThirdOptionInfo->getUpgradeType();
				optionChange2 |= (thirdOption << (shiftValue+8)) | (upgradeOptionType << shiftValue);

				bFirstSucceed = true;
			}
			else
			{
				if (pThirdOptionInfo->getUpgradeSecondRatio() < 5)
				{
					int noChangeRatio = 33;
					int downgradeRatio = 46;
					dice = rand() % 100;

					cout << "downgradeRatio" << pItemInfo->getName() << " �ɼǶ����� Ȯ�� " << downgradeRatio << endl;

					if ( dice < noChangeRatio )
					{
						// ��ȭ����
					}
					else if ( dice < noChangeRatio + downgradeRatio )
					{
						// �ɼǶ�����
							downgradePetOptionType( pPetInfo, pItem, firstOption, pFirstOptionInfo );

						OptionType_t previousOptionType = pThirdOptionInfo->getPreviousType();
						optionChange2 |= (thirdOption << (shiftValue+8)) | (previousOptionType << shiftValue);
					}
				}
			}
		}

						pPC->deleteItemFromExtraInventorySlot();
						pMouseItem->destroy();
						SAFE_DELETE( pMouseItem );
EnOK:
		
			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_THIRD_ENCHANT_OK );
			gcAddItemToItemVerify.setParameter( 0 );
			gcAddItemToItemVerify.setThirdOptionType( pPetInfo->getMixOptionType() );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );

					}
					break;
					case PetEnchantItemInfo::REVIVAL_FUNCTION:
					{
						//cout << "��Ȱ �õ��� �Դϴ�."  << endl;
						if ( pPetInfo->getPetHP() != 0 )
						{
							//cout << "�� ���� �� ��Ȱ��Ű�� ����" << endl;
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}

						pPC->deleteItemFromExtraInventorySlot();
						pMouseItem->destroy();
						SAFE_DELETE( pMouseItem );

						VSDateTime current = VSDateTime::currentDateTime();
						int Days = pPetInfo->getLastFeedTime().daysTo(current);
						if ( Days < 0 ) Days = 0;

						if ( pItemInfo->getItemType() != 14 )
						{
							int value = rand()%100;
							if ( Days >= 8 || value >= (10-Days/2)*10 )
							{
								GCAddItemToItemVerify gcAddItemToItemVerify;
								gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL );
								pGamePlayer->sendPacket( &gcAddItemToItemVerify );
								return;
							}
						}

						pPetInfo->setPetHP( pItemInfo->getFunctionGrade() );
						pPetInfo->setFeedTime( VSDateTime::currentDateTime() );
						pPetInfo->getPetItem()->savePetInfo();

						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_REVIVAL_OK );
						gcAddItemToItemVerify.setParameter( pPetInfo->getPetHP() );

						pGamePlayer->sendPacket( &gcAddItemToItemVerify );
					}
					break;
					case PetEnchantItemInfo::MUTANT_FUNCTION:
					{
						if ( pPetInfo->getPetType() == pItemInfo->getFunctionGrade() )
						{
							cout << "�������� �ƴ϶��ϴ�." << endl;
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}

						list<OptionType_t> optionTypeList;
						Item* pItem2 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_PET_ITEM, pItemInfo->getFunctionGrade(), optionTypeList );
						Assert( pItem2 != NULL );

						_TPOINT pt;
						if (!pInventory->CheckaddItem(invenX, invenY, pItem2, pItem))
						{
							SAFE_DELETE(pItem2);

							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );		
							return;
						}

						bool summonPet = pPC->getPetInfo() == pPetInfo;

						PetTypeInfo* pPetTypeInfo = PetTypeInfoManager::getInstance()->getPetTypeInfo(pItemInfo->getFunctionGrade());
						Assert( pPetTypeInfo != NULL );

						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
						gcAddItemToItemVerify.setParameter( pItemInfo->getFunctionGrade() );

						pGamePlayer->sendPacket( &gcAddItemToItemVerify );

						// Ŭ���̾�Ʈ�� �������� ������Ų��.
						GCDeleteInventoryItem gcDeleteInventoryItem;
						gcDeleteInventoryItem.setObjectID(pItem->getObjectID());
						pGamePlayer->sendPacket(&gcDeleteInventoryItem);

						// ���� ��ü������ �����ش�. 
						//nventory->deleteItem(pItem->getObjectID());
				//_TPOINT pt2;
						//CoordInven_t X2 = pt2.x;
						//CoordInven_t Y2 = pt2.y;
						pInventory->deleteItem(pItem->getObjectID());	
						cout << " ��⼭ ���� " << endl;
						// �����ϰ� �ƿ� ���ش�.
						//pItem->destroy();
						//pPetItem->whenPCLost(pPC);
						pItem->destroy();
						cout << " ��⼭ ����2 " << endl;
						//pPetItem->destroy();
						//SAFE_DELETE( pItem );
						//SAFE_DELETE( pPetItem );
						//SAFE_DELETE( pPetItem );
						cout << " ��⼭ ����2 " << endl;

						PetInfo* pPetInfo2 = new PetInfo;
						pPetInfo2->setPetType(pItemInfo->getFunctionGrade());
						pPetInfo2->setPetCreatureType( pPetTypeInfo->getPetCreatureType( pPetInfo->getPetLevel() ) );
						pPetInfo2->setPetLevel(pPetInfo->getPetLevel());
						pPetInfo2->setPetExp(pPetInfo->getPetExp());
						pPetInfo2->setPetHP(pPetInfo->getPetHP());
						pPetInfo2->setPetAttr(pPetInfo->getPetAttr());
						pPetInfo2->setPetAttrLevel(pPetInfo->getPetAttrLevel());
						pPetInfo2->setPetOption(pPetInfo->getPetOption());
						pPetInfo2->setPetVersionOption(pPetInfo->getPetVersionOption());
						pPetInfo2->setFoodType(pPetInfo->getFoodType());
						pPetInfo2->setGamble(pPetInfo->canGamble());
						pPetInfo2->setCutHead(pPetInfo->canCutHead());
						pPetInfo2->setAttack(pPetInfo->canAttack());
						pPetInfo2->setFeedTime( VSDateTime::currentDateTime() );
						pPetInfo2->setMagicRemainSec( pPetInfo->getMagicRemainSec() );
						pPetInfo2->setExpertPetChangerRemainSec( pPetInfo->getExpertPetChangerRemainSec());
						pPetInfo2->setEnchantSkillType( pPetInfo->getEnchantSkillType() );

						//list<OptionType_t> olist3;
						cout << " �ɼ� üũ " << endl;
						if(pMouseItem->getOptionTypeSize() != 0){

						cout << " �ɼ� ���� " << endl;

						list<OptionType_t> oList;

						list<OptionType_t> optionList2 = pMouseItem->getOptionTypeList();
						list<OptionType_t>::const_iterator itr2 = optionList2.begin();
						while(itr2 != optionList2.end())
						{
							oList.push_back(*itr2);
							itr2++;
						}
						pPetInfo2->setOptionType( oList );
						}else{
						cout << " �ɼ� üũ 2" << endl;
						pPetInfo2->setOptionType( pPetInfo->getOptionType() );
						}

						pPetInfo2->setMixOptionType( pPetInfo->getMixOptionType() );
						PetItem* pPetItem2 = dynamic_cast<PetItem*>(pItem2);
						if ( pPetItem2 != NULL )
						{
						pPetItem2->setPetInfo( pPetInfo2 );
						pPetInfo2->setPetItem( pPetItem2 );
						}

						pPC->deleteItemFromExtraInventorySlot();
						pMouseItem->destroy();
						SAFE_DELETE( pMouseItem );

	// �̺κ��� ���� �����ϴ� �����ۿ� ����Ѵ�.
						CoordInven_t X = pt.x;
						CoordInven_t Y = pt.y;

						pPC->getZone()->getObjectRegistry().registerObject( pItem2 );

						if(pInventory->addItem(invenX, invenY, pItem2))
						{
						pItem2->create( pPC->getName(), STORAGE_INVENTORY, 0, invenX, invenY );

	// Ŭ���̾�Ʈ�� ������ �߰��Ǿ����� �˸���.
						GCCreateItem gcCreateItem;
						makeGCCreateItem( &gcCreateItem, pItem2, invenX, invenY );
						pPlayer->sendPacket(&gcCreateItem);

						}
						if ( summonPet )
						{
							pPC->setPetInfo( pPetInfo2 );
							sendPetInfo( pGamePlayer );
						}

			//transportCreature(pCreature, pCreature->getZone()->getZoneID(), pCreature->getX(), pCreature->getY(), false);

					}
					break;
					case PetEnchantItemInfo::PET_RED_FUNCTION:
					{
						//cout << "�� ���� ��æƮ ���Դϴ�." << endl;
						if ( pPetInfo->getPetLevel() < 49 )
						{
							//cout << "������ �ȵ� �� ��æƮ���� ����" << endl;
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}

						pPC->deleteItemFromExtraInventorySlot();
						pMouseItem->destroy();
						SAFE_DELETE( pMouseItem );

						/*
						OptionType_t targetOption = rand()%87;
						targetOption++;
						*/

						OptionType_t targetOption = 0;
						int ratio = rand() % 100000;
						const list<PetEnchantOption*>& petEnchantOptions = g_pOptionInfoManager->getPetEnchantOptionList();
						list<PetEnchantOption*>::const_iterator itr = petEnchantOptions.begin();
						list<PetEnchantOption*>::const_iterator endItr = petEnchantOptions.end();

						for ( ; itr != endItr ; itr++ )
						{
							PetEnchantOption* pPetEnchantOption = *itr;
							if ( pPetEnchantOption->getRatio() > ratio )
							{
								targetOption = pPetEnchantOption->getOptionType();
								break;
							}
						}

						pPetInfo->setPetOption( targetOption );
						sendPetInfo( pGamePlayer );

							list<OptionType_t> olist;

							if ( pPetInfo->getPetOption() != 0 ) 
							olist.push_back(pPetInfo->getPetOption());

							if ( pPetInfo->getPetVersionOption() != 0 ) 
							olist.push_back(pPetInfo->getPetVersionOption());
			
							list<OptionType_t> optionList = pPetInfo->getOptionType();
							list<OptionType_t>::const_iterator itr3 = optionList.begin();

							while(itr3 != optionList.end())
							{
							olist.push_back(*itr3);
							itr3++;
							}

						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_THIRD_ENCHANT_OK );
						gcAddItemToItemVerify.setParameter( 0 );
						gcAddItemToItemVerify.setThirdOptionType( olist );
						pGamePlayer->sendPacket( &gcAddItemToItemVerify );

						char query[100];
						sprintf(query, "PetOption=%u", (uint)targetOption);
						pItem->tinysave(query);
					}
					break;
					case PetEnchantItemInfo::PET_ATTRCLEAR_FUNCTION :
					{
						if ( pPetInfo->getPetAttr() == 0xff )
						{
							//cout << "�̹� ��æƮ�� �������Դϴ�." << endl;
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}
						//cout << "ǥ�� ��æƮ �õ����Դϴ�." << endl;
						pPC->deleteItemFromExtraInventorySlot();
						pMouseItem->destroy();
						SAFE_DELETE( pMouseItem );

						if ( PetAttrInfoManager::Instance().enchantClearAttr( pPetInfo ) )
						{
							//cout << "��æƮ ����." << endl;
							pPetItem->savePetInfo();

							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
							gcAddItemToItemVerify.setParameter( ((uint)pPetInfo->getPetAttr())<<16 | (uint)pPetInfo->getPetAttrLevel() );

							pGamePlayer->sendPacket( &gcAddItemToItemVerify );

							if ( pPC->getPetInfo() == pPetInfo )
							{
								//cout << "�̹� ?ҷ??־�?��Ŷ ������ ���Դϴ�." << endl;
								sendPetInfo( pGamePlayer, true );
								pPC->initAllStatAndSend();
							}
							return;
						}
						else
						{
							//cout << "��æƮ ����" << endl;
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}
					}
					break;
					case PetEnchantItemInfo::PET_MAGIC_FUNCTION:
					{
						//cout << "��Ȱ �õ��� �Դϴ�."  << endl;
						if ( pPetInfo->getMagicRemainSec() != 0 )
						{
							//cout << "�� ���� �� ��Ȱ��Ű�� ����" << endl;
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}

						pPC->deleteItemFromExtraInventorySlot();
						pMouseItem->destroy();
						SAFE_DELETE( pMouseItem );

						VSDateTime current = VSDateTime::currentDateTime().addSecs(pItemInfo->getFunctionGrade());
						char query[100];
						sprintf(query, "MagicExpireTime='%s'", current.toDateTime().c_str());
						pItem->tinysave(query);

						pPetInfo->setMagicRemainSec( pItemInfo->getFunctionGrade() );
						pPetInfo->getPetItem()->savePetInfo();

						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
						gcAddItemToItemVerify.setParameter( pPetInfo->getMagicRemainSec() );

						pGamePlayer->sendPacket( &gcAddItemToItemVerify );
					}
					break;
					case PetEnchantItemInfo::PET_EXPERT_FUNCTION:
					{
						//cout << "��Ȱ �õ��� �Դϴ�."  << endl;
						if ( pPetInfo->getExpertPetChangerRemainSec() != 0 )
						{
							//cout << "�� ���� �� ��Ȱ��Ű�� ����" << endl;
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}

						pPC->deleteItemFromExtraInventorySlot();
						pMouseItem->destroy();
						SAFE_DELETE( pMouseItem );

						VSDateTime current = VSDateTime::currentDateTime().addSecs(pItemInfo->getFunctionGrade());
						char query[100];
						sprintf(query, "ExpertExpireTime='%s'", current.toDateTime().c_str());
						pItem->tinysave(query);

						pPetInfo->setExpertPetChangerRemainSec( pItemInfo->getFunctionGrade() );
						pPetInfo->getPetItem()->savePetInfo();

						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
						gcAddItemToItemVerify.setParameter( pPetInfo->getExpertPetChangerRemainSec() );

						pGamePlayer->sendPacket( &gcAddItemToItemVerify );
					}
					break;
					case PetEnchantItemInfo::PET_SHOCK_FUNCTION:
					{
						//cout << "��Ȱ �õ��� �Դϴ�."  << endl;
						if ( pPetInfo->getEnchantSkillType() != 0 )
						{
							//cout << "�� ���� �� ��Ȱ��Ű�� ����" << endl;
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}

						pPC->deleteItemFromExtraInventorySlot();
						pMouseItem->destroy();
						SAFE_DELETE( pMouseItem );

						char query[100];
						sprintf(query, "EnchantSkillType=%d", pItemInfo->getFunctionGrade());
						pItem->tinysave(query);

						pPetInfo->setEnchantSkillType( pItemInfo->getFunctionGrade() );
						pPetInfo->getPetItem()->savePetInfo();

						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
						gcAddItemToItemVerify.setParameter( pPetInfo->getEnchantSkillType() );

						pGamePlayer->sendPacket( &gcAddItemToItemVerify );
					}
					break;
					case PetEnchantItemInfo::PET_ICE_FUNCTION:
					{
						//cout << "��Ȱ �õ��� �Դϴ�."  << endl;
						if ( pPetInfo->getEnchantSkillType() == 0 )
						{
							//cout << "�� ���� �� ��Ȱ��Ű�� ����" << endl;
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}

						pPC->deleteItemFromExtraInventorySlot();
						pMouseItem->destroy();
						SAFE_DELETE( pMouseItem );

						char query[100];
						sprintf(query, "EnchantSkillType=%d", pItemInfo->getFunctionGrade());
						pItem->tinysave(query);

						pPetInfo->setEnchantSkillType( pItemInfo->getFunctionGrade() );
						pPetInfo->getPetItem()->savePetInfo();

						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
						gcAddItemToItemVerify.setParameter( pPetInfo->getEnchantSkillType() );

						pGamePlayer->sendPacket( &gcAddItemToItemVerify );
					}
					break;
					default:
					{
						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
						pGamePlayer->sendPacket( &gcAddItemToItemVerify );
						return;
					}
				}
			}
			break;
			case Item::ITEM_CLASS_MIXING_ITEM :
			{
				if ( pItem->getItemClass() != Item::ITEM_CLASS_PET_ITEM )
				{
					//cout << "�� �����ۿ��ٰ� �Ѱ� �ƴԴ�." << endl;
					GCAddItemToItemVerify gcAddItemToItemVerify;
					gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
					pGamePlayer->sendPacket( &gcAddItemToItemVerify );
					return;
				}

				MixingItemInfo* pItemInfo = dynamic_cast<MixingItemInfo*>(g_pMixingItemInfoManager->getItemInfo( pMouseItem->getItemType() ));
				Assert( pItemInfo != NULL );

				if ( pItemInfo->getType() != MixingItemInfo::TYPE_DETACH )
				{
					//cout << "�� �����ۿ��ٰ� �Ѱ� �ƴԴ�." << endl;
					GCAddItemToItemVerify gcAddItemToItemVerify;
					gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
					pGamePlayer->sendPacket( &gcAddItemToItemVerify );
					return;
				}

				PetItem* pPetItem = dynamic_cast<PetItem*>(pItem);
				PetInfo* pPetInfo = NULL;
				if ( pPetItem == NULL || ( pPetInfo = pPetItem->getPetInfo() ) == NULL || pPetInfo->getPetOption() == 0 )
				{
					//cout << "�� �������� �ƴϰų� �� �����ۿ� �� ���°� �����ϴ�." << endl;
					GCAddItemToItemVerify gcAddItemToItemVerify;
					gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
					pGamePlayer->sendPacket( &gcAddItemToItemVerify );
					return;
				}

				pPC->deleteItemFromExtraInventorySlot();
				pMouseItem->destroy();
				SAFE_DELETE( pMouseItem );

				pPetInfo->setPetOption(0);
				pPetItem->tinysave("PetOption=0");

				GCAddItemToItemVerify gcAddItemToItemVerify;
				gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
				gcAddItemToItemVerify.setParameter(0);

				pGamePlayer->sendPacket( &gcAddItemToItemVerify );

				if ( pPC->getPetInfo() == pPetInfo )
				{
					//cout << "�̹� �ҷ����־ ��Ŷ ������ ���Դϴ�." << endl;
					sendPetInfo( pGamePlayer, true );
					pPC->initAllStatAndSend();
				}
				return;
			}
			break;

			case Item::ITEM_CLASS_SLAYER_TUNING_ITEM :
			{
				ItemInfo* pItemInfo = g_pSlayerTuningItemInfoManager->getItemInfo( pMouseItem->getItemType() );
				Assert(pItemInfo!=NULL);

				SlayerTuningItemInfo* pSlayerTuningItemInfo = dynamic_cast<SlayerTuningItemInfo*>(pItemInfo);
				Assert(pSlayerTuningItemInfo != NULL);

					// ���� Ŭ������ �ƴϴ�. �׷��� ���� �޽����� ��������Ѵ�.
					if(pSlayerTuningItemInfo->getTunningItemClass() != pItem->getItemClass()){
						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE );
						pGamePlayer->sendPacket( &gcAddItemToItemVerify );
						return;
					}
					// ���� Ÿ���̸� �����޽����� ������� �Ѵ�.
					else if(pSlayerTuningItemInfo->getTunningItemType() == pItem->getItemType()){
						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE );
						pGamePlayer->sendPacket( &gcAddItemToItemVerify );
						return;
					}else{
						executeRedSunCore(pGamePlayer, pMouseItem, pItem);
					}
			} 
			break;

			case Item::ITEM_CLASS_VAMPIRE_TUNING_ITEM :
			{
				ItemInfo* pItemInfo = g_pVampireTuningItemInfoManager->getItemInfo( pMouseItem->getItemType() );
				Assert(pItemInfo!=NULL);

				VampireTuningItemInfo* pCreateItemInfo = dynamic_cast<VampireTuningItemInfo*>(pItemInfo);
				Assert(pCreateItemInfo != NULL);

					// ���� Ŭ������ �ƴϴ�. �׷��� ���� �޽����� ��������Ѵ�.
					if(pCreateItemInfo->getTunningItemClass() != pItem->getItemClass()){
						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE );
						pGamePlayer->sendPacket( &gcAddItemToItemVerify );
						return;
					}
					// ���� Ÿ���̸� �����޽����� ������� �Ѵ�.
					else if(pCreateItemInfo->getTunningItemType() == pItem->getItemType()){
						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE );
						pGamePlayer->sendPacket( &gcAddItemToItemVerify );
						return;
					}else{
						executeVampireTuningItem(pGamePlayer, pMouseItem, pItem);
					}
			} 
			break;

			case Item::ITEM_CLASS_OUSTERS_TUNING_ITEM :
			{
				ItemInfo* pItemInfo = g_pOustersTuningItemInfoManager->getItemInfo( pMouseItem->getItemType() );
				Assert(pItemInfo!=NULL);

				OustersTuningItemInfo* pCreateItemInfo = dynamic_cast<OustersTuningItemInfo*>(pItemInfo);
				Assert(pCreateItemInfo != NULL);

					// ���� Ŭ������ �ƴϴ�. �׷��� ���� �޽����� ��������Ѵ�.
					if(pCreateItemInfo->getTunningItemClass() != pItem->getItemClass()){
						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE );
						pGamePlayer->sendPacket( &gcAddItemToItemVerify );
						return;
					}
					// ���� Ÿ���̸� �����޽����� ������� �Ѵ�.
					else if(pCreateItemInfo->getTunningItemType() == pItem->getItemType()){
						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE );
						pGamePlayer->sendPacket( &gcAddItemToItemVerify );
						return;
					}else{
						executeOustersTuningItem(pGamePlayer, pMouseItem, pItem);
					}
			} 
			break;

			default:
			{
				//cout << "upgrade error" << endl;

				GCAddItemToItemVerify gcAddItemToItemVerify;
				gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
				pGamePlayer->sendPacket( &gcAddItemToItemVerify );
				return;
			}
		}
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}


#ifdef __GAME_SERVER__
	void executeUpGrade(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem)
		throw(Error)
	{
		__BEGIN_TRY

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);
		Inventory* 		pInventory  = pPC->getInventory();

		const ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( pItem->getItemClass(), pItem->getItemType() ); 

		EventStarInfo* pEventStarInfo = dynamic_cast<EventStarInfo*>(g_pItemInfoManager->getItemInfo(pMouseItem->getItemClass(), pMouseItem->getItemType()));
		Assert(pEventStarInfo!=NULL);

		int Ratio = Random(30,50);
		if(pItem->getGrade() == 1) { Ratio = 101; }
		Ratio += pEventStarInfo->getFunctionValue();
		int RandomRatio = Random(1,100);
		if ( pMouseItem->getNum() == 1 && pItem->getGrade() < 10 && RandomRatio < Ratio-pItem->getGrade() )
		{
		cout << " Ȯ�� : " <<  RandomRatio << "  / " << Ratio << endl;
			pItem->setGrade( pItem->getGrade() + 1 );
			char buffer[80];
			snprintf(buffer, 80, "Grade=%u", pItem->getGrade() );
			pItem->tinysave(buffer);

			pPC->deleteItemFromExtraInventorySlot();
			pMouseItem->destroy();
			SAFE_DELETE(pMouseItem);

			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_UP_GRADE_OK );
			gcAddItemToItemVerify.setParameter( pItem->getGrade() );

			pGamePlayer->sendPacket( &gcAddItemToItemVerify );
		}
		else
		{
		cout << " Ȯ�� : " <<  RandomRatio << "  / " << Ratio << endl;

			pItem->setGrade( pItem->getGrade() - 1 );
			char buffer[80];
			snprintf(buffer, 80, "Grade=%u", pItem->getGrade() );
			pItem->tinysave(buffer);

			pPC->deleteItemFromExtraInventorySlot();
			pMouseItem->destroy();
			SAFE_DELETE(pMouseItem);

			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_UP_GRADE_OK );
			gcAddItemToItemVerify.setParameter( pItem->getGrade() );

			pGamePlayer->sendPacket( &gcAddItemToItemVerify );
			return;
		}

		__END_CATCH
	}
	void executeTypeGrade(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem)
		throw(Error)
	{
		__BEGIN_TRY

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);
		Inventory* 		pInventory  = pPC->getInventory();

		const ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( pItem->getItemClass(), pItem->getItemType() ); 

		int Ratio = 20+pMouseItem->getHeroOption();
	if( pItemInfo->getNextItemType() != pItem->getItemType() && pItemInfo->getNextItemType() != 0){
		if ( pMouseItem->getNum() == 1 && pItem->getGrade() == 10 && rand()%100 < Ratio)
		{
			pItem->setItemType( pItemInfo->getNextItemType() );
			pItem->setGrade( 1 );
			char buffer[80];
			snprintf(buffer, 80, "ItemType=%u, Grade=%u", pItem->getItemType(),pItem->getGrade() );
			pItem->tinysave(buffer);

			pPC->deleteItemFromExtraInventorySlot();
			pMouseItem->destroy();
			SAFE_DELETE(pMouseItem);

			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
			gcAddItemToItemVerify.setParameter( 0 );

			pGamePlayer->sendPacket( &gcAddItemToItemVerify );

			// Ŭ���̾�Ʈ�� ���� ���� ������

			GCDeleteInventoryItem gcDeleteInventoryItem;
			gcDeleteInventoryItem.setObjectID(pItem->getObjectID());
			pGamePlayer->sendPacket(&gcDeleteInventoryItem);

						CoordInven_t X = -1, Y;
						pPC->getInventory()->findItemOID( pItem->getObjectID(), X, Y );
						Assert( X != -1 );

			GCCreateItem gcCreateItem;
			makeGCCreateItem( &gcCreateItem, pItem, X, Y );
			pGamePlayer->sendPacket(&gcCreateItem);
		}
		else
		{

			pPC->deleteItemFromExtraInventorySlot();
			pMouseItem->destroy();
			SAFE_DELETE(pMouseItem);

			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );
			return;
		}
	}else{
		GCAddItemToItemVerify gcAddItemToItemVerify;
		gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE );
		pGamePlayer->sendPacket( &gcAddItemToItemVerify );
	}
		__END_CATCH
	}
	void executeEnchantRareThreeOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY)
		throw (Error)
	{
		__BEGIN_TRY

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);
//		Inventory* 		pInventory  = pPC->getInventory();

		// ������ Ȯ���� itemType�� ���ؼ� �����ȴ�.
		const ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( 
													pItem->getItemClass(), 
													pItem->getItemType() );

		EventStarInfo* pEventStarInfo = dynamic_cast<EventStarInfo*>(g_pItemInfoManager->getItemInfo(pMouseItem->getItemClass(), pMouseItem->getItemType()));
		Assert(pEventStarInfo!=NULL);

		// ��æƮ �ҷ��� �������� ���� �ɼ��� 2���� �ƴϰų�
		// ����ũ �������� ���
		// Ȥ�� ���� 2�� �̻� ��� ��æƮ�Ҷ�� �� ��
		if (pItem->getOptionTypeSize()!=3
			|| pItemInfo->isUnique()
			|| pMouseItem->getNum() != 1
		)
		{
			//cout << "no Option " << endl;
			sendEnchantImpossible( pGamePlayer );
			return;
		}

		bool bFirstSucceed = false;
		uint optionChange = 0;
		uint optionChange2 = 0;
		int  shiftValue = 16;
		int  diceValue = 3500;

		list<OptionType_t> optionList = pItem->getOptionTypeList();
		list<OptionType_t>::const_iterator itr = optionList.begin();

		OptionType_t firstOption = *itr++;
		OptionType_t secondOption = *itr++;
		OptionType_t thirdOption  = *itr;

		OptionInfo* pFirstOptionInfo = getOptionInfo( firstOption );
		OptionInfo* pSecondOptionInfo = getOptionInfo( secondOption );
		OptionInfo* pThirdOptionInfo = getOptionInfo( thirdOption );

		//������Ʒ���Լ��
		if ( pFirstOptionInfo == NULL || pSecondOptionInfo == NULL || pThirdOptionInfo== NULL)
		{
			sendEnchantImpossible( pGamePlayer );
			return;
		}
		//����Ƿ��ǿ�������Ʒ
		bool bFirstUpgradePossible =  pFirstOptionInfo->isUpgradePossible();
		bool bSecondUpgradePossible = pSecondOptionInfo->isUpgradePossible();
		bool bThirdUpgradePossible =  pThirdOptionInfo->isUpgradePossible();
				cout << "��æƮ ���� 1" << endl;
		//���������������
		if ( !bFirstUpgradePossible && !bSecondUpgradePossible && !bThirdUpgradePossible)
		{
			sendEnchantImpossible( pGamePlayer );
			return;
		}
		//if ((rand() %6000) > diceValue)
			//diceValue*=2;
				cout << "��æƮ ���� 2" << endl;
		if ( bFirstUpgradePossible )
		{
				cout << "��æƮ ���� 3/" << (int)firstOption << endl;
			// ù��° �ɼ��� ��æƮ Ȯ���� ����� 2�� Ȯ���� ������.
			int succeedRatio = pFirstOptionInfo->getUpgradeSecondRatio() * ( pItemInfo->getUpgradeRatio() +( rand() %50) );
				cout << "��æƮ ���� 3.1/" << (int)thirdOption  << endl;
			succeedRatio += pEventStarInfo->getFunctionValue()*100;
			//int dice = rand()%10000;
			int dice = rand() % diceValue;
			cout << "dice : " << (int)dice <<  endl;
			cout << "diceValue : " << (int)diceValue <<  endl;

			//cout << "ù��° �ɼ� : " << pFirstOptionInfo->getHName() << " ��æƮ Ȯ�� " << succeedRatio << endl;
			//dice =succeedRatio-1;
			if ( dice < succeedRatio ) //���ͨ����������װ��
			{
				cout << "��æƮ ����" << endl;
				processUpgradeOptionType( pItem, firstOption, pFirstOptionInfo );

				OptionType_t upgradeOptionType = pFirstOptionInfo->getUpgradeType();
				optionChange = (firstOption << (shiftValue+8)) | (upgradeOptionType << shiftValue);

				bFirstSucceed = true;
				goto EnOK;
			}
			else
			{
				if (pFirstOptionInfo->getUpgradeSecondRatio() < 5)
				{
					int noChangeRatio = 33;
					int downgradeRatio = 46;
					dice = rand() % 100;

					cout << "downgradeRatio" << pItemInfo->getName() << " �ɼǶ����� Ȯ�� " << downgradeRatio << endl;

					if ( dice < noChangeRatio )
					{
						// ��ȭ����
					}
					else if ( dice < noChangeRatio + downgradeRatio )
					{
						// �ɼǶ�����
						downgradeOptionType( pItem, firstOption, pFirstOptionInfo );

						OptionType_t previousOptionType = pFirstOptionInfo->getPreviousType();
						optionChange = (firstOption << (shiftValue+8)) | (previousOptionType << shiftValue);
					}
				}
			}
		}
		shiftValue -= 16;

		if ( bSecondUpgradePossible )
		{
				cout << "��æƮ ���� 4/" << (int)secondOption << endl;
			// ��?��?�ɼ��� ��æƮ Ȯ���� ù��° �ɼ��� �������ο� ������.

			int succeedRatio= g_pOptionInfoManager->getRareUpgradeRatio( secondOption, bFirstSucceed ) * ( pItemInfo->getUpgradeRatio() +( rand() %50) );
				cout << "��æƮ ���� 4.1/" << (int)thirdOption  << endl;
			succeedRatio += pEventStarInfo->getFunctionValue()*100;
			//int dice = rand() %10000;
			int dice = rand() % diceValue;

			//cout << "�ι�° �ɼ� : " << pSecondOptionInfo->getHName() << " ��æƮ Ȯ�� " << succeedRatio << endl;
			//dice =succeedRatio-1;
			if ( dice < succeedRatio )
			{
				cout << "��æƮ ����" << endl;
				processUpgradeOptionType( pItem, secondOption, pSecondOptionInfo );

				OptionType_t upgradeOptionType = pSecondOptionInfo->getUpgradeType();
				optionChange |= (secondOption << (shiftValue+8)) | (upgradeOptionType << shiftValue);

				bFirstSucceed = true;
				goto EnOK;
			}
			else
			{
				if (pSecondOptionInfo->getUpgradeSecondRatio() < 5)
				{
					int noChangeRatio = 33;
					int downgradeRatio = 46;
					dice = rand() % 100;

					cout << "downgradeRatio" << pItemInfo->getName() << " �ɼǶ����� Ȯ�� " << downgradeRatio << endl;

					if ( dice < noChangeRatio )
					{
						// ��ȭ����
					}
					else if ( dice < noChangeRatio + downgradeRatio )
					{
						// �ɼǶ�����
						downgradeOptionType( pItem, secondOption, pSecondOptionInfo );

						OptionType_t previousOptionType = pSecondOptionInfo->getPreviousType();
						optionChange = (secondOption << (shiftValue+8)) | (previousOptionType << shiftValue);
					}
				}
			}
		}
		shiftValue=0;
		if ( bThirdUpgradePossible )
		{
				cout << "��æƮ ���� 5/" << (int)thirdOption  << endl;
			// �ι�° �ɼ��� ��æƮ Ȯ���� ù��° �ɼ��� �������ο� ������.
			int succeedRatio = g_pOptionInfoManager->getRareUpgradeRatio( thirdOption, bFirstSucceed ) * ( pItemInfo->getUpgradeRatio() +( rand() %50) );
				cout << "��æƮ ���� 5.1/" << (int)thirdOption  << endl;
			succeedRatio += pEventStarInfo->getFunctionValue()*100;
			//int dice = rand() %10000;

			int dice = rand() % diceValue;
			//cout << "�ι�° �ɼ� : " << pSecondOptionInfo->getHName() << " ��æƮ Ȯ�� " << succeedRatio << endl;
			//dice =succeedRatio-1;
			if ( dice < succeedRatio )
			{
				cout << "��æƮ ����" << endl;
				processUpgradeOptionType( pItem, thirdOption, pThirdOptionInfo );

				OptionType_t upgradeOptionType = pThirdOptionInfo->getUpgradeType();
				optionChange2 |= (thirdOption << (shiftValue+8)) | (upgradeOptionType << shiftValue);

				bFirstSucceed = true;
			}
			else
			{
				if (pThirdOptionInfo->getUpgradeSecondRatio() < 5)
				{
					int noChangeRatio = 33;
					int downgradeRatio = 46;
					dice = rand() % 100;

					cout << "downgradeRatio" << pItemInfo->getName() << " �ɼǶ����� Ȯ�� " << downgradeRatio << endl;

					if ( dice < noChangeRatio )
					{
						// ��ȭ����
					}
					else if ( dice < noChangeRatio + downgradeRatio )
					{
						// �ɼǶ�����
						downgradeOptionType( pItem, thirdOption, pThirdOptionInfo );

						OptionType_t previousOptionType = pThirdOptionInfo->getPreviousType();
						optionChange2 |= (thirdOption << (shiftValue+8)) | (previousOptionType << shiftValue);
					}
				}
			}
		}
EnOK:
				cout << "��æƮ ���� 5" << endl;
		//{
			// ��� �ִ� �� ����
			pPC->deleteItemFromExtraInventorySlot();

			// DB���� ����
			pMouseItem->destroy();

			// �޸𸮿��� ����
			SAFE_DELETE(pMouseItem);

			// ��� ��Ŷ ������
			cout << "optionChange : " << optionChange <<  endl;
		
			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_THIRD_ENCHANT_OK );
			gcAddItemToItemVerify.setParameter( 0 );
			gcAddItemToItemVerify.setThirdOptionType( pItem->getOptionTypeList() );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );

		//}

		__END_CATCH
	}
	void executeEnchantRareOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY)
		throw (Error)
	{
		__BEGIN_TRY

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);
//		Inventory* 		pInventory  = pPC->getInventory();

		// ������ Ȯ���� itemType�� ���ؼ� �����ȴ�.
		const ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( 
													pItem->getItemClass(), 
													pItem->getItemType() );
				EventStarInfo* pEventStarInfo = dynamic_cast<EventStarInfo*>(g_pItemInfoManager->getItemInfo(pMouseItem->getItemClass(), pMouseItem->getItemType()));
				Assert(pEventStarInfo!=NULL);

		// ��æƮ �ҷ��� �������� ���� �ɼ��� 2���� �ƴϰų�
		// ����ũ �������� ���
		// Ȥ�� ���� 2�� �̻� ��� ��æƮ�Ҷ�� �� ��
/*		// add by Coffee 2006.11.2  �ж��Ƿ�Ϊ��������Ʒ������Ǿ͵����¼ӵĳ������Ժ���
		if (pItem->getOptionTypeSize() ==3);
		{
			//��������װ��
			executeEnchantRareThreeOption(pGamePlayer, pMouseItem, pItem, invenX, invenY);
			return;
		}
		// end */
		if (pItem->getOptionTypeSize()!=2
			|| pItemInfo->isUnique()
			|| pMouseItem->getNum() != 1
		)
		{
			cout << "no Option 1" << endl;
			sendEnchantImpossible( pGamePlayer );
			return;
		}

		bool bFirstSucceed = false;
		uint optionChange = 0;
		int  shiftValue = 16;

		list<OptionType_t> optionList = pItem->getOptionTypeList();
		list<OptionType_t>::const_iterator itr = optionList.begin();

		OptionType_t firstOption = *itr++;
		OptionType_t secondOption = *itr;

		OptionInfo* pFirstOptionInfo = getOptionInfo( firstOption );
		OptionInfo* pSecondOptionInfo = getOptionInfo( secondOption );

		if ( pFirstOptionInfo == NULL || pSecondOptionInfo == NULL )
		{
			cout << "no Option 2" << endl;
			sendEnchantImpossible( pGamePlayer );
			return;
		}

		bool bFirstUpgradePossible = pFirstOptionInfo->isUpgradePossible();
		bool bSecondUpgradePossible = pSecondOptionInfo->isUpgradePossible();

		if ( !bFirstUpgradePossible && !bSecondUpgradePossible )
		{
			cout << "no Option 3" << endl;
			sendEnchantImpossible( pGamePlayer );
			return;
		}

		if ( bFirstUpgradePossible )
		{
			// ù��° �ɼ��� ��æƮ Ȯ���� ����� 2�� Ȯ���� ������.
			int succeedRatio = pFirstOptionInfo->getUpgradeSecondRatio() * pItemInfo->getUpgradeRatio();
			succeedRatio += pEventStarInfo->getFunctionValue()*100;
			int dice = rand()%10000;

			//cout << "ù��° ?ɼ?: " << pFirstOptionInfo->getHName() << " ��æƮ Ȯ�� " << succeedRatio << endl;

			if ( dice < succeedRatio )
			{
				//cout << "��æƮ ����" << endl;
				processUpgradeOptionType( pItem, firstOption, pFirstOptionInfo );

				OptionType_t upgradeOptionType = pFirstOptionInfo->getUpgradeType();
				optionChange = (firstOption << (shiftValue+8)) | (upgradeOptionType << shiftValue);

				bFirstSucceed = true;
			}
			else
			{
				int noChangeRatio = 33;
				int downgradeRatio = pItemInfo->getDowngradeRatio();
				dice = rand() % 100;

				//cout << "��æƮ ���� : " << pItemInfo->getName() << " �ɼǶ����� Ȯ�� " << downgradeRatio << endl;

				if ( dice < noChangeRatio )
				{
					// ��ȭ����
				}
				else if ( dice < noChangeRatio + downgradeRatio )
				{
					// �ɼǶ�����
					downgradeOptionType( pItem, firstOption, pFirstOptionInfo );

					OptionType_t previousOptionType = pFirstOptionInfo->getPreviousType();
					optionChange = (firstOption << (shiftValue+8)) | (previousOptionType << shiftValue);
				}
				else
				{
					// �ɼǾ�����
					pItem->removeOptionType( firstOption );
					optionChange = (firstOption << (shiftValue+8));

					// DB����
					string optionField;
					setOptionTypeToField( pItem->getOptionTypeList(), optionField );

					char pField[80];
					sprintf(pField, "OptionType='%s'", optionField.c_str());
					pItem->tinysave(pField);
				}
			}
		}
		else
		{
			OptionType_t prev = pFirstOptionInfo->getPreviousType();

			if ( prev != 0 )
			{
				//�ɼǶ����� Ȯ�� ����ؾ� �ȴ�.

				int noChangeRatio = 33;
				int downgradeRatio = pItemInfo->getDowngradeRatio();
				int dice = rand() % 100;

				//cout << "ù��° �ɼ� : " << pFirstOptionInfo->getHName() << " �� ������ Ȯ�� : " << downgradeRatio << endl;

				if ( dice < noChangeRatio )
				{
					// ��ȭ����
				}
				else if ( dice < noChangeRatio + downgradeRatio )
				{
					// �ɼǶ�����
					downgradeOptionType( pItem, firstOption, pFirstOptionInfo );

					OptionType_t previousOptionType = pFirstOptionInfo->getPreviousType();
					optionChange = (firstOption << (shiftValue+8)) | (previousOptionType << shiftValue);
				}
				else
				{
					// �ɼǾ�����
					pItem->removeOptionType( firstOption );
					optionChange = (firstOption << (shiftValue+8));

					// DB����
					string optionField;
					setOptionTypeToField( pItem->getOptionTypeList(), optionField );

					char pField[80];
					sprintf(pField, "OptionType='%s'", optionField.c_str());
					pItem->tinysave(pField);

				}
			}
		}

		shiftValue -= 16;

		if ( bSecondUpgradePossible )
		{
			// �ι�° �ɼ��� ��æƮ ??��?ù��° �ɼ��� �������ο� ������.
			int succeedRatio = g_pOptionInfoManager->getRareUpgradeRatio( secondOption, bFirstSucceed ) * pItemInfo->getUpgradeRatio();
			succeedRatio += pEventStarInfo->getFunctionValue()*100;
			int dice = rand() %10000;

			//cout << "�ι�° �ɼ� : " << pSecondOptionInfo->getHName() << " ��æƮ Ȯ�� " << succeedRatio << endl;

			if ( dice < succeedRatio )
			{
				//cout << "��æƮ ����" << endl;
				processUpgradeOptionType( pItem, secondOption, pSecondOptionInfo );

				OptionType_t upgradeOptionType = pSecondOptionInfo->getUpgradeType();
				optionChange |= (secondOption << (shiftValue+8)) | (upgradeOptionType << shiftValue);

				bFirstSucceed = true;
			}
			else
			{
				int noChangeRatio = 33;
				int downgradeRatio = pItemInfo->getDowngradeRatio();
				dice = rand() % 100;

				//cout << "��æƮ ���� : " << pItemInfo->getName() << " �ɼǶ����� Ȯ�� " << downgradeRatio << endl;

				if ( dice < noChangeRatio )
				{
					// ��ȭ����
				}
				else if ( dice < noChangeRatio + downgradeRatio )
				{
					// �ɼǶ�����
					downgradeOptionType( pItem, secondOption, pSecondOptionInfo );

					OptionType_t previousOptionType = pSecondOptionInfo->getPreviousType();
					optionChange |= (secondOption << (shiftValue+8)) | (previousOptionType << shiftValue);
				}
				else
				{
					// �ɼǾ�����
					pItem->removeOptionType( secondOption );
					optionChange |= (secondOption << (shiftValue+8));

					// DB����
					string optionField;
					setOptionTypeToField( pItem->getOptionTypeList(), optionField );

					char pField[80];
					sprintf(pField, "OptionType='%s'", optionField.c_str());
					pItem->tinysave(pField);
				}
			}
		}
		else
		{
			OptionType_t prev = pSecondOptionInfo->getPreviousType();

			if ( prev != 0 )
			{
				//�ɼǶ����� Ȯ�� ����ؾ� �ȴ�.
				int noChangeRatio = 33;
				int downgradeRatio = pItemInfo->getDowngradeRatio();
				int dice = rand() % 100;

				//cout << "�ι�° �ɼ� : " << pSecondOptionInfo->getHName() << " �� ������ Ȯ�� : " << downgradeRatio << endl;

				if ( dice < noChangeRatio )
				{
					// ��ȭ����
				}
				else if ( dice < noChangeRatio + downgradeRatio )
				{
					// �ɼǶ�����
					downgradeOptionType( pItem, secondOption, pSecondOptionInfo );

					OptionType_t previousOptionType = pSecondOptionInfo->getPreviousType();
					optionChange |= (secondOption << (shiftValue+8)) | (previousOptionType << shiftValue);
				}
				else
				{
					// �ɼǾ�����
					pItem->removeOptionType( secondOption );
					optionChange |= (secondOption << (shiftValue+8));

					// DB����
					string optionField;
					setOptionTypeToField( pItem->getOptionTypeList(), optionField );

					char pField[80];
					sprintf(pField, "OptionType='%s'", optionField.c_str());
					pItem->tinysave(pField);
				}
			}
		}

/*		// �ɼ��� �������� ���� �Ұ��������� �ʴٰ� ����..
		// ��� �ִ� �������� �´��� Ȯ���ϰ�
		// upgrade������ option�� ��쿡...


		//const list<OptionType_t>& optionList = pItem->getOptionTypeList();
		// �����ؼ� ����.. 
		list<OptionType_t>::const_iterator itr = optionList.begin();

		for (; itr!=optionList.end(); itr++)
		{
			OptionType_t currentOptionType = *itr;

			OptionInfo* pOptionInfo = getOptionInfo( currentOptionType );

			if (pOptionInfo==NULL)
			{
				sendEnchantImpossible( pGamePlayer );
				return;
			}

			bool bUpgradePossible = pOptionInfo->isUpgradePossible();

			if (bUpgradePossible)
			{
				//---------------------------------------------------------
				// item������ 1���� ��츸 �� �� �ֵ��� �صд�.
				// �������� ��쵵 �����ϰ� �Ϸ���
				// ������ ������ �ٿ��߰���.. client�� �����ؾ� �Ѵ�.
				// upgrade �����ұ�?
				//---------------------------------------------------------
				// �ɼ�Ȯ�� * Ÿ��Ȯ�� / 10000
				//---------------------------------------------------------
				// ù��° �ɼ�
				//---------------------------------------------------------
	
				// ù��° �ɼ��� �����ϸ� �ι�° �ɼ�Ȯ���� ����Ѵ�.
				int upgradeRatio = (bFirstSucceed? pOptionInfo->getUpgradeSecondRatio() 
												: pOptionInfo->getUpgradeRatio());


				int succeedRatio = upgradeRatio * pItemInfo->getUpgradeRatio();
				
				int dice = rand()%10000;
				bool bSucceed = (dice < succeedRatio);

				//cout << "EnchantCheck = " 
				//	<< pOptionInfo->getUpgradeRatio() << " * "
				//	<< pItemInfo->getUpgradeRatio() << " = "
				//	<< succeedRatio << ", dice = " << dice << " , succeed=" << (int)bSucceed << endl;

				//cout << "Before = " << getOptionTypeToString( pItem->getOptionTypeList() ) << endl;
				//cout << "CurrentOptionType = " << (int)currentOptionType << endl;


				if (pMouseItem->getNum()==1
					&& bSucceed)
				{
					processUpgradeOptionType( pItem, currentOptionType, pOptionInfo );

					OptionType_t upgradeOptionType = pOptionInfo->getUpgradeType();
					optionChange = (currentOptionType << (shiftValue+8)) | (upgradeOptionType << shiftValue);

					bFirstSucceed = true;
					//cout << gcAddItemToItemVerify.toString().c_str() << endl;
				}
				//---------------------------------------------------------
				// upgrade ����
				//---------------------------------------------------------
				else
				{
					//cout << "Failed!" << endl;
					bool bCrashItem = pItemInfo->isUpgradeCrash();

					if ( bCrashItem )
					{
						// ������ �μ��� ���� ItemTrace Log ������ ��.��; 
						if ( pItem != NULL && pItem->isTraceItem() )
						{
							remainTraceLog( pItem, pCreature->getName(), "GOD", ITEM_LOG_DELETE, DETAIL_ENCHANT);
						}
						crashItem(pItem, pInventory, invenX, invenY);

						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_CRASH );
						pGamePlayer->sendPacket( &gcAddItemToItemVerify );

						return;
					}
					else
					{
						// ������ list�� reference�� ���� ���⿡??�ɼ��� ���ŵ� �� �����Ƿ�
						// list iterator�� ����~�ɼ��� �ִ�.
						downgradeOptionType( pItem, currentOptionType, pOptionInfo );

						OptionType_t previousOptionType = pOptionInfo->getPreviousType();
						optionChange = (currentOptionType << (shiftValue+8)) | (previousOptionType << shiftValue);
					}
				}
			}
			else
			{
				impossibleCount ++;
			}

			shiftValue -= 16;
		}*/

		{
			// ��� �ִ� �� ����
			pPC->deleteItemFromExtraInventorySlot();

			// DB���� ����
			pMouseItem->destroy();

			// �޸𸮿��� ����
			SAFE_DELETE(pMouseItem);

			// ��� ��Ŷ ������
			sendEnchantOK(pGamePlayer, optionChange);
		}

		__END_CATCH
	}

	void executeEnchantSetRareOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY)
		throw (Error)
	{
		__BEGIN_TRY

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);
//		Inventory* 		pInventory  = pPC->getInventory();

		// ������ Ȯ���� itemType�� ���ؼ� �����ȴ�.
		const ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( 
													pItem->getItemClass(), 
													pItem->getItemType() );

		// ��æƮ �ҷ��� �������� ���� �ɼ��� 2���� �ƴϰų�
		// ����ũ �������� ���
		// Ȥ�� ���� 2�� �̻� ��� ��æƮ�Ҷ�� �� ��
		if (pItem->getOptionTypeSize2()!=2
			|| pItemInfo->isUnique()
			|| pMouseItem->getNum() != 1
		)
		{
			cout << "no Option 1" << endl;
			sendEnchantImpossible( pGamePlayer );
			return;
		}

		bool bFirstSucceed = false;
		uint optionChange = 0;
		int  shiftValue = 16;

		list<OptionType_t> optionList = pItem->getOptionTypeList2();
		list<OptionType_t>::const_iterator itr = optionList.begin();

		OptionType_t firstOption = *itr++;
		OptionType_t secondOption = *itr;

		OptionInfo* pFirstOptionInfo = getOptionInfo( firstOption );
		OptionInfo* pSecondOptionInfo = getOptionInfo( secondOption );

		if ( pFirstOptionInfo == NULL || pSecondOptionInfo == NULL )
		{
			cout << "no Option 2" << endl;
			sendEnchantImpossible( pGamePlayer );
			return;
		}

		bool bFirstUpgradePossible = pFirstOptionInfo->isUpgradePossible();
		bool bSecondUpgradePossible = pSecondOptionInfo->isUpgradePossible();

		if ( !bFirstUpgradePossible && !bSecondUpgradePossible )
		{
			cout << "no Option 3" << endl;
			sendEnchantImpossible( pGamePlayer );
			return;
		}

		if ( bFirstUpgradePossible )
		{
			// ù��° �ɼ��� ��æƮ Ȯ���� ����� 2??Ȯ���� ������.
			int succeedRatio = pFirstOptionInfo->getUpgradeSecondRatio() * pItemInfo->getUpgradeRatio();
			//succeedRatio += pMouseItem->getHeroOption()*100;
			int dice = rand()%10000;

			//cout << "ù��° �ɼ� : " << pFirstOptionInfo->getHName() << " ��æƮ Ȯ�� " << succeedRatio << endl;

			if ( dice < succeedRatio )
			{
				//cout << "��æƮ ����" << endl;
				processUpgradeSetOptionType( pItem, firstOption, pFirstOptionInfo );

				OptionType_t upgradeOptionType = pFirstOptionInfo->getUpgradeType();
				optionChange = (firstOption << (shiftValue+8)) | (upgradeOptionType << shiftValue);

				bFirstSucceed = true;
			}
			else
			{
				int noChangeRatio = 33;
				int downgradeRatio = pItemInfo->getDowngradeRatio();
				dice = rand() % 100;

				//cout << "��æƮ ���� : " << pItemInfo->getName() << " �ɼǶ����� Ȯ�� " << downgradeRatio << endl;

				if ( dice < noChangeRatio )
				{
					// ��ȭ����
				}
				else if ( dice < noChangeRatio + downgradeRatio )
				{
					// �ɼǶ�����
					downgradeSetOptionType( pItem, firstOption, pFirstOptionInfo );

					OptionType_t previousOptionType = pFirstOptionInfo->getPreviousType();
					optionChange = (firstOption << (shiftValue+8)) | (previousOptionType << shiftValue);
				}
				else
				{
					// �ɼǾ�����
					pItem->removeOptionType2( firstOption );
					optionChange = (firstOption << (shiftValue+8));

					// DB����
					string optionField;
					setOptionTypeToField( pItem->getOptionTypeList2(), optionField );

					char pField[80];
					sprintf(pField, "OptionType2='%s'", optionField.c_str());
					pItem->tinysave(pField);
				}
			}
		}
		else
		{
			OptionType_t prev = pFirstOptionInfo->getPreviousType();

			if ( prev != 0 )
			{
				//�ɼǶ����� Ȯ�� ����ؾ� �ȴ�.

				int noChangeRatio = 33;
				int downgradeRatio = pItemInfo->getDowngradeRatio();
				int dice = rand() % 100;

				//cout << "ù��° �ɼ� : " << pFirstOptionInfo->getHName() << " �� ������ Ȯ�� : " << downgradeRatio << endl;

				if ( dice < noChangeRatio )
				{
					// ��ȭ����
				}
				else if ( dice < noChangeRatio + downgradeRatio )
				{
					// �ɼǶ�����
					downgradeSetOptionType( pItem, firstOption, pFirstOptionInfo );

					OptionType_t previousOptionType = pFirstOptionInfo->getPreviousType();
					optionChange = (firstOption << (shiftValue+8)) | (previousOptionType << shiftValue);
				}
				else
				{
					// �ɼǾ�����
					pItem->removeOptionType2( firstOption );
					optionChange = (firstOption << (shiftValue+8));

					// DB����
					string optionField;
					setOptionTypeToField( pItem->getOptionTypeList2(), optionField );

					char pField[80];
					sprintf(pField, "OptionType2='%s'", optionField.c_str());
					pItem->tinysave(pField);

				}
			}
		}

		shiftValue -= 16;

		if ( bSecondUpgradePossible )
		{
			// �ι�° �ɼ�??��æƮ Ȯ���� ù��° �ɼ��� ������?ο?������.
			int succeedRatio = g_pOptionInfoManager->getRareUpgradeRatio( secondOption, bFirstSucceed ) * pItemInfo->getUpgradeRatio();
			//succeedRatio += pMouseItem->getHeroOption()*100;
			int dice = rand() %10000;

			//cout << "�ι�° �ɼ� : " << pSecondOptionInfo->getHName() << " ��æƮ Ȯ�� " << succeedRatio << endl;

			if ( dice < succeedRatio )
			{
				//cout << "��æƮ ����" << endl;
				processUpgradeSetOptionType( pItem, secondOption, pSecondOptionInfo );

				OptionType_t upgradeOptionType = pSecondOptionInfo->getUpgradeType();
				optionChange |= (secondOption << (shiftValue+8)) | (upgradeOptionType << shiftValue);

				bFirstSucceed = true;
			}
			else
			{
				int noChangeRatio = 33;
				int downgradeRatio = pItemInfo->getDowngradeRatio();
				dice = rand() % 100;

				//cout << "��æƮ ���� : " << pItemInfo->getName() << " �ɼǶ����� Ȯ�� " << downgradeRatio << endl;

				if ( dice < noChangeRatio )
				{
					// ��ȭ����
				}
				else if ( dice < noChangeRatio + downgradeRatio )
				{
					// �ɼǶ�����
					downgradeOptionType( pItem, secondOption, pSecondOptionInfo );

					OptionType_t previousOptionType = pSecondOptionInfo->getPreviousType();
					optionChange |= (secondOption << (shiftValue+8)) | (previousOptionType << shiftValue);
				}
				else
				{
					// �ɼǾ�����
					pItem->removeOptionType2( secondOption );
					optionChange |= (secondOption << (shiftValue+8));

					// DB����
					string optionField;
					setOptionTypeToField( pItem->getOptionTypeList2(), optionField );

					char pField[80];
					sprintf(pField, "OptionType2='%s'", optionField.c_str());
					pItem->tinysave(pField);
				}
			}
		}
		else
		{
			OptionType_t prev = pSecondOptionInfo->getPreviousType();

			if ( prev != 0 )
			{
				//�ɼǶ����� Ȯ�� ����ؾ� �ȴ�.
				int noChangeRatio = 33;
				int downgradeRatio = pItemInfo->getDowngradeRatio();
				int dice = rand() % 100;

				//cout << "�ι�° �ɼ� : " << pSecondOptionInfo->getHName() << " �� ������ Ȯ�� : " << downgradeRatio << endl;

				if ( dice < noChangeRatio )
				{
					// ��ȭ����
				}
				else if ( dice < noChangeRatio + downgradeRatio )
				{
					// �ɼǶ�����
					downgradeSetOptionType( pItem, secondOption, pSecondOptionInfo );

					OptionType_t previousOptionType = pSecondOptionInfo->getPreviousType();
					optionChange |= (secondOption << (shiftValue+8)) | (previousOptionType << shiftValue);
				}
				else
				{
					// �ɼǾ�����
					pItem->removeOptionType2( secondOption );
					optionChange |= (secondOption << (shiftValue+8));

					// DB����
					string optionField;
					setOptionTypeToField( pItem->getOptionTypeList2(), optionField );

					char pField[80];
					sprintf(pField, "OptionType2='%s'", optionField.c_str());
					pItem->tinysave(pField);
				}
			}
		}

		{
			// ��� �ִ� �� ����
			pPC->deleteItemFromExtraInventorySlot();

			// DB���� ����
			pMouseItem->destroy();

			// �޸𸮿��� ����
			SAFE_DELETE(pMouseItem);

			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_THIRD_ENCHANT_OK );
			gcAddItemToItemVerify.setParameter( 0 );
			gcAddItemToItemVerify.setThirdOptionType( pItem->getOptionTypeList2() );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );

			// ��� ��Ŷ ������
			//sendSetEnchantOK(pGamePlayer, optionChange);
		}

		__END_CATCH
	}

	void executeEnchantSetThreeOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY)
		throw (Error)
	{
		__BEGIN_TRY

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);
//		Inventory* 		pInventory  = pPC->getInventory();

		// ������ Ȯ���� itemType�� ���ؼ� �����ȴ�.
		const ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( 
													pItem->getItemClass(), 
													pItem->getItemType() );

				EventStarInfo* pEventStarInfo = dynamic_cast<EventStarInfo*>(g_pItemInfoManager->getItemInfo(pMouseItem->getItemClass(), pMouseItem->getItemType()));
				Assert(pEventStarInfo!=NULL);


		// ��æƮ ��?��?�������� ���� �ɼ��� 2���� �ƴϰų�
		// ����ũ �������� ���
		// Ȥ�� ���� 2�� �̻� ��� ��æƮ�Ҷ�� �� ��
		if (pItem->getOptionTypeSize2()!=3
			|| pItemInfo->isUnique()
			|| pMouseItem->getNum() != 1
		)
		{
			cout << "no Option 1" << endl;
			sendEnchantImpossible( pGamePlayer );
			return;
		}

		bool bFirstSucceed = false;
		uint optionChange = 0;
		int  shiftValue = 16;

		list<OptionType_t> optionList = pItem->getOptionTypeList2();
		list<OptionType_t>::const_iterator itr = optionList.begin();

		OptionType_t thirdOption  = *itr;
		itr++;
		OptionType_t secondOption = *itr;
		itr++;
		OptionType_t firstOption  = *itr;
		itr--;
		itr--;

	/*	OptionType_t firstOption = *itr++;
		OptionType_t secondOption = *itr;
	*/

		OptionInfo* pFirstOptionInfo = getOptionInfo( firstOption );
		OptionInfo* pSecondOptionInfo = getOptionInfo( secondOption );
		OptionInfo* pThreeOptionInfo = getOptionInfo( thirdOption );
		if ( pFirstOptionInfo == NULL || pSecondOptionInfo == NULL || pThreeOptionInfo == NULL)
		{
			cout << "no Option 2" << endl;
			sendEnchantImpossible( pGamePlayer );
			return;
		}

		bool bFirstUpgradePossible = pFirstOptionInfo->isUpgradePossible();
		bool bSecondUpgradePossible = pSecondOptionInfo->isUpgradePossible();
		bool bThreeUpgradePossible = pThreeOptionInfo->isUpgradePossible();

		if ( !bFirstUpgradePossible && !bSecondUpgradePossible && !bThreeUpgradePossible )
		{
			cout << "no Option 3" << endl;
			sendEnchantImpossible( pGamePlayer );
			return;
		}

		if ( bFirstUpgradePossible )
		{
			// ù��° �ɼ��� ��æƮ Ȯ���� ����� 2�� Ȯ���� ������.
			int succeedRatio = pFirstOptionInfo->getUpgradeSecondRatio() * pItemInfo->getUpgradeRatio();
			succeedRatio += pEventStarInfo->getFunctionValue()*100;
			int dice = rand()%10000;

			//cout << "ù��° �ɼ� : " << pFirstOptionInfo->getHName() << " ��æƮ Ȯ�� " << succeedRatio << endl;

			if ( dice < succeedRatio )
			{
				//cout << "��æƮ ����" << endl;
				processUpgradeSetOptionType( pItem, firstOption, pFirstOptionInfo );

				OptionType_t upgradeOptionType = pFirstOptionInfo->getUpgradeType();
				optionChange = (firstOption << (shiftValue+8)) | (upgradeOptionType << shiftValue);

				bFirstSucceed = true;
			}
			else
			{
				int noChangeRatio = 33;
				int downgradeRatio = pItemInfo->getDowngradeRatio();
				dice = rand() % 100;

				//cout << "��æƮ ���� : " << pItemInfo->getName() << " �ɼǶ����� Ȯ�� " << downgradeRatio << endl;

				if ( dice < noChangeRatio )
				{
					// ��ȭ����
				}
				else if ( dice < noChangeRatio + downgradeRatio || pMouseItem->getItemType() >= 50 && pMouseItem->getItemType() <= 52)
				{
					// �ɼǶ�����
					downgradeSetOptionType( pItem, firstOption, pFirstOptionInfo );

					OptionType_t previousOptionType = pFirstOptionInfo->getPreviousType();
					optionChange = (firstOption << (shiftValue+8)) | (previousOptionType << shiftValue);
				}
				else
				{
					// �ɼǾ�����
					pItem->removeOptionType2( firstOption );
					optionChange = (firstOption << (shiftValue+8));

					// DB����
					string optionField;
					setOptionTypeToField( pItem->getOptionTypeList2(), optionField );

					char pField[80];
					sprintf(pField, "OptionType2='%s'", optionField.c_str());
					pItem->tinysave(pField);
				}
			}
		}
		else
		{
			OptionType_t prev = pFirstOptionInfo->getPreviousType();

			if ( prev != 0 )
			{
				//�ɼǶ����� Ȯ�� ����ؾ� �ȴ�.

				int noChangeRatio = 33;
				int downgradeRatio = pItemInfo->getDowngradeRatio();
				int dice = rand() % 100;

				//cout << "ù��° �ɼ� : " << pFirstOptionInfo->getHName() << " �� ������ Ȯ�� : " << downgradeRatio << endl;

				if ( dice < noChangeRatio )
				{
					// ��ȭ����
				}
				else if ( dice < noChangeRatio + downgradeRatio || pMouseItem->getItemType() >= 50 && pMouseItem->getItemType() <= 52)
				{
					// �ɼǶ�����
					downgradeSetOptionType( pItem, firstOption, pFirstOptionInfo );

					OptionType_t previousOptionType = pFirstOptionInfo->getPreviousType();
					optionChange = (firstOption << (shiftValue+8)) | (previousOptionType << shiftValue);
				}
				else
				{
					// �ɼǾ�����
					pItem->removeOptionType2( firstOption );
					optionChange = (firstOption << (shiftValue+8));

					// DB����
					string optionField;
					setOptionTypeToField( pItem->getOptionTypeList2(), optionField );

					char pField[80];
					sprintf(pField, "OptionType2='%s'", optionField.c_str());
					pItem->tinysave(pField);

				}
			}
		}

		shiftValue -= 16;

		if ( bSecondUpgradePossible )
		{
			// �ι�° �ɼ��� ��æƮ Ȯ���� ù��° �ɼ��� �������ο� ������.
			int succeedRatio = g_pOptionInfoManager->getRareUpgradeRatio( secondOption, bFirstSucceed ) * pItemInfo->getUpgradeRatio();
			succeedRatio += pEventStarInfo->getFunctionValue()*100;
			int dice = rand() %10000;

			//cout << "�ι�° �ɼ� : " << pSecondOptionInfo->getHName() << " ��æƮ Ȯ�� " << succeedRatio << endl;

			if ( dice < succeedRatio )
			{
				//cout << "��æƮ ����" << endl;
				processUpgradeSetOptionType( pItem, secondOption, pSecondOptionInfo );

				OptionType_t upgradeOptionType = pSecondOptionInfo->getUpgradeType();
				optionChange |= (secondOption << (shiftValue+8)) | (upgradeOptionType << shiftValue);

				bFirstSucceed = true;
			}
			else
			{
				int noChangeRatio = 33;
				int downgradeRatio = pItemInfo->getDowngradeRatio();
				dice = rand() % 100;

				//cout << "��æƮ ���� : " << pItemInfo->getName() << " �ɼǶ����� Ȯ�� " << downgradeRatio << endl;

				if ( dice < noChangeRatio )
				{
					// ��ȭ����
				}
				else if ( dice < noChangeRatio + downgradeRatio || pMouseItem->getItemType() >= 50 && pMouseItem->getItemType() <= 52)
				{
					// �ɼǶ�����
					downgradeOptionType( pItem, secondOption, pSecondOptionInfo );

					OptionType_t previousOptionType = pSecondOptionInfo->getPreviousType();
					optionChange |= (secondOption << (shiftValue+8)) | (previousOptionType << shiftValue);
				}
				else
				{
					// �ɼǾ�����
					pItem->removeOptionType2( secondOption );
					optionChange |= (secondOption << (shiftValue+8));

					// DB����
					string optionField;
					setOptionTypeToField( pItem->getOptionTypeList2(), optionField );

					char pField[80];
					sprintf(pField, "OptionType2='%s'", optionField.c_str());
					pItem->tinysave(pField);
				}
			}
		}
		else
		{
			OptionType_t prev = pSecondOptionInfo->getPreviousType();

			if ( prev != 0 )
			{
				//�ɼǶ����� Ȯ�� ����ؾ� �ȴ�.
				int noChangeRatio = 33;
				int downgradeRatio = pItemInfo->getDowngradeRatio();
				int dice = rand() % 100;

				//cout << "�ι�° �ɼ� : " << pSecondOptionInfo->getHName() << " �� ������ Ȯ�� : " << downgradeRatio << endl;

				if ( dice < noChangeRatio )
				{
					// ��ȭ����
				}
				else if ( dice < noChangeRatio + downgradeRatio || pMouseItem->getItemType() >= 50 && pMouseItem->getItemType() <= 52)
				{
					// �ɼǶ�����
					downgradeSetOptionType( pItem, secondOption, pSecondOptionInfo );

					OptionType_t previousOptionType = pSecondOptionInfo->getPreviousType();
					optionChange |= (secondOption << (shiftValue+8)) | (previousOptionType << shiftValue);
				}
				else
				{
					// �ɼǾ�����
					pItem->removeOptionType2( secondOption );
					optionChange |= (secondOption << (shiftValue+8));

					// DB����
					string optionField;
					setOptionTypeToField( pItem->getOptionTypeList2(), optionField );

					char pField[80];
					sprintf(pField, "OptionType2='%s'", optionField.c_str());
					pItem->tinysave(pField);
				}
			}
		}

		shiftValue -= 16;

		if ( bThreeUpgradePossible )
		{
			// ù��° �ɼ��� ��æƮ Ȯ���� ����� 2�� Ȯ���� ������.
			int succeedRatio = pThreeOptionInfo->getUpgradeSecondRatio() * pItemInfo->getUpgradeRatio();
			succeedRatio += pEventStarInfo->getFunctionValue()*100;
			int dice = rand()%10000;

			//cout << "ù��° �ɼ� : " << pFirstOptionInfo->getHName() << " ��æƮ Ȯ??" << succeedRatio << endl;

			if ( dice < succeedRatio )
			{
				//cout << "��æƮ ����" << endl;
				processUpgradeSetOptionType( pItem, thirdOption, pThreeOptionInfo );

				OptionType_t upgradeOptionType = pThreeOptionInfo->getUpgradeType();
				optionChange = (thirdOption << (shiftValue+8)) | (upgradeOptionType << shiftValue);

				bFirstSucceed = true;
			}
			else
			{
				int noChangeRatio = 33;
				int downgradeRatio = pItemInfo->getDowngradeRatio();
				dice = rand() % 100;

				//cout << "��æƮ ���� : " << pItemInfo->getName() << " �ɼǶ����� Ȯ�� " << downgradeRatio << endl;

				if ( dice < noChangeRatio )
				{
					// ��ȭ����
				}
				else if ( dice < noChangeRatio + downgradeRatio || pMouseItem->getItemType() >= 50 && pMouseItem->getItemType() <= 52)
				{
					// �ɼǶ�����
					downgradeSetOptionType( pItem, thirdOption, pThreeOptionInfo );

					OptionType_t previousOptionType = pThreeOptionInfo->getPreviousType();
					optionChange = (thirdOption << (shiftValue+8)) | (previousOptionType << shiftValue);
				}
				else
				{
					// �ɼǾ�����
					pItem->removeOptionType2( thirdOption);
					optionChange = (thirdOption<< (shiftValue+8));

					// DB����
					string optionField;
					setOptionTypeToField( pItem->getOptionTypeList2(), optionField );

					char pField[80];
					sprintf(pField, "OptionType2='%s'", optionField.c_str());
					pItem->tinysave(pField);
				}
			}
		}
		else
		{
			OptionType_t prev = pThreeOptionInfo->getPreviousType();

			if ( prev != 0 )
			{
				//�ɼǶ����� Ȯ�� ����ؾ� �ȴ�.

				int noChangeRatio = 33;
				int downgradeRatio = pItemInfo->getDowngradeRatio();
				int dice = rand() % 100;

				//cout << "ù��° �ɼ� : " << pFirstOptionInfo->getHName() << " �� ������ Ȯ�� : " << downgradeRatio << endl;

				if ( dice < noChangeRatio )
				{
					// ��ȭ����
				}
				else if ( dice < noChangeRatio + downgradeRatio || pMouseItem->getItemType() >= 50 && pMouseItem->getItemType() <= 52)
				{
					// �ɼǶ�����
					downgradeSetOptionType( pItem, thirdOption, pThreeOptionInfo);

					OptionType_t previousOptionType = pThreeOptionInfo->getPreviousType();
					optionChange = (thirdOption<< (shiftValue+8)) | (previousOptionType << shiftValue);
				}
				else
				{
					// �ɼǾ�����
					pItem->removeOptionType2( thirdOption);
					optionChange = (thirdOption<< (shiftValue+8));

					// DB����
					string optionField;
					setOptionTypeToField( pItem->getOptionTypeList2(), optionField );

					char pField[80];
					sprintf(pField, "OptionType2='%s'", optionField.c_str());
					pItem->tinysave(pField);

				}
			}
		}


		{
			// ��� �ִ� �� ����
			pPC->deleteItemFromExtraInventorySlot();

			// DB���� ����
			pMouseItem->destroy();

			// �޸𸮿��� ����
			SAFE_DELETE(pMouseItem);

			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_THIRD_ENCHANT_OK );
			gcAddItemToItemVerify.setParameter( 0 );
			gcAddItemToItemVerify.setThirdOptionType( pItem->getOptionTypeList2() );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );

			// ��� ��Ŷ ������
			//sendSetEnchantOK(pGamePlayer, optionChange);
		}

		__END_CATCH
	}


	void executeEnchantOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY)
		throw (Error)
	{
		__BEGIN_TRY

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);
		Inventory* 		pInventory  = pPC->getInventory();

		// Item�� OptionInfo�� ���´�.
		OptionType_t currentOptionType = //pItem->getFirstOptionType();
										pItem->getRandomOptionType();

		int optionSize = pItem->getOptionTypeSize();

		// ������ Ȯ���� itemType�� ���ؼ� �����ȴ�.
		const ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( 
													pItem->getItemClass(), 
													pItem->getItemType() );


				EventStarInfo* pEventStarInfo = dynamic_cast<EventStarInfo*>(g_pItemInfoManager->getItemInfo(pMouseItem->getItemClass(), pMouseItem->getItemType()));
				Assert(pEventStarInfo!=NULL);

		// ��æƮ �ҷ��� �������� �����̰ų�
		// ���� �������̰ų�
		// ����ũ �������� ���
		if (optionSize!=1
			|| pItemInfo->isUnique())
		{
			//cout << "no Option " << endl;
			sendEnchantImpossible( pGamePlayer );
			return;
		}

		OptionInfo* pOptionInfo = getOptionInfo( currentOptionType );

		if (pOptionInfo==NULL)
		{
			sendEnchantImpossible( pGamePlayer );
			return;
		}

		// �ɼ��� �������� ��?�?�Ұ��������� �ʴٰ� ����..
		// ��� �ִ� �������� �´��� Ȯ���ϰ�
		// upgrade������ option�� ��쿡...
		bool bUpgradePossible = pOptionInfo->isUpgradePossible();
		if (optionSize>1 || bUpgradePossible)
		{
			//---------------------------------------------------------
			// item������ 1���� ��츸 �� �� �ֵ��� �صд�.
			// �������� ��쵵 �����ϰ� �Ϸ���
			// ������ ������ �ٿ��߰���.. client�� �����ؾ� �Ѵ�.
			// upgrade �����ұ�?
			//---------------------------------------------------------
			// �ɼ�Ȯ�� * Ÿ��Ȯ�� / 10000
			int succeedRatio = 0;

			if ( pMouseItem->getItemType() == 15 )
			{
				// ��� ��� 2~ 2003.5.11
				succeedRatio = pOptionInfo->getUpgradeSecondRatio() * pItemInfo->getUpgradeRatio();
				succeedRatio += pEventStarInfo->getFunctionValue()*100;
			}
			else
			{
				// ���� ��æƮ ���۵�
				succeedRatio = pOptionInfo->getUpgradeRatio() * 1+pItemInfo->getUpgradeRatio();
				succeedRatio += pEventStarInfo->getFunctionValue()*100;
			}

//			cout << "�ɼ� " << pOptionInfo->getHName() << " ��æƮ Ȯ�� : " << succeedRatio << endl;
			
			int dice = rand()%10000;
			bool bSucceed = (dice < succeedRatio);

			/*
			cout << "EnchantCheck = " 
				<< pOptionInfo->getUpgradeRatio() << " * "
				<< pItemInfo->getUpgradeRatio() << " = "
				<< succeedRatio << ", dice = " << dice << " , succeed=" << (int)bSucceed << endl;
			*/

			//cout << "Before = " << getOptionTypeToString( pItem->getOptionTypeList() ) << endl;
			//cout << "CurrentOptionType = " << (int)currentOptionType << endl;

			// �ɼ��� ������ �پ��ִ� ��쿡 ���� ������ �ɼ��� upgrade�� �Ұ����ϴٸ� ���з� ����.
			// ���� if���� optionSize>1 �� üũ�߱� ������.. bUpgradePossible�� ��찡 �ƴϸ�,
			// optionSize>1 �̶�� �Ǵ��� �� �ִ�.
			if (bUpgradePossible
				&& pMouseItem->getNum()==1
				&& bSucceed)
			{
//				cout << "��æƮ ����" << endl;
				processUpgradeOptionType( pItem, currentOptionType, pOptionInfo );

				OptionType_t upgradeOptionType = pOptionInfo->getUpgradeType();
				uint optionChange = (currentOptionType << 24) | (upgradeOptionType << 16);

				sendEnchantOK( pGamePlayer, optionChange );

				//cout << gcAddItemToItemVerify.toString().c_str() << endl;
			}
			//---------------------------------------------------------
			// upgrade ����
			//---------------------------------------------------------
			else
			{
				//cout << "Failed!" << endl;
				bool bCrashItem = pItemInfo->isUpgradeCrash();

				// ���� packet : �������� �μ������� �ƴ��� ����
				GCAddItemToItemVerify gcAddItemToItemVerify;

				if ( bCrashItem )
				{
					// ������ �μ��� ���� ItemTrace Log ������ ��.��; 
					if ( pItem != NULL && pItem->isTraceItem() )
					{
						remainTraceLog( pItem, pCreature->getName(), "GOD", ITEM_LOG_DELETE, DETAIL_ENCHANT);
					}

					crashItem( pItem, pInventory, invenX, invenY );

					gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_CRASH );

					//cout << "Broken" << endl;
				}
				else
				{
					downgradeOptionType( pItem, currentOptionType, pOptionInfo );

					OptionType_t previousOptionType = pOptionInfo->getPreviousType();
					uint optionChange = (currentOptionType << 24) | (previousOptionType << 16);

					gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_DECREASE );
					gcAddItemToItemVerify.setParameter( optionChange );
				}

				pGamePlayer->sendPacket( &gcAddItemToItemVerify );

				//cout << "Upgrade Failed " << (bCrashItem? ": Crash!":" ") << endl;
			}

			// ��� �ִ� �� ����
			pPC->deleteItemFromExtraInventorySlot();

			// DB���� ����
			pMouseItem->destroy();

			// �޸𸮿��� ����
			SAFE_DELETE(pMouseItem);
		}
		else
		{
			sendEnchantImpossible( pGamePlayer );
			//cout << "upgrade impossible" << endl;
		}

		__END_CATCH
	}

	void executeEnchantSetOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY)
		throw (Error)
	{
		__BEGIN_TRY

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);
		Inventory* 		pInventory  = pPC->getInventory();

		// Item�� OptionInfo�� ���´�.
		OptionType_t currentOptionType = pItem->getFirstOptionType2();
										//pItem->getRandomOptionType2();

		int optionSize = pItem->getOptionTypeSize2();

		// ������ Ȯ���� itemType�� ���ؼ� �����ȴ�.
		const ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( 
													pItem->getItemClass(), 
													pItem->getItemType() );

		// ��æƮ �ҷ��� �������� �����̰ų�
		// ���� �������̰ų�
		// ��?��?�������� ���
		if (optionSize!=1
			|| pItemInfo->isUnique())
		{
			//cout << "no Option " << endl;
			sendEnchantImpossible( pGamePlayer );
			return;
		}

		OptionInfo* pOptionInfo = getOptionInfo( currentOptionType );

		if (pOptionInfo==NULL)
		{
			sendEnchantImpossible( pGamePlayer );
			return;
		}

		// �ɼ��� �������� ���� �Ұ��������� �ʴٰ� ����..
		// ��� �ִ� ��?����??´��?Ȯ���ϰ�
		// upgrade������ option�� ��쿡...
		bool bUpgradePossible = pOptionInfo->isUpgradePossible();
		if (optionSize>1 || bUpgradePossible)
		{
			//---------------------------------------------------------
			// item������ 1���� ��츸 �� �� �ֵ��� �صд�.
			// �������� ��쵵 �����ϰ� �Ϸ���
			// ������ ������ �ٿ��߰���.. client�� �����ؾ� �Ѵ�.
			// upgrade �����ұ�?
			//---------------------------------------------------------
			// �ɼ�Ȯ�� * Ÿ��Ȯ�� / 10000
			int succeedRatio = 0;

			if ( pMouseItem->getItemType() == 15 )
			{
				// ��� ��� 2~ 2003.5.11
				succeedRatio = pOptionInfo->getUpgradeSecondRatio() * pItemInfo->getUpgradeRatio();
				//succeedRatio += pMouseItem->getHeroOption()*100;
			}
			else
			{
				// ���� ��æƮ ���۵�
				succeedRatio = pOptionInfo->getUpgradeRatio() * pItemInfo->getUpgradeRatio();
				//succeedRatio += pMouseItem->getHeroOption()*100;
			}

//			cout << "�ɼ� " << pOptionInfo->getHName() << " ��æƮ Ȯ�� : " << succeedRatio << endl;
			
			int dice = rand()%10000;
			bool bSucceed = (dice < succeedRatio);

			/*
			cout << "EnchantCheck = " 
				<< pOptionInfo->getUpgradeRatio() << " * "
				<< pItemInfo->getUpgradeRatio() << " = "
				<< succeedRatio << ", dice = " << dice << " , succeed=" << (int)bSucceed << endl;
			*/

			//cout << "Before = " << getOptionTypeToString( pItem->getOptionTypeList() ) << endl;
			//cout << "CurrentOptionType = " << (int)currentOptionType << endl;

			// ��?��?������ �پ��ִ� ��쿡 ���� ������ �ɼ�??upgrade�� �Ұ����ϴٸ� ���з� ����.
			// ���� if���� optionSize>1 �� üũ�߱� ������.. bUpgradePossible�� ��찡 �ƴϸ�,
			// optionSize>1 �̶�� �Ǵ��� �� �ִ�.
			if (bUpgradePossible
				&& pMouseItem->getNum()==1
				&& bSucceed)
			{
//				cout << "��æƮ ����" << endl;
				processUpgradeSetOptionType( pItem, currentOptionType, pOptionInfo );

				OptionType_t upgradeOptionType = pOptionInfo->getUpgradeType();
				uint optionChange = (currentOptionType << 24) | (upgradeOptionType << 16);

			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_THIRD_ENCHANT_OK );
			gcAddItemToItemVerify.setParameter( 0 );
			gcAddItemToItemVerify.setThirdOptionType( pItem->getOptionTypeList2() );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );

				//cout << gcAddItemToItemVerify.toString().c_str() << endl;
			}
			//---------------------------------------------------------
			// upgrade ����
			//---------------------------------------------------------
			else
			{
				//cout << "Failed!" << endl;
				bool bCrashItem = pItemInfo->isUpgradeCrash();

				// ���� packet : �������� �μ������� �ƴ��� ����
				GCAddItemToItemVerify gcAddItemToItemVerify;

				if ( bCrashItem )
				{
					// ������ �μ��� ���� ItemTrace Log ������ ��.��; 
					if ( pItem != NULL && pItem->isTraceItem() )
					{
						remainTraceLog( pItem, pCreature->getName(), "GOD", ITEM_LOG_DELETE, DETAIL_ENCHANT);
					}

					crashItem( pItem, pInventory, invenX, invenY );

					gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_CRASH );

					//cout << "Broken" << endl;
				}
				else
				{
					downgradeSetOptionType( pItem, currentOptionType, pOptionInfo );

					OptionType_t previousOptionType = pOptionInfo->getPreviousType();
					uint optionChange = (currentOptionType << 24) | (previousOptionType << 16);

			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_THIRD_ENCHANT_OK );
			gcAddItemToItemVerify.setParameter( 0 );
			gcAddItemToItemVerify.setThirdOptionType( pItem->getOptionTypeList2() );
				}

				pGamePlayer->sendPacket( &gcAddItemToItemVerify );

				//cout << "Upgrade Failed " << (bCrashItem? ": Crash!":" ") << endl;
			}

			// ��� �ִ� �� ����
			pPC->deleteItemFromExtraInventorySlot();

			// DB���� ����
			pMouseItem->destroy();

			// �޸𸮿��� ����
			SAFE_DELETE(pMouseItem);
		}
		else
		{
			sendEnchantImpossible( pGamePlayer );
			//cout << "upgrade impossible" << endl;
		}

		__END_CATCH
	}

	// ��Ʈ �ɼ��� �����Ҽ� �ִ�.
	void executeAddSetOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, OptionType_t addOptionType)
		throw (Error)
	{
		__BEGIN_TRY

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);
		int MinID,MaxID,LoopT;
		int i = 0;
		switch(addOptionType)
		{
			case 0 : 
			{
			MinID = 1;
			MaxID = 92;
			LoopT = 1;
			break;
			}
			case 1 : 
			{
			MinID = 1;
			MaxID = 92;
			LoopT = 2;
			break;
			}
			case 2 : 
			{
			MinID = 1;
			MaxID = 92;
			LoopT = 3;
			break;
			}
			defalut:	
			break;
		}
		// �� Ŭ������ ���� �� �ִ� �ɼ�Ŭ�����̰�..
		// �ɼ��� ����
		// ����ũ�� �ƴϰ�
		// ���콺�� �Ѱ��� ��� �ϴ� ��쿡 �ɼ� �߰��� �����ϴ�.
	if(pMouseItem->getItemType() >= 40 && pMouseItem->getItemType() <= 45){
		if (isPossibleOptionItemClass(pItem->getItemClass())
			&& !pItem->isUnique()
			&& pMouseItem->getNum()==1)
		{
			list<OptionType_t> oList;
			while(i < LoopT){
			oList.push_back(g_pCrystalOptionLoaderManager->getRandomItem( MinID , MaxID ));
			i++;
			}
			// �ɼ� ����
			if(pMouseItem->getItemType() >= 43 && pMouseItem->getItemType() <= 45){
			pItem->setOptionType2( oList );
			
			string optionField;
			setOptionTypeToField( pItem->getOptionTypeList2(), optionField );

			// DB����
			char pField[80];
			sprintf(pField, "OptionType2='%s'", optionField.c_str());
			pItem->tinysave(pField);
			}else{
			pItem->setOptionType( oList );
			
			string optionField;
			setOptionTypeToField( pItem->getOptionTypeList(), optionField );

			// DB����
			char pField[80];
			sprintf(pField, "OptionType='%s'", optionField.c_str());
			pItem->tinysave(pField);
			}

			uint optionChange = addOptionType;

			// ��� �ִ� �� ����
			pPC->deleteItemFromExtraInventorySlot();
			pMouseItem->destroy(); 					// DB���� ����
			//SAFE_DELETE(pMouseItem); 				// �޸𸮿��� ����


			// ����packet : upgrade�� option�� �־��ش�.
			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
			gcAddItemToItemVerify.setParameter( 0 );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );

			GCDeleteInventoryItem gcDeleteInventoryItem;
			gcDeleteInventoryItem.setObjectID(pItem->getObjectID());
			pGamePlayer->sendPacket(&gcDeleteInventoryItem);

						CoordInven_t X = -1, Y;
						pPC->getInventory()->findItemOID( pItem->getObjectID(), X, Y );
						Assert( X != -1 );

			GCCreateItem gcCreateItem;
			makeGCCreateItem( &gcCreateItem, pItem, X, Y );
			pGamePlayer->sendPacket(&gcCreateItem);

			//SAFE_DELETE(pItem); 				// �޸𸮿��� ����


			//cout << gcAddItemToItemVerify.toString().c_str() << endl;
		}
	}
	if(pMouseItem->getItemType() >= 33 && pMouseItem->getItemType() <= 38){
		if (isPossibleOptionItemClass(pItem->getItemClass())
			&& pItem->getOptionTypeSize2()==0 || pItem->getOptionTypeSize()==0
			&& !pItem->isUnique()
			&& pMouseItem->getNum()==1)
		{
			list<OptionType_t> oList;
			while(i < LoopT){
			oList.push_back(g_pCrystalOptionLoaderManager->getRandomItem( MinID , MaxID ));
			i++;
			}
			// �ɼ� ����
			if(pMouseItem->getItemType() >= 33 && pMouseItem->getItemType() <= 35){
			pItem->setOptionType2( oList );
			
			string optionField;
			setOptionTypeToField( pItem->getOptionTypeList2(), optionField );

			// DB����
			char pField[80];
			sprintf(pField, "OptionType2='%s'", optionField.c_str());
			pItem->tinysave(pField);
			}else{
			pItem->setOptionType( oList );
			
			string optionField;
			setOptionTypeToField( pItem->getOptionTypeList(), optionField );

			// DB����
			char pField[80];
			sprintf(pField, "OptionType='%s'", optionField.c_str());
			pItem->tinysave(pField);
			}

			uint optionChange = addOptionType;

			// ��� �ִ� �� ����
			pPC->deleteItemFromExtraInventorySlot();
			pMouseItem->destroy(); 					// DB���� ����
			//SAFE_DELETE(pMouseItem); 				// �޸𸮿��� ����


			// ����packet : upgrade�� option�� �־��ش�.
			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
			gcAddItemToItemVerify.setParameter( 0 );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );

			GCDeleteInventoryItem gcDeleteInventoryItem;
			gcDeleteInventoryItem.setObjectID(pItem->getObjectID());
			pGamePlayer->sendPacket(&gcDeleteInventoryItem);

						CoordInven_t X = -1, Y;
						pPC->getInventory()->findItemOID( pItem->getObjectID(), X, Y );
						Assert( X != -1 );

			GCCreateItem gcCreateItem;
			makeGCCreateItem( &gcCreateItem, pItem, X, Y );
			pGamePlayer->sendPacket(&gcCreateItem);

			//SAFE_DELETE(pItem); 				// �޸�?��?����


			//cout << gcAddItemToItemVerify.toString().c_str() << endl;
		}
		else
		{
			//cout << "Enchant Impossible" << endl;
			//cout << "impossibleOption : " << (int)currentOptionType << endl;
			// upgrade �� �� ���� option�̴�.
			// �Ұ� packet
			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );

			//cout << "upgrade impossible" << endl;
		}
	}
		__END_CATCH
	}

	// ���� �����ۿ� �ɼ��� �߰���Ų��.
	void executeAddOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, OptionType_t addOptionType)
		throw (Error)
	{
		__BEGIN_TRY

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);

		// �����̾� ���񽺰� �ƴ� ���� �ȵ���..
/*		if (!pGamePlayer->isPayPlaying()
			&& !pGamePlayer->isPremiumPlay())
		{
			//cout << "no Option " << endl;
			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE_NO_PREMIUM );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );
			return;
		}
*/

		// �� Ŭ������ ?��?�� �ִ� �ɼ�Ŭ�����̰�..
		// �ɼ��� ����
		// ����ũ�� �ƴϰ�
		// ���콺�� �Ѱ��� ��� �ϴ� ��쿡 �ɼ� �߰��� �����ϴ�.
		if (isPossibleOptionItemClass(pItem->getItemClass())
			&& pItem->getOptionTypeSize()==0 
			&& !pItem->isUnique()
			&& pMouseItem->getNum()==1)
		{
			// �ɼ� ����
			pItem->addOptionType( addOptionType );
			
			string optionField;
			setOptionTypeToField( pItem->getOptionTypeList(), optionField );

			// DB����
			char pField[80];
			sprintf(pField, "OptionType='%s'", optionField.c_str());
			pItem->tinysave(pField);

			uint optionChange = addOptionType;

			// ��� �ִ� �� ����
			pPC->deleteItemFromExtraInventorySlot();
			pMouseItem->destroy(); 					// DB���� ����
			SAFE_DELETE(pMouseItem); 				// �޸𸮿��� ����


			// ����packet : upgrade�� option�� �־��ش�.
			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
			gcAddItemToItemVerify.setParameter( optionChange );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );

			//cout << gcAddItemToItemVerify.toString().c_str() << endl;
		}
		else
		{
			//cout << "Enchant Impossible" << endl;
			//cout << "impossibleOption : " << (int)currentOptionType << endl;
			// upgrade �� �� ���� option�̴�.
			// �Ұ� packet
			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );

			//cout << "upgrade impossible" << endl;
		}

		__END_CATCH
	}

	// ���ɼ� �����ۿ� �ڶ��� �ٸ��� �ִ�.

	void executeAddCoralOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, int addOptionType)
		throw (Error)
	{
		__BEGIN_TRY

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);

		// �����̾� ���񽺰� �ƴ� ���� �ȵ���..
/*		if (!pGamePlayer->isPayPlaying()
			&& !pGamePlayer->isPremiumPlay())
		{
			//cout << "no Option " << endl;
			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE_NO_PREMIUM );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );
			return;
		}
*/

		// �� Ŭ������ ���� �� �ִ� �ɼ�Ŭ�����̰�..
		// �ɼ��� ����
		// ����ũ�� �ƴϰ�
		// ���콺�� �Ѱ��� ��� �ϴ� ��쿡 �ɼ� �߰��� �����ϴ�.
		if (isPossibleOptionItemClass(pItem->getItemClass())
			&& pItem->getOptionTypeSize()==0 
			&& !pItem->isUnique()
			&& pMouseItem->getNum()==1)
		{
			OptionType_t CoralOption;
			// �ɼ� ����
			switch(addOptionType){
				
				// ���� �ڶ�(��1~5)
				case 0 :
				{
				CoralOption = Random(1,5);
				break;
				}
				
				// �׸� �ڶ�(��1~5)
				case 1 :
				{
				CoralOption = Random(6,10);
				break;
				}

				// ��� �ڶ�(��1~5)
				case 2 :
				{
				CoralOption = Random(11,15);
				break;
				}

				// ��� �ڶ�(��1~5)
				case 3 :
				{
				CoralOption = Random(48,52);
				break;
				}

				// ��� �ڶ�(��1~5)
				case 4 :
				{
				CoralOption = Random(183,185);
				break;
				}

				// ��� �ڶ�(��1~5)
				case 5 :
				{
				CoralOption = Random(1,87);
				if(CoralOption == 32){CoralOption = 33;}
				if(CoralOption == 174){CoralOption = 175;}
				break;
				}
					default:
					break;
			}
			pItem->addOptionType( CoralOption );
			
			string optionField;
			setOptionTypeToField( pItem->getOptionTypeList(), optionField );

			// DB����
			char pField[80];
			sprintf(pField, "OptionType='%s'", optionField.c_str());
			pItem->tinysave(pField);

			uint optionChange = CoralOption;

			// ��� �ִ� �� ����
			pPC->deleteItemFromExtraInventorySlot();
			pMouseItem->destroy(); 					// DB���� ����
			SAFE_DELETE(pMouseItem); 				// �޸𸮿��� ����


			// ����packet : upgrade�� option�� �־��ش�.
			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
			gcAddItemToItemVerify.setParameter( optionChange );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );

			//cout << gcAddItemToItemVerify.toString().c_str() << endl;
		}
		else
		{
			//cout << "Enchant Impossible" << endl;
			//cout << "impossibleOption : " << (int)currentOptionType << endl;
			// upgrade �� �� ���� option�̴�.
			// �Ұ� packet
			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );

			//cout << "upgrade impossible" << endl;
		}

		__END_CATCH
	}

	void executeRedSunCore(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem) throw(Error)
	{
		__BEGIN_TRY

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);

		SlayerTuningItemInfo* pSlayerTuningItemInfo = dynamic_cast<SlayerTuningItemInfo*>(g_pItemInfoManager->getItemInfo(pMouseItem->getItemClass(), pMouseItem->getItemType()));
		Assert(pSlayerTuningItemInfo != NULL);

		pItem->setItemType(pSlayerTuningItemInfo->getTunningItemType());

		char pField[80];
		sprintf(pField, "ItemType=%u", pSlayerTuningItemInfo->getTunningItemType());
		pItem->tinysave(pField);

			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_CHANGE_ENCHANT_OK );
			gcAddItemToItemVerify.setParameter( pSlayerTuningItemInfo->getTunningItemType() );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );

			pPC->deleteItemFromExtraInventorySlot();
			pMouseItem->destroy();
			SAFE_DELETE(pMouseItem);
			cout << " ��������� ����.." << endl;

		__END_CATCH
	}


	void executeVampireTuningItem(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem) throw(Error)
	{
		__BEGIN_TRY

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);

		VampireTuningItemInfo* pCreateItemInfo = dynamic_cast<VampireTuningItemInfo*>(g_pItemInfoManager->getItemInfo(pMouseItem->getItemClass(), pMouseItem->getItemType()));
		Assert(pCreateItemInfo != NULL);

		pItem->setItemType(pCreateItemInfo->getTunningItemType());

		char pField[80];
		sprintf(pField, "ItemType=%u", pCreateItemInfo->getTunningItemType());
		pItem->tinysave(pField);

			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_CHANGE_ENCHANT_OK );
			gcAddItemToItemVerify.setParameter( pCreateItemInfo->getTunningItemType() );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );

			pPC->deleteItemFromExtraInventorySlot();
			pMouseItem->destroy();
			SAFE_DELETE(pMouseItem);
			cout << " ��������� ����.." << endl;

		__END_CATCH
	}

	void executeOustersTuningItem(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem) throw(Error)
	{
		__BEGIN_TRY

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);

		OustersTuningItemInfo* pCreateItemInfo = dynamic_cast<OustersTuningItemInfo*>(g_pItemInfoManager->getItemInfo(pMouseItem->getItemClass(), pMouseItem->getItemType()));
		Assert(pCreateItemInfo != NULL);

		pItem->setItemType(pCreateItemInfo->getTunningItemType());

		char pField[80];
		sprintf(pField, "ItemType=%u", pCreateItemInfo->getTunningItemType());
		pItem->tinysave(pField);

			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_CHANGE_ENCHANT_OK );
			gcAddItemToItemVerify.setParameter( pCreateItemInfo->getTunningItemType() );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );

			pPC->deleteItemFromExtraInventorySlot();
			pMouseItem->destroy();
			SAFE_DELETE(pMouseItem);
			cout << " ��������� ����.." << endl;

		__END_CATCH
	}

	void executeTransKit(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem) throw(Error)
	{
		__BEGIN_TRY

		GCAddItemToItemVerify gcResult;
		uint optionChange;

		const ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( pItem->getItemClass(), pItem->getItemType() );
		if ( pItemInfo->getReqGender() == GENDER_BOTH || pItemInfo->getReqGender() == GENDER_MAX
			|| pItemInfo->isUnique() 
			|| pMouseItem->getNum() != 1 )
		{
			gcResult.setCode( ADD_ITEM_TO_ITEM_VERIFY_TRANS_IMPOSSIBLE );
			pGamePlayer->sendPacket(&gcResult);
			return;
		}

		ItemType_t newItemType = pItem->getItemType() ^ 1;
		optionChange = ( pItem->getItemType() << 16 ) | newItemType;
		pItem->setItemType( newItemType );

		char query[50];
		sprintf(query, "ItemType=%u", newItemType );
		pItem->tinysave(query);

		gcResult.setCode( ADD_ITEM_TO_ITEM_VERIFY_TRANS_OK );
		gcResult.setParameter( optionChange );
		pGamePlayer->sendPacket(&gcResult);

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);

		pPC->deleteItemFromExtraInventorySlot();
		pMouseItem->destroy();
		SAFE_DELETE(pMouseItem);

		__END_CATCH
	}

	OptionInfo* getOptionInfo(OptionType_t optionType)
	{
		OptionInfo* pOptionInfo = NULL;

		try {
			pOptionInfo = g_pOptionInfoManager->getOptionInfo( optionType );

			if (pOptionInfo==NULL)
			{
				filelog("optionError.txt", "CGAddItemToItemHandler: no option [%d]", optionType);

				return NULL;
			}
		} catch (NoSuchElementException& t) {
			filelog("optionError.txt", "CGAddItemToItemHandler: no option [%d]", optionType);

			return NULL;
		}

		return pOptionInfo;
	}


	void	processUpgradeOptionType(
					Item* pItem,
					OptionType_t currentOptionType,
					OptionInfo* pOptionInfo)
		throw (Error)
	{
		__BEGIN_TRY

		//cout << "Succeed!" << endl;
		// upgrage�� option
		OptionType_t upgradeOptionType = pOptionInfo->getUpgradeType();

		// �ɼ� ����
		pItem->changeOptionType( currentOptionType, upgradeOptionType );

		//cout << "Succeed = " << getOptionTypeToString( pItem->getOptionTypeList() );
		
		string optionField;
		setOptionTypeToField( pItem->getOptionTypeList(), optionField );

		//list<OptionType_t> op;
		//setOptionTypeFromField( op, optionField );
		//cout << "Check = " << getOptionTypeToString( op ) << endl;

		// DB����
		char pField[80];
		sprintf(pField, "OptionType='%s'", optionField.c_str());
		pItem->tinysave(pField);

		__END_CATCH
	}

	void	processUpgradeSetOptionType(
					Item* pItem,
					OptionType_t currentOptionType,
					OptionInfo* pOptionInfo)
		throw (Error)
	{
		__BEGIN_TRY

		//cout << "Succeed!" << endl;
		// upgrage�� option
		OptionType_t upgradeOptionType = pOptionInfo->getUpgradeType();

		// �ɼ� ����
		pItem->changeOptionType2( currentOptionType, upgradeOptionType );

		//cout << "Succeed = " << getOptionTypeToString( pItem->getOptionTypeList() );
		
		string optionField;
		setOptionTypeToField( pItem->getOptionTypeList2(), optionField );

		//list<OptionType_t> op;
		//setOptionTypeFromField( op, optionField );
		//cout << "Check = " << getOptionTypeToString( op ) << endl;

		// DB����
		char pField[80];
		sprintf(pField, "OptionType2='%s'", optionField.c_str());
		pItem->tinysave(pField);

		__END_CATCH
	}

	void	crashItem(Item* pItem, Inventory* pInventory, CoordInven_t invenX, CoordInven_t invenY)
		throw (Error)
	{
		__BEGIN_TRY

		// inventory���� ������ ����
		pInventory->deleteItem( invenX, invenY );

		// DB���� ����
		pItem->destroy();

		// �޸𸮿��� ����
		SAFE_DELETE(pItem);

		__END_CATCH
	}

	void	downgradeOptionType(
					Item* pItem,
					OptionType_t currentOptionType,
					OptionInfo* pOptionInfo)
		throw (Error)
	{
		__BEGIN_TRY

		// �������� �ɼ��� �Ѵܰ� ����߸���.
		OptionType_t previousOptionType = pOptionInfo->getPreviousType();

		//cout << "FailBefore : " << getOptionTypeToString(pItem->getOptionTypeList()) << endl;

		// �ɼ� ����
		// ���� �ɼ��� ���ٸ� �ƿ� �ɼ��� ���ش�.
		if (previousOptionType==0)
		{
			pItem->removeOptionType( currentOptionType );
			//cout << "Remove = " << getOptionTypeToString( pItem->getOptionTypeList() ) << endl;
		}
		else
		{
			pItem->changeOptionType( currentOptionType, previousOptionType );
			//cout << "Down = " << getOptionTypeToString( pItem->getOptionTypeList() ) << endl;
		}

		// DB����
		string optionField;
		setOptionTypeToField( pItem->getOptionTypeList(), optionField );

		//cout << "FailAfter : " << getOptionTypeToString(pItem->getOptionTypeList()) << endl;

		char pField[80];
		sprintf(pField, "OptionType='%s'", optionField.c_str());
		pItem->tinysave(pField);


		__END_CATCH
	}

	void	downgradeSetOptionType(
					Item* pItem,
					OptionType_t currentOptionType,
					OptionInfo* pOptionInfo)
		throw (Error)
	{
		__BEGIN_TRY

		// �������� �ɼ��� �Ѵܰ� ����߸���.
		OptionType_t previousOptionType = pOptionInfo->getPreviousType();

		//cout << "FailBefore : " << getOptionTypeToString(pItem->getOptionTypeList()) << endl;

		// �ɼ� ����
		// ���� �ɼ��� ���ٸ� �ƿ� �ɼ��� ���ش�.
		if (previousOptionType==0)
		{
			pItem->removeOptionType2( currentOptionType );
			//cout << "Remove = " << getOptionTypeToString( pItem->getOptionTypeList() ) << endl;
		}
		else
		{
			pItem->changeOptionType2( currentOptionType, previousOptionType );
			//cout << "Down = " << getOptionTypeToString( pItem->getOptionTypeList() ) << endl;
		}

		// DB����
		string optionField;
		setOptionTypeToField( pItem->getOptionTypeList2(), optionField );

		//cout << "FailAfter : " << getOptionTypeToString(pItem->getOptionTypeList()) << endl;

		char pField[80];
		sprintf(pField, "OptionType2='%s'", optionField.c_str());
		pItem->tinysave(pField);


		__END_CATCH
	}

//-----------------------------------------------------------------
// �� ���� ��æƮ ���� �ҽ�
// �� ��æƮ�� 3�� �Ǵ� ���������� �ɼ��� �����Ǿ� �־��־�� �Ѵ�.
//-----------------------------------------------------------------
	void	processUpgradePetOptionType(
					PetInfo* pPetInfo,
					Item* pItem,
					OptionType_t currentOptionType,
					OptionInfo* pOptionInfo)
		throw (Error)
	{
		__BEGIN_TRY

		//cout << "Succeed!" << endl;
		// upgrage�� option
		OptionType_t upgradeOptionType = pOptionInfo->getUpgradeType();

		pPetInfo->changeMixOptionType( currentOptionType, upgradeOptionType );

		//cout << "Succeed = " << getOptionTypeToString( pItem->getOptionTypeList() );
		
		string optionField;
		setOptionTypeToField( pPetInfo->getMixOptionType(), optionField );
		//pPetInfo->setMixOptionType(pItem->getOptionTypeList2());

		//list<OptionType_t> op;
		//setOptionTypeFromField( op, optionField );
		//cout << "Check = " << getOptionTypeToString( op ) << endl;

		// DB����
		char pField[80];
		sprintf(pField, "OptionType2='%s'", optionField.c_str());
		pItem->tinysave(pField);

		__END_CATCH
	}

	void	downgradePetOptionType(
					PetInfo* pPetInfo,
					Item* pItem,
					OptionType_t currentOptionType,
					OptionInfo* pOptionInfo)
		throw (Error)
	{
		__BEGIN_TRY

		// �������� �ɼ��� �Ѵܰ� ����߸���.
		OptionType_t previousOptionType = pOptionInfo->getPreviousType();

		//cout << "FailBefore : " << getOptionTypeToString(pItem->getOptionTypeList()) << endl;
		pItem->setOptionType2(pPetInfo->getMixOptionType() );
		// �ɼ� ����
		// ���� �ɼ��� ���ٸ� �ƿ� �ɼ��� ���ش�.
		if (previousOptionType==0)
		{
			pPetInfo->removeMixOptionType( currentOptionType );
			//cout << "Remove = " << getOptionTypeToString( pItem->getOptionTypeList() ) << endl;
		}
		else
		{
			pPetInfo->changeMixOptionType( currentOptionType, previousOptionType );
			//cout << "Down = " << getOptionTypeToString( pItem->getOptionTypeList() ) << endl;
		}

		// DB����
		string optionField;
		setOptionTypeToField( pPetInfo->getMixOptionType(), optionField );
		//pPetInfo->setMixOptionType(pItem->getOptionTypeList2());
		//cout << "FailAfter : " << getOptionTypeToString(pItem->getOptionTypeList()) << endl;

		char pField[80];
		sprintf(pField, "OptionType2='%s'", optionField.c_str());
		pItem->tinysave(pField);


		__END_CATCH
	}

//--------------------------------------------------------
// �� ���ձ� ��æ??��
//--------------------------------------------------------

	void	sendEnchantImpossible(GamePlayer* pGamePlayer)
		throw (Error)
	{
		__BEGIN_TRY

		GCAddItemToItemVerify gcAddItemToItemVerify;
		gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE );
		pGamePlayer->sendPacket( &gcAddItemToItemVerify );

		__END_CATCH
	}

	void	sendEnchantOK(GamePlayer* pGamePlayer, DWORD optionChange)
		throw (Error)
	{
		__BEGIN_TRY

		GCAddItemToItemVerify gcAddItemToItemVerify;
		gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
		gcAddItemToItemVerify.setParameter( optionChange );
		pGamePlayer->sendPacket( &gcAddItemToItemVerify );

		__END_CATCH
	}

	void	sendSetEnchantOK(GamePlayer* pGamePlayer, DWORD optionChange)
		throw (Error)
	{
		__BEGIN_TRY

		GCAddItemToItemVerify gcAddItemToItemVerify;
		gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_SET_ENCHANT_OK );
		gcAddItemToItemVerify.setParameter( optionChange );
		pGamePlayer->sendPacket( &gcAddItemToItemVerify );

		__END_CATCH
	}

	void	sendEnchantOK(GamePlayer* pGamePlayer, DWORD optionChange , DWORD optionChange2)
		throw (Error)
	{
		__BEGIN_TRY

		GCAddItemToItemVerify gcAddItemToItemVerify;
		gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_THIRD_ENCHANT_OK );
		gcAddItemToItemVerify.setParameter( 0 );
		pGamePlayer->sendPacket( &gcAddItemToItemVerify );

		__END_CATCH
	}

#endif
