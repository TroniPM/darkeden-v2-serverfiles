//////////////////////////////////////////////////////////////////////////////
// Filename    : CreateBomb.cpp
// Written by  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CreateBomb.h"
#include "ItemFactoryManager.h"
#include "ItemUtil.h"

#include "item/Bomb.h"

#include "Gpackets/GCSkillToInventoryOK1.h"
#include "Gpackets/GCSkillToInventoryOK2.h"

int MaterialType2BombTypeMap[] =
{
	0,  // 0
	1,  // 1
	2,  // 2
	3,  // 3
	4,  // 4
	-1, // 5
	-1, // 6
	-1, // 7
	-1, // 8
	-1  // 9
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CreateBomb::execute(Slayer * pSlayer , ObjectID_t InvenObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, SkillSlot * pSkillSlot)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(CreateBomb)" << endl;

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

		// ��ź�� ���� ����� ���̰ų�, ���� ��ź ��ᰡ �ƴϰų�, 
		// OID�� Ʋ���ٸ� ����� �� ����.
		Item* pBombMaterial = pInventory->getItem(X, Y);
		if (pBombMaterial == NULL || pBombMaterial->getItemClass() != Item::ITEM_CLASS_BOMB_MATERIAL || 
			pBombMaterial->getObjectID() != InvenObjectID)
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayerinventory)" << endl;
			return;
		}

		bool bSamePosition = false;
		if (X == TargetX && Y == TargetY) bSamePosition = true;

		// ��� ��ġ�� Ÿ�� ��ġ�� ���� ���ƿ��� ����
		// ��ź�� ��ȯ�ϰ��� �ϴ� C4�� ���ڰ� 1�� ����̴�.
		// (������ C4�� �����ϰ�, ���� ��ġ�� ��ź�� �����Ѵٴ� �ǹ��̴�.)
		// 1�� �ƴ϶�� �����ؾ��Ѵ�.
		if (bSamePosition && pBombMaterial->getNum() != 1)
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayerinventory)" << endl;
			return;
		}

		// ������ Ÿ�԰� �̿� �����ϴ� ��ź�� Ÿ���� ���Ѵ�.
		ItemType_t MaterialType = pBombMaterial->getItemType();
		int BombType = MaterialType2BombTypeMap[MaterialType];
		if (BombType == -1)
		{
			// ��ź ��ᰡ �ƴ϶�, ���� �����, ��ų ���д�.
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayerinventory)" << endl;
			return;
		}

		GCSkillToInventoryOK1 _GCSkillToInventoryOK1;
		GCSkillToInventoryOK2 _GCSkillToInventoryOK2;

		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillLevel_t      SkillLevel = pSkillSlot->getExpLevel();
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		SkillGrade        Grade      = g_pSkillInfoManager->getGradeByDomainLevel(pSlayer->getSkillDomainLevel(DomainType));

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);
		bool bCanMake    = canMake(BombType, pSlayer->getSkillDomainLevel(DomainType), SkillLevel);

		if (bManaCheck && bTimeCheck && bRangeCheck && bCanMake)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToInventoryOK1);

			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			list<OptionType_t> optionNULL;
			Item* pBomb = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_BOMB, BombType, optionNULL);

			// ��ź����� ������ �ٿ��ش�.
			// �� �Լ� �ȿ��� ��ź����� ������ �ڵ������� �ϳ� �پ���, 
			// ���� 1���� ��ź����̾��ٸ� �κ��丮 �� DB���� �����ǰ� �ȴ�.
			decreaseItemNum(pBombMaterial, pInventory, pSlayer->getName(), STORAGE_INVENTORY, 0, X, Y);

			Item* pPrevBomb = pInventory->getItem(TargetX, TargetY);

			// ������ ��ź ��ü�� �ִٴ� ���� �׾ƾ� �Ѵٴ� ���̴�.
			if (pPrevBomb != NULL)
			{
				if (canStack(pPrevBomb, pBomb) == false)
				{
					// ���� Ÿ���� ��ź�� �ƴ� ���ε�... �̷� ��찡 ��� �ϸ� �����...
					SAFE_DELETE(pBomb);

					executeSkillFailException(pSlayer, getSkillType());

					//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayerinventory)" << endl;
					return;
				}

				// ������ �ϳ� ������Ű�� �����Ѵ�.
				pPrevBomb->setNum(pPrevBomb->getNum() + 1);
				pPrevBomb->save(pSlayer->getName(), STORAGE_INVENTORY, 0, TargetX, TargetY);
				
				// ���κ��� decreaseItemNum() �Լ� �κп��� ������ ���ڸ� ���ҽ�Ű�Ƿ�, 
				// ���⼭ �ٽ� �κ��丮�� ������ ���ڸ� ������Ų��.
				pInventory->increaseNum();

				// ��� ������� ��ź�� ������ ��ź�� ���������Ƿ� �����Ѵ�.
				SAFE_DELETE(pBomb);

				_GCSkillToInventoryOK1.setObjectID(pPrevBomb->getObjectID());
			}
			// ������ ��ź ��ü�� ���ٴ� ���� ��ź ��ü�� DB�� �����ؾ� �Ѵٴ� ���̴�.
			else
			{
				ObjectRegistry& OR = pZone->getObjectRegistry();
				OR.registerObject(pBomb);

				// ��ź�� Inventory�� ���� �ְ� DB���ٰ� �����Ѵ�.
				pBomb->setNum(1);
				pInventory->addItem(TargetX, TargetY, pBomb);
				pBomb->create(pSlayer->getName(), STORAGE_INVENTORY, 0, TargetX, TargetY);

				_GCSkillToInventoryOK1.setObjectID(pBomb->getObjectID());
			}

			// ��Ŷ�� ������.
			_GCSkillToInventoryOK1.setSkillType(SkillType);
			_GCSkillToInventoryOK1.setItemType(BombType);
			_GCSkillToInventoryOK1.setCEffectID(0);
			_GCSkillToInventoryOK1.setX(TargetX);
			_GCSkillToInventoryOK1.setY(TargetY);

			_GCSkillToInventoryOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToInventoryOK2.setSkillType(SkillType);
			
			// EXP UP!
			Exp_t ExpUp = 10 * (Grade + 1);
			shareAttrExp(pSlayer, ExpUp , 1, 8, 1, _GCSkillToInventoryOK1);
			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToInventoryOK1);
			increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToInventoryOK1);

			pPlayer->sendPacket(&_GCSkillToInventoryOK1);

			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &_GCSkillToInventoryOK2, pSlayer);

			pSkillSlot->setRunTime(output.Delay);
		}
		else
		{
			//executeSkillFailNormal(pSlayer, getSkillType(), NULL);
			// ��ź ����� ���� ��쿡��, �������� �� �����̰� ���� ������,
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

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(CreateBomb)" << endl;

	__END_CATCH
}

bool CreateBomb::canMake(ItemType_t BombType, int DomainLevel, int SkillLevel)
	throw()
{
	__BEGIN_TRY

	int ratio = 10 * ((SkillLevel/10) - BombType) + 40;
	if ((rand()%100) < ratio) return true;
	return false;

	__END_CATCH
}

CreateBomb g_CreateBomb;
