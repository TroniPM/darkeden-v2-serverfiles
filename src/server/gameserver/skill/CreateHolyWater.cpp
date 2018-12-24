//////////////////////////////////////////////////////////////////////////////
// Filename    : CreateHolyWater.cpp
// Written by  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CreateHolyWater.h"
#include "ItemFactoryManager.h"
#include "ItemUtil.h"

#include "item/HolyWater.h"

#include "Gpackets/GCSkillToInventoryOK1.h"
#include "Gpackets/GCSkillToInventoryOK2.h"


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CreateHolyWater::execute(Slayer * pSlayer , ObjectID_t InvenObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, SkillSlot * pSkillSlot)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayerinventory)" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();
		Inventory* pInventory = pSlayer->getInventory();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);
		Assert(pInventory != NULL);

		// ������ ���� ����� ���̰ų�, ���� ���� �ƴϰų�,
		// OID�� Ʋ���ٸ� ����� �� ����.
		Item* pWater = pInventory->getItem(X, Y);
		if (pWater == NULL || pWater->getItemClass() != Item::ITEM_CLASS_WATER || pWater->getObjectID() != InvenObjectID)
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayerinventory)" << endl;
			return;
		}

		bool bSamePosition = false;
		if (X == TargetX && Y == TargetY) bSamePosition = true;

		// ��� ��ġ�� Ÿ�� ��ġ�� ���� ���ƿ��� ����
		// ������ ��ȯ�ϰ��� �ϴ� ������ ���ڰ� 1�� ����̴�.
		// (������ ������ �����ϰ�, ���� ��ġ�� ������ �����Ѵٴ� �ǹ��̴�.)
		// 1�� �ƴ϶�� �����ؾ��Ѵ�.
		// ���� �Ѱ����� �ƴ϶� ������ ���� �� �ٲ�Ƿ� üũ�� �ʿ� ����.
/*		if (bSamePosition && pWater->getNum() != 1)
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayerinventory)" << endl;
			return;
		}*/

		GCSkillToInventoryOK1 _GCSkillToInventoryOK1;
		GCSkillToInventoryOK2 _GCSkillToInventoryOK2;

		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillLevel_t      SkillLevel = pSkillSlot->getExpLevel();
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		SkillGrade        Grade      = g_pSkillInfoManager->getGradeByDomainLevel(pSlayer->getSkillDomainLevel(DomainType));

		ItemType_t waterType = pWater->getItemType();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);
		bool bCanMake    = canMake(waterType, pSlayer->getSkillDomainLevel(DomainType), SkillLevel);

		if (bManaCheck && bTimeCheck && bRangeCheck && bCanMake)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToInventoryOK1);

			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			// ���� ���� ���� ItemType�� �̿��� Ȧ�����͸� �����Ѵ�.
			// �̴� Water�� HolyWater�� ItemType�� 1:1 ������ �Ǳ� ������
			// ������ �ڵ��̴�.
			list<OptionType_t> optionNULL;
			Item* pHolyWater = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_HOLYWATER, waterType, optionNULL);
			// ���� ������ �������ش�.
			pHolyWater->setNum( pWater->getNum() );

			// ������ ������ �ٿ��ش�.
			// �� �Լ� �ȿ��� ������ ������ �ڵ������� �ϳ� �پ���, 
			// ���� 1���� �����̾��ٸ� �κ��丮 �� DB���� �����ǰ� �ȴ�.
//			decreaseItemNum(pWater, pInventory, pSlayer->getName(), STORAGE_INVENTORY, 0, X, Y);
			// ���� ��� ������� ���� �ٲ������.
			pInventory->deleteItem(X,Y);
			pWater->destroy();
			SAFE_DELETE(pWater);

			Item* pPrevHolyWater = pInventory->getItem(TargetX, TargetY);

			// ������ ���� ��ü�� �ִٴ� ���� �׾ƾ� �Ѵٴ� ���̴�.
			if (pPrevHolyWater != NULL)
			{
				if (canStack(pPrevHolyWater, pHolyWater) == false)
				{
					// ���� Ÿ���� ������ �ƴ� ���ε�... �̷� ��찡 ��� �ϸ� �����...
					SAFE_DELETE(pHolyWater);

					executeSkillFailException(pSlayer, getSkillType());

					//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayerinventory)" << endl;
					return;
				}

				// ������ �ϳ� ������Ű�� �����Ѵ�.
				pPrevHolyWater->setNum(pPrevHolyWater->getNum() + pHolyWater->getNum());
				pPrevHolyWater->save(pSlayer->getName(), STORAGE_INVENTORY, 0, TargetX, TargetY);
				
				// ���κ��� decreaseItemNum() �Լ� �κп��� ������ ���ڸ� ���ҽ�Ű�Ƿ�, 
				// ���⼭ �ٽ� �κ��丮�� ������ ���ڸ� ������Ų��.
				pInventory->increaseNum( pHolyWater->getNum() );

				// ��� ������� ������ ������ ������ ���������Ƿ� �����Ѵ�.
				SAFE_DELETE(pHolyWater);

				_GCSkillToInventoryOK1.setObjectID(pPrevHolyWater->getObjectID());
			}
			// ������ ���� ��ü�� ���ٴ� ���� ���� ��ü�� DB�� �����ؾ� �Ѵٴ� ���̴�.
			else
			{
				ObjectRegistry& OR = pZone->getObjectRegistry();
				OR.registerObject(pHolyWater);

				// ������ Inventory�� ���� �ְ� DB���ٰ� �����Ѵ�.
				pInventory->addItem(TargetX, TargetY, pHolyWater);
				pHolyWater->create(pSlayer->getName(), STORAGE_INVENTORY, 0, TargetX, TargetY);

				_GCSkillToInventoryOK1.setObjectID(pHolyWater->getObjectID());
			}

			// ��Ŷ�� ������.
			_GCSkillToInventoryOK1.setSkillType(SkillType);
			_GCSkillToInventoryOK1.setItemType(waterType);
			_GCSkillToInventoryOK1.setCEffectID(0);
			_GCSkillToInventoryOK1.setX(TargetX);
			_GCSkillToInventoryOK1.setY(TargetY);

			_GCSkillToInventoryOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToInventoryOK2.setSkillType(SkillType);
			
			// EXP UP!
			Exp_t ExpUp = 10 * (Grade + 1);
			shareAttrExp(pSlayer, ExpUp , 1, 1, 8, _GCSkillToInventoryOK1);
			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToInventoryOK1);
			increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToInventoryOK1);

			pPlayer->sendPacket(&_GCSkillToInventoryOK1);

			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &_GCSkillToInventoryOK2, pSlayer);

			pSkillSlot->setRunTime(output.Delay);
		}
		else
		{
			//executeSkillFailNormal(pSlayer, getSkillType(), NULL);
			// ���� ����� ���� ��쿡��, �������� �� �����̰� ���� ������,
			// Ŭ���̾�Ʈ���Լ� ��Ŷ�� ����� ������ ���������� ���ƿ´�.
			// �� ��, ���� ��Ŷ�� ��ε� ĳ�����ϰ� �Ǹ�, ���� �ִ� ����� ���⿡��
			// ĳ���� ������ �ſ� ������ ���������� ǥ�õȴ�. (���ǵ��� ���� ��ó��...)
			// �׷��� �� �κп��� ��ε�ĳ������ ���� �ʰ�, ���ο��Ը� ��Ŷ�� �����ش�.
			// 2002-02-06 �輺��
			executeSkillFailException(pSlayer, getSkillType());
		}
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayerinventory)" << endl;

	__END_CATCH
}

bool CreateHolyWater::canMake(ItemType_t WaterType, int DomainLevel, int SkillLevel)
	throw()
{
	__BEGIN_TRY

	bool       rvalue = false;
	SkillGrade Grade  = g_pSkillInfoManager->getGradeByDomainLevel(DomainLevel);
	int        ratio  = 0;

	// ������ ������ ���� ���� �� �ִ� ������ ũ�⿡ ������ �ִ�.
	// �׷��� ������ ������ ������ �̻��� ��쿡�� �г�Ƽ�� ����� �ϴµ�,
	// �̴� ��� ó���� �� ������?
	if (WaterType == 2 && Grade >= SKILL_GRADE_EXPERT)
	{
		// ������Ʈ �̻��� �Ǿ�� ���� Ȧ�� ���͸� ���� �� �ִ�.
		rvalue = true;
		ratio = 50 + SkillLevel - 50;
	}
	else if (WaterType == 1 && Grade >= SKILL_GRADE_ADEPT)
	{
		// �Ʈ �̻��� �Ǿ�� �̵�� Ȧ�� ���͸� ���� �� �մ�.
		rvalue = true;
		ratio = 50 + SkillLevel - 30;
	}
	else if (WaterType == 0 && Grade >= SKILL_GRADE_APPRENTICE)
	{
		// ������Ƽ�� �̻��� �Ǿ�� ���� Ȧ�� ���͸� ���� �� �ִ�.
		rvalue = true;
		ratio = 50 + SkillLevel - 10;
	}

	// �ϴ� ���� �� �ִ� Ȯ���� �ִٸ� Ȯ�� üũ�� �Ѵ�.
	if (rvalue)
	{
		if ((rand()%100) < ratio) return true;
	}

	return false;

	__END_CATCH
}

CreateHolyWater g_CreateHolyWater;
