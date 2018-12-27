//////////////////////////////////////////////////////////////////////////////
// Filename    : CreateHolyPotion.cpp
// Written by  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CreateHolyPotion.h"
#include "ItemFactoryManager.h"
#include "ItemUtil.h"

#include "item/Potion.h"

#include "Gpackets/GCSkillToInventoryOK1.h"
#include "Gpackets/GCSkillToInventoryOK2.h"


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CreateHolyPotion::execute(Slayer * pSlayer , ObjectID_t InvenObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, SkillSlot * pSkillSlot)
	
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

		// 성수를 만들 대상이 널이거나, 보통 물이 아니거나,
		// OID가 틀리다면 사용할 수 없다.
		Item* pPotion = pInventory->getItem(X, Y);
		if (pPotion == NULL || pPotion->getItemClass() != Item::ITEM_CLASS_WATER || pPotion->getObjectID() != InvenObjectID)
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayerinventory)" << endl;
			return;
		}

		bool bSamePosition = false;
		if (X == TargetX && Y == TargetY) bSamePosition = true;

		// 대상 위치와 타겟 위치가 같게 날아오는 경우는
		// 성수로 변환하고자 하는 물병의 숫자가 1인 경우이다.
		// (이전의 물병을 삭제하고, 같은 위치에 성수를 생성한다는 의미이다.)
		// 1이 아니라면 리턴해야한다.
		// 이제 한개씩만 아니라 물병이 몽땅 다 바뀌므로 체크할 필요 없다.
		if (bSamePosition && pPotion->getNum() != 1)
		{
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

		// 땜빵 코드 -_-
		ItemType_t waterType = pPotion->getItemType() + 11;

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);
		bool bCanMake    = canMake(pPotion->getItemType(), pSlayer->getSkillDomainLevel(DomainType), SkillLevel);

		if (bManaCheck && bTimeCheck && bRangeCheck && bCanMake)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToInventoryOK1);

			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			// 원래 보통 물의 ItemType을 이용해 홀리워터를 생성한다.
			// 이는 Potion와 HolyPotion의 ItemType이 1:1 대응이 되기 때문에
			// 가능한 코드이다.
			list<OptionType_t> optionNULL;
			Item* pHolyPotion = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_POTION, waterType, optionNULL);

			// 물병의 갯수를 줄여준다.
			// 이 함수 안에서 물병의 갯수가 자동적으로 하나 줄어들고, 
			// 만일 1개인 물병이었다면 인벤토리 및 DB에서 삭제되게 된다.
			decreaseItemNum(pPotion, pInventory, pSlayer->getName(), STORAGE_INVENTORY, 0, X, Y);
			Item* pPrevHolyPotion = pInventory->getItem(TargetX, TargetY);

			// 기존의 성수 객체가 있다는 말은 쌓아야 한다는 말이다.
			if (pPrevHolyPotion != NULL)
			{
				if (canStack(pPrevHolyPotion, pHolyPotion) == false)
				{
					// 같은 타입의 성수가 아닐 때인데... 이런 경우가 어떻게 하면 생길까...
					SAFE_DELETE(pHolyPotion);

					executeSkillFailException(pSlayer, getSkillType());

					//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayerinventory)" << endl;
					return;
				}

				// 갯수를 하나 증가시키고 저장한다.
				pPrevHolyPotion->setNum(pPrevHolyPotion->getNum() + pHolyPotion->getNum());
				pPrevHolyPotion->save(pSlayer->getName(), STORAGE_INVENTORY, 0, TargetX, TargetY);
				
				// 위부분의 decreaseItemNum() 함수 부분에서 아이템 숫자를 감소시키므로, 
				// 여기서 다시 인벤토리의 아이템 숫자를 증가시킨다.
				pInventory->increaseNum( pHolyPotion->getNum() );

				// 방금 만들어진 성수는 기존의 성수에 더해졌으므로 삭제한다.
				SAFE_DELETE(pHolyPotion);

				_GCSkillToInventoryOK1.setObjectID(pPrevHolyPotion->getObjectID());
			}
			// 기존의 성수 객체가 없다는 말은 성수 객체를 DB에 생성해야 한다는 말이다.
			else
			{
				ObjectRegistry& OR = pZone->getObjectRegistry();
				OR.registerObject(pHolyPotion);

				// 성수를 Inventory로 집어 넣고 DB에다가 생성한다.
				pInventory->addItem(TargetX, TargetY, pHolyPotion);
				pHolyPotion->create(pSlayer->getName(), STORAGE_INVENTORY, 0, TargetX, TargetY);

				_GCSkillToInventoryOK1.setObjectID(pHolyPotion->getObjectID());
			}

			// 패킷을 보낸다.
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
			// 홀리포션 만들기는 도메인 경험치 안 준다.
//			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToInventoryOK1);
			increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToInventoryOK1);

			pPlayer->sendPacket(&_GCSkillToInventoryOK1);

			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &_GCSkillToInventoryOK2, pSlayer);

			pSkillSlot->setRunTime(output.Delay);
		}
		else
		{
			//executeSkillFailNormal(pSlayer, getSkillType(), NULL);
			// 성수 만들기 같은 경우에는, 실패했을 때 딜레이가 없기 때문에,
			// 클라이언트에게서 패킷이 상당히 빠르게 연속적으로 날아온다.
			// 이 때, 실패 패킷을 브로드 캐스팅하게 되면, 옆에 있는 사람이 보기에는
			// 캐스팅 동작이 매우 빠르게 연속적으로 표시된다. (스피드핵 쓰는 것처럼...)
			// 그래서 이 부분에서 브로드캐스팅을 하지 않고, 본인에게만 패킷을 날려준다.
			// 2002-02-06 김성민
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

bool CreateHolyPotion::canMake(ItemType_t PotionType, int DomainLevel, int SkillLevel)
	
{
	__BEGIN_TRY

	bool       rvalue = false;
	int        ratio  = 60 + SkillLevel;

	// 도메인 레벨에 따라 만들 수 있는 성수의 크기에 제한이 있다.
	// 그런데 도메인 레벨이 마스터 이상일 경우에는 패널티가 없어야 하는데,
	// 이는 어떻게 처리할 수 있을까?
	if (PotionType == 6 && DomainLevel >= 101)
	{
		rvalue = true;
	}
	else if (PotionType == 5 && DomainLevel >= 81)
	{
		rvalue = true;
	}
	else if (PotionType == 4 && DomainLevel >= 61)
	{
		// 어프렌티스 이상은 되어야 스몰 홀리 워터를 만들 수 있다.
		rvalue = true;
	}
	else if (PotionType == 3)
	{
		rvalue = true;
	}

	// 일단 만들 수 있는 확률이 있다면 확률 체크를 한다.
	if (rvalue)
	{
		if ((rand()%100) < ratio) return true;
	}

	return false;

	__END_CATCH
}

CreateHolyPotion g_CreateHolyPotion;
