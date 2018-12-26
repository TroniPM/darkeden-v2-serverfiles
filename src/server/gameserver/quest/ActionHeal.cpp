////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionHeal.cpp
// Written By  : 
// Description : 
////////////////////////////////////////////////////////////////////////////////

#include "ActionHeal.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "GamePlayer.h"
#include "Zone.h"
#include "DB.h"
#include "LogClient.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCStatusCurrentHP.h"

#include "EffectAftermath.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionHeal::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY
    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionHeal::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	Player* pPlayer = pCreature2->getPlayer();
	Zone*   pZone   = pCreature2->getZone();
	
	Assert(pPlayer != NULL);

	// �ϴ� Ŭ���̾�Ʈ�� ���ؼ� OK ��Ŷ�� �� ������.
	GCNPCResponse okpkt;
	okpkt.setCode(NPC_RESPONSE_HEAL);
	pPlayer->sendPacket(&okpkt);

	// �׾��ų� �ڸ� �ɷ������� �� ġ�����ش�.
	if ( pCreature2->isDead() || pCreature2->isFlag( Effect::EFFECT_CLASS_COMA ) )
	{
		return;
	}

	// �����̾���...
	if (pCreature2->isSlayer())
	{
		Slayer*             pSlayer        = dynamic_cast<Slayer*>(pCreature2);
		EffectManager*      pEffectManager = pSlayer->getEffectManager();
		GCModifyInformation modifyPkt;
		GCRemoveEffect      removePkt;
		GCStatusCurrentHP   hpPkt;

		// ���� HP�� MP�� Ǯ�� ä���ش�.
		if (pSlayer->getHP(ATTR_CURRENT) < pSlayer->getHP(ATTR_MAX))
		{
			pSlayer->setHP(pSlayer->getHP(ATTR_MAX), ATTR_CURRENT);
			modifyPkt.addShortData(MODIFY_CURRENT_HP, pSlayer->getHP(ATTR_CURRENT));

			hpPkt.setObjectID(pSlayer->getObjectID());
			hpPkt.setCurrentHP(pSlayer->getHP(ATTR_CURRENT));
		}
		if (pSlayer->getMP(ATTR_CURRENT) < pSlayer->getMP(ATTR_MAX))
		{
			pSlayer->setMP(pSlayer->getMP(ATTR_MAX), ATTR_CURRENT);
			modifyPkt.addShortData(MODIFY_CURRENT_MP, pSlayer->getMP(ATTR_CURRENT));
		}

		// ���� ����Ʈ�� �����Ѵ�.
		Effect* pBloodDrainEffect = pEffectManager->findEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN);
		if (pBloodDrainEffect != NULL)
		{
			// DB���� �����ϰ�, ����Ʈ �Ŵ������� �����Ѵ�.
			pBloodDrainEffect->destroy(pSlayer->getName());
			pEffectManager->deleteEffect(pSlayer, Effect::EFFECT_CLASS_BLOOD_DRAIN);

			// ���� �Ƹ�����Ʈ�� �����ϱ� ���� ������ ����Ʈ�� �ٿ��ش�.
			if (pSlayer->isFlag(Effect::EFFECT_CLASS_AFTERMATH))
			{
				Effect* pEffect = pEffectManager->findEffect(Effect::EFFECT_CLASS_AFTERMATH);
				EffectAftermath* pEffectAftermath = dynamic_cast<EffectAftermath*>(pEffect);
				pEffectAftermath->setDeadline(5*600); // 5�� ���� ���ӵȴ�.
			}
			else
			{
				EffectAftermath* pEffectAftermath = new EffectAftermath(pSlayer);
				pEffectAftermath->setDeadline(5*600); // 5�� ���� ���ӵȴ�.
				pEffectManager->addEffect(pEffectAftermath);
				pSlayer->setFlag(Effect::EFFECT_CLASS_AFTERMATH);
				pEffectAftermath->create(pSlayer->getName());
			}

			// ��Ŷ���� ������ ���Ѵ�.
			removePkt.addEffectList((EffectID_t)Effect::EFFECT_CLASS_BLOOD_DRAIN);

			// ������ ġ���ϸ� �ɷ�ġ�� ��ȭ�ϰ� �ȴ�.
			SLAYER_RECORD prev;
			pSlayer->getSlayerRecord(prev);
			pSlayer->initAllStat();
			pSlayer->sendModifyInfo(prev);
			pSlayer->sendRealWearingInfo();
		}

		// �� ����Ʈ�� �����Ѵ�.
		Effect* pEffectPoison = pEffectManager->findEffect(Effect::EFFECT_CLASS_POISON);
		if (pEffectPoison != NULL)
		{
			// ����Ʈ �Ŵ������� �����Ѵ�.
			pEffectManager->deleteEffect(pSlayer, Effect::EFFECT_CLASS_POISON);

			// ��Ŷ���� ������ ���Ѵ�.
			removePkt.addEffectList((EffectID_t)Effect::EFFECT_CLASS_POISON);
		}

		// ��ũ��� ������ ����Ʈ�� �����Ѵ�.
		Effect* pEffectDarkBluePoison = pEffectManager->findEffect(Effect::EFFECT_CLASS_DARKBLUE_POISON);
		if (pEffectDarkBluePoison != NULL)
		{
			// ����Ʈ �Ŵ������� �����Ѵ�.
			pEffectManager->deleteEffect(pSlayer, Effect::EFFECT_CLASS_DARKBLUE_POISON);

			// ��Ŷ���� ������ ���Ѵ�.
			removePkt.addEffectList((EffectID_t)Effect::EFFECT_CLASS_DARKBLUE_POISON);
		}

		// ��Ŷ �����ش�.
		removePkt.setObjectID(pSlayer->getObjectID());
		pPlayer->sendPacket(&modifyPkt);
		pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &removePkt);
		pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &hpPkt, pSlayer);

		log(LOG_HEAL, pSlayer->getName(), "");
	}
	else if (pCreature2->isVampire())
	{
		Vampire*            pVampire = dynamic_cast<Vampire*>(pCreature2);
		//EffectManager*      pEffectManager = pVampire->getEffectManager();
		GCModifyInformation modifyPkt;
		GCRemoveEffect      removePkt;
		GCStatusCurrentHP   hpPkt;

		// HP ä���ְ�...
		if (pVampire->getHP(ATTR_CURRENT) < pVampire->getHP(ATTR_MAX))
		{
			pVampire->setHP(pVampire->getHP(ATTR_MAX), ATTR_CURRENT);
			modifyPkt.addShortData(MODIFY_CURRENT_HP, pVampire->getHP(ATTR_CURRENT));

			hpPkt.setObjectID(pVampire->getObjectID());
			hpPkt.setCurrentHP(pVampire->getHP(ATTR_CURRENT));
		}

		// ��Ŷ �����ش�.
		removePkt.setObjectID(pVampire->getObjectID());
		pPlayer->sendPacket(&modifyPkt);
		pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &removePkt);
		pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &hpPkt, pVampire);

		log(LOG_HEAL, pVampire->getName(), "");
	}
	else if (pCreature2->isOusters())
	{
		Ousters*             pOusters        = dynamic_cast<Ousters*>(pCreature2);
		EffectManager*      pEffectManager = pOusters->getEffectManager();
		GCModifyInformation modifyPkt;
		GCRemoveEffect      removePkt;
		GCStatusCurrentHP   hpPkt;

		// ���� HP�� MP�� Ǯ�� ä���ش�.
		if (pOusters->getHP(ATTR_CURRENT) < pOusters->getHP(ATTR_MAX) || pOusters->getSilverDamage() != 0 )
		{
			Silver_t prev = pOusters->getSilverDamage();

			if ( prev != 0 )
			{
				pOusters->setSilverDamage(0);
				modifyPkt.addShortData(MODIFY_SILVER_DAMAGE, pOusters->getSilverDamage());
			}

			pOusters->setHP(pOusters->getHP(ATTR_MAX), ATTR_CURRENT);
			modifyPkt.addShortData(MODIFY_CURRENT_HP, pOusters->getHP(ATTR_CURRENT));

			hpPkt.setObjectID(pOusters->getObjectID());
			hpPkt.setCurrentHP(pOusters->getHP(ATTR_CURRENT));
		}
		if (pOusters->getMP(ATTR_CURRENT) < pOusters->getMP(ATTR_MAX))
		{
			pOusters->setMP(pOusters->getMP(ATTR_MAX), ATTR_CURRENT);
			modifyPkt.addShortData(MODIFY_CURRENT_MP, pOusters->getMP(ATTR_CURRENT));
		}

		// �� ����Ʈ�� �����Ѵ�.
		Effect* pEffectPoison = pEffectManager->findEffect(Effect::EFFECT_CLASS_POISON);
		if (pEffectPoison != NULL)
		{
			// ����Ʈ �Ŵ������� �����Ѵ�.
			pEffectManager->deleteEffect(pOusters, Effect::EFFECT_CLASS_POISON);

			// ��Ŷ���� ������ ���Ѵ�.
			removePkt.addEffectList((EffectID_t)Effect::EFFECT_CLASS_POISON);
		}

		// ��ũ��� ������ ����Ʈ�� �����Ѵ�.
		Effect* pEffectDarkBluePoison = pEffectManager->findEffect(Effect::EFFECT_CLASS_DARKBLUE_POISON);
		if (pEffectDarkBluePoison != NULL)
		{
			// ����Ʈ �Ŵ������� �����Ѵ�.
			pEffectManager->deleteEffect(pOusters, Effect::EFFECT_CLASS_DARKBLUE_POISON);

			// ��Ŷ���� ������ ���Ѵ�.
			removePkt.addEffectList((EffectID_t)Effect::EFFECT_CLASS_DARKBLUE_POISON);
		}

		// ���� ����Ʈ�� �����Ѵ�.
		Effect* pBloodDrainEffect = pEffectManager->findEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN);
		if (pBloodDrainEffect != NULL)
		{
			pBloodDrainEffect->setDeadline(0);

			// ���� �Ƹ�����Ʈ�� �����ϱ� ���� ������ ����Ʈ�� �ٿ��ش�.
			if (pOusters->isFlag(Effect::EFFECT_CLASS_AFTERMATH))
			{
				Effect* pEffect = pEffectManager->findEffect(Effect::EFFECT_CLASS_AFTERMATH);
				EffectAftermath* pEffectAftermath = dynamic_cast<EffectAftermath*>(pEffect);
				pEffectAftermath->setDeadline(5*600); // 5�� ���� ���ӵȴ�.
			}
			else
			{
				EffectAftermath* pEffectAftermath = new EffectAftermath(pOusters);
				pEffectAftermath->setDeadline(5*600); // 5�� ���� ���ӵȴ�.
				pEffectManager->addEffect(pEffectAftermath);
				pOusters->setFlag(Effect::EFFECT_CLASS_AFTERMATH);
				pEffectAftermath->create(pOusters->getName());
			}

			// ��Ŷ���� ������ ���Ѵ�.
			removePkt.addEffectList((EffectID_t)Effect::EFFECT_CLASS_BLOOD_DRAIN);
		}


		// ��Ŷ �����ش�.
		removePkt.setObjectID(pOusters->getObjectID());
		pPlayer->sendPacket(&modifyPkt);
		pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &removePkt);
		pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &hpPkt, pOusters);

		log(LOG_HEAL, pOusters->getName(), "");

	}
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
string ActionHeal::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionHeal("
	    << ")";
	return msg.toString();

	__END_CATCH
}
