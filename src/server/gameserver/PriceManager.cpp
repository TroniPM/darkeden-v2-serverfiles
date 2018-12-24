//////////////////////////////////////////////////////////////////////////////
// Filename    : PriceManager.cpp
// Written By  : �輺��
// Description :
// �������� �������� ��� �� ��, �� �ŸŰ����� �����ϴ� Ŭ�����̴�.
// ���������δ� ItemInfoManager�� ���� ������ �̿��� ����� �Ѵ�.
//////////////////////////////////////////////////////////////////////////////

#include "PriceManager.h"
#include "ItemInfoManager.h"
#include "OptionInfo.h"
#include "Item.h"
#include "ItemUtil.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "VariableManager.h"
#include "GamePlayer.h"

#include "item/Skull.h"
#include "item/SlayerPortalItem.h"
#include "item/VampirePortalItem.h"
#include "item/OustersSummonItem.h"

// global variable definition
PriceManager* g_pPriceManager = NULL;

// constants
const uint PORTAL_ITEM_CHARGE_PRICE = 5000;
const uint SUMMON_ITEM_CHARGE_PRICE = 1000;

//////////////////////////////////////////////////////////////////////////////
// getPrice()
// ������ ������ ������ ���� ���ǰ��� ���Ѵ�.
// nDiscount ����(�����)�� �̿��� ���ǰ��� ��Ʈ���� �� �ִ�.
//////////////////////////////////////////////////////////////////////////////
Price_t PriceManager::getPrice(Item* pItem, MarketCond_t nDiscount, ShopRackType_t shopType, Creature* pCreature) const
{
	// ÷�� ��¥�� �� �������� �ȾƵ� 1���ۿ� �� ��´�. 2003. 1. 15. Sequoia
	if (pItem->getCreateType() == Item::CREATE_TYPE_GAME ) return (Price_t)1;
	// ����Ʈ �������� �����~~~ 2003. 4. 14. Sequoia
	if ( pItem->isTimeLimitItem() ) return (Price_t)50;
	if ( pItem->getItemClass() == Item::ITEM_CLASS_MOON_CARD && pItem->getItemType() == 4 )
	{
		return (Price_t)g_pVariableManager->getVariable(CROWN_PRICE);
	}

	// �������� ���� ������ ����.
	ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType());
	double originalPrice = pItemInfo->getPrice();
	double finalPrice    = 0;

	if ( pItem->getGrade() != -1 )
	{
		double gradePercent = 80 + ( 5 * pItem->getGrade() );
//		originalPrice = getPercentValue( originalPrice, gradePercent );
		originalPrice *= (gradePercent/100.0);
	}

	// �����̾� ��Ż ���� ��쿡�� ���� ���ݿ��� ���� ���� ����ŭ�� ������ ���ؾ� �Ѵ�.
	if (pItem->getItemClass() == Item::ITEM_CLASS_SLAYER_PORTAL_ITEM)
	{
		SlayerPortalItem* pSlayerPortalItem = dynamic_cast<SlayerPortalItem*>(pItem);
		originalPrice += (pSlayerPortalItem->getCharge() * PORTAL_ITEM_CHARGE_PRICE);
	}
	else if (pItem->getItemClass() == Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM)
	{
		VampirePortalItem* pVampirePortalItem = dynamic_cast<VampirePortalItem*>(pItem);
		originalPrice += (pVampirePortalItem->getCharge() * PORTAL_ITEM_CHARGE_PRICE);
	}
	else if (pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM)
	{
		OustersSummonItem* pOustersSummonItem = dynamic_cast<OustersSummonItem*>(pItem);
		originalPrice += (pOustersSummonItem->getCharge() * SUMMON_ITEM_CHARGE_PRICE);

	}

	// �ɼ��� �ִٸ� �ɼǸ�ŭ�� ������ ���ؾ� �Ѵ�.
	/*const list<OptionType_t>& optionTypes = pItem->getOptionTypeList();
	if (!optionTypes.empty())
	{
		finalPrice = 0;

		// ���� = (���� ���� * �ɼ��� PriceMultiplier / 100) + ..
		double priceMultiplier = 0;
		list<OptionType_t>::const_iterator itr;
		for (itr=optionTypes.begin(); itr!=optionTypes.end(); itr++)
		{
			OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo( *itr );
			Assert(pOptionInfo != NULL);
			priceMultiplier = (double)(pOptionInfo->getPriceMultiplier());
			finalPrice += (originalPrice* priceMultiplier / 100);
		}

		originalPrice = finalPrice;
	}*/

	// �������� �ջ�Ǿ��ٸ� �ջ�� ��ŭ�� ������ ��ƾ� �Ѵ�.
	double maxDurability = (double)computeMaxDurability(pItem);
	double curDurability = (double)(pItem->getDurability());

	// ������ �߿� �������� ���� �͵��� �����ϱ� ������ ó�����ش�.
	if (maxDurability > 1) finalPrice = originalPrice* curDurability / maxDurability;
	else                   finalPrice = originalPrice;

	// ���� �ü��� ���� ������ �ٽ� �������ش�.
	finalPrice = finalPrice* nDiscount / 100;

	// ������ ������ ���� ������ �ٽ� �������ش�.
	if (shopType == SHOP_RACK_MYSTERIOUS)
	{
		finalPrice *= 10;
	}

	// ũ������ ��ȭ ��ҿ� ���� ������ �ٽ� �������ش�.
	if (pCreature != NULL)
	{
		if (pCreature->isSlayer())
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
			Attr_t CSTR = pSlayer->getSTR(ATTR_CURRENT);
			Attr_t CDEX = pSlayer->getDEX(ATTR_CURRENT);
			Attr_t CINT = pSlayer->getINT(ATTR_CURRENT);

			if ((CSTR + CDEX + CINT <= 40) &&
				(pItem->getItemClass() == Item::ITEM_CLASS_POTION) && 
				(pItem->getItemType() == 0 || pItem->getItemType() == 5))
			{
				finalPrice = getPercentValue((int)finalPrice, 70);
			}
		}
		else if (pCreature->isVampire())
		{
			// �����̾ �ذ��� �� ��쿡�� �ذ��� ������ ������ �ٿ��ش�. 
			if (pItem->getItemClass() == Item::ITEM_CLASS_SKULL)
			{
				finalPrice = finalPrice / 2.0;
			}
		}
		else if (pCreature->isOusters())
		{
			// �ƿ콺��� �ذ��� �� ��쿡�� �ذ��� ������ 75%.
			if (pItem->getItemClass() == Item::ITEM_CLASS_SKULL)
			{
				finalPrice *= 0.75;
			}
		}
	}

	// ���� ������̰� ������ �̸�
	if ( g_pVariableManager->getVariable( PREMIUM_HALF_EVENT ) )
	{
		if (
			pItem->getItemClass() == Item::ITEM_CLASS_POTION || pItem->getItemClass() == Item::ITEM_CLASS_SERUM ||
			pItem->getItemClass() == Item::ITEM_CLASS_LARVA || pItem->getItemClass() == Item::ITEM_CLASS_PUPA ||
			pItem->getItemClass() == Item::ITEM_CLASS_COMPOS_MEI
		)
		{
			if ( pCreature->isPC() )
			{
				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
				GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPC->getPlayer());
				if ( pGamePlayer->isPayPlaying() )
				{
					// �� ��.
					finalPrice = finalPrice / 2;
				}
			}
		}
	}

	// Blood Bible ���ʽ� ����
	if (pItem->getItemClass() == Item::ITEM_CLASS_POTION || pItem->getItemClass() == Item::ITEM_CLASS_SERUM )
	{
		if ( pCreature->isPC() )
		{
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			int ratio = pPC->getPotionPriceRatio();
			if ( ratio != 0 )
			{
				// ratio ���� ���̳ʽ� ���̴�.
				finalPrice += getPercentValue( (int)finalPrice, ratio );
			}
		}
	}

	return max(1, (int)finalPrice);
}

//////////////////////////////////////////////////////////////////////////////
// getRepairPrice()
// �������� ������ �� ��� ����� �����Ѵ�.
// ������ ������� ������ �ڻ쳭 �������� ��� 
// ���� ������ ������ 10���� 1�̴�.
//////////////////////////////////////////////////////////////////////////////
Price_t PriceManager::getRepairPrice(Item* pItem, Creature* pCreature) const
{
	// �������� ���� ������ ����.
	ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType());
	double originalPrice = pItemInfo->getPrice();
	double finalPrice    = 0;

	if ( pItem->getGrade() != -1 )
	{
		double gradePercent = 80 + ( 5 * pItem->getGrade() );
//		originalPrice = getPercentValue( originalPrice, gradePercent );
		originalPrice *= (gradePercent/100.0);
	}

	// �����̾� ��Ż ���� ��쿡�� ������ �� ���� ������, ������ �ø� ���� �ִ�.
	if (pItem->getItemClass() == Item::ITEM_CLASS_SLAYER_PORTAL_ITEM)
	{
		SlayerPortalItem* pSlayerPortalItem = dynamic_cast<SlayerPortalItem*>(pItem);
		int MaxCharge = pSlayerPortalItem->getMaxCharge();
		int CurCharge = pSlayerPortalItem->getCharge();

		return (MaxCharge - CurCharge) * PORTAL_ITEM_CHARGE_PRICE;
	}

	if (pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM)
	{
		OustersSummonItem* pOustersSummonItem = dynamic_cast<OustersSummonItem*>(pItem);
		int MaxCharge = pOustersSummonItem->getMaxCharge();
		int CurCharge = pOustersSummonItem->getCharge();

		return (MaxCharge - CurCharge) * SUMMON_ITEM_CHARGE_PRICE;
	}

	// �ɼ��� �ִٸ� �ɼǸ�ŭ�� ������ ���ؾ� �Ѵ�.
	/*const list<OptionType_t>& optionTypes = pItem->getOptionTypeList();
	if (!optionTypes.empty())
	{
		finalPrice = 0;
		// ���� = (��??���� * �ɼ��� PriceMultiplier�� ���� / 100) * �ɼ��� ����
		double priceMultiplier = 0;
		list<OptionType_t>::const_iterator itr;
		for (itr=optionTypes.begin(); itr!=optionTypes.end(); itr++)
		{
			OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo( *itr );
			Assert(pOptionInfo != NULL);
			priceMultiplier = (double)(pOptionInfo->getPriceMultiplier());
			finalPrice += (originalPrice* priceMultiplier / 100);
		}

		originalPrice = finalPrice;
	}*/
	/*
	if (pItem->getOptionType() != 0)
	{
		OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo(pItem->getOptionType());
		Assert(pOptionInfo != NULL);
		double priceMultiplier = (double)(pOptionInfo->getPriceMultiplier());
		originalPrice = originalPrice * priceMultiplier / 100;
	}
	*/

	// �������� �ջ�Ǿ��ٸ� �ջ�� ��ŭ�� ������ ��ƾ� �Ѵ�.
	double maxDurability = (double)computeMaxDurability(pItem);
	double curDurability = (double)(pItem->getDurability());

	// ������ �߿� �������� ���� �͵��� �����ϱ� ������ ó�����ش�.
	if (maxDurability != 0)
	{
		// �������� ���� �������� �ƽ���� �����Ѵ�.
		if (curDurability == maxDurability)
		{
			return 0;
		}

		// ���� �������� �ֳ� �������� ������ �� �������� �ջ�� ������ ���´�.
		// �̸� ���� ���ݿ��� ���ϸ�, �������� ���� ��ŭ �������� ���� �������� �ȴ�.
		finalPrice = originalPrice * curDurability / maxDurability;
	}
	else
	{
		// �������� ���� �������� �ջ������ �����Ƿ�, 
		// �������� ����� ������ ������ ���� �Ȱ���.
		finalPrice = originalPrice;
	}

	// ���� ����� ���� ���� 10���� 1�̴�.
	finalPrice = (originalPrice - finalPrice) / 10.0;

	if (finalPrice < 1.0)
	{
		return 1;
	}

	return max(0, (int)finalPrice);
}

//////////////////////////////////////////////////////////////////////////////
// getSilverCoatingPrice()
// �������� �� ������ ���� �����̴�.
//////////////////////////////////////////////////////////////////////////////
Price_t PriceManager::getSilverCoatingPrice(Item* pItem, Creature* pCreature) const
{
	if (pItem == NULL) return 0;

	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_BLADE:
		case Item::ITEM_CLASS_SWORD:
		case Item::ITEM_CLASS_CROSS:
		case Item::ITEM_CLASS_MACE:
			break;
		default:
			return 0;
	}

	ItemInfo* pItemInfo  = g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType());
	double    maxSilver  = pItemInfo->getMaxSilver();
	double    finalPrice = 0;

	// �������� ������� ���� �����̴�.
	finalPrice = maxSilver; 

	return max(0, (int)finalPrice);
}

//////////////////////////////////////////////////////////////////////////////
// getStashPrice()
// ������ ������ �����Ѵ�. 
// �׷��� ���� ������ ������ �ƴϱ� ������ �ڵ忡�� ����־� ���Ҵ�.
//////////////////////////////////////////////////////////////////////////////
Price_t PriceManager::getStashPrice(BYTE index, Creature* pCreature) const
{
	Price_t price = 0;

	switch (index)
	{
		case 1: price = 100000; break;
		case 2: price = 1000000; break;
		case 3: price = 10000000; break;
		default: 
			cerr << "PriceManager::getStashPrice() : Unknown Stash Index" << endl;
			Assert(false);
	}

	if (pCreature != NULL)
	{
		if (pCreature->isSlayer())
		{
		}
		else if (pCreature->isVampire())
		{
		}
		else if (pCreature->isOusters())
		{
		}
	}

	return price;
}


//////////////////////////////////////////////////////////////////////////////
// �̺�Ʈ�� ���� �Լ�
// 2001�� ũ�������� �̺�Ʈ�� ����Ͽ��� �� �����ۿ� ���� �����̴�.
// 2002�� ��̳����� ���� �̺�Ʈ�� ����ϱ�� �Ͽ��� ������ �ּ��� ����
//
// �� �̺�Ʈ�� ������ �Ͼ �� �ִ� �����,
// �̸��� STAR_EVENT_CODE�� �����ϴ� ���� ����ؾ� �ϰڴ�.
//////////////////////////////////////////////////////////////////////////////
int PriceManager::getStarPrice(Item* pItem, XMAS_STAR& star) const
{
	Assert(pItem != NULL);

	ItemType_t   IType = pItem->getItemType();
	OptionType_t OType = pItem->getFirstOptionType();

	Assert(OType != 0);

	OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo(OType);
	Assert(pOptionInfo!=NULL);
	OptionClass OClass = pOptionInfo->getClass();

	switch (OClass)
	{
		case OPTION_DAMAGE:       star.color = STAR_COLOR_BLACK; break;
		case OPTION_STR:          star.color = STAR_COLOR_RED;   break;
		case OPTION_INT:          star.color = STAR_COLOR_BLUE;  break;
		case OPTION_DEX:          star.color = STAR_COLOR_GREEN; break;
		case OPTION_ATTACK_SPEED: star.color = STAR_COLOR_CYAN;  break;
		default: Assert(false); break;
	}

	star.amount = (IType - 1) * 20;

	return 0;
}

int PriceManager::getBallPrice(int price, XMAS_STAR& star) const
{
	star.amount = price;
	star.color = STAR_COLOR_PINK;

	return 0;
}

// Mysterious Item ����
// itemClass�� pCreature�� �ɷ�ġ�� ���� ������ �޶�����.
Price_t PriceManager::getMysteriousPrice(Item::ItemClass itemClass, Creature* pCreature) const
{
	int multiplier = 1;

	if (pCreature->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

		Attr_t CSTR = pSlayer->getSTR(ATTR_BASIC);
		Attr_t CDEX = pSlayer->getDEX(ATTR_BASIC);
		Attr_t CINT = pSlayer->getINT(ATTR_BASIC);
		Attr_t CSUM = CSTR + CDEX + CINT;

		// 0~20 ����
		multiplier = CSUM / 15;
	}
	else if (pCreature->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

		Level_t CLevel = pVampire->getLevel();

		// 0~20 ����
		multiplier = CLevel / 5;
	}
	else if (pCreature->isOusters())
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

		Level_t CLevel = pOusters->getLevel();

		// 0~20 ����
		multiplier = CLevel / 5;
	}

	// 1~20����
	multiplier = max(1, multiplier);

	// ���� ����� �˾ƿ´�.
	InfoClassManager* pInfoClass = g_pItemInfoManager->getInfoManager( itemClass );
	Assert(pInfoClass!=NULL);

	// ���� ��� * �ɷ�ġ ����?
	int finalPrice = (int)pInfoClass->getAveragePrice() * multiplier;

	// Blood Bible ���ʽ� ����
	if ( pCreature->isPC() )
	{
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
		int ratio = pPC->getGamblePriceRatio();
		if ( ratio != 0 )
		{
			// ratio ���� ���̳ʽ� ���̴�.
			finalPrice += getPercentValue( finalPrice, ratio );
		}
	}

	return finalPrice;
}

