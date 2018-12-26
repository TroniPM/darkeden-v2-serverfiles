//////////////////////////////////////////////////////////////////////////////
// Filename    : CGDissectionCorpseHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGDissectionCorpse.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Corpse.h"
	#include "Relic.h"
	#include "BloodBible.h"
	#include "MonsterCorpse.h"
	#include "SlayerCorpse.h"
	#include "AlignmentManager.h"
	#include "PCSlayerInfo3.h"
	#include "PCVampireInfo3.h"
	#include "VampireCorpse.h"
	#include "PCVampireInfo3.h"
	#include "PCOustersInfo3.h"
	#include "OustersCorpse.h"
	#include "PCOustersInfo3.h"
	#include "Effect.h"
	#include "EffectRelicTable.h"
	#include "EffectPrecedence.h"
	#include "EffectHasSlayerRelic.h"
	#include "EffectHasVampireRelic.h"
	#include "ZoneUtil.h"
	#include "ItemUtil.h"
	#include "RelicUtil.h"
	#include "CreatureUtil.h"
    #include "DB.h"
	#include "CombatInfoManager.h"
	#include "ZoneGroupManager.h"
	#include "ItemInfoManager.h"
	#include "UniqueItemManager.h"
	#include "war/WarSystem.h"
	#include "ShrineInfoManager.h"
	#include "CastleInfoManager.h"
	#include "CastleShrineInfoManager.h"
	#include "StringPool.h"
	#include "PacketUtil.h"
	#include "MonsterInfo.h"
	#include "PetUtil.h"
	#include "PetInfo.h"

	#include "ctf/FlagManager.h"
	#include "EffectFlagInsert.h"
	#include "LevelWarManager.h"
	#include "GQuestManager.h"
	#include "Party.h"

	#include <stdio.h>

	#include "Gpackets/GCRemoveCorpseHead.h"
	#include "Gpackets/GCSystemMessage.h"
	#include "Gpackets/GCCreateItem.h"
	#include "Gpackets/GCAddEffect.h"
	#include "Gpackets/GCRemoveEffect.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGDissectionCorpseHandler::execute (CGDissectionCorpse* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	try 
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

		if (pGamePlayer->getPlayerStatus() != GPS_NORMAL) return;

		Creature*   pCreature = pGamePlayer->getCreature();
		Zone*       pZone     = pCreature->getZone();
		ZoneCoord_t ZoneX     = pPacket->getX();
		ZoneCoord_t ZoneY     = pPacket->getY();

		// �ٿ�带 �Ѿ���� �ʴ��� üũ�Ѵ�.
		if (!isValidZoneCoord(pZone, ZoneX, ZoneY)) 
		{
			return;
		}

		Tile& rTile = pZone->getTile(ZoneX , ZoneY);
        Item* pItem = rTile.getItem();

		// Coma���¶�� ���� �Ұ�. by sigi. 2002.12.10
        // ���� ���� ���¶�� ����
        if (pCreature->isFlag(Effect::EFFECT_CLASS_COMA)
       	 	|| pCreature->isFlag(Effect::EFFECT_CLASS_PARALYZE)
			|| pCreature->isVampire() && pCreature->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT))
           return;
		
		// �����̾��� ��� ������� Ÿ�� ������ ������ ���� �Ұ� by sigi
		if (pCreature->isSlayer())
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
			if (pSlayer->hasRideMotorcycle())
			{
				return;
			}
		}

		// �ƿ콺������ ��� ���� Ÿ�� ������ ���� �Ұ� by DEW
		if (pCreature->isOusters())
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
			if (pOusters->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH))
			{
				return;
			}
		}

		// �ٴڿ� �������� ������ ����
		// ������Ʈ ���̵� ��ġ���� ������ ����
		// �ٴڿ� �ִ� �������� ��ü�� �ƴϸ� ����
		if (pItem == NULL
			|| pItem->getObjectID() != pPacket->getObjectID()
			|| pItem->getItemClass() != Item::ITEM_CLASS_CORPSE)
		{
			return;
		}

		bool bSlayerRelicTable = pItem->isFlag(Effect::EFFECT_CLASS_SLAYER_RELIC_TABLE);
		bool bVampireRelicTable = pItem->isFlag(Effect::EFFECT_CLASS_VAMPIRE_RELIC_TABLE);

		// �����̾ �����̾��� ������������ Ŭ���� �� ����,
		// �����̾ �����̾��� ������������ Ŭ���� �� ����.
		if ( (pCreature->isSlayer() && bSlayerRelicTable)
			|| (pCreature->isVampire() && bVampireRelicTable) )
		{
			return;
		}

		// ������ ��� �������� �ƴ϶�� Ŭ���� �� ����.
		// ��ȣ ������ ��� ������������ Ŭ���� �� ����.
		if ( pItem->getItemType() == MONSTER_CORPSE )
		{
			MonsterCorpse* pMonsterCorpse = dynamic_cast<MonsterCorpse*>(pItem);
			if ( pMonsterCorpse->getTreasureCount() > 200 )
			{
				// ����Ʈ�� ��ü. ���� ��¥�� 200�� ���õǴ� ���ʹ� ������ --;
				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
				pPC->getGQuestManager()->touchWayPoint(pMonsterCorpse);
				return;
			}

			if ( g_pFlagManager->isFlagPole( pMonsterCorpse ) )
			{
				if ( !g_pFlagManager->hasFlagWar() ) return;
			}
			else if (
					pZone->getLevelWarManager() != NULL &&
					pZone->getLevelWarManager()->isSafe( pMonsterCorpse ) )
			{
				if ( !pZone->getLevelWarManager()->hasWar() ) return;
				else if ( ( pCreature->isSlayer() && pZone->getLevelWarManager()->getSafeIndex( pMonsterCorpse ) == 0 )
						 || ( pCreature->isVampire() && pZone->getLevelWarManager()->getSafeIndex( pMonsterCorpse ) == 1 )
						 || ( pCreature->isOusters() && pZone->getLevelWarManager()->getSafeIndex( pMonsterCorpse ) == 2 ) )
				{
					return;
				}
			}
			else if ( pMonsterCorpse->isShrine() )
			{
				// ��ȣ���� �ɷ������� �� ������.
				if ( pMonsterCorpse->isFlag( Effect::EFFECT_CLASS_SHRINE_SHIELD ) )
					return;
					
				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
				Assert( pPC );

				ZoneID_t 	castleZoneID;
				bool		isCastle;

				bool hasWar = false;

				isCastle = g_pCastleInfoManager->getCastleZoneID( pZone->getZoneID() , castleZoneID);

				if ( isCastle && g_pWarSystem->hasCastleActiveWar( castleZoneID ) )
				{
					// ��������� ��� ó��
					// if ( pItem->getItemClass() != Item::ITEM_CLASS_CASTLE_SYMBOL ) return;

					// �������� ������� ��� Ŭ���� �� ����.
#ifndef __OLD_GUILD_WAR__
#else
					if ( g_pCastleShrineInfoManager->isDefenderOfGuardShrine( pPC, pMonsterCorpse ) )
						return;
#endif

					CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( castleZoneID );
					if ( pCastleInfo->getRace() != pPC->getRace() )
						return;

					hasWar = true;
				}

				if ( g_pWarSystem->hasActiveRaceWar() )
				{
					// ������ ������ ��� ó��
					// if ( pItem->getItemClass() != Item::ITEM_CLASS_BLOOD_BIBLE ) return;

					// �������� ������� ��� Ŭ���� �� ����.
					if ( g_pShrineInfoManager->isDefenderOfGuardShrine( pPC, pMonsterCorpse ) )
						return;

					hasWar = true;
				}

				// ������ �ϰ͵� ������ ���ܿ��� �ϰ͵� �� ������.
				if (!hasWar)
				{
					return;
				}
			}
		}

		// �̱��� �Դٸ�, ����� ������ ������������ Ŭ���� ����̴�.
		// �� ���, ���� EffectRelic�� ��ŭ ���� �ִ��� üũ�ؾ� �Ѵ�.
		EffectRelicTable* pRelicTableEffect = NULL;

		// ���� ������ ������ ���� �پ��ִ� Effect�� ���´�.
		if (bSlayerRelicTable)
		{
			pRelicTableEffect = dynamic_cast<EffectRelicTable*>(
								pItem->getEffectManager().findEffect(Effect::EFFECT_CLASS_SLAYER_RELIC_TABLE));
		}
		else if (bVampireRelicTable)
		{
			pRelicTableEffect = dynamic_cast<EffectRelicTable*>(
								pItem->getEffectManager().findEffect(Effect::EFFECT_CLASS_VAMPIRE_RELIC_TABLE));
		}

		// ���� �����뿡�� �������� ��� �� �ִ� �ð��ΰ�?
		// SafeTime�� ���� �ʾ����� �ȵȴ�.
		// LockTime ������ �ȵȴ�.
		if (pRelicTableEffect!=NULL
			&& (!pRelicTableEffect->isSafeTime()
				|| pRelicTableEffect->isLockTime()))
		{
			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CANNOT_TAKE_RELIC_NOW ) );

			pGamePlayer->sendPacket( &gcSystemMessage );
			return;
		}

		// ������ üũ �ؾ� �Ѵ�.
		if (pItem->getItemType() != MONSTER_CORPSE) 
		{
			if ( pPacket->isPet() ) return;
			if ( !pZone->isPKZone() )
			{
				if (pItem->getItemType() == SLAYER_CORPSE && pCreature->isSlayer()) 
				{
					SlayerCorpse* pSlayerCorpse = dynamic_cast<SlayerCorpse*>(pItem);

					PCSlayerInfo3 & rPCSlayerInfo = pSlayerCorpse->getSlayerInfo();

					// �ڱ� ��ü�� �ƴ϶��
					if (rPCSlayerInfo.getName() != pCreature->getName()) 
					{
						// �������� ��ü�� ��ȣ���� ���Ѵ�....
						if (g_pAlignmentManager->getAlignmentType(rPCSlayerInfo.getAlignment()) >= NEUTRAL) 
						{
							Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

							// ������ -500 ��������~
							Alignment_t NewAlignment = max(-10000 , pSlayer->getAlignment() - 500);

							pSlayer->setAlignment(NewAlignment);
							GCModifyInformation gcModifyInformation;
							gcModifyInformation.addLongData(MODIFY_ALIGNMENT, NewAlignment);
							pGamePlayer->sendPacket(&gcModifyInformation);
						}
					}
				} 
				else if (pItem->getItemType() == VAMPIRE_CORPSE && pCreature->isVampire()) 
				{
					PCVampireInfo3 & rPCVampireInfo = dynamic_cast<VampireCorpse*>(pItem)->getVampireInfo();

					// �ڱ� ��ü�� �ƴ϶��
					if (rPCVampireInfo.getName() != pCreature->getName()) 
					{
						// �������� ��ü�� ��ȣ���� ���Ѵ�....
						if (g_pAlignmentManager->getAlignmentType(rPCVampireInfo.getAlignment()) >= NEUTRAL) 
						{
							Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

							// ������ -500 ��������~
							Alignment_t NewAlignment = max(-10000 , pVampire->getAlignment() - 500);

							pVampire->setAlignment(NewAlignment);
							GCModifyInformation gcModifyInformation;
							gcModifyInformation.addLongData(MODIFY_ALIGNMENT, NewAlignment);
							pGamePlayer->sendPacket(&gcModifyInformation);
						}
					}
				}
				else if (pItem->getItemType() == OUSTERS_CORPSE && pCreature->isOusters()) 
				{
					PCOustersInfo3 & rPCOustersInfo = dynamic_cast<OustersCorpse*>(pItem)->getOustersInfo();

					// �ڱ� ��ü�� �ƴ϶��
					if (rPCOustersInfo.getName() != pCreature->getName()) 
					{
						// �������� ��ü�� ��ȣ���� ���Ѵ�....
						if (g_pAlignmentManager->getAlignmentType(rPCOustersInfo.getAlignment()) >= NEUTRAL) 
						{
							Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

							// ������ -500 ��������~
							Alignment_t NewAlignment = max(-10000 , pOusters->getAlignment() - 500);

							pOusters->setAlignment(NewAlignment);
							GCModifyInformation gcModifyInformation;
							gcModifyInformation.addLongData(MODIFY_ALIGNMENT, NewAlignment);
							pGamePlayer->sendPacket(&gcModifyInformation);
						}
					}
				}
			}
		}
		else
		{
			MonsterCorpse* pMonsterCorpse = dynamic_cast<MonsterCorpse*>(pItem);
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			Assert( pPC != NULL );

			if ( pPacket->isPet() )
			{
				if ( pPC->getPetInfo() == NULL ) return; //(|| pMonsterCorpse->isNextTreasureHead() ) return;
			}

			if ( pMonsterCorpse != NULL && g_pFlagManager->isFlagPole( pMonsterCorpse ) )
			{
				if ( !g_pFlagManager->hasFlagWar() ) return;
				// ���� �����̸� �� �̴´�..
				if ( g_pFlagManager->getFlagPoleRace( pMonsterCorpse ) == pPC->getRace() )
					return;

				TPOINT tp;
				if ( pPC->isFlag( Effect::EFFECT_CLASS_HAS_FLAG ) ) return;
				if ( !pPC->getInventory()->getEmptySlot( 1, 2, tp ) ) return;

				if (
					   pPC->isFlag(Effect::EFFECT_CLASS_CASKET)
					|| pPC->isDead()
					|| pPC->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT)
					|| pPC->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH)
					|| pPC->isFlag(Effect::EFFECT_CLASS_TENDRIL)
					|| pPC->isFlag(Effect::EFFECT_CLASS_BLOCK_HEAD)
				) return;

				if (pPC->isSlayer())
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
					if (pSlayer->hasRideMotorcycle()) return;
				}

				if ( pPC->isFlag(Effect::EFFECT_CLASS_HIDE)
					|| pPC->isFlag(Effect::EFFECT_CLASS_INVISIBILITY)
					|| pPC->isFlag(Effect::EFFECT_CLASS_FADE_OUT)
					|| pPC->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF)
					|| pPC->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT)
					|| pPC->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE)
					|| pPC->isFlag(Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL) ) return;
			}
//			else if (
//					pZone->getLevelWarManager() != NULL &&
//					pZone->getLevelWarManager()->isSafe( pMonsterCorpse ) )
//			{
//				if ( !pZone->getLevelWarManager()->hasWar() ) return;
//			}
		}

		Corpse* pCorpse = dynamic_cast<Corpse*>(pItem);
		bool bDissectAll = false;

		// ��ü�� �������� 3�� ���� �� ���� �� ������ �� ���� �ٻǹٳ���. 
		// ���� �̾Ƴ��� �������� �ѹ��� �� �������´�.
		// 2003.1.14  by bezz, Sequoia, sigi
		if ( pCorpse->getTreasureCount() > 3 || pPacket->isPet() )
			bDissectAll = true;

		int treasureCount = 0;
		ObjectID_t PetOID = 0;

		if ( pPacket->isPet() ) PetOID = pCreature->getObjectID();

		do // while ( bDissectAll );
		{
			if ( pPacket->isPet() && pCorpse->getItemType() == MONSTER_CORPSE )
			{
				MonsterCorpse* pMonsterCorpse = dynamic_cast<MonsterCorpse*>(pItem);
				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
				PetInfo* pPetInfo = pPC->getPetInfo();

				if ( pPetInfo == NULL ) break;
				if ( pMonsterCorpse->isNextTreasureHead() && pPetInfo->canCutHead()==0 ) break;
			}

			Item* pTreasure = pCorpse->getTreasure();

			if (pTreasure == NULL)
				break;

			if ( pPacket->isPet() ) pTreasure->setFlag( Effect::EFFECT_CLASS_PET_DISSECT );

			////////////////////////////////////////////////////////////////
			// 2002�� ��̳� �̺�Ʈ
			// ������ �������� �������� �Կ������� ��ȯ�ȴ�.
			// �׷��Ƿ� ������ ���� ����(Ʈ���Ǻ��Ͼ�7��, �ж�Ű�� 3��)��
			// �Ѱ� ���� �� ����.
			// ���� ������ �������� ������ ���,
			// �������� ���ڸ� �ľ��ؼ�, ���� ���� �̻��̸� ������ �ʵ��� �Ѵ�.
			
			if (pTreasure->getItemClass() == Item::ITEM_CLASS_EVENT_STAR
					&& pTreasure->getItemType() == 0)
			{
				cout << "������ ����" << endl;
				Statement* pStmt = NULL;
				Result*    pResult = NULL;

				try
				{
					pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
					pResult = pStmt->executeQuery("SELECT ifnull(sum(Num),0) FROM EventStarObject WHERE ItemType=0;");

					if(pResult->getRowCount() != 1)
					{
						SAFE_DELETE(pStmt);
						throw ProtocolException("Fail to load data from DB");
					}

					if(pResult->next())
					{
						int BlackStarNumber = pResult->getInt(1);
						if(BlackStarNumber >= 7)
							cout << "�������� 10�� �Ѿ����ϴ�" << endl;
						else
						{
							(pZone->getObjectRegistry()).registerObject(pTreasure);

							TPOINT pt = pZone->addItem(pTreasure, ZoneX, ZoneY);
							if (pt.x != -1) 
							{
								if (pItem->getItemType() == MONSTER_CORPSE)
								{
									MonsterCorpse* pMonsterCorpse = dynamic_cast<MonsterCorpse*>(pItem);

									// ���� ��ü���� ���� �������̶�� �켱�� ����Ʈ�� �ٿ��־�� �Ѵ�.
									// Ȥ�ö� ������ ����Ʈ�� �ִٸ� �������ְ�,
									// ������ ����Ʈ�� ���Ѵ�.
									const string& 	HostName 	= pMonsterCorpse->getHostName();
									int 			HostPartyID	= pMonsterCorpse->getHostPartyID();

									bool			isPrecedence = true;
									if ( pTreasure->getItemClass() == Item::ITEM_CLASS_EVENT_ITEM && pTreasure->getItemType() == 3 )
									{
										isPrecedence = false;
									}

									// by sigi. 2002.12.12
									if (isPrecedence && (!HostName.empty() || HostPartyID!=0))
									{
										EffectPrecedence* pEffectPrecedence = new EffectPrecedence(pTreasure);
										pEffectPrecedence->setDeadline(100);
										pEffectPrecedence->setHostName( HostName );
										pEffectPrecedence->setHostPartyID( HostPartyID );
										EffectManager& rEffectManager = pTreasure->getEffectManager();
										rEffectManager.deleteEffect(Effect::EFFECT_CLASS_PRECEDENCE);
										rEffectManager.addEffect(pEffectPrecedence);
										pTreasure->setFlag(Effect::EFFECT_CLASS_PRECEDENCE);
									}

									// ���� �ذ��̶�� �������ٰ� ��ü���� ���� �����϶�� ��Ŷ�� �����־�� �Ѵ�.
									if (pTreasure->getItemClass() == Item::ITEM_CLASS_SKULL)
									{
										// �� �ڸ���~~ by sigi
										pMonsterCorpse->removeHead();

										GCRemoveCorpseHead _GCRemoveCorpseHead;
										_GCRemoveCorpseHead.setObjectID(pItem->getObjectID());
										//pZone->broadcastPacket(pt.x, pt.y, &_GCRemoveCorpseHead);
										pZone->broadcastPacket(ZoneX, ZoneY, &_GCRemoveCorpseHead); // ���� ��ü ��ǥ by sigi

										if ( pCreature->getPartyID() != 0 && HostPartyID == pCreature->getPartyID() )
										{
											Party* pParty = pCreature->getLocalPartyManager()->getParty( pCreature->getPartyID() );
											if ( pParty != NULL )
											{
												pParty->dissectCorpse( pCreature, pMonsterCorpse );
											}
										}
									}
								}

								// ������ ItemID�� �״�� �����Ѵ�.
								// ItemID�� 0�̸�.. create()�Ҷ� �ٽ� ItemID�� �޴´�.
								// by sigi. 2002.10.28
								pTreasure->create("", STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y, pTreasure->getItemID());
							}
							else 
							{
								SAFE_DELETE(pTreasure);
							}
						}
					}
					SAFE_DELETE(pStmt);
				} 
				catch(SQLQueryException & sqe)
				{
					SAFE_DELETE(pStmt);
					throw Error(sqe.toString());
				}
			}
			else if ( pTreasure->isFlagItem() )
			{
				// ����� �ٷ� �κ��丮�� �־��ش�.
				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
				Assert( pPC != NULL );

				Inventory* pInventory = pPC->getInventory();
				Assert( pInventory != NULL );

				TPOINT tp;

				if ( !pInventory->getEmptySlot( pTreasure, tp ) || pCorpse->getItemType() != MONSTER_CORPSE ||
						!g_pFlagManager->getFlag( pPC, dynamic_cast<MonsterCorpse*>(pCorpse) ) )
				{
					// ���� �ִ´�.
					pCorpse->addTreasure( pTreasure );

					pCorpse->setFlag( Effect::EFFECT_CLASS_FLAG_INSERT );
					EffectFlagInsert* pFlagEffect = new EffectFlagInsert(pCorpse);
					pCorpse->getEffectManager().addEffect( pFlagEffect );

					GCAddEffect gcAddEffect;
					gcAddEffect.setEffectID( Effect::EFFECT_CLASS_FLAG_INSERT );
					gcAddEffect.setObjectID( pCorpse->getObjectID() );
					gcAddEffect.setDuration( 65535 );

					pCorpse->getZone()->broadcastPacket( pCorpse->getX(), pCorpse->getY(), &gcAddEffect );

					continue;
				}

				pInventory->addItem( pTreasure, tp );

				char pField[80];
				sprintf(pField, "OwnerID='%s', Storage=%d, X=%d, Y=%d", pPC->getName().c_str(), STORAGE_INVENTORY, tp.x, tp.y);
				pTreasure->tinysave(pField);
				addSimpleCreatureEffect( pPC, Effect::EFFECT_CLASS_HAS_FLAG );

				GCCreateItem gcCreateItem;

				makeGCCreateItem( &gcCreateItem, pTreasure, tp.x, tp.y );
				pPC->getPlayer()->sendPacket( &gcCreateItem );
			}
			else
			{
				(pZone->getObjectRegistry()).registerObject(pTreasure);

				TPOINT pt = pZone->addItem(pTreasure, ZoneX, ZoneY, true, 0, PetOID);
				if (pt.x != -1) 
				{
					if (pItem->getItemType() == MONSTER_CORPSE)
					{
						MonsterCorpse* pMonsterCorpse = dynamic_cast<MonsterCorpse*>(pItem);

						if (dissectionRelicItem( pCorpse, pTreasure, pt ))
						{
							// pTreasure�� relicItem�� ���
						}

						treasureCount++;

						if (
							pZone->getLevelWarManager() != NULL &&
							pZone->getLevelWarManager()->isSafe( pMonsterCorpse ) )
						{
							Effect* pEffect = pMonsterCorpse->getEffectManager().findEffect( Effect::EFFECT_CLASS_KEEP_SWEEPER );
							if ( pEffect != NULL )
							{
								pEffect->setDeadline(0);

								GCRemoveEffect gcRE;
								gcRE.setObjectID( pMonsterCorpse->getObjectID() );
								gcRE.addEffectList( pEffect->getSendEffectClass() );

								pZone->broadcastPacket( pMonsterCorpse->getX(), pMonsterCorpse->getY(), &gcRE );
							}

							// ������ ���� �ѷ��ش�.
							char safeRace[15];
							if ( pZone->getLevelWarManager()->getSafeIndex( pMonsterCorpse ) == 0 )
							{
								sprintf( safeRace, g_pStringPool->c_str( STRID_SLAYER ) );
							}
							else if ( pZone->getLevelWarManager()->getSafeIndex( pMonsterCorpse ) == 1 )
							{
								sprintf( safeRace, g_pStringPool->c_str( STRID_VAMPIRE ) );
							}
							else if ( pZone->getLevelWarManager()->getSafeIndex( pMonsterCorpse ) == 2 )
							{
								sprintf( safeRace, g_pStringPool->c_str( STRID_OUSTERS ) );
							}
							else if ( pZone->getLevelWarManager()->getSafeIndex( pMonsterCorpse ) == 3 )
							{
								sprintf( safeRace, g_pStringPool->c_str( STRID_CENTER ) );
							}
							else 
							{
								Assert(false);
							}

							char race[15];
							if ( pCreature->isSlayer() )
							{
								sprintf( race, g_pStringPool->c_str( STRID_SLAYER ) );
							}
							else if ( pCreature->isVampire() )
							{
								sprintf( race, g_pStringPool->c_str( STRID_VAMPIRE ) );
							}
							else if ( pCreature->isOusters() )
							{
								sprintf( race, g_pStringPool->c_str( STRID_OUSTERS ) );
							}
							else
							{
								Assert(false);
							}

							const SweeperInfo* pSweeperInfo = dynamic_cast<SweeperInfo*>(g_pSweeperInfoManager->getItemInfo(pTreasure->getItemType()));

							char msg[100];
							sprintf( msg , g_pStringPool->c_str( STRID_PULL_OUT_SWEEPER ) ,
												safeRace,
												pSweeperInfo->getName().c_str(),
												pCreature->getName().c_str(),
												race
								   				);
							GCSystemMessage gcSystemMessage;
							gcSystemMessage.setMessage( msg );
							pZone->broadcastPacket( &gcSystemMessage );
						}

						// ���� ��ü���� ���� �������̶�� �켱�� ����Ʈ�� �ٿ��־�� �Ѵ�.
						// Ȥ�ö� ������ ����Ʈ�� �ִٸ� �������ְ�,
						// ������ ����Ʈ�� ���Ѵ�.
						// 2003.2.28 ������ ����Ʈ�� �ִٸ� �׳� �д�. ��ü�� �� �ٴڿ� �߰��� ��
						// �ٴڿ� �ִ� �������� �� ��쿡 �켱�� ����Ʈ�� ������ �ʱ� ����
						if (!bSlayerRelicTable && !bVampireRelicTable)
						{
							const string& 	HostName 	= pMonsterCorpse->getHostName();
							int 			HostPartyID	= pMonsterCorpse->getHostPartyID();

							// by sigi. 2002.12.12
							if ( 
								(!HostName.empty() || HostPartyID!=0)
							// by Sequoia. 2003. 2.28.
							&&	!pTreasure->isFlag(Effect::EFFECT_CLASS_PRECEDENCE)
							)
							{
								EffectPrecedence* pEffectPrecedence = new EffectPrecedence(pTreasure);
								if ( !pTreasure->isQuestItem() )
								{
									// ����Ʈ �������� ��Ƽ���� �� �ݴ´�.
									pEffectPrecedence->setDeadline(100);
									pEffectPrecedence->setHostPartyID( HostPartyID );
									pEffectPrecedence->setHostName( HostName );
								}
								else
								{
									// ����Ʈ �������� ������������ �켱���� �� ��������.
									pEffectPrecedence->setDeadline(999999);
									pEffectPrecedence->setHostName( pMonsterCorpse->getQuestHostName() );
								}
								EffectManager& rEffectManager = pTreasure->getEffectManager();
								rEffectManager.deleteEffect(Effect::EFFECT_CLASS_PRECEDENCE);
								rEffectManager.addEffect(pEffectPrecedence);
								pTreasure->setFlag(Effect::EFFECT_CLASS_PRECEDENCE);
							}
						}

						// ���� �ذ��̶�� �������ٰ� ��ü���� ���� �����϶�� ��Ŷ�� �����־�� �Ѵ�.
						if (pTreasure->getItemClass() == Item::ITEM_CLASS_SKULL)
						{
							// �� �ڸ���~~ by sigi
							pMonsterCorpse->removeHead();

							GCRemoveCorpseHead _GCRemoveCorpseHead;
							_GCRemoveCorpseHead.setObjectID(pItem->getObjectID());
							//pZone->broadcastPacket(pt.x, pt.y, &_GCRemoveCorpseHead);
							pZone->broadcastPacket(ZoneX, ZoneY, &_GCRemoveCorpseHead); // ���� ��ü ��ǥ by sigi

							if ( pCreature->getPartyID() != 0 && pMonsterCorpse->getHostPartyID() == pCreature->getPartyID() )
							{
								Party* pParty = pCreature->getLocalPartyManager()->getParty( pCreature->getPartyID() );
								if ( pParty != NULL )
								{
									pParty->dissectCorpse( pCreature, pMonsterCorpse );
								}
							}
						}
					}

					// DB�� �����Ѵ�.
					saveDissectionItem( pCreature, pTreasure, pt.x, pt.y );
				}
				else 
				{
					SAFE_DELETE(pTreasure);
				}
			}
		}
		while ( bDissectAll );

		if (pItem->getItemType() == MONSTER_CORPSE)
		{
			MonsterCorpse* pMonsterCorpse = dynamic_cast<MonsterCorpse*>(pItem);
			// �� ����ġ ����
			if ( pPacket->isPet() && treasureCount != 0 )
			{
				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
				GCModifyInformation gcMI;
				PetExp_t exp = computePetExp( getPCLevel( pPC ), g_pMonsterInfoManager->getMonsterInfo( pMonsterCorpse->getMonsterType() )->getLevel(), pPC->getPetInfo(), pGamePlayer );
				if( pCreature->isFlag(Effect::EFFECT_CLASS_PET_EXP1)) exp *=3;
				if ( !increasePetExp( pPC->getPetInfo(), exp, &gcMI ) )
				{
//					cout << "����ġ�� �ٲ����� : " << gcMI.toString() << endl;
					pGamePlayer->sendPacket( &gcMI );
				}
				else
				{
//					cout << "�������� �ߴ��" << endl;
					sendPetInfo( pGamePlayer, true );
				}

				addOlympicStat( pPC, 8, exp );
			}
		}
	} 
	catch (Throwable & t) 
	{
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}
