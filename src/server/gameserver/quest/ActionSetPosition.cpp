////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSetPosition.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionSetPosition.h"
#include "Zone.h"
#include "NPC.h"
#include "NPCInfo.h"
#include "Tile.h"
#include <fstream>

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionSetPosition::read (PropertyBuffer & propertyBuffer)
	
{
	__BEGIN_TRY

	try
	{
		m_ZoneID = propertyBuffer.getPropertyInt("ZoneID");
		m_X      = propertyBuffer.getPropertyInt("X");
		m_Y      = propertyBuffer.getPropertyInt("Y");
		m_Dir    = propertyBuffer.getPropertyInt("Dir");
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
void ActionSetPosition::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	try {
		Assert(pCreature1 != NULL);
		Assert(pCreature2 == NULL);
		Assert(!pCreature1->isPC());

		////////////////////////////////////////////////////////////////////////////////
		// ũ��ó�� ���� �����Ѵ�.
		// ���ο��� ZoneInfoManager, ZoneGroupManager �� 
		// �˻��ؼ� �����ϰ� �� �����͸� �������ش�.
		////////////////////////////////////////////////////////////////////////////////
		pCreature1->setZoneID(m_ZoneID);

		////////////////////////////////////////////////////////////////////////////////
		// ���� ũ��ó�� �߰��Ѵ�.
		// ���ο��� ũ��ó�� ��ǥ, ������ �������ش�.
		////////////////////////////////////////////////////////////////////////////////
		Zone * pZone = pCreature1->getZone();
		Assert(pZone != NULL);

		pZone->addCreature(pCreature1 , m_X , m_Y , m_Dir);

		NPC* pNPC = dynamic_cast<NPC*>(pCreature1);

		if (pNPC->isShowInMinimap())
		{
			NPCInfo* pNPCInfo = new NPCInfo();
			pNPCInfo->setName(pNPC->getName());
			pNPCInfo->setNPCID(pNPC->getNPCID());
			pNPCInfo->setX(pNPC->getX());
			pNPCInfo->setY(pNPC->getY());

			pZone->addNPCInfo(pNPCInfo);
			pZone->getTile( m_X-1, m_Y ).setBlocked(Creature::MOVE_MODE_WALKING);
		}
	} catch (Throwable &t) {
		cout << t.toString() << endl;
		throw; // -_-;
	}
	
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionSetPosition::toString () const
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionSetPosition("
		<< "ZoneID:" << (int)m_ZoneID
		<< ",X:"     << (int)m_X
		<< ",Y:"     << (int)m_Y
		<< ",Dir:"   << Dir2String[m_Dir]
		<< ")";
	return msg.toString();

	__END_CATCH
}
