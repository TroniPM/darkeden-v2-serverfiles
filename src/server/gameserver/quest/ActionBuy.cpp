////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionBuy.cpp
// Written By  : 
// Description : 
// NPC�� �÷��̾�κ��� �������� ����̴� �׼��̴�. Sell �׼ǰ�
// ���������� Ư���� �ϴ� ���� ����, ���� �÷��̾�� ���� 
// ������ ������ ��Ŷ���� �����ִ� ������ �Ѵ�.
////////////////////////////////////////////////////////////////////////////////

#include "ActionBuy.h"
#include "Creature.h"
#include "NPC.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCShopMarketCondition.h"
#include "GamePlayer.h"

////////////////////////////////////////////////////////////////////////////////
// ActionBuy �׼��� �׳� Ŭ���̾�Ʈ���� ShopVersion�� �����ִ� ���̹Ƿ�,
// Ư���� �о�鿩�� �� �Ķ���Ͱ� ����.
//
// ���߿� Ư�� ������ �������� ����̴� ���� ���� ���� ������� �ϸ�,
// ���⼭ ������Ƽ�� ���� �о���̸� �ǰ���. ��... NPC �κе� ���ľ�
// �� ���̰�...
////////////////////////////////////////////////////////////////////////////////
void ActionBuy::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY
    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// �׼��� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionBuy::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	NPC* pNPC = dynamic_cast<NPC*>(pCreature1);
	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);

	// ���� ����� �� �޾Ҵٴ� ����� Ŭ���̾�Ʈ���� �˷��ش�.
	GCNPCResponse okpkt;
	pPlayer->sendPacket(&okpkt);

	// ���� ���� �ü��� �˷��ش�.
	GCShopMarketCondition pkt;
	pkt.setObjectID(pNPC->getObjectID());
	pkt.setMarketCondBuy(pNPC->getMarketCondBuy());
	pkt.setMarketCondSell(pNPC->getMarketCondSell());
	pPlayer->sendPacket(&pkt);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionBuy::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionBuy(" << ")";
	return msg.toString();

	__END_CATCH
}
