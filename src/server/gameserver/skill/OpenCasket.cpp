//////////////////////////////////////////////////////////////////////////////
// Filename    : OpenCasket.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////
#include "OpenCasket.h"

#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK3.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCAddEffect.h"
#include "HitRoll.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ���� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void OpenCasket::execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayerself)" << endl;

	Assert(pVampire != NULL);
	//Assert(pVampireSkillSlot != NULL);

	//cout << "Open Casket" << endl;
	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t       SkillType  = getSkillType();
		//SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		// �� �ӿ� ����ִ� ��츸 ��� �����ϴ�.
		bool bEffected   = pVampire->isFlag(Effect::EFFECT_CLASS_CASKET);

		if (bEffected)
		{
			//cout << "Open Casket Succeed" << endl;

			// ����Ʈ Ŭ������ ����� ���δ�.
			EffectManager* pEffectManager = pVampire->getEffectManager();
			Assert(pEffectManager!=NULL);

			Effect* pEffect = pEffectManager->findEffect( Effect::EFFECT_CLASS_CASKET );

			if (pEffect!=NULL)
			{
				pEffect->setDeadline(0);
//				pEffect->unaffect();
//				pEffectManager->deleteEffect( Effect::EFFECT_CLASS_CASKET );
//				pVampire->removeFlag( Effect::EFFECT_CLASS_CASKET );
			}

			// ��Ŷ�� ����� ������.
			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(0);
		
			_GCSkillToSelfOK2.setObjectID(pVampire->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(0);
		
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
		
			pZone->broadcastPacket(pVampire->getX(), pVampire->getY(),  &_GCSkillToSelfOK2, pVampire);

			// set Next Run Time
			//pVampireSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			//cout << "Open Casket Failed1" << endl;
			executeSkillFailNormal(pVampire, getSkillType(), NULL);
		}
	} 
	catch (Throwable & t) 
	{
		//cout << "Open Casket Failed2" << endl;
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayerself)" << endl;

	__END_CATCH
}

OpenCasket g_OpenCasket;
