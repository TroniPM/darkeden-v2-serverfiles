//////////////////////////////////////////////////////////////////////////////
// Filename    : CGResurrectHandler.cpp
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGResurrect.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Effect.h"
	#include "EffectComa.h"
	#include "EffectManager.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGResurrectHandler::execute (CGResurrect* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	Creature* pCreature = pGamePlayer->getCreature();
	Assert(pCreature != NULL);

	if (pCreature->findEffect( Effect::EFFECT_CLASS_ETERNITY )) return;

	// ���� ũ���Ŀ��� COMA ����Ʈ�� �پ����� �ʴٸ� ������. 
	if (pCreature->isFlag(Effect::EFFECT_CLASS_COMA))
	{
		//cout << "�÷��� �پ�����." << endl;

		// COMA ����Ʈ�� �����Ѵ�.
		EffectManager* pEffectManager = pCreature->getEffectManager();
		Assert(pEffectManager != NULL);

		EffectComa* pEffectComa = (EffectComa*)(pEffectManager->findEffect(Effect::EFFECT_CLASS_COMA));
		Assert(pEffectComa != NULL);

		// ���� �� 5�ʰ� ���� ������ �ʾҴٸ�, �ǻ�Ƴ� �� ����.
		if (pEffectComa->canResurrect())
		{
			//cout << "5�ʰ� �������� ��Ȱ��ų �� ����." << endl;

			/*
			if (pCreature->isSlayer())
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
				//cout << "���� HP:" << pSlayer->getHP(ATTR_CURRENT);
			}
			else if (pCreature->isVampire())
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
				//cout << "���� HP:" << pVampire->getHP(ATTR_CURRENT);
			}
			*/

			// ��������� 0���� ������ش�. �̷��� �ϸ� ��Ʈ��Ʈ����
			// unaffect�Ǹ鼭 �÷��̾ �ڵ����� ��Ȱ��Ű�� �ȴ�.
			pEffectComa->setDeadline(0);
		}
		else
		{
			//cout << "5�ʰ� ������ �ʾҴ�." << endl;
		}
	}
	else
	{
		//cout << "�÷��װ� ����." << endl;

		// ��������� Ȯ���� �� �� ������, ��򰡿��� ���� �ڿ�
		// �ڸ� ����Ʈ�� ���ư� �����ų�, ���� ���¿��� HP�� �ö󰡴� ������ 
		// �߻��ϴ� �� �ϴ�. �׷��� ����Ʈ �ɷ����� ���� ��Ȳ���� ��Ŷ
		// ���ƿ��� ������ ���̴� �ڵ带 ����ִ´�.
		if (pCreature->isSlayer())
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
			pSlayer->setHP(0, ATTR_CURRENT);
			pSlayer->deleteEffect(Effect::EFFECT_CLASS_COMA);

			EffectComa* pEffectComa = new EffectComa(pSlayer);
			pEffectComa->setStartTime();
			pEffectComa->setDeadline(0);
			pSlayer->addEffect(pEffectComa);
			pSlayer->setFlag(Effect::EFFECT_CLASS_COMA);
		}
		else if (pCreature->isVampire())
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
			pVampire->setHP(0, ATTR_CURRENT);
			pVampire->deleteEffect(Effect::EFFECT_CLASS_COMA);

			EffectComa* pEffectComa = new EffectComa(pVampire);
			pEffectComa->setStartTime();
			pEffectComa->setDeadline(0);
			pVampire->addEffect(pEffectComa);
			pVampire->setFlag(Effect::EFFECT_CLASS_COMA);
		}
		else if (pCreature->isOusters())
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
			pOusters->setHP(0, ATTR_CURRENT);
			pOusters->deleteEffect(Effect::EFFECT_CLASS_COMA);

			EffectComa* pEffectComa = new EffectComa(pOusters);
			pEffectComa->setStartTime();
			pEffectComa->setDeadline(0);
			pOusters->addEffect(pEffectComa);
			pOusters->setFlag(Effect::EFFECT_CLASS_COMA);
		}
		else
		{
			Assert(false);
		}
	}

#endif

	__END_DEBUG_EX __END_CATCH
}

