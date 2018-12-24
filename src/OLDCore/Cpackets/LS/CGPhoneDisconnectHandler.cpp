//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPhoneDisconnectHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGPhoneDisconnect.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Slayer.h"
	#include "TelephoneCenter.h"

	#include "Gpackets/GCPhoneDisconnected.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGPhoneDisconnectHandler::execute (CGPhoneDisconnect* pPacket , Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	Creature* pCreature = pGamePlayer->getCreature();

	Assert (pCreature->isSlayer());

	Player* pTargetPlayer = NULL;

	bool Success = false;

	Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

	SlotID_t PhoneSlot = pPacket->getSlotID();
	SlotID_t TargetPhoneSlot = MAX_PHONE_SLOT;

	Assert (PhoneSlot < MAX_PHONE_SLOT);

	PhoneNumber_t PhoneNumber = pSlayer->getPhoneNumber();
	PhoneNumber_t TargetPhoneNumber = pSlayer->getPhoneSlotNumber(PhoneSlot);

	Assert (TargetPhoneNumber != 0);

	Slayer* pTargetSlayer = g_pTelephoneCenter->getSlayer(TargetPhoneNumber);

	//cout << "Disconnect PhoneSlot : " << (int)PhoneSlot << ", Phone Number : " << (int)TargetPhoneNumber << endl;

	// ã������....
	if (pTargetSlayer != NULL) 
	{
		pTargetPlayer = pTargetSlayer->getPlayer();

		if (pTargetSlayer->isSlotByPhoneNumber(PhoneNumber)) 
		{
			// �� ��ȣ�� �� ��ȣ�� ����ִ� ������ ã�´�.
			TargetPhoneSlot = pTargetSlayer->getSlotWithPhoneNumber(PhoneNumber);

			Success = true;
		}
	}

	// ���������� ã�� ������ ���
	if (Success) 
	{
		// ���� ����� �����̹Ƿ� 0 ���� ���� �� ����.
		pTargetSlayer->setPhoneSlotNumber(TargetPhoneSlot, 0);
		pSlayer->setPhoneSlotNumber(PhoneSlot, 0);

		// ���� ������� ������ ��Ŷ
		GCPhoneDisconnected gcPhoneDisconnected;
		gcPhoneDisconnected.setPhoneNumber(TargetPhoneNumber);
		gcPhoneDisconnected.setSlotID(PhoneSlot);

		// ��������� ����� ������� ������ ��Ŷ
		GCPhoneDisconnected gcPhoneDisconnected2;
		gcPhoneDisconnected2.setPhoneNumber(PhoneNumber);
		gcPhoneDisconnected2.setSlotID(TargetPhoneSlot);

		pPlayer->sendPacket(&gcPhoneDisconnected);
		pTargetPlayer->sendPacket(&gcPhoneDisconnected2);

		//cout << "Disconnected Successfull" << endl;

	// ������ ���� ��� -_-;
	} 
	else 
	{
		// ��ϵ� ��ȭ��ȣ�� ���� ����� Ư�� ������ ���� �����̴�.
		// ���� ��� ��ȣ�� �ʱ�ȭ �����ش�.
		pSlayer->setPhoneSlotNumber(PhoneSlot, 0);

		// ���� ������� ������ ��Ŷ
		GCPhoneDisconnected gcPhoneDisconnected;
		gcPhoneDisconnected.setPhoneNumber(TargetPhoneNumber);
		gcPhoneDisconnected.setSlotID(PhoneSlot);

		pPlayer->sendPacket(&gcPhoneDisconnected);

		//cout << "Not found That Slot PhoneNumber User" << endl;

	}

#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH
}
