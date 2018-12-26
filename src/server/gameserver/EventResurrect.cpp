//////////////////////////////////////////////////////////////////////////////
// Filename    : EventResurrect.cpp
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EventResurrect.h"
#include "GamePlayer.h"
#include "Zone.h"
#include "ZoneGroup.h"
#include "ZoneGroupManager.h"
#include "ZoneInfo.h"
#include "ZoneInfoManager.h"
#include "IncomingPlayerManager.h"
#include "ZonePlayerManager.h"
#include "Slayer.h"
#include "PCSlayerInfo2.h"
#include "Vampire.h"
#include "PCVampireInfo2.h"
#include "Ousters.h"
#include "TimeManager.h"
#include "PlayerStatus.h"

#include "PacketUtil.h"

#include "Gpackets/GCUpdateInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class EventResurrect member methods
//////////////////////////////////////////////////////////////////////////////

EventResurrect::EventResurrect(GamePlayer* pGamePlayer) 
	throw()
: Event(pGamePlayer)
{
//	m_pResurrectZone = NULL;
//	m_X = m_Y = 0;
}

EventResurrect::~EventResurrect() 
	throw()
{
}

void EventResurrect::activate () 
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(m_pGamePlayer != NULL);

	Creature * pDeadPC = m_pGamePlayer->getCreature();

	Assert(pDeadPC != NULL);

	// ���̵��� ���¿��� �׾��ٸ�, ���̵带 Ǯ���ش�.
	pDeadPC->removeFlag(Effect::EFFECT_CLASS_HIDE);

	// �����带 �ٲ��ش�.
	if (pDeadPC->isVampire() && pDeadPC->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT))
	{
		pDeadPC->setMoveMode(Creature::MOVE_MODE_FLYING);
	}
	else
	{
		pDeadPC->setMoveMode(Creature::MOVE_MODE_WALKING);
	}

	// HP�� ä���ش�.
	if (pDeadPC->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pDeadPC);
		pSlayer->setHP(pSlayer->getHP(ATTR_MAX), ATTR_CURRENT);
	}
	else if (pDeadPC->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pDeadPC);
		pVampire->setHP(pVampire->getHP(ATTR_MAX), ATTR_CURRENT);
	}
	else if (pDeadPC->isOusters())
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pDeadPC);
		pOusters->setHP(pOusters->getHP(ATTR_MAX), ATTR_CURRENT);
	}

	// �� zone�� �������� �ʴ´�. by sigi. 2002.5.11
	Zone* pOldZone = pDeadPC->getZone();
	Assert(pOldZone != NULL);

	try 
	{
		// ���׷��� ZPM���� �÷��̾ �����Ѵ�.
		pOldZone->getZoneGroup()->getZonePlayerManager()->deletePlayer(m_pGamePlayer->getSocket()->getSOCKET());

		// ���⼭ ������������� Save �̺�Ʈ�� IPM���� �������� �ʴ´�.
		m_pGamePlayer->setPlayerStatus(GPS_WAITING_FOR_CG_READY);

		// IPM���� �÷��̾ �ű��.
		//g_pIncomingPlayerManager->pushPlayer(m_pGamePlayer);
		pOldZone->getZoneGroup()->getZonePlayerManager()->pushOutPlayer(m_pGamePlayer);

	} 
	catch (NoSuchElementException& t) 
	{
		filelog("eventRessurect.txt", "%s-%s", t.toString().c_str(), pDeadPC->getName().c_str());
		cerr << "EventResurrect::activate() : NoSuchElementException" << endl;
		//throw Error("���� �÷��̾ �������� �ʽ��ϴ�.");
		// ��� ����������.. -_-;
		// �����ϰ�.. �׳� �����Ѵ�.
		// by sigi. 2002.11.25
	}

	// �׾��� ��� killCreature���� ���� ���� �ϱ� ������ �׳� �Ҵ� ������ �ȴ�.

	// �̰Ŵ� ZonePlayerManager�� heartbeat���� ó���Ѵ�.
	// �ּ�ó�� by sigi. 2002.5.14
	//pDeadPC->registerObject();

	/*
	// GCUpdateInfo ��Ŷ�� �����д�.
	GCUpdateInfo gcUpdateInfo;

	makeGCUpdateInfo(&gcUpdateInfo, pDeadPC);
	
	m_pGamePlayer->sendPacket(&gcUpdateInfo);
	*/

	__END_DEBUG
	__END_CATCH
}

string EventResurrect::toString () const 
	throw ()
{
	StringStream msg;
	msg << "EventResurrect("
		<< ")";
	return msg.toString();
}
