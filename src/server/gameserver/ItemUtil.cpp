//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemUtil.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "DB.h"
#include "ItemUtil.h"
#include "ItemInfo.h"
#include "ItemInfoManager.h"
#include "OptionInfo.h"
#include "Player.h"
#include "PlayerCreature.h"
#include "Inventory.h"
#include "Utility.h"
#include "VSDateTime.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Treasure.h"
#include "UniqueItemManager.h"
#include "RelicUtil.h"
#include "GoodsInfoManager.h"
#include "ItemGradeManager.h"

#include "item/AR.h"
#include "item/SR.h"
#include "item/SG.h"
#include "item/SMG.h"
#include "item/Magazine.h"
#include "item/SlayerPortalItem.h"
#include "item/Relic.h"
#include "item/OustersSummonItem.h"
#include "ItemFactoryManager.h"
#include "VariableManager.h"

#include "Gpackets/GCCreateItem.h"

#include <fstream>
#include <stdio.h>

#include "Corpse.h"
#include "MonsterCorpse.h"
#include "ctf/FlagManager.h"

#include "PetInfo.h"
#include "PetExpInfo.h"
#include "PetTypeInfo.h"
#include "item/PetItem.h"

#if defined(__THAILAND_SERVER__) || defined(__CHINA_SERVER__)
	
	#include "SystemAvailabilitiesManager.h"

#endif // __THAILAND_SERVER__

//////////////////////////////////////////////////////////////////////////////
// Ω◊¿œ ºˆ ¿÷¥¬ æ∆¿Ã≈€¿Œ∞°?
//////////////////////////////////////////////////////////////////////////////
bool isStackable(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_POTION:
		case Item::ITEM_CLASS_MAGAZINE:
		case Item::ITEM_CLASS_EVENT_STAR:
		case Item::ITEM_CLASS_SKULL:
		case Item::ITEM_CLASS_SERUM:
		case Item::ITEM_CLASS_VAMPIRE_ETC:
		case Item::ITEM_CLASS_WATER:
		case Item::ITEM_CLASS_HOLYWATER:
		case Item::ITEM_CLASS_BOMB_MATERIAL:
		case Item::ITEM_CLASS_BOMB:
		case Item::ITEM_CLASS_MINE:
		case Item::ITEM_CLASS_EVENT_ETC:
		case Item::ITEM_CLASS_RESURRECT_ITEM:
		case Item::ITEM_CLASS_ETC:
		case Item::ITEM_CLASS_MIXING_ITEM:
		case Item::ITEM_CLASS_LARVA:
		case Item::ITEM_CLASS_PUPA:
		case Item::ITEM_CLASS_COMPOS_MEI:
		case Item::ITEM_CLASS_EFFECT_ITEM:
		case Item::ITEM_CLASS_MOON_CARD:
		case Item::ITEM_CLASS_PET_ENCHANT_ITEM:
		case Item::ITEM_CLASS_LUCKY_BAG:
		case Item::ITEM_CLASS_PET_FOOD:
		case Item::ITEM_CLASS_COMMON_ITEM:
		case Item::ITEM_CLASS_MONEY://add by sonic 2006.10.30  Ω´Ω«Æ…ËŒ™ø…µ˛º”
			return true;
		default:
			return false;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// Ω◊¿œ ºˆ ¿÷¥¬ æ∆¿Ã≈€¿Œ∞°?
//////////////////////////////////////////////////////////////////////////////
bool isStackable(const Item* pItem)
{
	//if (pItem == NULL) return false;

	/*
	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_POTION:
		case Item::ITEM_CLASS_MAGAZINE:
		case Item::ITEM_CLASS_EVENT_STAR:
		case Item::ITEM_CLASS_SKULL:
		case Item::ITEM_CLASS_SERUM:
		case Item::ITEM_CLASS_VAMPIRE_ETC:
		case Item::ITEM_CLASS_WATER:
		case Item::ITEM_CLASS_HOLYWATER:
		case Item::ITEM_CLASS_BOMB_MATERIAL:
		case Item::ITEM_CLASS_BOMB:
		case Item::ITEM_CLASS_MINE:
			return true;
		default:
			return false;
	}
	*/

	// by sigi. 2002.5.13
	return pItem!=NULL 
			&& pItem->isStackable();
}

//////////////////////////////////////////////////////////////////////////////
// ∞∞¿∫ ≈¨∑°Ω∫, ≈∏¿‘¿« æ∆¿Ã≈€¿Œ∞°?
//////////////////////////////////////////////////////////////////////////////
bool isSameItem(Item::ItemClass IClass1, Item::ItemClass IClass2, ItemType_t type1, ItemType_t type2)
{
	return IClass1 == IClass2 
			&& type1 == type2;
}

//////////////////////////////////////////////////////////////////////////////
// ∞∞¿∫ ≈¨∑°Ω∫, ≈∏¿‘¿« æ∆¿Ã≈€¿Œ∞°?
//////////////////////////////////////////////////////////////////////////////
bool isSameItem(const Item* pItem1, const Item* pItem2)
{
	return pItem1!=NULL && pItem2!=NULL
			&& pItem1->getItemClass() == pItem2->getItemClass() 
			&& pItem1->getItemType() == pItem2->getItemType();
}

//////////////////////////////////////////////////////////////////////////////
// µŒ æ∆¿Ã≈€¿ª Ω◊¿ª ºˆ ¿÷¥¬∞°?
//////////////////////////////////////////////////////////////////////////////
bool canStack(const Item* pItem1, const Item* pItem2)
{
	return isStackable(pItem1) 
			&& isSameItem(pItem1, pItem2);
}

//////////////////////////////////////////////////////////////////////////////
// µŒ º’ π´±‚¿Œ∞°?
//////////////////////////////////////////////////////////////////////////////
bool isTwohandWeapon(const Item* pItem)
{
	if (pItem == NULL) return false;

	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_BLADE:
		case Item::ITEM_CLASS_AR:
		case Item::ITEM_CLASS_SR:
		case Item::ITEM_CLASS_SG:
		case Item::ITEM_CLASS_SMG:
		case Item::ITEM_CLASS_CROSS:
		case Item::ITEM_CLASS_MACE:
		case Item::ITEM_CLASS_VAMPIRE_WEAPON:
			return true;
		default:
			return false;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// ¡¢±Ÿ¿¸ π´±‚¿Œ∞°?
//////////////////////////////////////////////////////////////////////////////
bool isMeleeWeapon(const Item* pItem)
{
	if (pItem == NULL) return false;

	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_SWORD:
		case Item::ITEM_CLASS_BLADE:
		case Item::ITEM_CLASS_CROSS:
		case Item::ITEM_CLASS_MACE:
		case Item::ITEM_CLASS_VAMPIRE_WEAPON:
		case Item::ITEM_CLASS_OUSTERS_CHAKRAM:
		case Item::ITEM_CLASS_OUSTERS_WRISTLET:
			return true;
		default:
			return false;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// ¿¸ªÁ, ±∫¿Œ º∫¡˜¿⁄ π´±‚¿Œ∞°?
//////////////////////////////////////////////////////////////////////////////
bool isFighterWeapon(const Item* pItem)
{
	if (pItem == NULL) return false;

	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_SWORD:
		case Item::ITEM_CLASS_BLADE:
			return true;
		default:
			return false;
	}

	return false;
}

bool isArmsWeapon(const Item* pItem)
{
	if (pItem == NULL) return false;

	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_AR:
		case Item::ITEM_CLASS_SR:
		case Item::ITEM_CLASS_SG:
		case Item::ITEM_CLASS_SMG:
			return true;
			break;
		default:
			return false;
			break;
	}

	return false;
}

bool isClericWeapon(const Item* pItem)
{
	if (pItem == NULL) return false;

	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_CROSS:
		case Item::ITEM_CLASS_MACE:
			return true;
		default:
			return false;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// √—ø° ∏¬¥¬ ≈∫√¢¿Œ∞°?
//////////////////////////////////////////////////////////////////////////////
bool isSuitableMagazine(const Item* pGun, const Item* pMagazine, bool hasVivid)
{
	if (pGun == NULL || pMagazine == NULL) return false;
	if (pMagazine->getItemClass() != Item::ITEM_CLASS_MAGAZINE) return false;

	ItemType_t magazineType = pMagazine->getItemType();
	MagazineInfo* pInfo = dynamic_cast<MagazineInfo*>(g_pItemInfoManager->getItemInfo( Item::ITEM_CLASS_MAGAZINE, magazineType ));

	switch (pGun->getItemClass())
	{
		case Item::ITEM_CLASS_SG:
			if ( pInfo->getGunType() != MagazineInfo::SG ) return false;
//			if (magazineType == 0) return true;
//			if (magazineType == 1) return true;
//			if (magazineType == 8) return true;
//			if (magazineType == 9) return true;
			break;
		case Item::ITEM_CLASS_AR:
			if ( pInfo->getGunType() != MagazineInfo::AR ) return false;
//			if (magazineType == 2) return true;
//			if (magazineType == 3) return true;
//			if (magazineType == 10) return true;
//			if (magazineType == 11) return true;
			break;
		case Item::ITEM_CLASS_SMG:
			if ( pInfo->getGunType() != MagazineInfo::SMG ) return false;
//			if (magazineType == 4) return true;
//			if (magazineType == 5) return true;
//			if (magazineType == 12) return true;
//			if (magazineType == 13) return true;
			break;
		case Item::ITEM_CLASS_SR:
			if ( pInfo->getGunType() != MagazineInfo::SR ) return false;
//			if (magazineType == 6) return true;
//			if (magazineType == 7) return true;
//			if (magazineType == 14) return true;
//			if (magazineType == 15) return true;
			break;
		default:
			return false;
	}

	if ( pInfo->isVivid() && !hasVivid ) return false;

	return true;
}

//////////////////////////////////////////////////////////////////////////////
// ΩΩ∑π¿ÃæÓøÎ π´±‚¿Œ∞°?
//////////////////////////////////////////////////////////////////////////////
bool isSlayerWeapon(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_SWORD:
		case Item::ITEM_CLASS_BLADE:
		case Item::ITEM_CLASS_CROSS:
		case Item::ITEM_CLASS_MACE:
		case Item::ITEM_CLASS_AR:
		case Item::ITEM_CLASS_SR:
		case Item::ITEM_CLASS_SG:
		case Item::ITEM_CLASS_SMG:
			return true;
		default:
			return false;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// πÏ∆ƒ¿ÃæÓøÎ π´±‚¿Œ∞°?
//////////////////////////////////////////////////////////////////////////////
bool isVampireWeapon(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_VAMPIRE_WEAPON:
			return true;
		default:
			return false;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// æ∆øÏΩ∫≈ÕΩ∫øÎ π´±‚¿Œ∞°?
//////////////////////////////////////////////////////////////////////////////
bool isOustersWeapon(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_OUSTERS_CHAKRAM:
		case Item::ITEM_CLASS_OUSTERS_WRISTLET:
			return true;
		default:
			return false;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// ΩΩ∑π¿ÃæÓøÎ πÊæÓ±∏¿Œ∞°?
//////////////////////////////////////////////////////////////////////////////
bool isSlayerArmor(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_COAT:
		case Item::ITEM_CLASS_TROUSER:
		case Item::ITEM_CLASS_GLOVE:
		case Item::ITEM_CLASS_BELT:
		case Item::ITEM_CLASS_SHOES:
		case Item::ITEM_CLASS_SHIELD:
		case Item::ITEM_CLASS_HELM:
		case Item::ITEM_CLASS_SHOULDER_ARMOR:
			return true;
		default:
			break;
	}

	return false;
}
//////////////////////////////////////////////////////////////////////////////
// πÏ∆ƒ¿ÃæÓøÎ πÊæÓ±∏¿Œ∞°?
//////////////////////////////////////////////////////////////////////////////
bool isVampireArmor(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_VAMPIRE_COAT:
		case Item::ITEM_CLASS_PERSONA:
			return true;
		default:
			break;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// æ∆øÏΩ∫≈ÕΩ∫ πÊæÓ±∏¿Œ∞°?
//////////////////////////////////////////////////////////////////////////////
bool isOustersArmor(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_OUSTERS_COAT:
		case Item::ITEM_CLASS_OUSTERS_BOOTS:
		case Item::ITEM_CLASS_OUSTERS_CIRCLET:
		case Item::ITEM_CLASS_OUSTERS_ARMSBAND:
		case Item::ITEM_CLASS_MITTEN:
			return true;
		default:
			break;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// ΩΩ∑π¿ÃæÓøÎ æ«ººªÁ∏Æ¿Œ∞°?
//////////////////////////////////////////////////////////////////////////////
bool isSlayerAccessory(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_NECKLACE:
		case Item::ITEM_CLASS_BRACELET:
		case Item::ITEM_CLASS_RING:
		case Item::ITEM_CLASS_CARRYING_RECEIVER:
			return true;
		default:
			break;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////
// πÏ∆ƒ¿ÃæÓøÎ æ«ººªÁ∏Æ¿Œ∞°?
//////////////////////////////////////////////////////////////////////////////
bool isVampireAccessory(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_VAMPIRE_NECKLACE:
		case Item::ITEM_CLASS_VAMPIRE_BRACELET:
		case Item::ITEM_CLASS_VAMPIRE_RING:
		case Item::ITEM_CLASS_VAMPIRE_AMULET:
		case Item::ITEM_CLASS_VAMPIRE_EARRING:
		case Item::ITEM_CLASS_DERMIS:
			return true;
		default:
			break;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////
// æ∆øÏΩ∫≈ÕΩ∫øÎ æ«ººªÁ∏Æ¿Œ∞°?
//////////////////////////////////////////////////////////////////////////////
bool isOustersAccessory(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_OUSTERS_ARMSBAND:
		case Item::ITEM_CLASS_OUSTERS_PENDENT:
		case Item::ITEM_CLASS_OUSTERS_RING:
		case Item::ITEM_CLASS_OUSTERS_STONE:
		case Item::ITEM_CLASS_FASCIA:
			return true;
		default:
			break;
	}
	return false;
}


//////////////////////////////////////////////////////////////////////////////
// ºˆ∏Æ∞°¥…«— æ∆¿Ã≈€¿Œ∞°?
//////////////////////////////////////////////////////////////////////////////
bool isRepairableItem(const Item* pItem)
{
	// ¿Ø¥œ≈© æ∆¿Ã≈€¿∫ ºˆ∏Æ«“ « ø‰∞° æ¯¥Ÿ.
	if (pItem == NULL
		|| pItem->isUnique()
		|| pItem->isTimeLimitItem()) return false;
	if ( pItem->isFlagItem() ) return false;

	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_MOTORCYCLE:
		case Item::ITEM_CLASS_POTION:
		case Item::ITEM_CLASS_MAGAZINE:
		case Item::ITEM_CLASS_WATER:
		case Item::ITEM_CLASS_HOLYWATER:
		case Item::ITEM_CLASS_BOMB_MATERIAL:
		case Item::ITEM_CLASS_ETC:
		case Item::ITEM_CLASS_KEY:
		case Item::ITEM_CLASS_BOMB:
		case Item::ITEM_CLASS_MINE:
		case Item::ITEM_CLASS_LEARNINGITEM:
		case Item::ITEM_CLASS_CORPSE:
		case Item::ITEM_CLASS_SKULL:
		case Item::ITEM_CLASS_SERUM:
		case Item::ITEM_CLASS_VAMPIRE_ETC:
		case Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM:
		case Item::ITEM_CLASS_EVENT_GIFT_BOX:
		case Item::ITEM_CLASS_EVENT_STAR:
		case Item::ITEM_CLASS_MONEY:
		case Item::ITEM_CLASS_VAMPIRE_AMULET:
		case Item::ITEM_CLASS_QUEST_ITEM:
		case Item::ITEM_CLASS_RELIC:
		case Item::ITEM_CLASS_BLOOD_BIBLE:
		case Item::ITEM_CLASS_CASTLE_SYMBOL:
		case Item::ITEM_CLASS_COUPLE_RING:
		case Item::ITEM_CLASS_VAMPIRE_COUPLE_RING:
		case Item::ITEM_CLASS_EVENT_ITEM:
		case Item::ITEM_CLASS_MOON_CARD:
		case Item::ITEM_CLASS_SWEEPER:
//		case Item::ITEM_CLASS_PET_ITEM:
		case Item::ITEM_CLASS_LUCKY_BAG:
		case Item::ITEM_CLASS_CARRYING_RECEIVER:
		case Item::ITEM_CLASS_DERMIS:
		case Item::ITEM_CLASS_FASCIA:
			return false;
		default:
			return true;
	}

	return true;
}


//////////////////////////////////////////////////////////////////////////////
// æ∆¿Ã≈€¿ª ºˆ∏Æ«—¥Ÿ.
//////////////////////////////////////////////////////////////////////////////
void repairItem(Item* pItem)
{
	if (pItem != NULL
		&& !pItem->isUnique()
		&& isRepairableItem(pItem))
	{
		Item::ItemClass IClass = pItem->getItemClass();

		if (IClass == Item::ITEM_CLASS_SLAYER_PORTAL_ITEM)
		{
			SlayerPortalItem* pSlayerPortalItem = dynamic_cast<SlayerPortalItem*>(pItem);
			pSlayerPortalItem->setCharge(pSlayerPortalItem->getMaxCharge());
		}
		else if ( IClass == Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM )
		{
			OustersSummonItem* pOustersSummonItem = dynamic_cast<OustersSummonItem*>(pItem);
			pOustersSummonItem->setCharge(pOustersSummonItem->getMaxCharge());
		}
		else
		{
			// √÷≥ª ≥ª±∏ƒ°∏¶ æÚæÓ≥ªº≠
			Durability_t maxDurability = computeMaxDurability(pItem);
			// ºˆ∏Æ«—¥Ÿ.
			pItem->setDurability(maxDurability);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
// æ∆¿Ã≈€¿« √÷¥Î ≥ª±∏µµ∏¶ æÚæÓ≥Ω¥Ÿ.
//////////////////////////////////////////////////////////////////////////////
Durability_t computeMaxDurability(Item* pItem)
{
	if (pItem == NULL) return 0;

//	ItemInfo*    pItemInfo     = g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType());
//	unsigned long maxDurability = pItemInfo->getDurability();

	unsigned long maxDurability = pItem->getMaxDurability();

	// 100%ø°º≠ Ω√¿€
	unsigned long plusPoint = 100;

	const list<OptionType_t>& optionTypes = pItem->getOptionTypeList();
	//OptionType_t OptionType = pItem->getOptionType();

	list<OptionType_t>::const_iterator itr;

	for (itr=optionTypes.begin(); itr!=optionTypes.end(); itr++)
	{
		OptionType_t OptionType = *itr;

		if (OptionType != 0)
		{
			OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo(OptionType);

			if (pOptionInfo->getClass() == OPTION_DURABILITY)
			{
				plusPoint += (pOptionInfo->getPlusPoint()-100);
			}
		}
	}

	maxDurability = (maxDurability * plusPoint / 100);
	// 65000 ≥—æÓ∞°∏È ª‡ªÁ∏Æ≥≠¥Ÿ -_-;;;
//	maxDurability = min( (unsigned long)65000, maxDurability );

	return (Durability_t)maxDurability;
}

//////////////////////////////////////////////////////////////////////////////
// ≈∫√¢¿ª ∞•æ∆≥¢øˆ¡ÿ¥Ÿ. 
//////////////////////////////////////////////////////////////////////////////
Bullet_t reloadArmsItem(Item* pGun, Item* pMagazine)
{
	Assert(pGun != NULL);
	Assert(pMagazine != NULL);

	// vivid magazine √º≈©¥¬ ø©±‚ µÈæÓø¿±‚ ¿¸ø° «—¥Ÿ. ¿Ã «‘ºˆ¥¬ π´¡∂∞« reload«ÿ¡ÿ¥Ÿ.
	if (isSuitableMagazine(pGun, pMagazine, true) == false) return false;

	Item::ItemClass IClass        = pGun->getItemClass();
	ItemType_t      MagazineType  = pMagazine->getItemType();
	ItemInfo*       pItemInfo     = g_pItemInfoManager->getItemInfo(Item::ITEM_CLASS_MAGAZINE, MagazineType);
	MagazineInfo*   pMagazineInfo = dynamic_cast<MagazineInfo*>(pItemInfo);
	Bullet_t        BulletCount   = pMagazineInfo->getMaxBullets();
	Silver_t        Silver        = pMagazineInfo->getMaxSilver();

	if (IClass == Item::ITEM_CLASS_AR)
	{
		AR* pAR = dynamic_cast<AR*>(pGun);
		pAR->setBulletCount(BulletCount);
		pAR->setSilver(Silver);
		return pAR->getBulletCount();
	}
	else if (IClass == Item::ITEM_CLASS_SR)
	{
		SR* pSR = dynamic_cast<SR*>(pGun);
		pSR->setBulletCount(BulletCount);
		pSR->setSilver(Silver);
		return pSR->getBulletCount();
	}
	else if (IClass == Item::ITEM_CLASS_SG)
	{
		SG* pSG = dynamic_cast<SG*>(pGun);
		pSG->setBulletCount(BulletCount);
		pSG->setSilver(Silver);
		return pSG->getBulletCount();
	}
	else if (IClass == Item::ITEM_CLASS_SMG)
	{
		SMG* pSMG = dynamic_cast<SMG*>(pGun);
		pSMG->setBulletCount(BulletCount);
		pSMG->setSilver(Silver);
		return pSMG->getBulletCount();
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
// √—æÀ¿ª ª©¡ÿ¥Ÿ.
//////////////////////////////////////////////////////////////////////////////
Bullet_t decreaseBullet(Item* pWeapon) 
	
{
	__BEGIN_TRY

	if (pWeapon == NULL)
	{
		ofstream file("bulletBug.txt", ios::out | ios::app);
		file << "decreaseBullet() : pWeapon is NULL" <<  endl;
		return 0;
	}

	Item::ItemClass IClass = pWeapon->getItemClass();
	Bullet_t        bullet = 0;
	Silver_t        silver = 0;

	// Gun class∏¶ √ﬂ∞°«ﬂ¥Ÿ. by sigi. 2002.5.8
	/*
	if (IClass == Item::ITEM_CLASS_AR
		|| IClass == Item::ITEM_CLASS_SMG
		|| IClass == Item::ITEM_CLASS_SR
		|| IClass == Item::ITEM_CLASS_SG)
	{
		Gun* pGun = dynamic_cast<Gun*>(pWeapon);

		bullet = max(0, (int)(pGun->getBulletCount() - 1));
		pGun->setBulletCount(bullet);

		silver = max(0, (int)(pGun->getSilver() - 1));
		pGun->setSilver(silver);
	}
	else
	{
		filelog("bulletBug.log", "decreaseBullet() : Invalid item class : %s\n", ItemClass2String[IClass].c_str());
		throw ("decreaseBullet() : Invalid item class");
	}
	*/

	///*
	if (IClass == Item::ITEM_CLASS_AR)
	{
		AR* pAR = dynamic_cast<AR*>(pWeapon);
		bullet = max(0, (int)(pAR->getBulletCount() - 1));
		pAR->setBulletCount(bullet);

		silver = max(0, (int)(pAR->getSilver() - 1));
		pAR->setSilver(silver);
	}
	else if (IClass == Item::ITEM_CLASS_SR)
	{
		SR* pSR = dynamic_cast<SR*>(pWeapon);
		bullet = max(0, (int)(pSR->getBulletCount() - 1));
		pSR->setBulletCount(bullet);

		silver = max(0, (int)(pSR->getSilver() - 1));
		pSR->setSilver(silver);
	}
	else if (IClass == Item::ITEM_CLASS_SG)
	{
		SG* pSG = dynamic_cast<SG*>(pWeapon);
		bullet = max(0, (int)(pSG->getBulletCount() - 1));
		pSG->setBulletCount(bullet);

		silver = max(0, (int)(pSG->getSilver() - 1));
		pSG->setSilver(silver);
	}
	else if (IClass == Item::ITEM_CLASS_SMG)
	{
		SMG* pSMG = dynamic_cast<SMG*>(pWeapon);
		bullet = max(0, (int)(pSMG->getBulletCount() - 1));
		pSMG->setBulletCount(bullet);

		silver = max(0, (int)(pSMG->getSilver() - 1));
		pSMG->setSilver(silver);
	}
	else
	{
		filelog("bulletBug.log", "decreaseBullet() : Invalid item class : %s\n", ItemClass2String[IClass].c_str());
		throw ("decreaseBullet() : Invalid item class");
	}
	//*/

	return bullet;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// ≥≤¿∫ √—æÀ¿« ∞πºˆ∏¶ ∏Æ≈œ
//////////////////////////////////////////////////////////////////////////////
Bullet_t getRemainBullet(Item* pWeapon) 
	
{
	__BEGIN_TRY

	if (pWeapon == NULL) 
	{
		return 0;
	}

	Item::ItemClass IClass = pWeapon->getItemClass();

	// by sigi. 2002.5.16
	/*
	if (pWeapon->isGun())
	{
		Gun* pGun = dynamic_cast<Gun*>(pGun);

		return pGun->getBulletCount();
	}
	*/
	if (IClass == Item::ITEM_CLASS_AR)
	{
		AR* pAR = dynamic_cast<AR*>(pWeapon);
		return pAR->getBulletCount();
	}
	else if (IClass == Item::ITEM_CLASS_SR)
	{
		SR* pSR = dynamic_cast<SR*>(pWeapon);
		return pSR->getBulletCount();
	}
	else if (IClass == Item::ITEM_CLASS_SG)
	{
		SG* pSG = dynamic_cast<SG*>(pWeapon);
		return pSG->getBulletCount();
	}
	else if (IClass == Item::ITEM_CLASS_SMG)
	{
		SMG* pSMG = dynamic_cast<SMG*>(pWeapon);
		return pSMG->getBulletCount();
	}
	else
	{
		filelog("bullet.log", "getRemainBullet() : Invalid item class : %s\n", ItemClass2String[IClass].c_str());
		throw ("getRemainBullet() : Invalid item class");
	}

	return 0;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ¡÷¿ª ºˆ ¿÷¥¬ æ∆¿Ã≈€¿Œ∞°? 
//////////////////////////////////////////////////////////////////////////////
bool isPortableItem(Item* pItem)
{
	Assert(pItem != NULL);

	if ( pItem->isTimeLimitItem() ) return false;

	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_CORPSE:
		case Item::ITEM_CLASS_MOTORCYCLE:
		case Item::ITEM_CLASS_COUPLE_RING:
		case Item::ITEM_CLASS_VAMPIRE_COUPLE_RING:
		case Item::ITEM_CLASS_SUB_INVENTORY:
			return false;
		default:
			return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// ªÁøÎ«“ ºˆ ¿÷¥¬ æ∆¿Ã≈€¿Œ∞°?
// ø©±‚º≠¿« ªÁøÎ¿Ã∂ı, ªÁøÎ«ÿº≠ ªÁ∂Û¡ˆ¥¬ º“∏º∫ æ∆¿Ã≈€¿ª ∏ª«—¥Ÿ.
//////////////////////////////////////////////////////////////////////////////
bool isUsableItem(Item* pItem, Creature* pUser)
{
	Assert(pItem != NULL);
	Assert(pUser != NULL);

	// ≥™¡ﬂø° ∞∞¿∫ ≈¨∑°Ω∫¡ˆ∏∏, æÓ∂≤ ∞Õ¿∫ ªÁøÎ«“ ºˆ ¿÷∞Ì,
	// æÓ∂≤ ∞Õ¿∫ ªÁøÎ«“ ºˆ æ¯¥¬ ∞Õ¿Ã ≥™ø¿¡ˆ æ ¿ª±Ó?
	//ItemType_t IType = pItem->getItemType();

	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_POTION:
			if (pUser->isSlayer()) return true;
			break;
		case Item::ITEM_CLASS_MAGAZINE:
			if (pUser->isSlayer()) return true;
			break;
		case Item::ITEM_CLASS_KEY:
			if (g_pVariableManager->isSummonMotorcycle() && pUser->isSlayer()) return true;
			break;
		case Item::ITEM_CLASS_ETC:
			if (pUser->isSlayer() && pItem->getItemType() == 1) return true;
			break;
		case Item::ITEM_CLASS_SERUM:
			if (pUser->isVampire()) return true;
			break;
		case Item::ITEM_CLASS_VAMPIRE_ETC:
			if (pUser->isVampire()) return true;
			break;
		case Item::ITEM_CLASS_SLAYER_PORTAL_ITEM:
			if (pUser->isSlayer()) return true;
			break;
		case Item::ITEM_CLASS_EVENT_TREE:
			if ( pItem->getItemType() == 12 || ( pItem->getItemType() >= 26 && pItem->getItemType() <=28 ) ) return true;	// øœº∫µ» ∆Æ∏Æ
			break;

		case Item::ITEM_CLASS_EVENT_ETC:
			return true;
			break;

		case Item::ITEM_CLASS_COUPLE_RING:
			if ( pUser->isSlayer() ) return true;
			break;
		case Item::ITEM_CLASS_VAMPIRE_COUPLE_RING:
			if ( pUser->isVampire() ) return true;
			break;

		case Item::ITEM_CLASS_DYE_POTION:
			return true;

		case Item::ITEM_CLASS_RESURRECT_ITEM:
			if ( pUser->isFlag(Effect::EFFECT_CLASS_COMA) ) return true;
			break;

		case Item::ITEM_CLASS_PUPA:
			if (pUser->isOusters()) return true;
			break;

		case Item::ITEM_CLASS_COMPOS_MEI:
			if (pUser->isOusters()) return true;
			break;

		case Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM:
		case Item::ITEM_CLASS_OUSTERSWING_ITEM:
			if (pUser->isOusters()) return true;
			break;

		case Item::ITEM_CLASS_EFFECT_ITEM:
		case Item::ITEM_CLASS_PET_ITEM:
		case Item::ITEM_CLASS_PET_FOOD:
		case Item::ITEM_CLASS_PET_ENCHANT_ITEM:
			return true;
			break;

		case Item::ITEM_CLASS_EVENT_GIFT_BOX:
			if ( pItem->getItemType() >= 6  && pItem->getItemType() <= 15 ) return true;
			if ( pItem->getItemType() >= 19 && pItem->getItemType() <= 21 ) return true;
			if ( pItem->getItemType() >= 26 ) return true;
			break;

		case Item::ITEM_CLASS_SMS_ITEM:
			return true;
			break;

		case Item::ITEM_CLASS_TRAP_ITEM:
			return true;
			break;
		// add by Coffee 2007-6-9
		case Item::ITEM_CLASS_MOON_CARD:
			if ( pItem->getItemType() >=5 && pItem->getItemType() <=7 ) return true;
			break;
		case Item::ITEM_CLASS_SUB_INVENTORY:
			return true;
			break;
		case Item::ITEM_CLASS_SKILLBOOK:
			return true;
			break;
		default :
			return false;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// æ∆¿Ã≈€¿« º˝¿⁄∏¶ ¡Ÿ¿Œ¥Ÿ.
//////////////////////////////////////////////////////////////////////////////
ItemNum_t decreaseItemNum(Item* pItem, Inventory* pInventory, 
	const string& OwnerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y)
{
	Assert(pItem != NULL);
	Assert(pInventory != NULL);
	Assert(OwnerID != "");
	Assert(isStackable(pItem));

	if (pItem->getNum() > 1)
	{
		pItem->setNum(pItem->getNum() - 1); // æ∆¿Ã?€¿?∞πºˆ∏¶ «œ≥™ ¡Ÿ¿Œ¥Ÿ.
		pInventory->decreaseItemNum(); // ?Œ∫•≈‰∏?√— ∞πºˆ∏¶ ¡Ÿ¿Œ¥Ÿ.
		pInventory->decreaseWeight(pItem->getWeight()); // ¿Œ∫•≈‰∏Æ √— π´∞‘∏¶ ¡Ÿ¿Œ¥Ÿ.
		//pItem->save(OwnerID, storage, storageID, x, y); // æ∆¿Ã≈€ ¡§∫∏∏¶ ¿˙¿Â«—¥Ÿ.
		// æ∆¿Ã≈€ ¿˙¿Â √÷¿˚»≠. 2002.7.25 by sigi
		char pField[80];
		sprintf(pField, "Num=%d", pItem->getNum());
		pItem->tinysave(pField);


		return pItem->getNum();
	}
	else // æ∆¿Ã≈€¿Ã 1∞≥¬•∏Æø¥¿∏¥œ, ªË¡¶«—¥Ÿ.
	{
		pInventory->deleteItem(x, y);
		pItem->destroy();
		SAFE_DELETE(pItem);
		return 0;
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void processItemBug(Creature* pCreature, Item* pItem)
{
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert(pPC != NULL);
	Assert(pItem != NULL);

	pPC->addItemToGarbage(pItem);
}

void processItemBugEx(Creature* pCreature, Item* pItem)
{
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert(pPC != NULL);
	Assert(pItem != NULL);

	pPC->addItemToGarbage(pItem);
	pItem->save(pCreature->getName(), STORAGE_GARBAGE, 0, 0, 0);
}

bool hasOptionType(const list<OptionType_t>& optionTypes, OptionType_t optionType)
{
	if (optionTypes.empty())
		return false;

	list<OptionType_t>::const_iterator itr;

	for (itr=optionTypes.begin(); itr!=optionTypes.end(); itr++)
	{
		if (*itr==optionType)
			return true;
	}

	return false;
}

bool hasOptionClass(const list<OptionType_t>& optionTypes, OptionType_t optionType)
{
	if (optionTypes.empty())
		return false;

	try {

		OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo( optionType );

		if (pOptionInfo==NULL)
			return false;

		OptionClass newOptionClass = pOptionInfo->getClass();
			
		list<OptionType_t>::const_iterator itr;

		for (itr=optionTypes.begin(); itr!=optionTypes.end(); itr++)
		{
			pOptionInfo = g_pOptionInfoManager->getOptionInfo( *itr );
			if (pOptionInfo==NULL) return false;
			if (pOptionInfo->getClass()==newOptionClass)
				return true;
		}
	} catch (Throwable& t) {
		// π´Ω√..
		filelog("hasOptionClassBug.txt", "%s", t.toString().c_str());
	}

	return false;
}

void setOptionTypeFromField(list<OptionType_t>& optionTypes, const string& optionField)
{
	if (optionField.empty()) return;

	//cout << "setOptionType: " << optionField.c_str() << " --> ";

	const char* pOptionField = optionField.c_str();
	unsigned char ch;
	while (ch=*pOptionField++)
	{
		optionTypes.push_back( (OptionType_t)ch );
		//cout << (int)ch << " ";
	}
	//cout << endl;
}

void setOptionTypeToField(const list<OptionType_t>& optionTypes, string& optionField)
{
	if (optionTypes.empty()) return;

	//cout << "setOptionType: ";
	unsigned char ch;

	list<OptionType_t>::const_iterator itr;
	for (itr=optionTypes.begin(); itr!=optionTypes.end(); itr++)
	{
		ch = *itr;

		// ∆Øºˆ~πÆ¿⁄¿Œ ∞ÊøÏø°¥¬ ¿Ã∞≈ «ÿ¡‡æﬂµ»¥Á.
		if (ch=='\'' || ch=='\\')
		{
			optionField += '\\';
		}

		optionField += ch;

		//cout << (int)ch << " ";
	}

	//cout << " --> " << optionField.c_str() << endl;
}

string getOptionTypeToString(const list<OptionType_t>& optionTypes)
{
	if (optionTypes.empty()) return string("NONE");

	string optionField;
	unsigned char ch;

	char str[12];

	list<OptionType_t>::const_iterator itr;
	for (itr=optionTypes.begin(); itr!=optionTypes.end(); itr++)
	{
		ch = *itr;
		sprintf(str, "%d", (int)ch);
		optionField += str;
		optionField += " ";
	}

	return optionField;
}


//////////////////////////////////////////////////////////////////////////////
// ∑πæÓ æ∆¿Ã≈€ : ¥Ÿ¿Ω ø…º«¿ª ∫Ÿ¿œ±Ó?
//////////////////////////////////////////////////////////////////////////////
bool isPossibleNextOption(ITEM_TEMPLATE* pTemplate)
{
	// «ˆ¿Á¥¬ ø…º«¿Ã 2∞≥±Ó¡ˆπ€ø° æ» ∫Ÿ¥¬¥Ÿ.
	if (pTemplate->OptionType.size()>=5)
		return false;

	// æ∆π´∞Õµµ æ¯¥Ÿ∏È π´¡∂∞« ∫Ÿ¿Œ¥Ÿ...∞Ì «œ¥¬∞« æ∆¥œ¡ˆ∏∏ æÓ¬∂µÁ ±◊∑∏¥Ÿ - -;
	if (pTemplate->OptionType.empty())
		return true;

	// æ∆¿Ã≈€ø° ∆Ø?∞»?¿˚øÎµ«æÓ ¿÷¥¬ ø…º« »Æ∑¸¿ª ¿˚øÎΩ√≈≤¥Ÿ.
	if (pTemplate->NextOptionRatio!=0)
	{
		int dice = rand()%100;
		//cout << "NextOptionRatio : " << dice << " < " << (int)pTemplate->NextOptionRatio << endl;
		return dice < pTemplate->NextOptionRatio;
	}

	try {
		// æ∆¿Ã≈€ ¡æ∑˘∫∞∑Œ.. ¥Ÿ¿Ω ø…º«¿Ã ∫Ÿ¿ª »Æ∑¸¿ª ±∏«—¥Ÿ.
		ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo(pTemplate->ItemClass, pTemplate->ItemType);
		Ratio_t nextItemRatio = pItemInfo->getNextOptionRatio();

		// «ˆ¿Á ∫Ÿ¿∫ ø…º«ø° ¥Î«ÿº≠.. ¥Ÿ¿Ω ø…º«¿Ã ∫Ÿ¿ª »Æ∑¸¿ª ±∏«—¥Ÿ.
		list<OptionType_t>::const_iterator itr = pTemplate->OptionType.begin();
		Ratio_t nextOptionRatio = nextItemRatio;	// ∞ËªÍ ¡Ÿ¿œ∑¡∞Ì..
		Ratio_t baseMultiplier = 100;				// 100%
		for (; itr!=pTemplate->OptionType.end(); itr++)
		{
			OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo( *itr );
			if (pOptionInfo==NULL)
				return false;
			nextOptionRatio *= pOptionInfo->getNextOptionRatio();
			baseMultiplier *= 100;
		}

		// [øπ¡¶] ø…º«¿Ã µŒ ∞≥ ∫ŸæÓ ¿÷¥¬ æ∆¿Ã≈€ø°º≠ 
		//        ººπ¯¬∞ ø…º«¿Ã ∫Ÿ¿ª »Æ∑¸¿Ã∂Û∏È..
		//
		// nextItemRatio = 10 %
		// nextOptionRatio1 = 20 %
		// nextOptionRatio2 = 30 %
		//
		// total nextOptionRatio = nextItemRatio * nextOptionRatio1 * nextOptionRatio2
		//                       = 10 * 20 * 30 = 6000
		//
		// baseMultiplier = 100(√ ±‚∞™) * 100(option1) * 100(option2)
		//                = 1000000
		//
		// selectRatio = 0~baseMultiplier = 0~1000000
		//
		// Succeed = nextOptionRatio/baseMultiplier 
		//         = 6000/1000000
		//         = 6 / 1000
		//         = 0.6%

		Ratio_t selectRatio = rand()%baseMultiplier;

		// ∑πæÓ æ∆¿Ã≈€ ∑Á∆√ »Æ∑¸¿ª ¿˚øÎΩ√≈≤¥Ÿ.
		nextOptionRatio = getPercentValue( nextOptionRatio, g_pVariableManager->getRareItemRatio() );

		// »Æ∑¸ √º≈©
		return selectRatio < nextOptionRatio;

	} catch (Throwable& t) {
		// ¿œ¥‹ π´Ω√«—¥Ÿ.
		filelog("nextOptionBug.txt", "%s", t.toString().c_str());
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// ∞∑∫Ì æ∆¿Ã≈€ ª˝º∫
//////////////////////////////////////////////////////////////////////////////
Item* getRandomMysteriousItem(Creature* pCreature, Item::ItemClass itemClass, int maxLevel)
	
{
	__BEGIN_TRY

	Assert(pCreature!=NULL);

	InfoClassManager* pInfoClass = g_pItemInfoManager->getInfoManager( itemClass );
	Assert(pInfoClass!=NULL);

	ItemType_t itemType = 0;
	OptionType_t optionType = 1;

	ItemInfo* pItemInfo = NULL;

	//----------------------------------------------------------------------
	// Slayer¿Œ ∞ÊøÏ
	//----------------------------------------------------------------------
	if (pCreature->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
		
		Attr_t CSTR = pSlayer->getSTR(ATTR_BASIC);
		Attr_t CDEX = pSlayer->getDEX(ATTR_BASIC);
		Attr_t CINT = pSlayer->getINT(ATTR_BASIC);
		Attr_t CSUM = CSTR + CDEX + CINT;

		Attr_t    ReqSTR, ReqSTR2;
		Attr_t    ReqDEX, ReqDEX2;
		Attr_t    ReqINT, ReqINT2;
		Attr_t    ReqSum, ReqSum2;
		Attr_t    ReqGender;

		// gamble«“ ºˆ ¿÷¥¬ «—∞Ë∏¶ ¡ª ¥ı ≥Ù«Ù∫ª¥Ÿ.
		CSTR += 3;
		CDEX += 3;
		CINT += 3;
		CSUM += 5;

		// level¡¶«—
		if (maxLevel!=0)
		{
			int maxAttr = maxLevel * 2 / 3;	// attr¿∫ SUM¿« 2/3¿∏∑Œ ∫ª¥Ÿ.
			CSTR = min((int)maxAttr, (int)CSTR);
			CDEX = min((int)maxAttr, (int)CDEX);
			CINT = min((int)maxAttr, (int)CINT);
			CSUM = min((int)maxLevel, (int)CSUM);
		}

		// 10π¯∏∏ µπ∑¡∫ª¥Ÿ.
		int i = 10;
		do
		{
			itemType = pInfoClass->getRandomItemType();

			// ¿Ã itemType¿ª ª˝º∫«ÿµµ µ«¥¬ level¿Œ¡ˆ »Æ¿Œ«—¥Ÿ.
			pItemInfo = g_pItemInfoManager->getItemInfo(itemClass, itemType);

			ReqSTR2 = ReqSTR    = pItemInfo->getReqSTR();
			ReqDEX2 = ReqDEX    = pItemInfo->getReqDEX();
			ReqINT2 = ReqINT    = pItemInfo->getReqINT();
			ReqSum2 = ReqSum    = pItemInfo->getReqSum();
			ReqGender = pItemInfo->getReqGender();

			if (CSTR >= ReqSTR
				&& CDEX >= ReqDEX
				&& CINT >= ReqINT
				&& CSUM >= ReqSum
				&& (ReqGender==GENDER_BOTH
					|| pSlayer->getSex() == MALE && ReqGender == GENDER_MALE
					|| pSlayer->getSex() == FEMALE && ReqGender == GENDER_FEMALE))
			{
				// ¿Ã item type¿∏∑Œ ∞·¡§«—¥Ÿ.
				break;
			}

		} while (--i);

		if (i==0)
		{
			// ø©¿⁄¿Œ ∞ÊøÏ¥¬ ±‚∫ª item type¿Ã ¥Ÿ∏£¥Ÿ.
			if ((itemClass==Item::ITEM_CLASS_COAT || itemClass==Item::ITEM_CLASS_TROUSER)
				&& pSlayer->getSex()==FEMALE)
			{
				itemType = 1;
			}
			else
			{
				itemType = 0;
			}

			// πÿø°º≠ √º≈©«“∂ß π´Ω√«œ±‚ ¿ß«ÿº≠..
			pItemInfo = NULL;
		}


		// æ∆¿Ã≈€¿Ã ø…º«¿ª ∞°¡ˆ∞Ì ¿÷¥Ÿ∏È, 
		// ø…º«¿« ¡æ∑˘ø° µ˚∂Ûº≠ ¥…∑¬ƒ° ¡¶«—¿ª ø√∑¡¡ÿ¥Ÿ.
		int maxOptionLevel = max(1, min(100, (int)(CSUM/3)));

		const vector<OptionType_t>& optionVector = g_pOptionInfoManager->getPossibleGambleOptionVector((Item::ItemClass)itemClass, maxOptionLevel);
		vector<OptionType_t>::const_iterator iOption;

		/*
		cout << "optionVector[" << (int)itemClass << "][" << (int)maxOptionLevel << "] = (" << optionVector.size() << ") = ";

		for (iOption=optionVector.begin(); iOption!=optionVector.end(); iOption++)
		{
			cout << (int)*iOption << "  ";
		}
		cout << endl;
		*/

		// Total OptionRatio∏¶ ±∏«—¥Ÿ.
		int itemOptionRatio = g_pOptionInfoManager->getTotalGambleRatio((Item::ItemClass)itemClass, maxOptionLevel);

		if (optionVector.size()>0 && itemOptionRatio>0
			&& (pItemInfo==NULL || !pItemInfo->isUnique()))
		{
			// 10π¯∏∏ µπ∑¡∫ª¥Ÿ.
			int i = 10;
			
			do {
				// random¿∏∑Œ option¿ª º±≈√«—¥Ÿ.
				int optionRatio = random()%itemOptionRatio;
				int ratioSum      = 0;

				//cout << "Ratio = " << optionRatio << "/" << itemOptionRatio << endl;

				OptionInfo* pOptionInfo = NULL;

				for (iOption=optionVector.begin(); iOption!=optionVector.end(); iOption++)
				{
					optionType = *iOption;

					pOptionInfo = g_pOptionInfoManager->getOptionInfo( optionType );
					ratioSum += pOptionInfo->getRatio();

					if (optionRatio < ratioSum)
					{
						// ¿Ã option¿ª º±≈√«—¥Ÿ.
						//cout << "select : " << (int)optionType << endl;
						break;
					}
				}

				// option¿« ø‰±∏ ¥…∑¬ƒ°∏¶ ¥ı«ÿº≠
				if (ReqSTR != 0) ReqSTR = ReqSTR2 + (pOptionInfo->getReqSum() * 2);
				if (ReqDEX != 0) ReqDEX = ReqDEX2 + (pOptionInfo->getReqSum() * 2);
				if (ReqINT != 0) ReqINT = ReqINT2 + (pOptionInfo->getReqSum() * 2);
				if (ReqSum != 0) ReqSum = ReqSum2 + (pOptionInfo->getReqSum());

				//if (ReqSTR != 0) cout << "CSTR = " << (int)CSTR << ", ReqSTR = " << (int)ReqSTR2 << " + " << (int)pOptionInfo->getReqSum() << "*2 = " << (int)ReqSTR << endl;
				//if (ReqDEX != 0) cout << "CDEX = " << (int)CDEX << ", ReqDEX = " << (int)ReqDEX2 << " + " << (int)pOptionInfo->getReqSum() << "*2 = " << (int)ReqDEX << endl;
				//if (ReqINT != 0) cout << "CINT = " << (int)CINT << ", ReqINT = " << (int)ReqINT2 << " + " << (int)pOptionInfo->getReqSum() << "*2 = " << (int)ReqINT << endl;
				//if (ReqSum != 0) cout << "CSUM = " << (int)CSUM << ", ReqSum = " << (int)ReqSum2 << " + " << (int)pOptionInfo->getReqSum() << " = " << (int)ReqSum << endl;

				//cout << "CSTR=" << CSTR << ", "
				//	<< "CDEX=" << CDEX << ", "
				//	<< "CINT=" << CINT << endl;

				// player¿« ¥…∑¬ƒ°ø° ∏¬¥¬ æ∆¿Ã≈€¿Œ¡ˆ »Æ¿Œ«—¥Ÿ.
				if (CSTR >= ReqSTR
					&& CDEX >= ReqDEX
					&& CINT >= ReqINT
					&& CSUM >= ReqSum)
				{
					// ¿Ã option type¿∏∑Œ ∞·¡§«—¥Ÿ.
					//cout << "OK!" << endl;
					break;
				}

			} while (--i);

			if (i==0)
			{
				optionType = 0;	//(rand()%3==0? 1: (rand()%2? 6:11));
			}
		}
		// π´ø… 	// ¿˚¿˝«—∞‘ æ¯¿∏∏È STR+1, DEX+1, INT+1 ¡ﬂø°º≠ æœ∞≈≥™..
		else optionType = 0;	//(rand()%3==0? 1: (rand()%2? 6:11));
	}
	//----------------------------------------------------------------------
	// Vampire¿Œ ∞ÊøÏ
	//----------------------------------------------------------------------
	else if (pCreature->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
	
		Level_t	CLevel = pVampire->getLevel();

		// gamble«“ ºˆ ¿÷??«—∞Ë∏¶ ¡ª ¥ı ≥Ù«Ù∫ª¥Ÿ.
		CLevel += 3;

		// level¡¶«—
		if (maxLevel!=0)
		{
			CLevel = min((int)maxLevel, (int)CLevel);
		}

		Attr_t    ReqLevel, ReqLevel2;
		Attr_t    ReqGender;


		// 10π¯∏∏ µπ∑¡∫ª¥Ÿ.
		int i = 10;
		do
		{
			itemType = pInfoClass->getRandomItemType();

			// ¿Ã itemType¿ª ª˝º∫«ÿµµ µ«¥¬ level¿Œ¡ˆ »Æ¿Œ«—¥Ÿ.
			pItemInfo = g_pItemInfoManager->getItemInfo(itemClass, itemType);

			ReqLevel2 = ReqLevel  = pItemInfo->getReqLevel();
			ReqGender = pItemInfo->getReqGender();

			// ∑π∫ß ¡¶«—¿Ã æ¯∞≈≥™ ¡¶«— ∑π∫ß¿Ã ≥Ù∞Ì
			// º∫∫∞¿Ã ∏¬æ∆æﬂ «—¥Ÿ.
			if ((ReqLevel <= 0 || CLevel >= ReqLevel)
				&& (ReqGender==GENDER_BOTH
					|| pVampire->getSex()==MALE && ReqGender==GENDER_MALE
					|| pVampire->getSex()==FEMALE && ReqGender==GENDER_FEMALE)
				)
			{
				break;
			}

		} while (--i);

		if (i==0)
		{
			// ø©¿⁄¿Œ ∞ÊøÏ¥¬ ±‚∫ª item type¿Ã ¥Ÿ∏£¥Ÿ.
			if (Item::ITEM_CLASS_VAMPIRE_COAT && pVampire->getSex()==FEMALE)
			{
				itemType = 1;
			}
			else
			{
				itemType = 0;
			}
		}

		// æ∆¿Ã≈€¿Ã ø…º«¿ª ∞°¡ˆ∞Ì ¿÷¥Ÿ∏È, 
		// ø…º«¿« ¡æ∑˘ø° µ˚∂Ûº≠ ¥…∑¬ƒ° ¡¶«—¿ª ø√∑¡¡ÿ¥Ÿ.
		int maxOptionLevel = max(1, min(100, (int)CLevel));

		const vector<OptionType_t>& optionVector = g_pOptionInfoManager->getPossibleGambleOptionVector((Item::ItemClass)itemClass, maxOptionLevel);
		vector<OptionType_t>::const_iterator iOption;

		// Total OptionRatio∏¶ ±∏«—¥Ÿ.
		int itemOptionRatio = g_pOptionInfoManager->getTotalGambleRatio((Item::ItemClass)itemClass, maxOptionLevel);

		/*
		cout << "optionVector[" << (int)itemClass << "][" << (int)maxOptionLevel << "] = (" << optionVector.size() << ") = ";

		for (iOption=optionVector.begin(); iOption!=optionVector.end(); iOption++)
		{
			cout << (int)*iOption << "  ";
		}
		cout << endl;
		*/


		if (optionVector.size()>0 && itemOptionRatio>0
			&& (pItemInfo==NULL || !pItemInfo->isUnique()))
		{
			// 10π¯∏∏ µπ∑¡∫ª¥Ÿ.
			int i = 10;
			
			do {
				// random¿∏∑Œ option¿ª º±≈√«—¥Ÿ.
				int optionRatio = random()%itemOptionRatio;
				int ratioSum      = 0;

				//cout << "Ratio = " << optionRatio << "/" << itemOptionRatio << endl;

				OptionInfo* pOptionInfo = NULL;

				for (iOption=optionVector.begin(); iOption!=optionVector.end(); iOption++)
				{
					optionType = *iOption;

					pOptionInfo = g_pOptionInfoManager->getOptionInfo( optionType );
					ratioSum += pOptionInfo->getRatio();

					if (optionRatio < ratioSum)
					{
						// ¿Ã option¿ª º±≈√«—¥Ÿ.
						break;
					}
				}

				// option¿« ø‰±∏ ¥…∑¬ƒ°∏¶ ¥ı«ÿº≠
				ReqLevel = ReqLevel2 + pOptionInfo->getReqLevel();

				// player¿« ¥…∑¬ƒ°ø° ∏¬¥¬ æ∆¿Ã≈€¿Œ¡ˆ »Æ¿Œ«—¥Ÿ.
				if (ReqLevel <= 0 || CLevel >= ReqLevel)
				{
					// ¿Ã option type¿∏∑Œ ∞·¡§«—¥Ÿ.
					break;
				}

			} while (--i);

			if (i==0)
			{
				optionType = 0;//(rand()%3==0? 1: (rand()%2? 6:11));
			}
		}
		// π´ø…!  // ¿˚¿˝«—∞‘ æ¯¿∏∏È STR+1, DEX+1, INT+1 ¡ﬂø°º≠ æœ∞≈≥™..
		else optionType = 0;//(rand()%3==0? 1: (rand()%2? 6:11));
	}
	//----------------------------------------------------------------------
	// Ousters¿Œ ∞ÊøÏ
	//----------------------------------------------------------------------
	else if (pCreature->isOusters())
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
	
		Level_t	CLevel = pOusters->getLevel();

		// gamble«“ ºˆ ¿÷¥¬ «—∞Ë∏¶ ¡ª ¥ı ≥Ù«Ù∫ª¥Ÿ.
		CLevel += 3;

		// level¡¶«—
		if (maxLevel!=0)
		{
			CLevel = min((int)maxLevel, (int)CLevel);
		}

		Attr_t    ReqLevel, ReqLevel2;

		// 10π¯∏∏ µπ∑¡∫ª¥Ÿ.
		int i = 10;
		do
		{
			itemType = pInfoClass->getRandomItemType();

			// ¿Ã itemType¿ª ª˝º∫«ÿµµ µ«¥¬ level¿Œ¡ˆ »Æ¿Œ«—¥Ÿ.
			pItemInfo = g_pItemInfoManager->getItemInfo(itemClass, itemType);

			ReqLevel2 = ReqLevel  = pItemInfo->getReqLevel();

			// ∑π∫ß ¡¶«—¿Ã æ¯∞≈≥™ ¡¶«— ∑π∫ß¿Ã ≥Ù∞Ì
			// º∫∫∞¿Ã ∏¬æ∆æﬂ «—¥Ÿ.
			if ((ReqLevel <= 0 || CLevel >= ReqLevel))
			{
				break;
			}

		} while (--i);

		if (i==0)
		{
			itemType = 0;
		}

		// æ∆¿Ã≈€¿Ã ø…º«¿ª ∞°¡ˆ∞Ì ?÷¥Ÿ∏? 
		// ø…º«¿« ¡æ∑˘ø° µ˚∂Ûº≠ ¥…∑¬ƒ° ¡¶«—¿ª ø√∑¡¡ÿ¥Ÿ.
		int maxOptionLevel = max(1, min(100, (int)CLevel));

		const vector<OptionType_t>& optionVector = g_pOptionInfoManager->getPossibleGambleOptionVector((Item::ItemClass)itemClass, maxOptionLevel);
		vector<OptionType_t>::const_iterator iOption;

		// Total OptionRatio∏¶ ±∏«—¥Ÿ.
		int itemOptionRatio = g_pOptionInfoManager->getTotalGambleRatio((Item::ItemClass)itemClass, maxOptionLevel);

		/*
		cout << "optionVector[" << (int)itemClass << "][" << (int)maxOptionLevel << "] = (" << optionVector.size() << ") = ";

		for (iOption=optionVector.begin(); iOption!=optionVector.end(); iOption++)
		{
			cout << (int)*iOption << "  ";
		}
		cout << endl;
		*/


		if (optionVector.size()>0 && itemOptionRatio>0
			&& (pItemInfo==NULL || !pItemInfo->isUnique()))
		{
			// 10π¯∏∏ µπ∑¡∫ª¥Ÿ.
			int i = 10;
			
			do {
				// random¿∏∑Œ option¿ª º±≈√«—¥Ÿ.
				int optionRatio = random()%itemOptionRatio;
				int ratioSum      = 0;

				//cout << "Ratio = " << optionRatio << "/" << itemOptionRatio << endl;

				OptionInfo* pOptionInfo = NULL;

				for (iOption=optionVector.begin(); iOption!=optionVector.end(); iOption++)
				{
					optionType = *iOption;

					pOptionInfo = g_pOptionInfoManager->getOptionInfo( optionType );
					ratioSum += pOptionInfo->getRatio();

					if (optionRatio < ratioSum)
					{
						// ¿Ã option¿ª º±≈√«—¥Ÿ.
						break;
					}
				}

				// option¿« ø‰±∏ ¥…∑¬ƒ°∏¶ ¥ı«ÿº≠
				ReqLevel = ReqLevel2 + pOptionInfo->getReqLevel();

				// player¿« ¥…∑¬ƒ°ø° ∏¬¥¬ æ∆¿Ã≈€¿Œ¡ˆ »Æ¿Œ«—¥Ÿ.
				if (ReqLevel <= 0 || CLevel >= ReqLevel)
				{
					// ¿Ã option type¿∏∑Œ ∞·¡§«—¥Ÿ.
					break;
				}

			} while (--i);

			if (i==0)
			{
				optionType = 0;//(rand()%3==0? 1: (rand()%2? 6:11));
			}
		}
		// π´ø…!  // ¿˚¿˝«—∞‘ æ¯¿∏∏È STR+1, DEX+1, INT+1 ¡ﬂø°º≠ æœ∞≈≥™..
		else optionType = 0;//(rand()%3==0? 1: (rand()%2? 6:11));
	}

	// item¿ª ª˝º∫«ÿº≠ ≥—∞‹¡ÿ¥Ÿ.
	list<OptionType_t> optionTypes;
	if (optionType!=0)
		optionTypes.push_back( optionType );
	Item* pItem = g_pItemFactoryManager->createItem(itemClass, itemType, optionTypes);
	pItem->setHeroOption(-1);
	pItem->setHeroOptionAttr(0);
	pItem->setEnchantLevel(0);
	pItem->setGrade( min(6,ItemGradeManager::Instance().getRandomGambleGrade()) );

	return pItem;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ø…º«¿Ã ∫Ÿ¿ª ºˆ ¿÷¥¬ æ∆¿Ã≈€¿Œ∞°?
//////////////////////////////////////////////////////////////////////////////
bool isPossibleOptionItemClass(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_HELM :
		case Item::ITEM_CLASS_NECKLACE :
		case Item::ITEM_CLASS_RING :
		case Item::ITEM_CLASS_BRACELET :
		case Item::ITEM_CLASS_SHIELD :
		case Item::ITEM_CLASS_GLOVE :
		case Item::ITEM_CLASS_COAT :
		case Item::ITEM_CLASS_BELT :
		case Item::ITEM_CLASS_TROUSER :
		case Item::ITEM_CLASS_SHOES :
		case Item::ITEM_CLASS_SWORD :
		case Item::ITEM_CLASS_BLADE :
		case Item::ITEM_CLASS_CROSS :
		case Item::ITEM_CLASS_MACE :
		case Item::ITEM_CLASS_AR :
		case Item::ITEM_CLASS_SR :
		case Item::ITEM_CLASS_SG :
		case Item::ITEM_CLASS_SMG :
		case Item::ITEM_CLASS_CARRYING_RECEIVER :
		case Item::ITEM_CLASS_SHOULDER_ARMOR :

		case Item::ITEM_CLASS_VAMPIRE_NECKLACE :
		case Item::ITEM_CLASS_VAMPIRE_RING :
		case Item::ITEM_CLASS_VAMPIRE_BRACELET :
		case Item::ITEM_CLASS_VAMPIRE_EARRING :
		case Item::ITEM_CLASS_VAMPIRE_COAT :
		case Item::ITEM_CLASS_VAMPIRE_WEAPON :
		case Item::ITEM_CLASS_VAMPIRE_AMULET :
		case Item::ITEM_CLASS_DERMIS :
		case Item::ITEM_CLASS_PERSONA :

		case Item::ITEM_CLASS_OUSTERS_ARMSBAND:
		case Item::ITEM_CLASS_OUSTERS_BOOTS:
		case Item::ITEM_CLASS_OUSTERS_CHAKRAM:
		case Item::ITEM_CLASS_OUSTERS_CIRCLET:
		case Item::ITEM_CLASS_OUSTERS_COAT:
		case Item::ITEM_CLASS_OUSTERS_PENDENT:
		case Item::ITEM_CLASS_OUSTERS_RING:
		case Item::ITEM_CLASS_OUSTERS_STONE:
		case Item::ITEM_CLASS_OUSTERS_WRISTLET:
		case Item::ITEM_CLASS_FASCIA :
		case Item::ITEM_CLASS_MITTEN :

		case Item::ITEM_CLASS_CORE_ZAP:
		case Item::ITEM_CLASS_ETHEREAL:
		case Item::ITEM_CLASS_STONE_ABILITY:
		case Item::ITEM_CLASS_NECKLACEZAP:
		case Item::ITEM_CLASS_COATZAP:
		case Item::ITEM_CLASS_BOOTZAP:
		case Item::ITEM_CLASS_WEAPONZAP:
		case Item::ITEM_CLASS_HELMZAP:
		case Item::ITEM_CLASS_GLOVEZAP:
		case Item::ITEM_CLASS_BELTZAP:
		case Item::ITEM_CLASS_SHOESZAP:
			return true;

		default :
			return false;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// ¥Ÿ¿Ω ¥‹∞Ë∑Œ æ˜±◊∑π¿ÃµÂµ… ºˆ ¿÷¥¬ ItemType¿Œ∞°
//////////////////////////////////////////////////////////////////////////////
bool isPossibleUpgradeItemType(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_HELM :
		case Item::ITEM_CLASS_NECKLACE :
		case Item::ITEM_CLASS_RING :
		case Item::ITEM_CLASS_BRACELET :
		case Item::ITEM_CLASS_SHIELD :
		case Item::ITEM_CLASS_GLOVE :
		case Item::ITEM_CLASS_COAT :
		case Item::ITEM_CLASS_BELT :
		case Item::ITEM_CLASS_TROUSER :
		case Item::ITEM_CLASS_SHOES :
		case Item::ITEM_CLASS_SWORD :
		case Item::ITEM_CLASS_BLADE :
		case Item::ITEM_CLASS_CROSS :
		case Item::ITEM_CLASS_MACE :
		case Item::ITEM_CLASS_AR :
		case Item::ITEM_CLASS_SR :
		case Item::ITEM_CLASS_SG :
		case Item::ITEM_CLASS_SMG :

		case Item::ITEM_CLASS_VAMPIRE_NECKLACE :
		case Item::ITEM_CLASS_VAMPIRE_RING :
		case Item::ITEM_CLASS_VAMPIRE_BRACELET :
		case Item::ITEM_CLASS_VAMPIRE_EARRING :
		case Item::ITEM_CLASS_VAMPIRE_COAT :
		case Item::ITEM_CLASS_VAMPIRE_WEAPON :
		case Item::ITEM_CLASS_VAMPIRE_AMULET :

		case Item::ITEM_CLASS_OUSTERS_ARMSBAND:
		case Item::ITEM_CLASS_OUSTERS_BOOTS:
		case Item::ITEM_CLASS_OUSTERS_CHAKRAM:
		case Item::ITEM_CLASS_OUSTERS_CIRCLET:
		case Item::ITEM_CLASS_OUSTERS_COAT:
		case Item::ITEM_CLASS_OUSTERS_PENDENT:
		case Item::ITEM_CLASS_OUSTERS_RING:
		case Item::ITEM_CLASS_OUSTERS_STONE:
		case Item::ITEM_CLASS_OUSTERS_WRISTLET:

		case Item::ITEM_CLASS_STONE_ABILITY:

			return true;

		default :
			return false;
	}

	return false;
}

ItemType_t getUpgradeItemType(Item::ItemClass IClass, ItemType_t itemType, ItemType_t upgradeCount)
{
	if (upgradeCount==0)
		return itemType;

	InfoClassManager* pInfoClass = g_pItemInfoManager->getInfoManager(IClass);
	Assert(pInfoClass!=NULL);

	// æ∆¿Ã≈€ æ˜±◊∑π¿ÃµÂ ¡§∫∏∞° DBø° µÈæÓ∞£¥Ÿ. ø©±‚º≠¥¬ ¡÷æÓ¡¯ »∏ºˆ∏∏≈≠ ¥Ÿ¿Ω ItemType¿∏∑Œ ø≈∞‹∞£¥Ÿ.
	ItemType_t newItemType = itemType;

	for ( int i=0; i<upgradeCount; i++ )
	{
		ItemInfo* pItemInfo = pInfoClass->getItemInfo( newItemType );
		Assert(pItemInfo!=NULL);

		newItemType = pItemInfo->getNextItemType();
	}

	//cout << "ItemType Upgrade By Luck: " << itemType << " --[+" << upgradeCount << "]--> ";

/*	int maxItemType = pInfoClass->getInfoCount()-1;

	// ¿ÃπÃ √÷∞Ì æ∆¿Ã≈€¿Œ ∞ÊøÏ
	if (itemType==maxItemType)
	{
		//cout << itemType << "(max)" << endl;
		return itemType;
	}

	int itemTypeGap = 1;

	// æ∆¿Ã≈€ ¥‹∞Ë º¯º≠∞° 2¥‹∞Ëæø µ«æÓ ¿÷¥¬ æ∆¿Ã≈€
	if (IClass==Item::ITEM_CLASS_COAT
		|| IClass==Item::ITEM_CLASS_TROUSER
		|| IClass==Item::ITEM_CLASS_VAMPIRE_COAT)
	{
		itemTypeGap = 2;
	}

	int newItemType = min(maxItemType, itemType + upgradeCount*itemTypeGap);

	// 2¥‹∞Ëæø ∞«≥ ∂ÁæÓæﬂ«“ ∞ÊøÏ
	if (itemTypeGap==2
		&& (itemType & 0x01)!=(newItemType & 0x01)) newItemType -= 1;

	// √÷∞Ì æ∆¿Ã≈€¿Ã ¿Ø¥œ≈©¿œ ºˆµµ ¿÷¥¬µ•.. ¿Ã∞« ª©¡÷¿⁄..
	while (newItemType > itemType)
	{
		ItemInfo* pItemInfo = pInfoClass->getItemInfo( newItemType );
		Assert(pItemInfo!=NULL);

		// ¿Ø¥œ≈©∂Û∏È.. «— ¥‹∞Ëæø ≥∑√Á¡ÿ¥Ÿ.
		if (pItemInfo->isUnique()) newItemType-=itemTypeGap;
		else break;
	}

	//cout << newItemType << endl;*/

	return newItemType;
}

ItemType_t getDowngradeItemType(Item::ItemClass IClass, ItemType_t itemType)
{
	InfoClassManager* pInfoClass = g_pItemInfoManager->getInfoManager(IClass);
	Assert(pInfoClass!=NULL);

	for ( int i=0; i<pInfoClass->getInfoCount(); ++i )
	{
		ItemInfo* pItemInfo = pInfoClass->getItemInfo( i );
		Assert(pItemInfo!=NULL);

		if ( pItemInfo->getNextItemType() == itemType ) return i;
	}

	return itemType;
}

/*
//////////////////////////////////////////////////////////////////////////////
// ≈©∏ÆΩ∫∏∂Ω∫ ∆Æ∏Æ ¿Ã∫•∆ÆøÎ
//////////////////////////////////////////////////////////////////////////////
// ∆Æ∏Æ ¡∂∞¢¿ª ∞Àªˆ
TPOINT checkEventTree( PlayerCreature* pPC, CoordInven_t iX, CoordInven_t iY )
{
	__BEGIN_TRY

	Assert( pPC != NULL );

	TPOINT pt;
	pt.x = -1;
	pt.y = -1;

	Inventory*		pInventory		= pPC->getInventory();
	Item*			pCurItem		= pInventory->getItem( iX, iY );

	if ( pCurItem == NULL )
		return pt;

	ItemType_t		itemType		= pCurItem->getItemType();

	CoordInven_t	startX = iX - itemType % 3; 
	CoordInven_t	startY = iY - itemType / 3;

	if ( pInventory->getWidth() - 3 < startX )
		return pt;
	if ( pInventory->getHeight() - 4 < startY )
		return pt;

	CoordInven_t curIX = 0, curIY = 0;
	ItemType_t compType = 0;

	// ∆Æ∏Æ ¡∂∞¢¿Ã ¡¶¥Î∑Œ ∏¬√Á¡Æ ¿÷¥¬¡ˆ »Æ¿Œ«—¥Ÿ.
	for ( curIY = startY; curIY < startY + 4; curIY++ )
	{
		for ( curIX = startX; curIX < startX + 3; curIX++ )
		{
			pCurItem = pInventory->getItem( curIX, curIY );
			if ( pCurItem == NULL )
				return pt;

			if ( pCurItem->getItemClass() != Item::ITEM_CLASS_EVENT_TREE || 
				 pCurItem->getItemType() != compType )
				return pt;

			compType++;
		}
	}

	pt.x = startX;
	pt.y = startY;

	return pt;

	__END_CATCH
}

// ∞Ì¥ÎπÆ«Â
TPOINT checkEventDocument( PlayerCreature* pPC, CoordInven_t iX, CoordInven_t iY )
{
	__BEGIN_TRY

	Assert( pPC != NULL );

	TPOINT pt;
	pt.x = -1;
	pt.y = -1;

	Inventory*		pInventory		= pPC->getInventory();
	Item*			pCurItem		= pInventory->getItem( iX, iY );

	if ( pCurItem == NULL )
		return pt;

	ItemType_t		itemType		= pCurItem->getItemType();

	// ∞Ì¥ÎπÆ«Â ¡∂∞¢¿∫ 13∫Œ≈Õ Ω√¿€«—¥Ÿ
	itemType = itemType - 13;

	CoordInven_t	startX = iX - itemType % 3; 
	CoordInven_t	startY = iY - itemType / 3;

	if ( pInventory->getWidth() - 3 < startX )
		return pt;
	if ( pInventory->getHeight() - 4 < startY )
		return pt;

	CoordInven_t curIX = 0, curIY = 0;

	// ∞Ì¥ÎπÆ«Â ¡∂∞¢¿∫ 13∫Œ≈Õ Ω√¿€«—¥Ÿ
	ItemType_t compType = 13;

	// ∞Ì¥Î π´«Â ¡∂∞¢¿Ã ¡¶¥Î∑Œ ∏¬√Á¡Æ ¿÷¥¬¡ˆ »Æ¿Œ«—¥Ÿ.
	for ( curIY = startY; curIY < startY + 4; curIY++ )
	{
		for ( curIX = startX; curIX < startX + 3; curIX++ )
		{
			pCurItem = pInventory->getItem( curIX, curIY );
			if ( pCurItem == NULL )
				return pt;

			if ( pCurItem->getItemClass() != Item::ITEM_CLASS_EVENT_TREE || 
				 pCurItem->getItemType() != compType )
				return pt;

			compType++;
		}
	}

	pt.x = startX;
	pt.y = startY;

	return pt;

	__END_CATCH
}

// ¿Œ«¸ -_-;; ¿Ã∞≈ ¿œπ›»≠ ±›πÊ Ω√≈≥ ∞Õ ∞∞¿∫µ• ;; ¿Œ¿⁄∏∏ «œ≥™ ¥ı πﬁµµ∑œ «œ∏È -_-;
// ¥„ø° ƒ˘Ω∫∆Æ ∂ß¥¬ ¿œπ›»≠ Ω√≈∞µµ∑œ «œ¿⁄. §—.§—a
TPOINT checkEventDoll( PlayerCreature* pPC, CoordInven_t iX, CoordInven_t iY )
{
	__BEGIN_TRY

	Assert( pPC != NULL );

	TPOINT pt;
	pt.x = -1;
	pt.y = -1;

	Inventory*		pInventory		= pPC->getInventory();
	Item*			pCurItem		= pInventory->getItem( iX, iY );

	if ( pCurItem == NULL )
		return pt;

	ItemType_t		itemType		= pCurItem->getItemType();

	// ¿Œ«¸ ¡∂∞¢¿∫ 29∫Œ≈Õ Ω√¿€«—¥Ÿ
	itemType = itemType - 29;

	CoordInven_t	startX = iX - itemType % 3; 
	CoordInven_t	startY = iY - itemType / 3;

	if ( pInventory->getWidth() - 3 < startX )
		return pt;
	if ( pInventory->getHeight() - 4 < startY )
		return pt;

	CoordInven_t curIX = 0, curIY = 0;

	// ¿Œ«¸ ¡∂∞¢¿∫ 29∫Œ≈Õ Ω√¿€«—¥Ÿ
	ItemType_t compType = 29;

	// ∞Ì¥Î π´«Â ¡∂∞¢¿Ã ¡¶¥Î∑Œ ∏¬√Á¡Æ ¿÷¥¬¡ˆ »Æ¿Œ«—¥Ÿ.
	for ( curIY = startY; curIY < startY + 4; curIY++ )
	{
		for ( curIX = startX; curIX < startX + 3; curIX++ )
		{
			pCurItem = pInventory->getItem( curIX, curIY );
			if ( pCurItem == NULL )
				return pt;

			if ( pCurItem->getItemClass() != Item::ITEM_CLASS_EVENT_TREE || 
				 pCurItem->getItemType() != compType )
				return pt;

			compType++;
		}
	}

	pt.x = startX;
	pt.y = startY;

	return pt;

	__END_CATCH
}
*/

// ¿œπ›»≠ Ω√≈≤ ∞≈ checkEventTree ∂˚ checkEventDocument ∂˚ checkEventDoll ¿∫ ¡ˆøÏ¿⁄
TPOINT checkEventPuzzle( PlayerCreature* pPC, CoordInven_t iX, CoordInven_t iY, int start)
{
	__BEGIN_TRY

	Assert( pPC != NULL );

	TPOINT pt;
	pt.x = -1;
	pt.y = -1;

	Inventory*		pInventory		= pPC->getInventory();
	Item*			pCurItem		= pInventory->getItem( iX, iY );

	if ( pCurItem == NULL )
		return pt;

	ItemType_t		itemType		= pCurItem->getItemType();

	itemType = itemType - start;

	CoordInven_t	startX = iX - itemType % 3; 
	CoordInven_t	startY = iY - itemType / 3;

	if ( pInventory->getWidth() - 3 < startX )
		return pt;
	if ( pInventory->getHeight() - 4 < startY )
		return pt;

	CoordInven_t curIX = 0, curIY = 0;

	ItemType_t compType = start;

	for ( curIY = startY; curIY < startY + 4; curIY++ )
	{
		for ( curIX = startX; curIX < startX + 3; curIX++ )
		{
			pCurItem = pInventory->getItem( curIX, curIY );
			if ( pCurItem == NULL )
				return pt;

			if ( pCurItem->getItemClass() != Item::ITEM_CLASS_EVENT_TREE || 
				 pCurItem->getItemType() != compType )
				return pt;

			compType++;
		}
	}

	pt.x = startX;
	pt.y = startY;

	return pt;

	__END_CATCH
}

// ¿Œ∫•≈‰∏Æ¿« (X0, Y0) - (X1, y1) π¸¿ß¿« æ∆¿Ã≈€¿ª ¡ˆøÓ¥Ÿ.
void deleteInventoryItem( Inventory* pInventory, CoordInven_t invenX0, CoordInven_t invenY0, CoordInven_t invenX1, CoordInven_t invenY1 )
{
	__BEGIN_TRY
	
	CoordInven_t curIX = 0, curIY = 0;
	Item* pCurItem = 0;

	// ∏¬√Á¡¯ ∆Æ∏Æ ¡∂∞¢¿ª ¡ˆøÓ¥Ÿ.
	for ( curIY = invenY0; curIY <= invenY1; curIY++ )
	{
		for ( curIX = invenX0; curIX <= invenX1; curIX++ )
		{
			pCurItem = pInventory->getItem( curIX, curIY );

			if ( pCurItem != NULL )
			{
				// ¿Œ∫•≈‰∏Æø°º≠ ¡ˆøÓ¥Ÿ.
				pInventory->deleteItem( pCurItem->getObjectID() );

				// DB ø°º≠ ≥Ø∏∞¥Ÿ.
				pCurItem->destroy();

				SAFE_DELETE( pCurItem );
			}
		}
	}

	__END_CATCH
}

typedef struct {
	Item::ItemClass itemClass;
	ItemType_t		itemType;
	CoordInven_t	x;
	CoordInven_t	y;
	ItemNum_t		num;
} NewbieItem;

const int maxNewbieItemNum = 23;
const int maxVampireNewbieItemNum = 21;
const int maxOustersNewbieItemNum = 33;

const NewbieItem NewbieItems[maxNewbieItemNum] =
{
	{ Item::ITEM_CLASS_EFFECT_ITEM,	6, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	7, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	8, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	14, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	15, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	16, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	17, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	18, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	23, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	25, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	26, 0, 0, 9 },
	{ Item::ITEM_CLASS_KEY,		2, 0, 0, 1 },
	{ Item::ITEM_CLASS_SLAYER_PORTAL_ITEM,	2, 0, 0, 1 },
	{ Item::ITEM_CLASS_POTION,	4, 9, 4, 30 },
	{ Item::ITEM_CLASS_POTION,	9, 9, 5, 30 },
	{ Item::ITEM_CLASS_STONE_ABILITY,		0, 0, 0, 1 },
	{ Item::ITEM_CLASS_STONE_ABILITY,		0, 0, 0, 1 },
	{ Item::ITEM_CLASS_STONE_ABILITY,		0, 0, 0, 1 },
	{ Item::ITEM_CLASS_STONE_ABILITY,		0, 0, 0, 1 },
	{ Item::ITEM_CLASS_COMMON_ITEM,		2, 0, 0, 5 },
	{ Item::ITEM_CLASS_COMMON_ITEM,		3, 0, 0, 5 },
	{ Item::ITEM_CLASS_COMMON_ITEM,		4, 0, 0, 5 },
	{ Item::ITEM_CLASS_COMMON_ITEM,		58, 0, 0, 5 },
};

const NewbieItem VampireNewbieItems[maxVampireNewbieItemNum ] =
{
	{ Item::ITEM_CLASS_EFFECT_ITEM,	6, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	7, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	8, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	14, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	15, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	16, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	17, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	18, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	23, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	25, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	26, 0, 0, 9 },
	{ Item::ITEM_CLASS_VAMPIRE_ETC,		1, 0, 0, 9 },
	{ Item::ITEM_CLASS_SERUM,	3, 0, 0, 30 },
	{ Item::ITEM_CLASS_STONE_ABILITY,		0, 0, 0, 1 },
	{ Item::ITEM_CLASS_STONE_ABILITY,		0, 0, 0, 1 },
	{ Item::ITEM_CLASS_STONE_ABILITY,		0, 0, 0, 1 },
	{ Item::ITEM_CLASS_STONE_ABILITY,		0, 0, 0, 1 },
	{ Item::ITEM_CLASS_COMMON_ITEM,		2, 0, 0, 5 },
	{ Item::ITEM_CLASS_COMMON_ITEM,		3, 0, 0, 5 },
	{ Item::ITEM_CLASS_COMMON_ITEM,		4, 0, 0, 5 },
	{ Item::ITEM_CLASS_COMMON_ITEM,		58, 0, 0, 5 },
};

const NewbieItem OustersNewbieItems[maxOustersNewbieItemNum] =
{
	{ Item::ITEM_CLASS_EFFECT_ITEM,	6, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	7, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	8, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	14, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	15, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	16, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	17, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	18, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	23, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	25, 0, 0, 9 },
	{ Item::ITEM_CLASS_EFFECT_ITEM,	26, 0, 0, 9 },
	{ Item::ITEM_CLASS_OUSTERS_STONE,		4, 0, 0, 1 },
	{ Item::ITEM_CLASS_OUSTERS_STONE,		4, 0, 0, 1 },
	{ Item::ITEM_CLASS_OUSTERS_STONE,		4, 0, 0, 1 },
	{ Item::ITEM_CLASS_OUSTERS_STONE,		4, 0, 0, 1 },
	{ Item::ITEM_CLASS_OUSTERS_STONE,		9, 0, 0, 1 },
	{ Item::ITEM_CLASS_OUSTERS_STONE,		9, 0, 0, 1 },
	{ Item::ITEM_CLASS_OUSTERS_STONE,		9, 0, 0, 1 },
	{ Item::ITEM_CLASS_OUSTERS_STONE,		9, 0, 0, 1 },
	{ Item::ITEM_CLASS_OUSTERS_STONE,		14, 0, 0, 1 },
	{ Item::ITEM_CLASS_OUSTERS_STONE,		14, 0, 0, 1 },
	{ Item::ITEM_CLASS_OUSTERS_STONE,		14, 0, 0, 1 },
	{ Item::ITEM_CLASS_OUSTERS_STONE,		14, 0, 0, 1 },
	{ Item::ITEM_CLASS_OUSTERS_CHAKRAM,		14, 0, 0, 1 },
	{ Item::ITEM_CLASS_OUSTERS_WRISTLET,		42, 0, 0, 1 },
	{ Item::ITEM_CLASS_OUSTERS_WRISTLET,		43, 0, 0, 1 },
	{ Item::ITEM_CLASS_OUSTERS_WRISTLET,		44, 0, 0, 1 },
	{ Item::ITEM_CLASS_PUPA,		4, 0, 0, 30 },
	{ Item::ITEM_CLASS_COMPOS_MEI,		4, 0, 0, 30 },
	{ Item::ITEM_CLASS_STONE_ABILITY,		0, 0, 0, 1 },
	{ Item::ITEM_CLASS_STONE_ABILITY,		0, 0, 0, 1 },
	{ Item::ITEM_CLASS_STONE_ABILITY,		0, 0, 0, 1 },
	{ Item::ITEM_CLASS_STONE_ABILITY,		0, 0, 0, 1 },
};

// ¿Œ∫•≈‰∏Æø° √ ∫∏¿⁄øÎ æ∆¿Ã≈€¿ª ≥÷æÓ¡ÿ¥Ÿ.
bool addNewbieItemToInventory( Slayer* pSlayer, bool sendPacket )
	
{
	__BEGIN_TRY

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pSlayer);

	if( sendPacket )
	{
		filelog("NewbieItemError.log", "Someone request packet to addNewbieItemToInventory() function!");
		return false;
	}

	Zone* pZone = pSlayer->getZone();
	Inventory* pInventory = pSlayer->getInventory();
	ObjectRegistry& objectRegister = pZone->getObjectRegistry();

	if( pInventory == NULL ) return false;
	if( pZone == NULL ) return false;

	if( pInventory->getItemNum() != 0 ) return false;

	list<OptionType_t> olist2;
	olist2.push_back(206);
	olist2.push_back(203);

	list<OptionType_t> olist;
	GCCreateItem gcCreateItem;

	for( int i=0; i<maxNewbieItemNum; i++ )
	{
		Item* pItem = NULL;
		if(NewbieItems[i].itemClass != Item::ITEM_CLASS_STONE_ABILITY){
		pItem = g_pItemFactoryManager->createItem( NewbieItems[i].itemClass, NewbieItems[i].itemType, olist );
		}else{
		pItem = g_pItemFactoryManager->createItem( NewbieItems[i].itemClass, NewbieItems[i].itemType, olist2);
		}
		pItem->setCreateType( Item::CREATE_TYPE_GAME );
		pItem->setHeroOption(0);	
		pItem->setHeroOptionAttr(0);
		pItem->setNum( NewbieItems[i].num );
		objectRegister.registerObject( pItem );

		_TPOINT p;
		if (pInventory->getEmptySlot(pItem, p))
		{
			pInventory->addItem(p.x, p.y, pItem);
	           		pItem->create( pSlayer->getName(), STORAGE_INVENTORY, 0, p.x, p.y);
			if(NewbieItems[i].itemClass != Item::ITEM_CLASS_KEY && NewbieItems[i].itemClass != Item::ITEM_CLASS_SLAYER_PORTAL_ITEM){
					pPC->addTimeLimitItem( pItem, 604800);
					pPC->sendTimeLimitItemInfo();	
			}
		}
	}

	return true;
	
	__END_CATCH
}

bool addNewbieGoldToInventory( Slayer* pSlayer, bool sendPacket )
	
{
	__BEGIN_TRY

	if( sendPacket )
	{
		filelog("NewbieItemError.log", "Someone request packet to addNewbieGoldToInventory() function!");
		return false;
	}

	if( pSlayer == NULL ) return false;
	if( pSlayer->getGold() != 0 ) return false;

	pSlayer->setGoldEx(500000);

	return true;

	__END_CATCH
}

bool addNewbieItemToGear( Slayer* pSlayer, bool sendPacket )
	
{
	__BEGIN_TRY

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pSlayer);


	if( sendPacket )
	{
		filelog("NewbieItemError.log", "Someone request packet to addNewbieItemToGear() function!");
		return false;
	}

	if( pSlayer == NULL ) return false;

	Zone* pZone = pSlayer->getZone();
	ObjectRegistry& objectRegister = pZone->getObjectRegistry();

	if( pZone == NULL ) return false;
	
	list<OptionType_t> olist;
	olist.push_back(185);
	olist.push_back(182);
	list<OptionType_t> olist2;
	olist2.push_back(114);
	olist2.push_back(82);
	olist2.push_back(185);

	list<OptionType_t> olist3;
	olist3.push_back(185);
	olist3.push_back(182);

	list<OptionType_t> olist4;
	olist4.push_back(185);
	olist4.push_back(47);

	list<OptionType_t> olist5;
	olist5.push_back(185);
	olist5.push_back(117);

	list<OptionType_t> olist6;
	olist6.push_back(114);
	olist6.push_back(185);

	if( !pSlayer->isWear( Slayer::WEAR_BODY ) && !pSlayer->isWear( Slayer::WEAR_LEG ) )
	{
		Item* pCoat = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_COAT, ((pSlayer->getSex()==MALE)?24:25), olist );
		Item* pTrouser = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_TROUSER, ((pSlayer->getSex()==MALE)?24:25), olist );
		Item* pShoes = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_SHOES,10, olist6);
		Item* pGlove = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_GLOVE,11, olist5);
		Item* pHelm = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_HELM,12, olist6);
		Item* pBelt = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_BELT,7, olist6);
		Item* pNeck = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_NECKLACE,13, olist4);
		Item* pBracelet1 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_BRACELET,13, olist4);
		Item* pBracelet2 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_BRACELET,13, olist4);
		Item* pRing1 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_RING,13, olist4);
		Item* pRing2 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_RING,13, olist4);
		Item* pRing3 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_RING,13, olist4);
		Item* pRing4 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_RING,13, olist4);

		pCoat->setCreateType( Item::CREATE_TYPE_GAME );
		pTrouser->setCreateType( Item::CREATE_TYPE_GAME );
		pShoes->setCreateType( Item::CREATE_TYPE_GAME );
		pGlove->setCreateType( Item::CREATE_TYPE_GAME );
		pHelm->setCreateType( Item::CREATE_TYPE_GAME );
		pBelt->setCreateType( Item::CREATE_TYPE_GAME );
		pNeck->setCreateType( Item::CREATE_TYPE_GAME );
		pBracelet1->setCreateType( Item::CREATE_TYPE_GAME );
		pBracelet2->setCreateType( Item::CREATE_TYPE_GAME );
		pRing1->setCreateType( Item::CREATE_TYPE_GAME );
		pRing2->setCreateType( Item::CREATE_TYPE_GAME );
		pRing3->setCreateType( Item::CREATE_TYPE_GAME );
		pRing4->setCreateType( Item::CREATE_TYPE_GAME );

		pCoat->setHeroOption(0);	
		pCoat->setHeroOptionAttr(0);	
		pTrouser->setHeroOption(0);
		pTrouser->setHeroOptionAttr(0);
		pShoes->setHeroOption(0);
		pShoes->setHeroOptionAttr(0);
		pGlove->setHeroOption(0);
		pGlove->setHeroOptionAttr(0);
		pHelm->setHeroOption(0);
		pHelm->setHeroOptionAttr(0);
		pBelt->setHeroOption(0);
		pBelt->setHeroOptionAttr(0);
		pNeck->setHeroOption(0);
		pNeck->setHeroOptionAttr(0);
		pBracelet1->setHeroOption(0);
		pBracelet1->setHeroOptionAttr(0);
		pBracelet2->setHeroOption(0);
		pBracelet2->setHeroOptionAttr(0);
		pRing1->setHeroOption(0);
		pRing1->setHeroOptionAttr(0);
		pRing2->setHeroOption(0);
		pRing2->setHeroOptionAttr(0);
		pRing3->setHeroOption(0);
		pRing3->setHeroOptionAttr(0);
		pRing4->setHeroOption(0);
		pRing4->setHeroOptionAttr(0);


		objectRegister.registerObject( pCoat );
		objectRegister.registerObject( pTrouser );
		objectRegister.registerObject( pShoes );
		objectRegister.registerObject( pGlove );
		objectRegister.registerObject( pHelm );
		objectRegister.registerObject( pBelt );
		objectRegister.registerObject( pNeck );
		objectRegister.registerObject( pBracelet1 );
		objectRegister.registerObject( pBracelet2 );
		objectRegister.registerObject( pRing1 );
		objectRegister.registerObject( pRing2 );
		objectRegister.registerObject( pRing3 );
		objectRegister.registerObject( pRing4 );

		pCoat->create( pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_BODY, 0, pCoat->getItemID() );
		pTrouser->create( pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_LEG, 0, pTrouser->getItemID() );
		pShoes->create( pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_FOOT, 0, pShoes->getItemID() );
		pGlove->create( pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_HAND3, 0, pGlove->getItemID() );
		pHelm->create( pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_HEAD, 0, pHelm->getItemID() );
		pBelt->create( pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_BELT, 0, pBelt->getItemID() );
		pNeck->create( pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_NECK, 0, pNeck->getItemID() );
		pBracelet1->create( pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_WRIST1, 0, pBracelet1->getItemID() );
		pBracelet2->create( pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_WRIST2, 0, pBracelet2->getItemID() );
		pRing1->create( pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_FINGER1, 0, pRing1 ->getItemID() );
		pRing2->create( pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_FINGER2, 0, pRing2 ->getItemID() );
		pRing3->create( pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_FINGER3, 0, pRing3 ->getItemID() );
		pRing4->create( pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_FINGER4, 0, pRing4 ->getItemID() );


		pPC->addTimeLimitItem( pCoat, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pTrouser, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pShoes, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pGlove, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pHelm, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pBelt, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pNeck, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pBracelet1, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pBracelet2, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pRing1, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pRing2, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pRing3, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pRing4, 604800);
		pPC->sendTimeLimitItemInfo();
		
		pSlayer->wearItem( Slayer::WEAR_BODY, pCoat );
		pSlayer->wearItem( Slayer::WEAR_LEG , pTrouser );
		pSlayer->wearItem( Slayer::WEAR_FOOT, pShoes);
		pSlayer->wearItem( Slayer::WEAR_HAND3, pGlove);
		pSlayer->wearItem( Slayer::WEAR_HEAD, pHelm);
		pSlayer->wearItem( Slayer::WEAR_BELT, pBelt);
		pSlayer->wearItem( Slayer::WEAR_NECK, pNeck);
		pSlayer->wearItem( Slayer::WEAR_WRIST1, pBracelet1);
		pSlayer->wearItem( Slayer::WEAR_WRIST2, pBracelet2);
		pSlayer->wearItem( Slayer::WEAR_FINGER1, pRing1);
		pSlayer->wearItem( Slayer::WEAR_FINGER2, pRing2);
		pSlayer->wearItem( Slayer::WEAR_FINGER3, pRing3);
		pSlayer->wearItem( Slayer::WEAR_FINGER4, pRing4);
	}
	// µµ ΩΩ∑π¿ÃæÓ¿œ ∞ÊøÏ
	switch(pSlayer->getHighestSkillDomain()){
	// µµΩΩ∑π¿ÃæÓ¿Œ ∞ÊøÏ¥Ÿ.
		case 0 :
			{
			Item* pWeapon = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_BLADE,14, olist2);
			pWeapon->setCreateType( Item::CREATE_TYPE_GAME );
			pWeapon->setHeroOption(0);	
			pWeapon->setHeroOptionAttr(0);
			objectRegister.registerObject( pWeapon );
			pWeapon->create( pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_LEFTHAND, 0, pWeapon->getItemID() );
			pPC->addTimeLimitItem( pWeapon, 604800);
			pPC->sendTimeLimitItemInfo();
			pSlayer->wearItem( Slayer::WEAR_LEFTHAND, pWeapon);
			}
		break;
		case 1 :
			{
			Item* pWeapon = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_SWORD,14, olist2);
			pWeapon->setHeroOption(0);	
			pWeapon->setHeroOptionAttr(0);
			pWeapon->setCreateType( Item::CREATE_TYPE_GAME );
			objectRegister.registerObject( pWeapon );
			pWeapon->create( pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_RIGHTHAND, 0, pWeapon->getItemID() );
			pPC->addTimeLimitItem( pWeapon, 604800);
			pPC->sendTimeLimitItemInfo();
			pSlayer->wearItem( Slayer::WEAR_RIGHTHAND, pWeapon);

			Item* pSheid = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_SHIELD,13, olist3);
			pSheid->setHeroOption(0);	
			pSheid->setHeroOptionAttr(0);
			pSheid->setCreateType( Item::CREATE_TYPE_GAME );
			objectRegister.registerObject( pSheid );
			pSheid->create( pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_LEFTHAND, 0, pSheid->getItemID() );
			pPC->addTimeLimitItem( pSheid, 604800);
			pPC->sendTimeLimitItemInfo();
			pSlayer->wearItem( Slayer::WEAR_LEFTHAND, pSheid);
			}
		break;
		case 2 :
			{
			Item* pWeapon = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_AR,14, olist2);
			pWeapon->setHeroOption(0);	
			pWeapon->setHeroOptionAttr(0);
			pWeapon->setCreateType( Item::CREATE_TYPE_GAME );
			objectRegister.registerObject( pWeapon );
			pWeapon->create( pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_LEFTHAND, 0, pWeapon->getItemID() );
			pPC->addTimeLimitItem( pWeapon, 604800);
			pPC->sendTimeLimitItemInfo();
			pSlayer->wearItem( Slayer::WEAR_LEFTHAND, pWeapon);
			}
		break;
		case 3 :
			{
			Item* pWeapon = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_CROSS,12, olist2);
			pWeapon->setHeroOption(0);	
			pWeapon->setHeroOptionAttr(0);
			pWeapon->setCreateType( Item::CREATE_TYPE_GAME );
			objectRegister.registerObject( pWeapon );
			pWeapon->create( pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_LEFTHAND, 0, pWeapon->getItemID() );
			pPC->addTimeLimitItem( pWeapon, 604800);
			pPC->sendTimeLimitItemInfo();
			pSlayer->wearItem( Slayer::WEAR_LEFTHAND, pWeapon);
			}
		break;
		case 4 :
			{
			Item* pWeapon = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_MACE,12, olist2);
			pWeapon->setHeroOption(0);	
			pWeapon->setHeroOptionAttr(0);
			pWeapon->setCreateType( Item::CREATE_TYPE_GAME );
			objectRegister.registerObject( pWeapon );
			pWeapon->create( pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_LEFTHAND, 0, pWeapon->getItemID() );
			pPC->addTimeLimitItem( pWeapon, 604800);
			pPC->sendTimeLimitItemInfo();
			pSlayer->wearItem( Slayer::WEAR_LEFTHAND, pWeapon);
			}
		break;
		default :
		break;
	}


	return true;
	
	__END_CATCH
}
bool addNewbieItemToGear( Vampire* pVampire, bool sendPacket )
	
{
	__BEGIN_TRY

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pVampire);


	if( sendPacket )
	{
		filelog("NewbieItemError.log", "Someone request packet to addNewbieItemToGear() function!");
		return false;
	}

	if( pVampire == NULL ) return false;

	Zone* pZone = pVampire->getZone();
	ObjectRegistry& objectRegister = pZone->getObjectRegistry();

	if( pZone == NULL ) return false;
	
	list<OptionType_t> olist;
	olist.push_back(185);
	olist.push_back(182);
	list<OptionType_t> olist2;
	olist2.push_back(114);
	olist2.push_back(82);
	olist2.push_back(185);

	list<OptionType_t> olist3;
	olist3.push_back(185);
	olist3.push_back(182);

	list<OptionType_t> olist4;
	olist4.push_back(185);
	olist4.push_back(47);

	list<OptionType_t> olist6;
	olist6.push_back(114);
	olist6.push_back(185);

		Item* pCoat = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_VAMPIRE_COAT, ((pVampire->getSex()==MALE)?20:21), olist );
		Item* pEarring1 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_VAMPIRE_EARRING,13, olist6);
		Item* pEarring2 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_VAMPIRE_EARRING,13, olist6);
		Item* pAmulet1 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_VAMPIRE_AMULET,13, olist4);
		Item* pAmulet2 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_VAMPIRE_AMULET,13, olist4);
		Item* pAmulet3 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_VAMPIRE_AMULET,13, olist4);
		Item* pAmulet4 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_VAMPIRE_AMULET,13, olist4);
		Item* pNeck = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_VAMPIRE_NECKLACE,13, olist6);
		Item* pBracelet1 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_VAMPIRE_BRACELET,12, olist4);
		Item* pBracelet2 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_VAMPIRE_BRACELET,12, olist4);
		Item* pRing1 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_VAMPIRE_RING,13, olist4);
		Item* pRing2 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_VAMPIRE_RING,13, olist4);
		Item* pRing3 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_VAMPIRE_RING,13, olist4);
		Item* pRing4 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_VAMPIRE_RING,13, olist4);
		Item* pWeapon = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_VAMPIRE_WEAPON,19, olist2);

		pCoat->setCreateType( Item::CREATE_TYPE_GAME );
		pEarring1->setCreateType( Item::CREATE_TYPE_GAME );
		pEarring2->setCreateType( Item::CREATE_TYPE_GAME );
		pAmulet1->setCreateType( Item::CREATE_TYPE_GAME );
		pAmulet2->setCreateType( Item::CREATE_TYPE_GAME );
		pAmulet3->setCreateType( Item::CREATE_TYPE_GAME );
		pAmulet4->setCreateType( Item::CREATE_TYPE_GAME );
		pNeck->setCreateType( Item::CREATE_TYPE_GAME );
		pBracelet1->setCreateType( Item::CREATE_TYPE_GAME );
		pBracelet2->setCreateType( Item::CREATE_TYPE_GAME );
		pRing1->setCreateType( Item::CREATE_TYPE_GAME );
		pRing2->setCreateType( Item::CREATE_TYPE_GAME );
		pRing3->setCreateType( Item::CREATE_TYPE_GAME );
		pRing4->setCreateType( Item::CREATE_TYPE_GAME );
		pWeapon->setCreateType( Item::CREATE_TYPE_GAME );

		pCoat->setHeroOption(0);	
		pCoat->setHeroOptionAttr(0);	
		pEarring1->setHeroOption(0);
		pEarring1->setHeroOptionAttr(0);
		pEarring2->setHeroOption(0);
		pEarring2->setHeroOptionAttr(0);
		pAmulet1->setHeroOption(0);
		pAmulet1->setHeroOptionAttr(0);
		pAmulet2->setHeroOption(0);
		pAmulet2->setHeroOptionAttr(0);
		pAmulet3->setHeroOption(0);
		pAmulet3->setHeroOptionAttr(0);
		pAmulet4->setHeroOption(0);
		pAmulet4->setHeroOptionAttr(0);
		pNeck->setHeroOption(0);
		pNeck->setHeroOptionAttr(0);
		pBracelet1->setHeroOption(0);
		pBracelet1->setHeroOptionAttr(0);
		pBracelet2->setHeroOption(0);
		pBracelet2->setHeroOptionAttr(0);
		pRing1->setHeroOption(0);
		pRing1->setHeroOptionAttr(0);
		pRing2->setHeroOption(0);
		pRing2->setHeroOptionAttr(0);
		pRing3->setHeroOption(0);
		pRing3->setHeroOptionAttr(0);
		pRing4->setHeroOption(0);
		pRing4->setHeroOptionAttr(0);
		pWeapon->setHeroOption(0);
		pWeapon->setHeroOptionAttr(0);


		pZone->registerObject( pCoat );
		pZone->registerObject( pEarring1 );
		pZone->registerObject( pEarring2 );
		pZone->registerObject( pAmulet1 );
		pZone->registerObject( pAmulet2 );
		pZone->registerObject( pAmulet3 );
		pZone->registerObject( pAmulet4 );
		pZone->registerObject( pNeck );
		pZone->registerObject( pBracelet1 );
		pZone->registerObject( pBracelet2 );
		pZone->registerObject( pRing1 );
		pZone->registerObject( pRing2 );
		pZone->registerObject( pRing3 );
		pZone->registerObject( pRing4 );
		pZone->registerObject( pWeapon );

		pCoat->create( pVampire->getName(), STORAGE_GEAR, 0, Vampire::WEAR_BODY, 0, pCoat->getItemID() );
		pEarring1->create( pVampire->getName(), STORAGE_GEAR, 0, Vampire::WEAR_EARRING1, 0, pEarring1->getItemID() );
		pEarring2->create( pVampire->getName(), STORAGE_GEAR, 0, Vampire::WEAR_EARRING2, 0, pEarring2->getItemID() );
		pAmulet1->create( pVampire->getName(), STORAGE_GEAR, 0, Vampire::WEAR_AMULET1, 0, pAmulet1->getItemID() );
		pAmulet2->create( pVampire->getName(), STORAGE_GEAR, 0, Vampire::WEAR_AMULET2, 0, pAmulet2->getItemID() );
		pAmulet3->create( pVampire->getName(), STORAGE_GEAR, 0, Vampire::WEAR_AMULET3, 0, pAmulet3->getItemID() );
		pAmulet4->create( pVampire->getName(), STORAGE_GEAR, 0, Vampire::WEAR_AMULET4, 0, pAmulet4->getItemID() );
		pNeck->create( pVampire->getName(), STORAGE_GEAR, 0, Vampire::WEAR_NECK, 0, pNeck->getItemID() );
		pBracelet1->create( pVampire->getName(), STORAGE_GEAR, 0, Vampire::WEAR_WRIST1, 0, pBracelet1->getItemID() );
		pBracelet2->create( pVampire->getName(), STORAGE_GEAR, 0, Vampire::WEAR_WRIST2, 0, pBracelet2->getItemID() );
		pRing1->create( pVampire->getName(), STORAGE_GEAR, 0, Vampire::WEAR_FINGER1, 0, pRing1 ->getItemID() );
		pRing2->create( pVampire->getName(), STORAGE_GEAR, 0, Vampire::WEAR_FINGER2, 0, pRing2 ->getItemID() );
		pRing3->create( pVampire->getName(), STORAGE_GEAR, 0, Vampire::WEAR_FINGER3, 0, pRing3 ->getItemID() );
		pRing4->create( pVampire->getName(), STORAGE_GEAR, 0, Vampire::WEAR_FINGER4, 0, pRing4 ->getItemID() );
		pWeapon->create( pVampire->getName(), STORAGE_GEAR, 0, Vampire::WEAR_RIGHTHAND, 0, pWeapon->getItemID() );

		pPC->addTimeLimitItem( pCoat, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pEarring1, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pEarring2, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pAmulet1, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pAmulet2, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pAmulet3, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pAmulet4, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pNeck, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pBracelet1, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pBracelet2, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pRing1, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pRing2, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pRing3, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pRing4, 604800);
		pPC->sendTimeLimitItemInfo();
		pPC->addTimeLimitItem( pWeapon, 604800);
		pPC->sendTimeLimitItemInfo();
		
		pVampire->wearItem( Vampire::WEAR_BODY, pCoat );
		pVampire->wearItem( Vampire::WEAR_EARRING1, pEarring1);
		pVampire->wearItem( Vampire::WEAR_EARRING2, pEarring2);
		pVampire->wearItem( Vampire::WEAR_AMULET1, pAmulet1);
		pVampire->wearItem( Vampire::WEAR_AMULET2, pAmulet2);
		pVampire->wearItem( Vampire::WEAR_AMULET3, pAmulet3);
		pVampire->wearItem( Vampire::WEAR_AMULET4, pAmulet4);
		pVampire->wearItem( Vampire::WEAR_NECK, pNeck);
		pVampire->wearItem( Vampire::WEAR_WRIST1, pBracelet1);
		pVampire->wearItem( Vampire::WEAR_WRIST2, pBracelet2);
		pVampire->wearItem( Vampire::WEAR_FINGER1, pRing1);
		pVampire->wearItem( Vampire::WEAR_FINGER2, pRing2);
		pVampire->wearItem( Vampire::WEAR_FINGER3, pRing3);
		pVampire->wearItem( Vampire::WEAR_FINGER4, pRing4);
		pVampire->wearItem( Vampire::WEAR_RIGHTHAND, pWeapon);

	return true;
	
	__END_CATCH
}

// ¿Œ∫•≈‰∏Æø° √ ∫∏¿⁄øÎ æ∆¿Ã≈€¿ª ≥÷æÓ¡ÿ¥Ÿ.
bool addNewbieItemToInventory( Vampire* pVampire, bool sendPacket )
	
{
	__BEGIN_TRY

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pVampire);

	if( sendPacket )
	{
		filelog("NewbieItemError.log", "Someone request packet to addNewbieItemToInventory() function!");
		return false;
	}

	Zone* pZone = pVampire->getZone();
	Inventory* pInventory = pVampire->getInventory();
	ObjectRegistry& objectRegister = pZone->getObjectRegistry();

	if( pInventory == NULL ) return false;
	if( pZone == NULL ) return false;

	if( pInventory->getItemNum() != 0 ) return false;

	list<OptionType_t> olist2;
	olist2.push_back(206);
	olist2.push_back(203);

	list<OptionType_t> olist;
	GCCreateItem gcCreateItem;

	for( int i=0; i<maxVampireNewbieItemNum; i++ )
	{
		Item* pItem = NULL;
		if(VampireNewbieItems[i].itemClass != Item::ITEM_CLASS_STONE_ABILITY){
		pItem = g_pItemFactoryManager->createItem( VampireNewbieItems[i].itemClass, VampireNewbieItems[i].itemType, olist );
		}else{
		pItem = g_pItemFactoryManager->createItem( VampireNewbieItems[i].itemClass, VampireNewbieItems[i].itemType, olist2);
		}
		pItem->setCreateType( Item::CREATE_TYPE_GAME );
		pItem->setNum( VampireNewbieItems[i].num );
		pItem->setHeroOption(0);	
		pItem->setHeroOptionAttr(0);
		pZone->registerObject( pItem );

		_TPOINT p;
		if (pInventory->getEmptySlot(pItem, p))
		{
			pInventory->addItem(p.x, p.y, pItem);
	           		pItem->create( pVampire->getName(), STORAGE_INVENTORY, 0, p.x, p.y);
			if(VampireNewbieItems[i].itemClass != Item::ITEM_CLASS_VAMPIRE_ETC){
				pPC->addTimeLimitItem( pItem, 604800);
				pPC->sendTimeLimitItemInfo();
			}
		}
	}

	return true;
	
	__END_CATCH
}

bool addNewbieGoldToInventory( Vampire* pVampire, bool sendPacket )
	
{
	__BEGIN_TRY

	if( sendPacket )
	{
		filelog("NewbieItemError.log", "Someone request packet to addNewbieGoldToInventory() function!");
		return false;
	}

	if( pVampire == NULL ) return false;
	if( pVampire->getGold() != 0 ) return false;

	pVampire->setGoldEx(500000);

	return true;

	__END_CATCH
}

bool addNewbieGoldToInventory( Ousters* pOusters, bool sendPacket = false ) 
{
	__BEGIN_TRY

	if( sendPacket )
	{
		filelog("NewbieItemError.log", "Someone request packet to addNewbieItemToInventory() function!");
		return false;
	}

	if( pOusters == NULL ) return false;
	if( pOusters->getGold() != 0 ) return false;

	pOusters->setGoldEx(500000);

	return true;

	__END_CATCH
}

bool addNewbieItemToInventory( Ousters* pOusters, bool sendPacket = false ) 
{
	__BEGIN_TRY

	if( sendPacket )
	{
		filelog("NewbieItemError.log", "Someone request packet to addNewbieGoldToInventory() function!");
		return false;
	}

	if( pOusters == NULL ) return false;

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pOusters);

	Zone* pZone = pOusters->getZone();
	if ( pZone == NULL ) return false;
	
	Inventory* pInventory = pOusters->getInventory();
	if ( pInventory == NULL ) return false;

	list<OptionType_t> olist2;
	olist2.push_back(114);
	olist2.push_back(82);
	olist2.push_back(185);

	list<OptionType_t> olist4;
	olist4.push_back(185);
	olist4.push_back(47);

	if ( pInventory->getItemNum() != 0 ) return false;

	ObjectRegistry& objectRegister = pZone->getObjectRegistry();

	list<OptionType_t> olist1;
	olist1.push_back(206);
	olist1.push_back(203);

	list<OptionType_t> olist;

	for( int i=0; i<maxOustersNewbieItemNum; i++ )
	{
		Item* pItem = NULL;
		if(OustersNewbieItems[i].itemClass == Item::ITEM_CLASS_OUSTERS_STONE){
		pItem = g_pItemFactoryManager->createItem( OustersNewbieItems[i].itemClass, OustersNewbieItems[i].itemType, olist4 );
		}else if(OustersNewbieItems[i].itemClass == Item::ITEM_CLASS_OUSTERS_CHAKRAM || OustersNewbieItems[i].itemClass == Item::ITEM_CLASS_OUSTERS_WRISTLET){
		pItem = g_pItemFactoryManager->createItem( OustersNewbieItems[i].itemClass, OustersNewbieItems[i].itemType, olist2 );
		}else if(OustersNewbieItems[i].itemClass == Item::ITEM_CLASS_STONE_ABILITY){
		pItem = g_pItemFactoryManager->createItem( OustersNewbieItems[i].itemClass, OustersNewbieItems[i].itemType, olist1 );
		}else{
		pItem = g_pItemFactoryManager->createItem( OustersNewbieItems[i].itemClass, OustersNewbieItems[i].itemType, olist );
		}
		pItem->setCreateType( Item::CREATE_TYPE_GAME );
		pItem->setNum( OustersNewbieItems[i].num );
		pItem->setHeroOption(0);	
		pItem->setHeroOptionAttr(0);
		objectRegister.registerObject( pItem );

		_TPOINT p;
		if (pInventory->getEmptySlot(pItem, p))
		{
			pInventory->addItem(p.x, p.y, pItem);
	           		pItem->create( pOusters->getName(), STORAGE_INVENTORY, 0, p.x, p.y);
			pPC->addTimeLimitItem( pItem, 604800);
			pPC->sendTimeLimitItemInfo();
		}
	}

	return true;

	__END_CATCH
}

bool addNewbieItemToGear( Ousters* pOusters, bool sendPacket = false ) 
{
	__BEGIN_TRY

	if( sendPacket )
	{
		filelog("NewbieItemError.log", "Someone request packet to addNewbieItemToInventory() function!");
		return false;
	}

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pOusters);

	if( pOusters == NULL ) return false;
	Zone* pZone = pOusters->getZone();
	Assert( pZone != NULL );

	list<OptionType_t> olist;
	olist.push_back(185);
	olist.push_back(182);

	list<OptionType_t> olist4;
	olist4.push_back(185);
	olist4.push_back(47);

	list<OptionType_t> olist5;
	olist5.push_back(185);
	olist5.push_back(117);

	list<OptionType_t> olist6;
	olist6.push_back(114);
	olist6.push_back(185);

		Item* pCoat = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_OUSTERS_COAT, 12, olist );
		Item* pBoot = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_OUSTERS_BOOTS, 12, olist );
		Item* pCirclet = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_OUSTERS_CIRCLET, 13, olist6);
		Item* pArmsband1 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_OUSTERS_ARMSBAND, 13, olist6);
		Item* pArmsband2 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_OUSTERS_ARMSBAND, 13, olist6);
		Item* pRing1 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_OUSTERS_RING,13, olist4);
		Item* pRing2 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_OUSTERS_RING,13, olist4);
		Item* pPendent1 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_OUSTERS_PENDENT,13, olist4);
		Item* pPendent2 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_OUSTERS_PENDENT,13, olist4);
		Item* pPendent3 = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_OUSTERS_PENDENT,13, olist4);

	pCoat->setCreateType( Item::CREATE_TYPE_GAME );
	pBoot->setCreateType( Item::CREATE_TYPE_GAME );
	pCirclet->setCreateType( Item::CREATE_TYPE_GAME );
	pArmsband1->setCreateType( Item::CREATE_TYPE_GAME );
	pArmsband2->setCreateType( Item::CREATE_TYPE_GAME );
	pRing1->setCreateType( Item::CREATE_TYPE_GAME );
	pRing2->setCreateType( Item::CREATE_TYPE_GAME );
	pPendent1->setCreateType( Item::CREATE_TYPE_GAME );
	pPendent2->setCreateType( Item::CREATE_TYPE_GAME );
	pPendent3->setCreateType( Item::CREATE_TYPE_GAME );

		pCoat->setHeroOption(0);	
		pCoat->setHeroOptionAttr(0);
		pBoot->setHeroOption(0);	
		pBoot->setHeroOptionAttr(0);
		pCirclet->setHeroOption(0);	
		pCirclet->setHeroOptionAttr(0);
		pArmsband1->setHeroOption(0);	
		pArmsband1->setHeroOptionAttr(0);
		pArmsband2->setHeroOption(0);	
		pArmsband2->setHeroOptionAttr(0);
		pRing1->setHeroOption(0);	
		pRing1->setHeroOptionAttr(0);
		pRing2->setHeroOption(0);	
		pRing2->setHeroOptionAttr(0);
		pPendent1->setHeroOption(0);	
		pPendent1->setHeroOptionAttr(0);
		pPendent2->setHeroOption(0);	
		pPendent2->setHeroOptionAttr(0);
		pPendent3->setHeroOption(0);	
		pPendent3->setHeroOptionAttr(0);

	pZone->registerObject( pCoat );
	pZone->registerObject( pBoot );
	pZone->registerObject( pCirclet );
	pZone->registerObject( pArmsband1 );
	pZone->registerObject( pArmsband2 );
	pZone->registerObject( pRing1 );
	pZone->registerObject( pRing2 );
	pZone->registerObject( pPendent1 );
	pZone->registerObject( pPendent2 );
	pZone->registerObject( pPendent3 );

	pCoat->create( pOusters->getName(), STORAGE_GEAR, 0, Ousters::WEAR_COAT, 0, pCoat->getItemID() );
	pBoot->create( pOusters->getName(), STORAGE_GEAR, 0, Ousters::WEAR_BOOTS, 0, pBoot->getItemID() );
	pCirclet->create( pOusters->getName(), STORAGE_GEAR, 0, Ousters::WEAR_CIRCLET, 0, pCirclet->getItemID() );
	pArmsband1->create( pOusters->getName(), STORAGE_GEAR, 0, Ousters::WEAR_ARMSBAND1, 0, pArmsband1->getItemID() );
	pArmsband2->create( pOusters->getName(), STORAGE_GEAR, 0, Ousters::WEAR_ARMSBAND2, 0, pArmsband2->getItemID() );
	pRing1->create( pOusters->getName(), STORAGE_GEAR, 0, Ousters::WEAR_RING1, 0, pRing1->getItemID() );
	pRing2->create( pOusters->getName(), STORAGE_GEAR, 0, Ousters::WEAR_RING2, 0, pRing2->getItemID() );
	pPendent1->create( pOusters->getName(), STORAGE_GEAR, 0, Ousters::WEAR_NECKLACE1, 0, pPendent1->getItemID() );
	pPendent2->create( pOusters->getName(), STORAGE_GEAR, 0, Ousters::WEAR_NECKLACE2, 0, pPendent2->getItemID() );
	pPendent3->create( pOusters->getName(), STORAGE_GEAR, 0, Ousters::WEAR_NECKLACE3, 0, pPendent3->getItemID() );

	pPC->addTimeLimitItem( pCoat, 604800);
	pPC->sendTimeLimitItemInfo();
	pPC->addTimeLimitItem( pBoot, 604800);
	pPC->sendTimeLimitItemInfo();
	pPC->addTimeLimitItem( pCirclet, 604800);
	pPC->sendTimeLimitItemInfo();
	pPC->addTimeLimitItem( pArmsband1, 604800);
	pPC->sendTimeLimitItemInfo();
	pPC->addTimeLimitItem( pArmsband2, 604800);
	pPC->sendTimeLimitItemInfo();
	pPC->addTimeLimitItem( pRing1, 604800);
	pPC->sendTimeLimitItemInfo();
	pPC->addTimeLimitItem( pRing2, 604800);
	pPC->sendTimeLimitItemInfo();
	pPC->addTimeLimitItem( pPendent1, 604800);
	pPC->sendTimeLimitItemInfo();
	pPC->addTimeLimitItem( pPendent2, 604800);
	pPC->sendTimeLimitItemInfo();
	pPC->addTimeLimitItem( pPendent3, 604800);
	pPC->sendTimeLimitItemInfo();



	pOusters->wearItem(Ousters::WEAR_COAT, pCoat);
	pOusters->wearItem(Ousters::WEAR_BOOTS, pBoot);
	pOusters->wearItem(Ousters::WEAR_CIRCLET, pCirclet);
	pOusters->wearItem(Ousters::WEAR_ARMSBAND1, pArmsband1);
	pOusters->wearItem(Ousters::WEAR_ARMSBAND2, pArmsband2);
	pOusters->wearItem(Ousters::WEAR_RING1, pRing1);
	pOusters->wearItem(Ousters::WEAR_RING2, pRing2);
	pOusters->wearItem(Ousters::WEAR_NECKLACE1, pPendent1);
	pOusters->wearItem(Ousters::WEAR_NECKLACE2, pPendent2);
	pOusters->wearItem(Ousters::WEAR_NECKLACE3, pPendent3);

	return true;

	__END_CATCH
}

Item::ItemClass getBestNewbieWeaponClass(Slayer* pSlayer)
	
{
	__BEGIN_TRY

	Assert(pSlayer!=NULL);

	Attr_t STR = pSlayer->getSTR();
	Attr_t DEX = pSlayer->getDEX();
	Attr_t INT = pSlayer->getINT();

	// STR
	if (STR>=DEX && STR>=INT)
	{
		return (rand()%2? Item::ITEM_CLASS_SWORD : Item::ITEM_CLASS_BLADE);
	}
	// DEX
	else if (DEX>=STR && DEX>=INT)
	{
		return Item::ITEM_CLASS_AR;
	}

	// INT
	return (rand()%2? Item::ITEM_CLASS_CROSS : Item::ITEM_CLASS_MACE);


	__END_CATCH
}

void makeOptionList(const string& options, list<OptionType_t>& optionList)
	
{
	uint a = 0, b = 0;

	//////////////////////////////////////////////
	// DEX+1,INT+2
	// a     ba     b
	//////////////////////////////////////////////
	optionList.clear();
	if (options.size()<=1) return;

	do
	{
		b = options.find_first_of(',', a);

		string  optionName = trim( options.substr(a, b-a) );

		OptionType_t optionType;
		
		try {
			optionType = g_pOptionInfoManager->getOptionType(optionName);
		} catch (NoSuchElementException&) {
			throw Error("±◊∑± ø…º«¿Ã æ¯¥‹¥Ÿ.");
		}

		optionList.push_back( optionType );

		a = b+1;

	} while (b!=string::npos && b < options.size() -1);
}

void
saveDissectionItem(Creature* pCreature, Item* pTreasure, int x, int y)
	
{
	__BEGIN_TRY

	Assert(pCreature!=NULL);
	Assert(pTreasure!=NULL);

	// relic¿Ã æ∆¥— ∞ÊøÏ∏∏.. DBø° æ∆¿Ã≈€¿ª ª˝º∫«—¥Ÿ.
	// ««¿« º∫º≠¿œ ∞ÊøÏ ¿ÃπÃ DBø° ¿÷¿∏π«∑Œ DB∏¶ æ˜µ•¿Ã∆Æ«ÿ¡ÿ¥Ÿ.
	switch (pTreasure->getItemClass())
	{	
		case Item::ITEM_CLASS_RELIC:
		{
			// Relic¿∫ DBø° ¿˙¿Â«“ « ø‰ æ¯¥Ÿ.
		}
		break;

		case Item::ITEM_CLASS_BLOOD_BIBLE:
		case Item::ITEM_CLASS_CASTLE_SYMBOL:
		case Item::ITEM_CLASS_SWEEPER:
		{
			char query[128];

			sprintf( query, "ObjectID = %lu, Storage=%u, StorageID=%u, X=%u, Y=%u",
					pTreasure->getObjectID(), STORAGE_ZONE, pCreature->getZone()->getZoneID(), x, y);
			pTreasure->tinysave( query );
		}
		break;

		default:
		{
			ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( pTreasure->getItemClass(), pTreasure->getItemType() );
			Assert(pItemInfo!=NULL);

			// ¿Ø¥œ≈© æ∆¿Ã≈€¿Œ ∞ÊøÏ¥¬
			// æ∆¿Ã≈€ ¿⁄√ºø° ¿Ø¥œ≈© º≥¡§¿ª «ÿ¡÷∞Ì
			// DBø° ¿Ø¥œ≈© æ∆¿Ã≈€¿« ∞≥ºˆ∏¶ ∫Ø∞ÊΩ√ƒ—¡ÿ¥Ÿ.
			//
			// (*) ∏ÛΩ∫≈Õ∞° ¡◊æ˙¿ª ∂ß,
			//     ∏ÛΩ∫≈Õ æ»ø° ¿÷¥¬ æ∆¿Ã≈€ø°¥¬ ¿Ø¥œ??º≥¡§µµ æ»«œ∞Ì
			//     DBø°µµ ∞≥ºˆ ∫Ø∞Ê¿ª æ»«—¥Ÿ. ±◊∑°º≠, ¡ˆøˆ¡Ÿ∂ßµµ π´Ω√«—¥Ÿ.
			//     «ˆ¿Á ¿Ø¥œ≈© æ∆¿Ã≈€¿∫ ∏ÛΩ∫≈Õ∏¶ ≈Î«ÿº≠∏∏ ≥™≈∏≥™∞Ì
			//     CGDissectionCorpse∏¶ ≈Î«ÿº≠ ª˝º∫(!)µ«∞Ì
			//     EffectDecayItem¿ª ≈Î«ÿº≠∏∏ ¡¶∞≈µ»¥Ÿ.

			if (pItemInfo->isUnique())
			{
				pTreasure->setUnique();
				UniqueItemManager::createItem(pTreasure->getItemClass(), pTreasure->getItemType());
				filelog("uniqueItem.txt", "[CGDissectionCorpse] %s %s", pCreature->getName().c_str(), pTreasure->toString().c_str());
			}

			// ±‚¡∏¿« ItemID∏¶ ±◊¥Î∑Œ ¿Ø¡ˆ«—¥Ÿ.
			// ItemID∞° 0¿Ã∏È.. create()«“∂ß ¥ŸΩ√ ItemID∏¶ πﬁ¥¬¥Ÿ.
			// by sigi. 2002.10.28
			pTreasure->create("", STORAGE_ZONE, pCreature->getZone()->getZoneID(), x, y, pTreasure->getItemID() );
		}
	}

	__END_CATCH
}

bool canDecreaseDurability( Item* pItem )
	
{
	__BEGIN_TRY

	if ( pItem == NULL ) return false;
	if ( pItem->isUnique() ) return false;
	if ( pItem->isTimeLimitItem() ) return false;
	if ( pItem->isQuestItem() ) return false;
	if ( pItem->isFlagItem() ) return false;

	switch ( pItem->getItemClass() )
	{
		case Item::ITEM_CLASS_VAMPIRE_AMULET:
		case Item::ITEM_CLASS_COUPLE_RING:
		case Item::ITEM_CLASS_VAMPIRE_COUPLE_RING:
		case Item::ITEM_CLASS_SWEEPER:
		case Item::ITEM_CLASS_CORE_ZAP:
		case Item::ITEM_CLASS_ETHEREAL:
		case Item::ITEM_CLASS_NECKLACEZAP:
		case Item::ITEM_CLASS_COATZAP:
		case Item::ITEM_CLASS_CARRYING_RECEIVER:
		case Item::ITEM_CLASS_DERMIS:
		case Item::ITEM_CLASS_FASCIA:
			return false;
		default:
			break;
	}
	return true;
		
	__END_CATCH
}

bool canSell( Item* pItem )
{



	if ( pItem==NULL ) return false;
	if ( pItem->isTimeLimitItem() ) return true;

	if ( pItem->isUnique() ) return false;
	if ( isCoupleRing( pItem ) ) return false;


	if ( pItem->isQuestItem() ) return true;
	if ( pItem->isFlagItem() ) return false;
	// ƒ˘Ω∫∆Æ æ∆¿Ã≈€¿∫ 50ø¯ø° ∆» ºˆ ¿÷¥Ÿ.
	//if ( pItem->isTimeLimitItem() ) return false;

	Item::ItemClass itemClass = pItem->getItemClass();

	if ( itemClass==Item::ITEM_CLASS_MOTORCYCLE
		|| itemClass==Item::ITEM_CLASS_KEY
		|| itemClass==Item::ITEM_CLASS_CORPSE
		|| itemClass==Item::ITEM_CLASS_MONEY
		|| itemClass==Item::ITEM_CLASS_PET_ITEM
		//          || itemClass==Item::ITEM_CLASS_EVENT_GIFT_BOX
		|| isRelicItem( itemClass )
	)
		return false;
	if ( itemClass == Item::ITEM_CLASS_SWEEPER ) return false;

	// edit by coffee 2007-7-7 –ﬁ∏ƒ»ŒŒÒŒÔ∆∑ …˙√¸¬›–˝Œ™ø…≥ˆ €
	if ( itemClass==Item::ITEM_CLASS_EVENT_ITEM && pItem->getItemType() == 31 ) return true;

	if ( itemClass==Item::ITEM_CLASS_EVENT_ITEM && pItem->getItemType() != 28 ) return false;

	return true;
}

bool canPutInStash( Item* pItem )
{
	if ( pItem==NULL ) return false;
	if ( pItem->isUnique() ) return false;
	if ( pItem->isTimeLimitItem() ) return false;
	if ( isRelicItem( pItem ) ) return false;
	if ( isCoupleRing( pItem ) ) return false;
	if ( pItem->isQuestItem() ) return false;
	if ( pItem->isFlagItem() ) return false;

	Item::ItemClass itemClass = pItem->getItemClass();

	if ( itemClass == Item::ITEM_CLASS_EVENT_ITEM ) return false;
	if ( itemClass == Item::ITEM_CLASS_SWEEPER ) return false;

	if ( itemClass == Item::ITEM_CLASS_LUCKY_BAG && pItem->getItemType() == 3 ) return false;
	if ( itemClass == Item::ITEM_CLASS_EVENT_ITEM && pItem->getItemType() == 28 ) return false;

	return true;
}

bool canTrade( Item* pItem )
{
	if ( pItem==NULL ) return false;
	if ( isRelicItem( pItem ) ) return false;
	if ( isCoupleRing( pItem ) ) return false;
	if ( pItem->isTimeLimitItem() ) return false;
	if ( pItem->isQuestItem() ) return false;
	if ( pItem->isFlagItem() ) return false;

	Item::ItemClass itemClass = pItem->getItemClass();
	ItemType_t itemType = pItem->getItemType();

	if ( itemClass == Item::ITEM_CLASS_EVENT_ITEM )
		return false;
	if ( itemClass == Item::ITEM_CLASS_SWEEPER ) return false;

	// π›¥ﬁ ƒ´µÂ¥¬ ∆Æ∑π¿ÃµÂ «“ ºˆ æ¯¥Ÿ.
	if ( itemClass == Item::ITEM_CLASS_MOON_CARD && pItem->getItemType() == 0 )
		return false;

	// «¡∏ÆπÃæˆ √º«Ë±« ¡∂∞¢ -_-
	if ( itemClass == Item::ITEM_CLASS_LUCKY_BAG && pItem->getItemType() == 3 ) return false;
	if ( itemClass == Item::ITEM_CLASS_EVENT_ITEM && pItem->getItemType() == 28 ) return false;
	if ( itemClass == Item::ITEM_CLASS_EFFECT_ITEM && pItem->getItemType() >= 4 && pItem->getItemType() <= 6 ) return false;

	// ¿Ã∫•∆Æ ∂±±π¿∫ ±≥»Ø ∫“∞°.
	if ( itemClass == Item::ITEM_CLASS_EVENT_STAR && ( itemType >= 17 && itemType <= 21 ) )
		return false;

	// ∫π¡∂∏Æ æ∆¿Ã≈€ ±≥»Ø ∫“∞°
	if ( itemClass == Item::ITEM_CLASS_MIXING_ITEM && itemType == 18 )
		return false;

	if ( itemClass == Item::ITEM_CLASS_SUB_INVENTORY)
		return false;

	return true;
}
bool isCoupleRing( Item* pItem )
{
	switch ( pItem->getItemClass() )
	{
		case Item::ITEM_CLASS_COUPLE_RING:
		case Item::ITEM_CLASS_VAMPIRE_COUPLE_RING:
			return true;
		default:
			return false;
	}
}

bool suitableItemClass( Item::ItemClass iClass, SkillDomainType_t domainType )
{
	switch ( domainType )
	{
		case SKILL_DOMAIN_BLADE:
			if ( iClass == Item::ITEM_CLASS_BLADE ) return true;
			return false;
			
		case SKILL_DOMAIN_SWORD:
			if ( iClass == Item::ITEM_CLASS_SWORD ) return true;
			return false;
			
		case SKILL_DOMAIN_GUN:
			if ( iClass == Item::ITEM_CLASS_AR ||
				 iClass == Item::ITEM_CLASS_SR ||
				 iClass == Item::ITEM_CLASS_SMG ||
				 iClass == Item::ITEM_CLASS_SG ) return true;
			return false;
			
		case SKILL_DOMAIN_HEAL:
			if ( iClass == Item::ITEM_CLASS_CROSS ) return true;
			return false;
			
		case SKILL_DOMAIN_ENCHANT:
			if ( iClass == Item::ITEM_CLASS_MACE ) return true;
			return false;
			
		case SKILL_DOMAIN_ETC:
			return false;
			
		case SKILL_DOMAIN_VAMPIRE:
			if ( iClass == Item::ITEM_CLASS_VAMPIRE_WEAPON ) return true;
			return false;
			
		default:
			return false;
	}

	Assert( false );
}

void setItemGender( Item* pItem, GenderRestriction gender )
{
	if ( gender == GENDER_BOTH || gender == GENDER_MAX ) return;

	ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( pItem->getItemClass(), pItem->getItemType() );
	if ( pItemInfo->getReqGender() == gender ) return;
	if ( pItemInfo->getReqGender() == GENDER_BOTH || pItemInfo->getReqGender() == GENDER_MAX ) return;

	int genderDiff = (int)gender - (int)pItemInfo->getReqGender();
	Assert( genderDiff == 1 || genderDiff == -1 );

	pItem->setItemType( pItem->getItemType() + genderDiff );
}

bool bTraceLog( Item* pItem )
{
	Item::ItemClass iClass = pItem->getItemClass();

	// PetItem ¿∫ π´¡∂∞« ≥≤±‰¥Ÿ
	if ( iClass == Item::ITEM_CLASS_PET_ITEM || iClass == Item::ITEM_CLASS_CORE_ZAP )
		return true;

	// ∆˜º«¿« ∆ƒ∂ı ªÁ≈¡¿Ã∂˚ »Úªˆ ∂±±π¿∫ ≥≤±‰¥Ÿ
	if ( iClass == Item::ITEM_CLASS_POTION &&
			( pItem->getItemType() == 10 || pItem->getItemType() == 11 ) )
		return true;

	// Serum ø° ª°∞£ ªÁ≈¡¿∫ ≥≤±‰¥Ÿ
	if ( iClass == Item::ITEM_CLASS_SERUM && 
			( pItem->getItemType() == 4 || pItem->getItemType() == 5 ) )
		return true;

	switch ( iClass )
	{
		case Item::ITEM_CLASS_CARRYING_RECEIVER:
		case Item::ITEM_CLASS_SHOULDER_ARMOR:
		case Item::ITEM_CLASS_DERMIS:
		case Item::ITEM_CLASS_PERSONA:
		case Item::ITEM_CLASS_FASCIA:
		case Item::ITEM_CLASS_MITTEN:
			return true;
			break;
		default:
			break;
	}

	if ( iClass == Item::ITEM_CLASS_MOTORCYCLE ||
		 iClass == Item::ITEM_CLASS_POTION ||
		 iClass == Item::ITEM_CLASS_WATER ||
		 iClass == Item::ITEM_CLASS_HOLYWATER ||
		 iClass == Item::ITEM_CLASS_ETC ||
		 iClass == Item::ITEM_CLASS_KEY ||
		 iClass == Item::ITEM_CLASS_MAGAZINE ||
		 iClass == Item::ITEM_CLASS_BOMB_MATERIAL ||
		 iClass == Item::ITEM_CLASS_BOMB ||
		 iClass == Item::ITEM_CLASS_MINE ||
		 iClass == Item::ITEM_CLASS_LEARNINGITEM ||
		 iClass == Item::ITEM_CLASS_MONEY ||
		 iClass == Item::ITEM_CLASS_CORPSE ||
		 iClass == Item::ITEM_CLASS_SKULL ||
		 iClass == Item::ITEM_CLASS_SERUM ||
		 iClass == Item::ITEM_CLASS_VAMPIRE_ETC ||
		 iClass == Item::ITEM_CLASS_SLAYER_PORTAL_ITEM ||
		 iClass == Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM ||
		 iClass == Item::ITEM_CLASS_RELIC ||
		 iClass == Item::ITEM_CLASS_BLOOD_BIBLE ||
		 iClass == Item::ITEM_CLASS_CASTLE_SYMBOL ||
		 iClass == Item::ITEM_CLASS_DYE_POTION ||
		 iClass == Item::ITEM_CLASS_RESURRECT_ITEM ||
		 iClass == Item::ITEM_CLASS_SWEEPER ||
		 pItem->isTimeLimitItem() ) return false;

	const list<OptionType_t>& optionList = pItem->getOptionTypeList();
	list<OptionType_t>::const_iterator itr;

	// ¿˙«◊ ø…º«¿Ã ¿÷¥¬ ∞« ±‚∑œ ≥≤±‰¥Ÿ
	for (itr=optionList.begin(); itr!=optionList.end(); itr++)
	{
		OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo( *itr );
		if (pOptionInfo==NULL) return false;

		OptionClass optionClass = pOptionInfo->getClass();

		if ( optionClass == OPTION_POISON ||
			 optionClass == OPTION_ACID ||
			 optionClass == OPTION_CURSE ||
			 optionClass == OPTION_BLOOD ) return true;
	}

	// ∫Ò?Í∂?∆Ê¥¯∆Æ¥¬ ±‚∑œ ≥≤±‰¥Ÿ
	// Event Star ¥¬ ±‚∑œ ≥≤±‰¥Ÿ
	if ( iClass == Item::ITEM_CLASS_QUEST_ITEM ||
		 iClass == Item::ITEM_CLASS_EVENT_STAR ||
		 iClass == Item::ITEM_CLASS_MIXING_ITEM ) return true;

	// ±◊ ø‹¿« æ∆¿Ã≈€¿Œ ∞ÊøÏ 3¥‹ ¿Ã«œ¥¬ ±‚∑œ ≥≤±‚¡ˆ æ ¥¬¥Ÿ
	if ( (int)(pItem->getItemType()) < 3 ) return false;

	return true;
}

void remainTraceLog ( Item* pItem, const string& preOwner, const string& owner, ItemTraceLogType logType, ItemTraceDetailType detailType )
	
{
	__BEGIN_TRY

	Assert( pItem != NULL);

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		string optionName = getOptionTypeToString(pItem->getOptionTypeList());

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery(
				"INSERT INTO ItemTraceLog (ItemID, ItemClass, ItemType, OptionType, PreOwnerID, OwnerID, LogType, DetailType, Time) VALUES ( %u,'%s',%u,'%s','%s','%s','%s','%s',now() )",
				pItem->getItemID(),
				ItemClass2ShortString[ (int)(pItem->getItemClass()) ].c_str(),
				pItem->getItemType(),
				optionName.c_str(),
				preOwner.c_str(),
				owner.c_str(),
				ItemTraceLogType2String[ (int)logType ].c_str(),
				ItemTraceLogDetailType2String[ (int)detailType ].c_str()
				);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

void remainTraceLogNew ( Item* pItem, const string& owner, ITLType logType, ITLDType detailType, ZoneID_t zid=0, int x=0, int y=0)
	
{
	__BEGIN_TRY

	Assert( pItem != NULL);

/*	Statement* pStmt = NULL;

	BEGIN_DB
	{
		string optionName = getOptionTypeToString(pItem->getOptionTypeList());

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery(
				"INSERT INTO ItemTrace2Log (ItemID, ItemClass, ItemType, OptionType, OwnerID, ActionType, DetailType, Zone, X, Y ,Time) VALUES ( %u,'%s',%u,'%s','%s','%s','%s','%s','%d','%d','%d',now() )",
				pItem->getItemID(),
				ItemClass2ShortString[ (int)(pItem->getItemClass()) ].c_str(),
				pItem->getItemType(),
				optionName.c_str(),
				owner.c_str(),
				ITLType2String[ (int)logType ].c_str(),
				ITLDType2String[ (int)detailType ].c_str(),
				zid,
				x,
				y
				);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
*/
	__END_CATCH
}

void remainMoneyTraceLog ( const string& preOwner, const string& owner, ItemTraceLogType logType, ItemTraceDetailType detailType, int amount )
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery(
				"INSERT INTO MoneyTraceLog (PreOwnerID, OwnerID, LogType, DetailType, Amount, Time) VALUES ( '%s','%s','%s','%s', %d, now() )",
				preOwner.c_str(),
				owner.c_str(),
				ItemTraceLogType2String[ (int)logType ].c_str(),
				ItemTraceLogDetailType2String[ (int)detailType ].c_str(),
				amount
				);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

// Web ø°º≠ ªÍ æ∆¿Ã≈€¿ª ∏∏µÂ¥¬ «‘ºˆ
Item* createItemByGoodsID( DWORD goodsID )
{
	GoodsInfo* pGoodsInfo = g_pGoodsInfoManager->getGoodsInfo( goodsID );
	if ( pGoodsInfo == NULL )
	{
		filelog( "buyItemBug.txt", "buyID(%d) ø° «ÿ¥Á«œ¥¬ ªÛ«∞¿Ã æ¯Ω¿¥œ¥Ÿ.", (int)goodsID );
		return NULL;
	}

	Item::ItemClass ItemClass = pGoodsInfo->getItemClass();
	ItemType_t ItemType = pGoodsInfo->getItemType();
	Grade_t Grade = pGoodsInfo->getGrade();
	list<OptionType_t> optionTypeList = pGoodsInfo->getOptionTypeList();
	list<OptionType_t> optionTypeList2 = pGoodsInfo->getOptionTypeList2();
	Silver_t Silver = pGoodsInfo->getSilver();
	EnchantLevel_t EnchantLevel = pGoodsInfo->getEnchantLevel();
	EnchantLevel_t HeroOption = pGoodsInfo->getHeroOption();
	EnchantLevel_t HeroOptionAttr = pGoodsInfo->getHeroOptionAttr();
	int Num = pGoodsInfo->getNum();
	bool bTimeLimit = pGoodsInfo->isTimeLimit();
	int Hour = pGoodsInfo->getHour();

	if ( !g_pItemInfoManager->isPossibleItem( ItemClass, ItemType, optionTypeList ) )
	{
		filelog( "buyItemBug.txt", "buyID(%d) ø° «ÿ¥Á«œ¥¬ æ∆¿Ã≈€¿∫ ∏∏µÈ ºˆ æ¯Ω¿¥œ¥Ÿ.", (int)goodsID );
		return NULL;
	}

	Item* pItem	= g_pItemFactoryManager->createItem( ItemClass, ItemType, optionTypeList );
	if ( pItem == NULL )
	{
		filelog( "buyItemBug.txt", "buyID(%d) ø° «ÿ¥Á«œ¥¬ æ∆¿Ã≈€ ∏∏µÈ±‚ø° Ω«∆–«ﬂΩ¿¥œ¥Ÿ.", (int)goodsID );
		return NULL;
	}

	pItem->setGrade(Grade);
	pItem->setOptionType2(optionTypeList2);
	pItem->setSilver(Silver);
	pItem->setEnchantLevel(EnchantLevel);
	pItem->setHeroOption(HeroOption);
	pItem->setHeroOptionAttr(HeroOptionAttr);
	pItem->setNum(Num);
	pItem->setTimeLimitItem( bTimeLimit );
	pItem->setHour( Hour );
	pItem->setCreateType( Item::CREATE_TYPE_MALL );

	if ( ItemClass == Item::ITEM_CLASS_PET_ITEM )
	{
		PetItem* pPetItem = dynamic_cast<PetItem*>(pItem);
		Assert( pPetItem != NULL );

		PetType_t petType = ItemType;
		PetTypeInfo* pPetTypeInfo = PetTypeInfoManager::getInstance()->getPetTypeInfo(petType);
		PetExpInfo* pPetExpInfo = PetExpInfoManager::Instance().getPetExpInfo(48);//modify by viva for PetInfo
		if ( pPetTypeInfo == NULL || pPetExpInfo == NULL )
		{
			filelog( "buyItemBug.txt", "buyID(%d) ø° «ÿ¥Á«œ¥¬ ∆Í æ∆¿Ã≈€ ¡§∫∏??¿ÃªÛ«’¥œ¥Ÿ.", (int)goodsID );
			SAFE_DELETE( pItem );
			return NULL;
		}

		PetInfo* pPetInfo = new PetInfo;

		pPetInfo->setPetType( petType );
		pPetInfo->setPetLevel(49);//modify by viva for PetInfo
		pPetInfo->setPetCreatureType(pPetTypeInfo->getPetCreatureType(49));//modify by viva for PetInfo
		pPetInfo->setPetAttr(23);//modify by viva for PetInfo
		pPetInfo->setPetExp( pPetExpInfo->getPetGoalExp() );
		//pPetInfo->setPetExp(1999998000);
		pPetInfo->setPetAttrLevel(11);//modify by viva for PetInfo
		pPetInfo->setFoodType(0);
		pPetInfo->setGamble(1);//modify by viva for PetInfo
		pPetInfo->setCutHead(0);//modify by viva for PetInfo
		pPetInfo->setAttack(1);//modify by viva for PetInfo
		pPetInfo->setPetHP(5760);
		pPetInfo->setFeedTime( VSDateTime::currentDateTime() );

		// æÁπÊ«‚ ∏µ≈©
		pPetItem->setPetInfo( pPetInfo );
		pPetInfo->setPetItem( pPetItem );
	}

	return pItem;
}

bool bWinPrize( DWORD rewardID, DWORD questLevel )
{
	bool Lotto = false;
	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery(
				"UPDATE EventQuestRewardSchedule SET Count = Count - 1 WHERE Count > 0 AND RewardID = %d AND QuestLevel = %d AND Time < now() LIMIT 1", rewardID, questLevel );

		if ( pStmt->getAffectedRowCount() > 0 )
			Lotto = true;

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	return Lotto;
}

void deleteFlagEffect( Corpse* pFlagPole, Item* pFlag )
{
	if ( pFlag == NULL ) return;
	if ( !pFlag->isFlagItem() ) return;

	if ( !pFlagPole->isFlag( Effect::EFFECT_CLASS_FLAG_INSERT ) ) return;
	Effect* pEffect = pFlagPole->getEffectManager().findEffect(Effect::EFFECT_CLASS_FLAG_INSERT);
	if ( pEffect != NULL ) pEffect->setDeadline(0);
}

void countResurrectItem()
{
	__BEGIN_TRY
	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery(
				"UPDATE ResurrectItemCount SET Count=Count+1");

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	__END_CATCH
}

Item* fitToPC( Item* pItem, PlayerCreature* pPC )
{
	if ( pItem == NULL || pPC == NULL ) return pItem;

	if ( isSlayerWeapon( pItem->getItemClass() ) && pPC->isSlayer() )
	{
		Item::ItemClass targetClass = Item::ITEM_CLASS_MAX;
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		int add = 0;
		switch ( pSlayer->getHighestSkillDomain() )
		{
			case SKILL_DOMAIN_BLADE:
				{
					targetClass = Item::ITEM_CLASS_BLADE;
				}
				break;
			case SKILL_DOMAIN_SWORD:
				{
					targetClass = Item::ITEM_CLASS_SWORD;
				}
				break;
			case SKILL_DOMAIN_GUN:
				{
					targetClass = Item::ITEM_CLASS_AR;
				}
				break;
			case SKILL_DOMAIN_HEAL:
				{
					targetClass = Item::ITEM_CLASS_CROSS;
					add = -2;
				}
				break;
			case SKILL_DOMAIN_ENCHANT:
				{
					targetClass = Item::ITEM_CLASS_MACE;
					add = -2;
				}
				break;
			default:
				break;
		}

		if ( targetClass != Item::ITEM_CLASS_MAX && targetClass != pItem->getItemClass() )
		{
			Item* pNewItem = g_pItemFactoryManager->createItem( targetClass, pItem->getItemType() + add, pItem->getOptionTypeList() );
			if ( pNewItem != NULL )
			{
				SAFE_DELETE( pItem );
				pItem = pNewItem;
			}
		}
	}

	if ( isOustersWeapon( pItem->getItemClass() ) && pPC->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
		ElementalDomain maxDomain = ELEMENTAL_DOMAIN_FIRE;
		SkillBonus_t maxBonus = pOusters->getSkillPointCount( maxDomain );

		for ( ElementalDomain domain = ELEMENTAL_DOMAIN_WATER ; domain <= ELEMENTAL_DOMAIN_COMBAT ; ++(int&)domain )
		{
			if ( domain == ELEMENTAL_DOMAIN_WIND ) continue;
			SkillBonus_t bonus = pOusters->getSkillPointCount( domain );
			if ( domain == ELEMENTAL_DOMAIN_COMBAT ) bonus += pOusters->getSkillPointCount( ELEMENTAL_DOMAIN_ELEMENTAL_COMBAT );
			if ( bonus > maxBonus )
			{
				maxBonus = bonus;
				maxDomain = domain;
			}
		}

		Item::ItemClass targetClass = Item::ITEM_CLASS_OUSTERS_WRISTLET;
		int add = 0;

		switch ( maxDomain )
		{
			case ELEMENTAL_DOMAIN_FIRE:
				{
				}
				break;
			case ELEMENTAL_DOMAIN_WATER:
				{
					add = 10;
				}
				break;
			case ELEMENTAL_DOMAIN_EARTH:
				{
					add = 20;
				}
				break;
			case ELEMENTAL_DOMAIN_WIND:
				{
				}
				break;
			case ELEMENTAL_DOMAIN_COMBAT:
				{
					targetClass = Item::ITEM_CLASS_OUSTERS_CHAKRAM;
				}
				break;
			default:
				break;
		}

		if ( targetClass == pItem->getItemClass() )
		{
			pItem->setItemType( pItem->getItemType() + add );
		}
		else
		{
			Item* pNewItem = g_pItemFactoryManager->createItem( targetClass, pItem->getItemType() + add, pItem->getOptionTypeList() );
			if ( pNewItem != NULL )
			{
				SAFE_DELETE( pItem );
				pItem = pNewItem;
			}
		}
	}

	if ( pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_STONE && pPC->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
		ElementalDomain maxDomain = ELEMENTAL_DOMAIN_FIRE;
		SkillBonus_t maxBonus = pOusters->getSkillPointCount( maxDomain );

		for ( ElementalDomain domain = ELEMENTAL_DOMAIN_WATER ; domain <= ELEMENTAL_DOMAIN_EARTH ; ++(int&)domain )
		{
			SkillBonus_t bonus = pOusters->getSkillPointCount( domain );
			if ( bonus > maxBonus )
			{
				maxBonus = bonus;
				maxDomain = domain;
			}
		}

		int add = 0;

		switch ( maxDomain )
		{
			case ELEMENTAL_DOMAIN_FIRE:
				{
				}
				break;
			case ELEMENTAL_DOMAIN_WATER:
				{
					add = 5;
				}
				break;
			case ELEMENTAL_DOMAIN_EARTH:
				{
					add = 10;
				}
				break;
			default:
				break;
		}

		pItem->setItemType( pItem->getItemType() + add );
	}

	setItemGender( pItem, (pPC->getSex()==MALE)?GENDER_MALE:GENDER_FEMALE );

	return pItem;
}

#if defined(__THAILAND_SERVER__) || defined(__CHINA_SERVER__)
	
ItemType_t getItemTypeByItemLimit( Item::ItemClass itemClass, ItemType_t itemType )
{
	static ItemType_t limitItemType = (ItemType_t)SystemAvailabilitiesManager::getInstance()->getItemLevelLimit();
	ItemType_t rItemType = itemType;

	//  cout << "Original itemType : " << itemType << " , SystemItemLimit : " << limitItemType << endl;

	ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( itemClass, rItemType );

	// øπø‹ªÁ«◊. æ∆¿Ã≈€ ∑π∫ß¿Ã æ¯¥¬ æ∆¿Ã≈€¿œ ∞ÊøÏ ∆–Ω∫
	if ( pItemInfo->getItemLevel() == 99 || pItemInfo->getItemLevel() == 255 )
	{
		return true;
	}

	int counter = 0;    // ∏∏æ‡¿« ∏∏æ‡¿ª ¿ß«— ƒ´øÓ≈Õ. π´«—∑Á«¡∞° µŒ∑¡øˆ~

	//cout << "i. ItemLevel : " << pItemInfo->getItemLevel() << endl;

	while ( limitItemType <= pItemInfo->getItemLevel() && counter++ < 10 )
	{
		rItemType = getDowngradeItemType( itemClass, rItemType );
		pItemInfo = g_pItemInfoManager->getItemInfo( itemClass, rItemType );
	}

	//  cout << "o. ItemLevel : " << pItemInfo->getItemLevel() << endl;
	//  cout << "Return itemType : " << rItemType << endl;
	return rItemType;
}

#endif // __THAILAND_SERVER__
