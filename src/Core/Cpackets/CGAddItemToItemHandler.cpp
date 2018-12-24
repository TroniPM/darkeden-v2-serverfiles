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
	#include "PlayerCreature.h"
	#include "Inventory.h"
	#include "Item.h"
	#include "ItemInfoManager.h"
#include "ItemFactoryManager.h"
	#include "OptionInfo.h"
	#include "ItemUtil.h"
	#include "EventStar.h"
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

	#include "SystemAvailabilitiesManager.h"

	void executeUpGrade(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem) throw(Error);
	void executeTypeGrade(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem) throw(Error);
	void executeEnchantOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY) throw(Error);
	void executeEnchantRareOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY) throw(Error);
	void executeEnchantRareThreeOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY) throw(Error);
	void executeEnchantSetOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY) throw(Error);
	void executeEnchantSetRareOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY) throw(Error);
	void executeEnchantSetThreeOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY) throw(Error);
	void executeAddOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, OptionType_t addOptionType) throw(Error);
	void executeAddCoralOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, int addOptionType) throw(Error);
	void executeAddSetOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, OptionType_t addOptionType) throw(Error);
	void executeTransKit(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem) throw(Error);
	void executeRedSunCore(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem) throw(Error);
	extern bool isPossibleOptionItemClass(Item::ItemClass IClass);

	OptionInfo* getOptionInfo(OptionType_t optionType);

	void    	processUpgradeOptionType(Item* pItem, OptionType_t currentOptionType, OptionInfo* pOptionInfo) throw (Error);
	void    	processUpgradeSetOptionType(Item* pItem, OptionType_t currentOptionType, OptionInfo* pOptionInfo) throw (Error);
	void		crashItem(Item* pItem, Inventory* pInventory, CoordInven_t invenX, CoordInven_t invenY) throw (Error);
	void    	downgradeOptionType(Item* pItem, OptionType_t currentOptionType, OptionInfo* pOptionInfo) throw (Error);
	void    	downgradeSetOptionType(Item* pItem, OptionType_t currentOptionType, OptionInfo* pOptionInfo) throw (Error);
	void		sendEnchantImpossible(GamePlayer* pGamePlayer) throw (Error);
	void		sendEnchantOK(GamePlayer* pGamePlayer, DWORD optionChange) throw (Error);
	void		sendSetEnchantOK(GamePlayer* pGamePlayer, DWORD optionChange) throw (Error);
	// add by sonic �������Է��صķ��
	void		sendEnchantOK(GamePlayer* pGamePlayer, DWORD optionChange, DWORD optionCHange2) throw (Error);

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

		// �κ��丮�� �ִ� ������
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
				if (pEventStarInfo->getFunctionFlag() == 20)
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
						if(pMouseItem->getItemType()==6)// ��������װ��
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
							//cout << "��æƮ ����." << endl;
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
					case PetEnchantItemInfo::RARE_FUNCTION:
					{
						//cout << "�� ���� ��æƮ ���Դϴ�." << endl;
						if ( pPetInfo->getPetLevel() != 49 )
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

						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
						gcAddItemToItemVerify.setParameter( targetOption );
						pGamePlayer->sendPacket( &gcAddItemToItemVerify );

						char query[100];
						sprintf(query, "PetOption=%u", (uint)targetOption);
						pItem->tinysave(query);
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
						if ( pPetInfo->getPetType() != 1 )
						{
							cout << "�������� �ƴ϶��ϴ�." << endl;
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}

						bool summonPet = pPC->getPetInfo() == pPetInfo;

						pPC->deleteItemFromExtraInventorySlot();
						pMouseItem->destroy();
						SAFE_DELETE( pMouseItem );

						PetTypeInfo* pPetTypeInfo = PetTypeInfoManager::getInstance()->getPetTypeInfo(2);
						Assert( pPetTypeInfo != NULL );

						pPetInfo->setPetType(2);
						pPetInfo->setPetCreatureType( pPetTypeInfo->getPetCreatureType( pPetInfo->getPetLevel() ) );
						pPetItem->setItemType(2);

						pPetItem->tinysave( "ItemType=2" );

//						if ( pPC->getPetInfo() == pPetInfo ) sendPetInfo( pGamePlayer );
						if ( summonPet )
						{
							pPC->setPetInfo( NULL );
							sendPetInfo( pGamePlayer );
						}

						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
						gcAddItemToItemVerify.setParameter( 0 );

						pGamePlayer->sendPacket( &gcAddItemToItemVerify );

						GCDeleteInventoryItem gcDI;
						gcDI.setObjectID( pPetItem->getObjectID() );
						pGamePlayer->sendPacket( &gcDI );

						CoordInven_t X = -1, Y;
						pPC->getInventory()->findItemOID( pPetItem->getObjectID(), X, Y );
						Assert( X != -1 );

						GCCreateItem gcCI;
						makeGCCreateItem( &gcCI, pPetItem, X, Y );
						pGamePlayer->sendPacket( &gcCI );

						if ( summonPet )
						{
							pPC->setPetInfo( pPetInfo );
							sendPetInfo( pGamePlayer );
						}
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

		int Ratio = Random(30,50);
		if(pItem->getGrade() == 1) { Ratio = 101; }
		if(pMouseItem->getHeroOption() > 0){ Ratio += pMouseItem->getHeroOption();}
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
		cout << " Ȯ�� : " <<  RandomRatio << "  / " << Ratio << endl;

			pItem->setGrade( pItem->getGrade() - 1 );
			char buffer[80];
			snprintf(buffer, 80, "Grade=%u", pItem->getGrade() );
			pItem->tinysave(buffer);

			pPC->deleteItemFromExtraInventorySlot();
			pMouseItem->destroy();
			SAFE_DELETE(pMouseItem);

			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL );
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
		
		OptionType_t thirdOption  = *itr;
		itr++;
		OptionType_t secondOption = *itr;
		itr++;
		OptionType_t firstOption  = *itr;
		itr--;
		itr--;
		
		/*
		OptionType_t thirdOption  = *itr++;
		OptionType_t secondOption = *itr;
		OptionType_t firstOption  = *itr++;
		*/

		OptionInfo* pFirstOptionInfo = getOptionInfo( firstOption );
		OptionInfo* pSecondOptionInfo = getOptionInfo( secondOption );
		OptionInfo* pThirdOptionInfo = getOptionInfo( thirdOption );
//		cout << "firstOption : " << pFirstOptionInfo->getName() <<  endl;
//		cout << "secondOption : " << pSecondOptionInfo->getName() <<  endl;
//		cout << "thirdOption : " << pThirdOptionInfo->getName() <<  endl;
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
		//if ((rand() %6000) > diceValue)
			//diceValue*=2;
		if ( bFirstUpgradePossible )
		{
			// ù��° �ɼ��� ��æƮ Ȯ���� ����� 2�� Ȯ���� ������.
			int succeedRatio = pFirstOptionInfo->getUpgradeSecondRatio() * ( pItemInfo->getUpgradeRatio() +( rand() %50) );
			succeedRatio += getPercentValue(succeedRatio,pMouseItem->getHeroOption());
			//int dice = rand()%10000;
			int dice = rand() % diceValue;
			cout << "dice : " << (int)dice <<  endl;
			cout << "diceValue : " << (int)diceValue <<  endl;

			//cout << "ù��° �ɼ� : " << pFirstOptionInfo->getHName() << " ��æƮ Ȯ�� " << succeedRatio << endl;
			//dice =succeedRatio-1;
			if ( dice < succeedRatio ) //���ͨ����������װ��
			{
				//cout << "��æƮ ����" << endl;
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
			// �ι�° �ɼ��� ��æƮ Ȯ���� ù��° �ɼ��� �������ο� ������.

			int succeedRatio= g_pOptionInfoManager->getRareUpgradeRatio( secondOption, bFirstSucceed ) * ( pItemInfo->getUpgradeRatio() +( rand() %50) );
			succeedRatio += getPercentValue(succeedRatio,pMouseItem->getHeroOption());
			//int dice = rand() %10000;
			int dice = rand() % diceValue;

			//cout << "�ι�° �ɼ� : " << pSecondOptionInfo->getHName() << " ��æƮ Ȯ�� " << succeedRatio << endl;
			//dice =succeedRatio-1;
			if ( dice < succeedRatio )
			{
				//cout << "��æƮ ����" << endl;
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
			// �ι�° �ɼ��� ��æƮ Ȯ���� ù��° �ɼ��� �������ο� ������.
			int succeedRatio = g_pOptionInfoManager->getRareUpgradeRatio( thirdOption, bFirstSucceed ) * ( pItemInfo->getUpgradeRatio() +( rand() %50) );
			succeedRatio += getPercentValue(succeedRatio,pMouseItem->getHeroOption());
			//int dice = rand() %10000;

			int dice = rand() % diceValue;
			//cout << "�ι�° �ɼ� : " << pSecondOptionInfo->getHName() << " ��æƮ Ȯ�� " << succeedRatio << endl;
			//dice =succeedRatio-1;
			if ( dice < succeedRatio )
			{
				//cout << "��æƮ ����" << endl;
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
			gcAddItemToItemVerify.setThirdOptionType( pItem->getOptionType() );
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
			succeedRatio += getPercentValue(succeedRatio,pMouseItem->getHeroOption());
			int dice = rand()%10000;

			//cout << "ù��° �ɼ� : " << pFirstOptionInfo->getHName() << " ��æƮ Ȯ�� " << succeedRatio << endl;

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
			// �ι�° �ɼ��� ��æƮ Ȯ���� ù��° �ɼ��� �������ο� ������.
			int succeedRatio = g_pOptionInfoManager->getRareUpgradeRatio( secondOption, bFirstSucceed ) * pItemInfo->getUpgradeRatio();
			succeedRatio += getPercentValue(succeedRatio,pMouseItem->getHeroOption());
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
						// ������ list�� reference�� ���� ���⿡�� �ɼ��� ���ŵ� �� �����Ƿ�
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
			succeedRatio += getPercentValue(succeedRatio,pMouseItem->getHeroOption());
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
			// �ι�° �ɼ��� ��æƮ Ȯ���� ù��° �ɼ��� �������ο� ������.
			int succeedRatio = g_pOptionInfoManager->getRareUpgradeRatio( secondOption, bFirstSucceed ) * pItemInfo->getUpgradeRatio();
			succeedRatio += getPercentValue(succeedRatio,pMouseItem->getHeroOption());
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

		// ��æƮ �ҷ��� �������� ���� �ɼ��� 2���� �ƴϰų�
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
			succeedRatio += getPercentValue(succeedRatio,pMouseItem->getHeroOption());
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
			// �ι�° �ɼ��� ��æƮ Ȯ���� ù��° �ɼ��� �������ο� ������.
			int succeedRatio = g_pOptionInfoManager->getRareUpgradeRatio( secondOption, bFirstSucceed ) * pItemInfo->getUpgradeRatio();
			succeedRatio += getPercentValue(succeedRatio,pMouseItem->getHeroOption());
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

		shiftValue -= 16;

		if ( bThreeUpgradePossible )
		{
			// ù��° �ɼ��� ��æƮ Ȯ���� ����� 2�� Ȯ���� ������.
			int succeedRatio = pThreeOptionInfo->getUpgradeSecondRatio() * pItemInfo->getUpgradeRatio();
			succeedRatio += getPercentValue(succeedRatio,pMouseItem->getHeroOption());
			int dice = rand()%10000;

			//cout << "ù��° �ɼ� : " << pFirstOptionInfo->getHName() << " ��æƮ Ȯ�� " << succeedRatio << endl;

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
				else if ( dice < noChangeRatio + downgradeRatio )
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
				else if ( dice < noChangeRatio + downgradeRatio )
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

		// �ɼ��� �������� ���� �Ұ��������� �ʴٰ� ����..
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
				succeedRatio += getPercentValue(succeedRatio,pMouseItem->getHeroOption());
			}
			else
			{
				// ���� ��æƮ ���۵�
				succeedRatio = pOptionInfo->getUpgradeRatio() * pItemInfo->getUpgradeRatio();
				succeedRatio += getPercentValue(succeedRatio,pMouseItem->getHeroOption());
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

		// �ɼ��� �������� ���� �Ұ��������� �ʴٰ� ����..
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
				succeedRatio += getPercentValue(succeedRatio,pMouseItem->getHeroOption());
			}
			else
			{
				// ���� ��æƮ ���۵�
				succeedRatio = pOptionInfo->getUpgradeRatio() * pItemInfo->getUpgradeRatio();
				succeedRatio += getPercentValue(succeedRatio,pMouseItem->getHeroOption());
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
				processUpgradeSetOptionType( pItem, currentOptionType, pOptionInfo );

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
					downgradeSetOptionType( pItem, currentOptionType, pOptionInfo );

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

			//SAFE_DELETE(pItem); 				// �޸𸮿��� ����


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

		// �� Ŭ������ ���� �� �ִ� �ɼ�Ŭ�����̰�..
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

		if ( pMouseItem->getEnchantLevel() != 0 && pMouseItem->getEnchantLevel() != pItem->getItemClass() )
		{
			GCAddItemToItemVerify gcResult;
			gcResult.setCode( ADD_ITEM_TO_ITEM_VERIFY_TRANS_IMPOSSIBLE );
			pGamePlayer->sendPacket(&gcResult);
			return;
		}

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);

		if(pMouseItem->getEnchantLevel() == 0){
			list<OptionType_t> optionTypeList;
			Item* pMouseItem2 = g_pItemFactoryManager->createItem( pMouseItem->getItemClass(), pMouseItem->getItemType(), optionTypeList );
			pMouseItem2->setEnchantLevel(pItem->getItemClass());
			pMouseItem2->setHeroOptionAttr(pItem->getItemType());

			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
			gcAddItemToItemVerify.setParameter( 0 );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );

			GCDeleteInventoryItem gcDeleteInventoryItem;
			gcDeleteInventoryItem.setObjectID(pItem->getObjectID());
			pGamePlayer->sendPacket(&gcDeleteInventoryItem);

			// �κ��丮���� �����Ѵ�.
			pPC->getInventory()->deleteItem(pItem->getObjectID());
			pItem->destroy();
			SAFE_DELETE(pItem);

			pPC->deleteItemFromExtraInventorySlot();
			pMouseItem->destroy();
			SAFE_DELETE(pMouseItem);
			cout << " ��������� ����.." << endl;

			_TPOINT pt;

			// ����ǿ��� ������ �̹� ����߱⶧���� �κ��丮�� �ڸ��� �ִ��� ���θ� �ľ��Ѵ�.
			if (!pPC->getInventory()->getEmptySlot(pMouseItem2, pt))
			{
			// ConditionHasInvenSpace ����ǰ� �ݵ�� �Բ� ��߸� �Ѵ�.
			throw Error("ActionCreateGetItem: ���� ConditionHasInvenSpace�� ���� ����. �κ��丮�� �ڸ�����.");
			}

			CoordInven_t X = pt.x;
			CoordInven_t Y = pt.y;

			cout << " ��������� ����..2" << endl;

			pPC->getZone()->getObjectRegistry().registerObject( pMouseItem2 );
			cout << " ��������� ����..3" << endl;
			pPC->getInventory()->addItem( X, Y, pMouseItem2 );
			cout << " ��������� ����..4" << endl;
			pMouseItem2->create( pPC->getName(), STORAGE_INVENTORY, 0, X, Y );
			cout << " ��������� ����..5" << endl;

			GCCreateItem gcCreateItem;
			makeGCCreateItem( &gcCreateItem, pMouseItem2, X, Y );
			pGamePlayer->sendPacket(&gcCreateItem);
		}else{
			pItem->setItemType(pMouseItem->getHeroOptionAttr());
			
			_TPOINT pt;

			// ����ǿ��� ������ �̹� ����߱⶧���� �κ��丮�� �ڸ��� �ִ��� ���θ� �ľ��Ѵ�.
			if (!pPC->getInventory()->getEmptySlot(pItem, pt))
			{
			// ConditionHasInvenSpace ����ǰ� �ݵ�� �Բ� ��߸� �Ѵ�.
			throw Error("ActionCreateGetItem: ���� ConditionHasInvenSpace�� ���� ����. �κ��丮�� �ڸ�����.");
			}

			char pField[80];
			sprintf(pField, "ItemType=%u", pItem->getItemType());
			pItem->tinysave(pField);

			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
			gcAddItemToItemVerify.setParameter( 0 );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );

			pPC->deleteItemFromExtraInventorySlot();
			pMouseItem->destroy();
			SAFE_DELETE(pMouseItem);
			cout << " ��������� ����.." << endl;

			GCDeleteInventoryItem gcDeleteInventoryItem;
			gcDeleteInventoryItem.setObjectID(pItem->getObjectID());
			pGamePlayer->sendPacket(&gcDeleteInventoryItem);

			CoordInven_t X = pt.x;
			CoordInven_t Y = pt.y;

			pPC->getInventory()->findItemOID( pItem->getObjectID(), X, Y );
			Assert( X != -1 );

			GCCreateItem gcCreateItem;
			makeGCCreateItem( &gcCreateItem, pItem, X, Y );
			pGamePlayer->sendPacket(&gcCreateItem);

		}

		__END_CATCH
	}
	void executeTransKit(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem) throw(Error)
	{
		__BEGIN_TRY

		GCAddItemToItemVerify gcResult;
		uint optionChange;

		ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( pItem->getItemClass(), pItem->getItemType() );
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
