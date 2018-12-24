//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestWebMarketHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////
#include "CGRequestWebMarket.h"

	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "DB.h"
	#include "Properties.h"
	#include "GoodsInventory.h"
	#include "Gpackets/GCGoodsList.h"
	#include "Gpackets/GCShowWebMarket.h"
	#include "Zone.h"
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGRequestWebMarketHandler::execute (CGRequestWebMarket* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY
		
	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

	switch ( pPacket->getCode() )
	{
		case CGRequestWebMarket::REQUEST_WEB_MARKET:
			{
				// 키 생성
				DWORD key = rand() << ( time(0) % 10 ) + rand() >> ( time(0) % 10 );

				cout << "Key: " << key << endl;

				// 키 저장
				/*Statement* pStmt = NULL;
				Result* pResult = NULL;
				
				BEGIN_DB
				{
					pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
					pResult = pStmt->executeQuery( "UPDATE WebMarketKey SET `Key` = %u WHERE PlayerID = '%s'", key, pGamePlayer->getID().c_str() );

					if ( pStmt->getAffectedRowCount() == 0 )
					{
						pStmt->executeQuery( "INSERT INTO WebMarketKey VALUES( '%s', %u )", pGamePlayer->getID().c_str(), key );
					}
				}
				END_DB( pStmt )*/

				// 월드ID 불러오기
				static int WorldID = g_pConfig->getPropertyInt("Dimension") * 3 + g_pConfig->getPropertyInt("WorldID");

				// 패킷 생성
				GCShowWebMarket gcShowWebMarket;
				gcShowWebMarket.setPlayerID( pGamePlayer->getID() );
				gcShowWebMarket.setName( pPC->getName() );
				gcShowWebMarket.setWorldID( WorldID );
				gcShowWebMarket.setKey( key );

				// 패킷 보내기
				pGamePlayer->sendPacket( &gcShowWebMarket );
			}
			break;

		case CGRequestWebMarket::REQUEST_BUY_COMPLETE:
			{
				// GoodsObject 를 새로 로딩한다
				pPC->loadGoods();
			}
			break;

		case CGRequestWebMarket::REQUEST_GOODS_LIST:
		{
				pPC->loadGoods();
				pPC->registerGoodsInventory( pPC->getZone()->getObjectRegistry() );

				GoodsInventory::ListItem& iList = pPC->getGoodsInventory()->getGoods();

				GoodsInventory::ListItemItr itr = iList.begin();
				GoodsInventory::ListItemItr endItr = iList.end();

				int count = 0;
				GCGoodsList gcGoodsList;

				for ( ; itr != endItr ; ++itr )
				{
					if ( count++ >= 20 ) break;

					Item* pItem = (*itr).m_pItem;
		
					GoodsInfo* pGI = new GoodsInfo;
					pGI->objectID = pItem->getObjectID();
					pGI->itemClass = (BYTE)pItem->getItemClass();
					pGI->itemType = pItem->getItemType();
					pGI->grade = pItem->getGrade();
					pGI->optionType = pItem->getOptionTypeList();
					pGI->num = pItem->getNum();
					pGI->silver = pItem->getSilver();
					pGI->enchantLevel = pItem->getEnchantLevel();
					pGI->HeroOption = pItem->getHeroOption();
					pGI->HeroOptionAttr = pItem->getHeroOptionAttr();
						if ( pItem->isTimeLimitItem() )
						{
							if ( pItem->getHour() == 0 ) pGI->timeLimit = 1;
							else pGI->timeLimit = pItem->getHour() * 3600;
						}
						else
						pGI->timeLimit = 0;

					gcGoodsList.addGoodsInfo( pGI );
				}
//		cout << pGI->toString() << endl;

			pGamePlayer->sendPacket( &gcGoodsList );
		}
			break;
		default:
			break;
	}

	__END_CATCH	
}

