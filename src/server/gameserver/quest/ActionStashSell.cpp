////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionStashSell.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionStashSell.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "PriceManager.h"
#include "Gpackets/GCStashSell.h"
#include "GamePlayer.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionStashSell::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY 
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// �׼��� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionStashSell::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY 

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	Price_t     price;
	BYTE        curStashNum;
	GCStashSell pkt;

	if (pCreature2->isSlayer())
	{
		// ���� ������ �ִ� �������� ������ ���� �������� ���� ���Ѵ�.
		curStashNum = dynamic_cast<Slayer*>(pCreature2)->getStashNum();

		if (curStashNum < STASH_RACK_MAX)
		{
			price = g_pPriceManager->getStashPrice(curStashNum+1);
		}
		else price = 0;
	}
	else if (pCreature2->isVampire())
	{
		// ���� ������ �ִ� �������� ������ ���� �������� ���� ���Ѵ�.
		curStashNum = dynamic_cast<Vampire*>(pCreature2)->getStashNum();

		if (curStashNum < STASH_RACK_MAX)
		{
			price = g_pPriceManager->getStashPrice(curStashNum+1);
		}
		else price = 0;
	}
	else if (pCreature2->isOusters())
	{
		// ���� ������ �ִ� �������� ������ ���� �������� ���� ���Ѵ�.
		curStashNum = dynamic_cast<Ousters*>(pCreature2)->getStashNum();

		if (curStashNum < STASH_RACK_MAX)
		{
			price = g_pPriceManager->getStashPrice(curStashNum+1);
		}
		else price = 0;
	}

	// ��Ŷ���� ���� ������ �ش�.
	pkt.setPrice(price);

	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);
	pPlayer->sendPacket(&pkt);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionStashSell::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ActionStashSell(" << ")";

	return msg.toString();

	__END_CATCH
}
