//////////////////////////////////////////////////////////////////////////////
// Filename    : ThrowHolyWater.cpp
// Written by  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "ThrowHolyWater.h"
#include "ItemFactoryManager.h"
#include "ItemUtil.h"

#include "item/HolyWater.h"

#include "Gpackets/GCThrowItemOK1.h"
#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCThrowItemOK2.h"
#include "Gpackets/GCThrowItemOK3.h"
#include "Gpackets/GCModifyInformation.h"


//////////////////////////////////////////////////////////////////////
//
// ThrowHolyWater::execute()
//
//////////////////////////////////////////////////////////////////////
void ThrowHolyWater::execute(Slayer* pSlayer , ObjectID_t TargetObjectID, ObjectID_t ItemObjectID, CoordInven_t InvenX, CoordInven_t InvenY)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pSlayer != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();
		Inventory* pInventory = pSlayer->getInventory();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);
		Assert(pInventory != NULL);
		Assert(InvenX < pInventory->getWidth());
		Assert(InvenY < pInventory->getHeight());

		Item* pItem = pInventory->getItem(InvenX, InvenY);

		if (pItem == NULL)
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		ObjectID_t ObjectID        = pItem->getObjectID();
		Creature*  pTargetCreature = NULL;

		// ��Ŷ�� �� �Ŷ�, ������ ���̵� Ʋ���ų�, 
		// ������ �ƴ϶�� �����ߴٰ� �����ش�.
		if (ObjectID != ItemObjectID || pItem->getItemClass() != Item::ITEM_CLASS_HOLYWATER)
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCThrowItemOK2 _GCThrowItemOK2;
		GCModifyInformation gcAttackerMI;

		// ������ Ÿ�� ũ���ĸ� ã�´�.
		/*
		try 
		{ 
			pTargetCreature = pZone->getCreature(TargetObjectID); 
		}
		catch (NoSuchElementException) 
		{ 
			pTargetCreature = NULL; 
		}
		*/

		pTargetCreature = pZone->getCreature(TargetObjectID); 

		// Ŭ���̾�Ʈ���� ����ȭ ������ ����, �����Ͱ� ���� �� �ִ�.
		// ������ �ΰ��� �������� �����µ�, ���� ���� ���������� ����,
		// Ÿ���� �װ� �� ��, Ŭ���̾�Ʈ�� ��ó �� ��Ŷ�� ���� ���ϰ�,
		// �ٽ� �ѹ� ������ ���� ���, �� �����ϸ� ����ϴ�.
		if (pTargetCreature == NULL)
		{
			// ���� ������ ���ڸ� �ٿ��־�� �Ѵ�.
			decreaseItemNum(pItem, pInventory, pSlayer->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		} 
		else 
		{
			HolyWater* pHolyWater = dynamic_cast<HolyWater*>(pItem);

			Damage_t MinDamage = pHolyWater->getMinDamage();
			Damage_t MaxDamage = pHolyWater->getMaxDamage();
			Damage_t Damage    = max(1, Random(MinDamage, MaxDamage));

			// �Ϲ� ������ �ƴ϶�� �������� 0���� ������ �ش�. 
			// �� �κп��� checkZoneLevelToHitTarget �Լ��� �θ��� ������
			// ���⼭ �������� ���� �˻縦 �� �ʿ䰡 ����.
			// -- 2002-01-31 �輺��
			//if (!(pZone->getZoneLevel() & NO_SAFE_ZONE)) Damage = 0;

			list<Creature*> cList;
			cList.push_back(pSlayer);

			bool bHitRoll        = HitRoll::isSuccess(pSlayer, pTargetCreature);
			bool bPK             = verifyPK(pSlayer, pTargetCreature);
			bool bRangeCheck     = verifyDistance(pSlayer, pTargetCreature, 10);
			bool bZoneLevelCheck = checkZoneLevelToHitTarget(pTargetCreature) && canAttack( pSlayer, pTargetCreature );

			// ���� �Ǿ��ٸ�, �������� �ش�..
			// ������ ���� �ʾƵ� ������ �ѹ� ������ ���̴�.
			if (bHitRoll && bPK && bRangeCheck && bZoneLevelCheck)
			{
				// ������ �����̾ �ƴ� ��쿡�� ����ġ�� �÷��ش�.
				if (!pTargetCreature->isSlayer())
				{
					shareAttrExp(pSlayer, Damage, 1, 1, 8, gcAttackerMI);

					// ��þ �������� �÷��ش�.
					// 2003. 1. 12 by bezz
					// Throw Holy Water �� SkillInfo �� ����.
					// �׷��� Create Holy Water �� Point �� ����.
					SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo( SKILL_CREATE_HOLY_WATER );
					increaseDomainExp( pSlayer, SKILL_DOMAIN_ENCHANT, pSkillInfo->getPoint(), gcAttackerMI, pTargetCreature->getLevel() );
				}

				if (pTargetCreature->isSlayer()) 
				{
					/*
					GCModifyInformation gcModifyInfo;

					Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pTargetCreature);
					setDamage(pTargetSlayer, Damage, NULL, 0, &_GCThrowItemOK2);
					computeAlignmentChange(pTargetSlayer, Damage, pSlayer, &_GCThrowItemOK2, &gcAttackerMI);

					Player* pTargetPlayer = pTargetSlayer->getPlayer();
					pTargetPlayer->sendPacket(&_GCThrowItemOK2);
					*/
				} 
				else if (pTargetCreature->isVampire()) 
				{
					Vampire* pTargetVampire = dynamic_cast<Vampire*>(pTargetCreature);

					setDamage(pTargetVampire, Damage, NULL, 0, &_GCThrowItemOK2);

					// ���� ��������ŭ�� Ȧ�� �������� �ش�.
					Silver_t silverDamage    = max(1, getPercentValue(Damage, 10));
					Silver_t newSilverDamage = pTargetVampire->getSilverDamage() + silverDamage;
					pTargetVampire->saveSilverDamage(newSilverDamage);

					Player* pTargetPlayer = pTargetVampire->getPlayer();
					pTargetPlayer->sendPacket(&_GCThrowItemOK2);

					GCModifyInformation gcModifyInfo;
					gcModifyInfo.addShortData(MODIFY_SILVER_DAMAGE, newSilverDamage);
					pTargetPlayer->sendPacket(&gcModifyInfo);
				} 
				else if (pTargetCreature->isOusters()) 
				{
					Ousters* pTargetOusters = dynamic_cast<Ousters*>(pTargetCreature);

					setDamage(pTargetOusters, Damage, NULL, 0, &_GCThrowItemOK2);

					// ���� ��������ŭ�� Ȧ�� �������� �ش�.
					Silver_t silverDamage    = max(1, getPercentValue(Damage, 10));
					Silver_t newSilverDamage = pTargetOusters->getSilverDamage() + silverDamage;
					pTargetOusters->saveSilverDamage(newSilverDamage);

					Player* pTargetPlayer = pTargetOusters->getPlayer();
					pTargetPlayer->sendPacket(&_GCThrowItemOK2);

					GCModifyInformation gcModifyInfo;
					gcModifyInfo.addShortData(MODIFY_SILVER_DAMAGE, newSilverDamage);
					pTargetPlayer->sendPacket(&gcModifyInfo);
				} 
				else if (pTargetCreature->isMonster()) 
				{
					Monster* pTargetMonster = dynamic_cast<Monster*>(pTargetCreature);
					setDamage(pTargetMonster, Damage, pSlayer, getSkillType(), NULL, NULL);

					Silver_t silverDamage = max(1, getPercentValue(Damage, 10));
					Silver_t newSilverDamage = pTargetMonster->getSilverDamage() + silverDamage;
					pTargetMonster->setSilverDamage(newSilverDamage);
				}

				cList.push_back(pTargetCreature);

				// �ֺ� ����鿡�� OK3 Packet�� ������.
				GCThrowItemOK3 _GCThrowItemOK3;
				_GCThrowItemOK3.setObjectID(pSlayer->getObjectID()); 
				_GCThrowItemOK3.setTargetObjectID(TargetObjectID);
				pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &_GCThrowItemOK3, cList);

				// ���� ������� OK Packet�� ������.
				GCThrowItemOK1 _GCThrowItemOK1;
				_GCThrowItemOK1.setObjectID(TargetObjectID);

				pPlayer->sendPacket(&_GCThrowItemOK1);
				pPlayer->sendPacket(&gcAttackerMI);
			}
			else // ���� �����⿡ �������� ���...
			{
				executeSkillFailNormal(pSlayer, getSkillType(), pTargetCreature);
			}

			// �µ� ���� �ʾҵ� ������ ���ڴ� �ٿ��־�� �Ѵ�.
			decreaseItemNum(pItem, pInventory, pSlayer->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
		}
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

ThrowHolyWater g_ThrowHolyWater;
