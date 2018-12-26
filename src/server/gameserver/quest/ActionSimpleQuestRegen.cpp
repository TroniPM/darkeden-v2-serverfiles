////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSimpleQuestRegen.cpp
// Written By  : 
// Description : 
// ���� NPC�� ���� ó�� �ε��� ��, ���� NPC�� �Ȱ� �� ��������
// �غ��ϴ� �׼��̴�. ShopTemplate Ŭ������ �Ŵ����� ������ ��.
////////////////////////////////////////////////////////////////////////////////

#include "ActionSimpleQuestRegen.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
ActionSimpleQuestRegen::ActionSimpleQuestRegen()
	throw()
{
	__BEGIN_TRY

	m_Period.tv_sec     = 0;
	m_Period.tv_usec    = 0;
	m_NextRegen.tv_sec  = 0;
	m_NextRegen.tv_usec = 0;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
ActionSimpleQuestRegen::~ActionSimpleQuestRegen()
	throw()
{
	__BEGIN_TRY

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionSimpleQuestRegen::read (PropertyBuffer & propertyBuffer)
    
{
	__BEGIN_TRY

	try 
	{
		//int m_Num   = propertyBuffer.getPropertyInt("Num");

		// ���� ������Ʈ �ֱ⸦ �о���δ�. (�� ����)
		int nSecond = propertyBuffer.getPropertyInt("Period");

		m_Period.tv_sec = nSecond;

		// ���� ���� ������Ʈ�� ���� �� ���ΰ��� ������ �ش�.
		Timeval currentTime;
		getCurrentTime(currentTime);
		m_NextRegen = currentTime;
	} 
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
	
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// �׼��� �����Ѵ�.
// NOTE : ShopTemplate�� �� �׼��� ����Ǳ� ���� ��� �ε�Ǿ� �־�� �Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionSimpleQuestRegen::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

/*	Assert(pCreature1 != NULL);
	Assert(pCreature1->isNPC());

	NPC* pNPC = dynamic_cast<NPC*>(pCreature1);
	Assert(pNPC != NULL);

	Zone* pZone = pNPC->getZone();
	Assert(pZone != NULL);

	// ���� �ð��� ����.
	Timeval currentTime;
	getCurrentTime(currentTime);

	// ������Ʈ�� �ð��� ���� ���� �ʾҴٸ� �� �����Ѵ�.
	if (currentTime < m_NextRegen) return;

	// ������ NPC�� �̾߱��ϰ� �ִ� �÷��̾ ������ ���� �˻��Ѵ�.
	VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
	int centerX = pNPC->getX();
	int centerY = pNPC->getY();
	try
	{
		for (int zx = centerX - 5; zx <= centerX+5; zx++)
		{
			for (int zy = centerY - 5; zy <= centerY+5; zy++)
			{
				// ��ǥ�� �Ѱ踦 �Ѿ�� �ʾҴ��� üũ...
				if (!rect.ptInRect(zx, zy))
				{
					continue;
				}

				Tile& tile = pZone->getTile(zx, zy);

				// �ɾ�ٴϴ� ũ���ĸ� �˻�
				if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
				{
					Creature* pNearCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
					Assert(pNearCreature != NULL);
					// NPC�� �̾߱��ϰ� �ִ� ���� ������ �� ����
					if (pNearCreature->isPC())
					{
						return;
					}
				}
				// ���ƴٴϴ� ũ���ĸ� �˻�
				if (tile.hasCreature(Creature::MOVE_MODE_FLYING))
				{
					Creature* pNearCreature = tile.getCreature(Creature::MOVE_MODE_FLYING);
					Assert(pNearCreature != NULL);
					// NPC�� �̾߱��ϰ� �ִ� ���� ������ �� ����
					if (pNearCreature->isPC())
					{
						return;
					}
				}
			}
		}
	}
	catch (Throwable & t)
	{
		filelog("questBUG.txt", "%s", t.toString().c_str());
		return;
	}

	try {

		pNPC->regenSimpleQuest();


	} catch (Error& t) {
		// ������ �ٽ� ������.
		filelog("regenQuestBug.txt", "%s", t.toString().c_str());
		throw;
	} catch (Throwable& t) {
		filelog("regenQuestBug.txt", "%s", t.toString().c_str());
	}

	// ���� ������Ʈ�� �ð��� �����ش�.
	m_NextRegen = m_NextRegen + m_Period;*/

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionSimpleQuestRegen::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ActionSimpleQuestRegen()";

	return msg.toString();

	__END_CATCH
}
