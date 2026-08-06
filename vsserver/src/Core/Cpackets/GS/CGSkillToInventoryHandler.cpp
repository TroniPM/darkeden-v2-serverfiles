//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSkillToInventoryHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGSkillToInventory.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "SkillHandlerManager.h"
	#include "ZoneUtil.h"
	#include "VampireWingItem.h"
	#include "ItemInfo.h"
	#include "ItemInfoManager.h"

	#include "skill/Sniping.h"

	#include "Gpackets/GCSkillFailed1.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSkillToInventoryHandler::execute (CGSkillToInventory* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);	// by sigi

	if (pGamePlayer->getPlayerStatus() == GPS_NORMAL) 
	{
		Creature* pCreature = pGamePlayer->getCreature();
		Assert(pCreature != NULL);	// by sigi

		Zone* pZone = pCreature->getZone();
		Assert(pZone != NULL);
	
		SkillType_t SkillType = pPacket->getSkillType();

		// 완전 안전지대라면 기술 사용 불가. by sigi. 2002.11.14
		ZoneLevel_t ZoneLevel = pZone->getZoneLevel(pCreature->getX(), pCreature->getY());
		if (ZoneLevel & COMPLETE_SAFE_ZONE)
		{
			GCSkillFailed1 _GCSkillFailed1;
			_GCSkillFailed1.setSkillType(SkillType);
			pPlayer->sendPacket(&_GCSkillFailed1);

			return;
		}

		BYTE        X         = pPacket->getX();
		BYTE        Y         = pPacket->getY();
		BYTE        TX        = pPacket->getTargetX();
		BYTE        TY        = pPacket->getTargetY();

		disableFlags( pCreature, pZone, SkillType);

		if (pCreature->isSlayer()) 
		{
			Slayer*    pSlayer    = dynamic_cast<Slayer*>(pCreature);
			SkillSlot* pSkillSlot = pSlayer->hasSkill(SkillType);
			bool       bSuccess   = true;

			if (pSkillSlot == NULL) bSuccess = false;
			if ( SkillType == SKILL_INSTALL_MINE ) {
				bSuccess = true;
				TY = 0;
			} else {
				if (!isAbleToUseInventorySkill(pSlayer, X, Y, TX, TY)) bSuccess = false;
			}

			if (bSuccess)
			{
				SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SkillType);
				Assert(pSkillHandler != NULL);
   			 	pSkillHandler->execute(pSlayer, pPacket->getObjectID(), X, Y, TX, TY, pSkillSlot);
   			 }
             else
             {
                 GCSkillFailed1 _GCSkillFailed1;
				_GCSkillFailed1.setSkillType(SkillType);
                 pPlayer->sendPacket(&_GCSkillFailed1);
             }
		} 
		else if (pCreature->isVampire()) 
		{
			Vampire*          pVampire          = dynamic_cast<Vampire*>(pCreature);
			Inventory* pInventory = pVampire->getInventory();
			VampireSkillSlot* pVampireSkillSlot = pVampire->hasSkill(SkillType);
			bool              bSuccess          = true;

			// 인벤토리를 확인한다.
			// 특정 아이템일 경우 특수 이동 수단으로 변경처리해야 한다.
			// 선 컴파일후, 제작지원을 시작.
			Item* pItem = pInventory->getItemWithObjectID(pPacket->getObjectID());

			Assert(pItem != NULL);

			Item::ItemClass itemClass 	= pItem->getItemClass();
			ItemType_t 		itemtype 	= pItem->getItemType();

			if(itemClass == Item::ITEM_CLASS_VAMPIRE_ETC){
					pVampire->SetBatType(1);
					pVampire->setWingItemType(itemtype);
			}
			if(itemClass == Item::ITEM_CLASS_VAMPIREWING_ITEM){

				VampireWingItemInfo*	pInfo		= dynamic_cast<VampireWingItemInfo*>(g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType() ));
				if(pInfo != NULL ){
					pVampire->SetBatType(2);
					pVampire->setWingItemType(itemtype);
					pVampire->setWingColor(0);
					pVampire->setWingEffectColor(0);
				}
			}

			
			if (pVampireSkillSlot == NULL) bSuccess = false;
			if (!isAbleToUseInventorySkill(pVampire, X, Y, TX, TY)) bSuccess = false;

			if (bSuccess) 
			{
				SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SkillType);
				Assert(pSkillHandler != NULL);
   			 	pSkillHandler->execute(pVampire, pPacket->getObjectID(), X, Y, TX, TY, pVampireSkillSlot);
   			 }
             else
             {
                 GCSkillFailed1 _GCSkillFailed1;
				_GCSkillFailed1.setSkillType(SkillType);
                 pPlayer->sendPacket(&_GCSkillFailed1);
             }
		}
		else if (pCreature->isOusters()) 
		{
			Ousters*          pOusters          = dynamic_cast<Ousters*>(pCreature);
			OustersSkillSlot* pOustersSkillSlot = pOusters->hasSkill(SkillType);
			bool              bSuccess          = true;
			
			if (pOustersSkillSlot == NULL) bSuccess = false;
			if (!isAbleToUseInventorySkill(pOusters, X, Y, TX, TY)) bSuccess = false;

			if (bSuccess) 
			{
				SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SkillType);
				Assert(pSkillHandler != NULL);
   			 	pSkillHandler->execute(pOusters, pPacket->getObjectID(), X, Y, TX, TY, pOustersSkillSlot);
   			 }
             else
             {
                 GCSkillFailed1 _GCSkillFailed1;
				_GCSkillFailed1.setSkillType(SkillType);
                 pPlayer->sendPacket(&_GCSkillFailed1);
             }
		}
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

