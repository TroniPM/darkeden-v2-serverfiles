//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyTunnel.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "BloodyTunnel.h"
#include "ZoneUtil.h"
#include "EffectSchedule.h"
#include "EffectVampirePortal.h"

#include "item/VampirePortalItem.h"

#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToInventoryOK1.h"
#include "Gpackets/GCSkillToSelfOK3.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� �κ��丮 �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void BloodyTunnel::execute(Vampire* pVampire, ObjectID_t InvenObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, VampireSkillSlot* pSkillSlot)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pVampire != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();
		Inventory* pInventory = pVampire->getInventory();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);
		Assert(pInventory!= NULL);

		// ���� ���̶�� BloodyTunnel�� ����� �� ����.
		// �ϴ��� ZoneID�� ���µ�.. ZoneInfo�� �ֵ��� �ؾ��Ѵ�.
		///*
		//if (pZone->getZoneID()==1122 || pZone->getZoneID()==1123)
		// �̺�Ʈ �����/OX ����. by sigi. 2002.8.31
		//int zoneID = pZone->getZoneID();
		//if (zoneID==1005 || zoneID==1006)
		if (pZone->isNoPortalZone()
			|| pZone->isMasterLair()
			|| pZone->isCastle()
			|| pZone->isHolyLand())
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}
		//*/


		Item* pItem = pInventory->getItem(X, Y);
		// �������� ���ų�, �����̾� ��Ż �������� �ƴϰų�, OID�� Ʋ���ٸ� ��� ��� �Ұ�
		if (pItem == NULL || pItem->getItemClass() != Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM || pItem->getObjectID() != InvenObjectID)
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		VampirePortalItem* pVampirePortalItem = dynamic_cast<VampirePortalItem*>(pItem);
		Assert(pVampirePortalItem != NULL);

		// �����̾� ��Ż �����ۿ� ��ϵ� ��ġ�� ���� ��쿡�� ���д�.
		ZoneID_t    zoneid = pVampirePortalItem->getZoneID();
		ZoneCoord_t tx     = pVampirePortalItem->getX();
		ZoneCoord_t ty     = pVampirePortalItem->getY();
		if (zoneid == 0)
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		// ���� ��ǥ ���� ��ǥ�� �����Ѵ�.
		Zone* pTargetZone = getZoneByZoneID(zoneid);

		// �ƴ��� ������ �ٸ� ������ ������� �ʴ´�.
		if (pZone->isHolyLand() != pTargetZone->isHolyLand())
		{
			executeSkillFailException(pVampire, getSkillType());
			return;
		}

		//cout << "Ÿ�� �� ������ ȹ�� ����" << endl;

		VSRect* pRect = pTargetZone->getOuterRect();

		if (!pRect->ptInRect(tx, ty))
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		//cout << "��ǥ ���� ����" << endl;
		
		GCSkillToInventoryOK1 _GCSkillToInventoryOK1;

		SkillType_t SkillType  = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		int  RequiredMP     = decreaseConsumeMP(pVampire, pSkillInfo);
		bool bManaCheck     = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck     = verifyRunTime(pSkillSlot);
		bool bRangeCheck    = checkZoneLevelToUseSkill(pVampire);
		//bool bHitRoll       = HitRoll::isSuccessMagic(pVampire, pSkillInfo, pSkillSlot);
		bool bHitRoll       = true;

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll)
		{
			decreaseMana(pVampire, RequiredMP, _GCSkillToInventoryOK1);

			SkillInput input(pVampire);
			SkillOutput output;
			computeOutput(input, output);

			// ������ �����ٰ� ��Ż�� ���Ѵ�.
			ZONE_COORD s_coord;
			ZONE_COORD t_coord;

			s_coord.id = pZone->getZoneID();
			s_coord.x  = pVampire->getX();
			s_coord.y  = pVampire->getY();

			t_coord.id = pTargetZone->getZoneID();
			t_coord.x  = tx;
			t_coord.y  = ty;

			pZone->addVampirePortal(s_coord.x, s_coord.y, pVampire, t_coord);
			pTargetZone->addVampirePortal(t_coord.x, t_coord.y, pVampire, s_coord);

			_GCSkillToInventoryOK1.setSkillType(SkillType);
			_GCSkillToInventoryOK1.setObjectID(InvenObjectID);
			_GCSkillToInventoryOK1.setCEffectID(0);
			_GCSkillToInventoryOK1.setDuration(0);
		
			pPlayer->sendPacket(&_GCSkillToInventoryOK1);

			// ���� ���� ���δ�.
			pVampirePortalItem->setCharge(pVampirePortalItem->getCharge()-1);

			if (pVampirePortalItem->getCharge() > 0)
			{
				// ���� ������ ���Ҵٸ� ����д�.
				pVampirePortalItem->save(pVampire->getName(), STORAGE_INVENTORY, 0, X, Y);
			}
			else
			{
				// ��Ż �������� ������ �� �Ҹ�Ǿ��ٸ� ������Ų��.
				pInventory->deleteItem(X, Y);
				pVampirePortalItem->destroy();

				// ������ ������ ��ü�� ��������, NULL�� �Ǹ�,
				// ����Ʈ ���ο����� ������ �����͵� NULL�� �ǰ���...
				SAFE_DELETE(pVampirePortalItem);
			}

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pVampire, getSkillType(), NULL);
		}
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

BloodyTunnel g_BloodyTunnel;
