////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTakeDonation.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionTakeDonation.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"

#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCModifyInformation.h"

////////////////////////////////////////////////////////////////////////////////
// read from property buffer
////////////////////////////////////////////////////////////////////////////////
void ActionTakeDonation::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try
	{
		// ���� ���� ���� �о���δ�.
		m_Amount = (Gold_t)propertyBuffer.getPropertyInt("Amount");
	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}

    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// �׼��� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionTakeDonation::execute (Creature * pCreature1, Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);

	int oldAlignment = 0;
	int newAlignment = 0;

	GCNPCResponse       gcNPCResponse;
	GCModifyInformation gcModifyInformation;

	if (pCreature2->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature2);

		// ��η����� ���� ���� ���ٸ� ����� ���� ����. 
		if (pSlayer->getGold() < m_Amount)
		{
			gcNPCResponse.setCode(NPC_RESPONSE_DONATION_FAIL_MONEY);
			pPlayer->sendPacket(&gcNPCResponse);
			return;
		}

		// ��� �ݾ׿� ���� ������ ȸ�������ش�.
		oldAlignment = pSlayer->getAlignment();
		newAlignment = pSlayer->getAlignment();

		// ������ -2500 ������ ��쿡�� ��ȭ�Ѵ�.
		if (oldAlignment < -2500)
		{
			if (-4999 <= oldAlignment && oldAlignment <= -2500)
			{
				newAlignment = min(-2500, (int)(oldAlignment + m_Amount/100));
			}
			else if (-7499 <= oldAlignment && oldAlignment <= -5000)
			{
				newAlignment = min(-2500, (int)(oldAlignment + m_Amount/200));
			}
			else if (-10000 <= oldAlignment && oldAlignment <= -7500)
			{
				newAlignment = min(-2500, (int)(oldAlignment + m_Amount/500));
			}

			pSlayer->saveAlignment(newAlignment);
		}

		// ��αݾ׸�ŭ ���� ���δ�.
		//pSlayer->setGoldEx(pSlayer->getGold() - m_Amount);
		// by sigi. 2002.9.17
		pSlayer->decreaseGoldEx(m_Amount);

		// ��Ŷ�� ������.
		gcNPCResponse.setCode(NPC_RESPONSE_DONATION_OK);
		gcNPCResponse.setParameter(pSlayer->getGold());
		pPlayer->sendPacket(&gcNPCResponse);

		gcModifyInformation.addShortData(MODIFY_ALIGNMENT, pSlayer->getAlignment());
		pPlayer->sendPacket(&gcModifyInformation);
	}
	else if (pCreature2->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature2);

		// ��η����� ���� ���� ���ٸ� ����� ���� ����. 
		if (pVampire->getGold() < m_Amount)
		{
			gcNPCResponse.setCode(NPC_RESPONSE_DONATION_FAIL_MONEY);
			pPlayer->sendPacket(&gcNPCResponse);
			return;
		}

		// ��� �ݾ׿� ���� ������ ȸ�������ش�.
		oldAlignment = pVampire->getAlignment();
		newAlignment = pVampire->getAlignment();

		// ������ -2500 ������ ��쿡�� ��ȭ�Ѵ�.
		if (oldAlignment < -2500)
		{
			if (-4999 <= oldAlignment && oldAlignment <= -2500)
			{
				newAlignment = min(-2500, (int)(oldAlignment + m_Amount/100));
			}
			else if (-7499 <= oldAlignment && oldAlignment <= -5000)
			{
				newAlignment = min(-2500, (int)(oldAlignment + m_Amount/200));
			}
			else if (-10000 <= oldAlignment && oldAlignment <= -7500)
			{
				newAlignment = min(-2500, (int)(oldAlignment + m_Amount/500));
			}

			pVampire->saveAlignment(newAlignment);
		}

		// ��αݾ׸�ŭ ���� ���δ�.
		//pVampire->setGoldEx(pVampire->getGold() - m_Amount);
		// by sigi. 2002.9.18
		pVampire->decreaseGoldEx(m_Amount);

		// ��Ŷ�� ������.
		gcNPCResponse.setCode(NPC_RESPONSE_DONATION_OK);
		gcNPCResponse.setParameter(pVampire->getGold());
		pPlayer->sendPacket(&gcNPCResponse);

		gcModifyInformation.addShortData(MODIFY_ALIGNMENT, pVampire->getAlignment());
		pPlayer->sendPacket(&gcModifyInformation);
	}
	else if (pCreature2->isOusters())
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature2);

		// ��η����� ���� ���� ���ٸ� ����� ���� ����. 
		if (pOusters->getGold() < m_Amount)
		{
			gcNPCResponse.setCode(NPC_RESPONSE_DONATION_FAIL_MONEY);
			pPlayer->sendPacket(&gcNPCResponse);
			return;
		}

		// ��� �ݾ׿� ���� ������ ȸ�������ش�.
		oldAlignment = pOusters->getAlignment();
		newAlignment = pOusters->getAlignment();

		// ������ -2500 ������ ��쿡�� ��ȭ�Ѵ�.
		if (oldAlignment < -2500)
		{
			if (-4999 <= oldAlignment && oldAlignment <= -2500)
			{
				newAlignment = min(-2500, (int)(oldAlignment + m_Amount/100));
			}
			else if (-7499 <= oldAlignment && oldAlignment <= -5000)
			{
				newAlignment = min(-2500, (int)(oldAlignment + m_Amount/200));
			}
			else if (-10000 <= oldAlignment && oldAlignment <= -7500)
			{
				newAlignment = min(-2500, (int)(oldAlignment + m_Amount/500));
			}

			pOusters->saveAlignment(newAlignment);
		}

		// ��αݾ׸�ŭ ���� ���δ�.
		//pOusters->setGoldEx(pOusters->getGold() - m_Amount);
		// by sigi. 2002.9.18
		pOusters->decreaseGoldEx(m_Amount);

		// ��Ŷ�� ������.
		gcNPCResponse.setCode(NPC_RESPONSE_DONATION_OK);
		gcNPCResponse.setParameter(pOusters->getGold());
		pPlayer->sendPacket(&gcNPCResponse);

		gcModifyInformation.addShortData(MODIFY_ALIGNMENT, pOusters->getAlignment());
		pPlayer->sendPacket(&gcModifyInformation);
	}
	else Assert(false);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionTakeDonation::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionTakeDonation("
		<< "Amount:" << (int)m_Amount
		<< ")";
	return msg.toString();

	__END_CATCH
}
