//////////////////////////////////////////////////////////////////////////////
// Filename    : CGReloadFromInventoryHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGReloadFromInventory.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "Slayer.h"
	#include "Inventory.h"
	#include "Item.h"
	#include "ItemUtil.h"
	#include "ItemInfo.h"
	#include "ItemInfoManager.h"
	#include "EffectManager.h"
	#include "EffectReloadTimer.h"

	#include "Gpackets/GCCannotUse.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGReloadFromInventoryHandler::execute (CGReloadFromInventory* pPacket , Player* pPlayer)
	
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	try 
	{
		GamePlayer*  pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
		Creature*    pCreature   = pGamePlayer->getCreature();

		Assert(pCreature->isSlayer());

		Slayer*      pSlayer     = dynamic_cast<Slayer*>(pCreature);
		Item*        pArmsItem   = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		ObjectID_t   ItemObjectID;
		CoordInven_t x, y;
		bool         Success     = false;
		Item*        pItem       = NULL;
		Inventory*   pInventory  = NULL;

		if (pArmsItem != NULL) 
		{
			if (isArmsWeapon(pArmsItem))
			{
				pInventory = pSlayer->getInventory();
				x          = pPacket->getX();
				y          = pPacket->getY();
				if  (x>9 || y>5) {
					filelog("InventoryError.log","X,Y wrong!Player Name [%s]",pSlayer->getName().c_str());
					x=9;
					y=5;
				}
				pItem      = pInventory->getItem(x, y);

				//Assert(pItem != NULL);
				if (pItem == NULL)
				{
					GCCannotUse _GCCannotUse;
					_GCCannotUse.setObjectID(pPacket->getObjectID());
					pPlayer->sendPacket(&_GCCannotUse);
					return;
				}
		
				// �κ��丮 ������ �ִ� �������� Object�� �޴´�.
				ItemObjectID = pItem->getObjectID();
		
				if (ItemObjectID != pPacket->getObjectID())
				{
					GCCannotUse _GCCannotUse;
					_GCCannotUse.setObjectID(pPacket->getObjectID());
					pPlayer->sendPacket(&_GCCannotUse);
					return;
				}

				SkillSlot*	pVivid = pSlayer->getSkill( SKILL_VIVID_MAGAZINE );
				bool		hasVivid = (pVivid != NULL) && pVivid->canUse();

				if (isSuitableMagazine(pArmsItem, pItem, hasVivid)) Success = true;
			}
		} 

		// reload delay�� �����Ƿ� effect�� ��� ��Ų��.
		EffectManager* pEffectManager = pSlayer->getEffectManager();
		if (pEffectManager == NULL) return;

		if (Success && !pSlayer->isFlag(Effect::EFFECT_CLASS_RELOAD_TIMER)) 
		{
			EffectReloadTimer* pEffect = new EffectReloadTimer(pSlayer);
			
			pEffect->setFromInventory(true);
			pEffect->setObjectID(ItemObjectID);
			pEffect->setInventoryXY(x, y);
			
			if (pSlayer->hasSkill(SKILL_FAST_RELOAD)) pEffect->setDeadline(7); // ���� reload(0.7��)
			else                                      pEffect->setDeadline(2*10); // ���� reload(2sec)

			pSlayer->setFlag(Effect::EFFECT_CLASS_RELOAD_TIMER);
			pEffectManager->addEffect(pEffect);
		} 
		else 
		{
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotUse);
		}

	} 
	catch (Throwable & t) 
	{
		//cout << t.toString();
	}

#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH
}
