//////////////////////////////////////////////////////////////////////////////
// Filename    : EventRegeneration.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EventRegeneration.h"
#include "GamePlayer.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Item.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
EventRegeneration::EventRegeneration (GamePlayer* pGamePlayer) 
	throw (Error)
: Event(pGamePlayer)
{
}


//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
EventRegeneration::~EventRegeneration () 
	throw ()
{
}

			
//////////////////////////////////////////////////////////////////////////////
// activate
//////////////////////////////////////////////////////////////////////////////
void EventRegeneration::activate () 
	throw (Error)
{
	__BEGIN_TRY

	if (m_pGamePlayer->getPlayerStatus() == GPS_NORMAL) 
	{
		Assert(m_pGamePlayer != NULL);

		Creature* pCreature = m_pGamePlayer->getCreature();
		Assert(pCreature != NULL);
		Assert(pCreature->isPC());

		Zone* pZone = pCreature->getZone();

		if (pCreature->isAlive())
		{
			if (pCreature->isSlayer())
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

				HP_t oldHP   = pSlayer->getHP(ATTR_CURRENT); // ���� HP
				MP_t oldMP   = pSlayer->getMP(ATTR_CURRENT); // ���� MP

				HP_t maxHP   = pSlayer->getHP(ATTR_MAX); // ���� �ƽ� HP
				MP_t maxMP   = pSlayer->getMP(ATTR_MAX); // ���� �ƽ� MP

				// �������� ���� ȸ����ų HP�� MP�� ���� ����Ѵ�.
				//HP_t regenHP = getPercentValue(maxHP, pSlayer->getHPRegen()); 
				//MP_t regenMP = getPercentValue(maxMP, pSlayer->getMPRegen());
				HP_t regenHP = pSlayer->getHPRegen() * 2;
				MP_t regenMP = pSlayer->getMPRegen() * 2;

				// MAX�� �Ѿ�� ����ϴ�.
				HP_t newHP   = min((int)(oldHP + regenHP), (int)maxHP); 
				MP_t newMP   = min((int)(oldMP + regenMP), (int)maxMP);

				pSlayer->setHP(newHP, ATTR_CURRENT);
				pSlayer->setMP(newMP, ATTR_CURRENT);

				GCModifyInformation GCMI;

				// HP�� ����Ǿ����� ��ε�ĳ�������ش�.
				if (oldHP != newHP)
				{
					GCMI.addShortData(MODIFY_CURRENT_HP, newHP); 

					GCStatusCurrentHP gcStatusCurrentHP;
					gcStatusCurrentHP.setObjectID(pSlayer->getObjectID());
					gcStatusCurrentHP.setCurrentHP(newHP);
					pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcStatusCurrentHP, pSlayer);
				}

				if (oldMP != newMP)
				{
					GCMI.addShortData(MODIFY_CURRENT_MP, newMP); 
				}

				// HP�� MP�� ����Ǿ��ٸ�, ����Ǿ��ٴ� ����� ���ο��� �˷��ش�.
				if (GCMI.getShortCount() != 0 || GCMI.getLongCount() != 0)
					m_pGamePlayer->sendPacket(&GCMI);
			}
			else if (pCreature->isVampire())
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
				HP_t     oldHP    = pVampire->getHP(ATTR_CURRENT);
				HP_t     maxHP    = pVampire->getHP(ATTR_MAX) - pVampire->getSilverDamage();
				HP_t     regenHP  = 0;
				HP_t     newHP    = 0;
 
				/*
				if (pVampire->isFlag(Effect::EFFECT_CLASS_HIDE))
				{
					// ���̵��ϰ� ���� ���� ���ú��� HP�� ���� ���� �ȴ�.
					regenHP = getPercentValue(maxHP, 15 + pVampire->getHPRegen() + pVampire->getINT(ATTR_CURRENT)/60);
					newHP   = min((int)(oldHP + regenHP), (int)maxHP);
				}
				else
				{
					// ���ÿ���...
					regenHP = getPercentValue(maxHP, 10 + pVampire->getHPRegen() + pVampire->getINT(ATTR_CURRENT)/60);
					newHP   = min((int)(oldHP + regenHP), (int)maxHP);
				}
				*/

				// ���� �����ΰ� �ƴѰ����� �˻��Ѵ�.
				// ���̵峪 ���� �� �ִ� ���� �˻簡 ���� ������,
				// �̵� ���¿� ���� HP ȸ�� ��ƾ�� Vampire::heartbeat()�� �� �ֱ� �����̴�.
				if (pVampire->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT))
				{
					// ���� ���¿����� HP�� ȸ������ �ʴ´�.
					regenHP = 0;
				}
				else
				{
					// ���ÿ���...
					regenHP = pVampire->getHPRegen() * 2;
				}

				newHP = min((int)(oldHP + regenHP), (int)maxHP);

				pVampire->setHP(newHP, ATTR_CURRENT);

				GCModifyInformation GCMI;

				// HP�� ����Ǿ����� ��ε�ĳ�������ش�.
				if (oldHP != newHP)
				{
					GCMI.addShortData(MODIFY_CURRENT_HP, newHP); 

					GCStatusCurrentHP gcStatusCurrentHP;
					gcStatusCurrentHP.setObjectID(pVampire->getObjectID());
					gcStatusCurrentHP.setCurrentHP(newHP);
					pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcStatusCurrentHP, pVampire);
				}

				// HP�� ����Ǿ��ٴ� ����� ���ο��� �˷��ش�.
				if (GCMI.getShortCount() != 0 || GCMI.getLongCount() != 0) m_pGamePlayer->sendPacket(&GCMI);
			}
			else if (pCreature->isOusters())
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
		
				HP_t oldHP   = pOusters->getHP(ATTR_CURRENT); // ���� HP
				MP_t oldMP   = pOusters->getMP(ATTR_CURRENT); // ���� MP

				HP_t maxHP   = pOusters->getHP(ATTR_MAX); // ���� �ƽ� HP
				MP_t maxMP   = pOusters->getMP(ATTR_MAX); // ���� �ƽ� MP

				// �������� ���� ȸ����ų HP�� MP�� ���� ����Ѵ�.
				//HP_t regenHP = getPercentValue(maxHP, pOusters->getHPRegen()); 
				//MP_t regenMP = getPercentValue(maxMP, pOusters->getMPRegen());
				HP_t regenHP = pOusters->getHPRegen() * 2;
				MP_t regenMP = pOusters->getMPRegen() * 2;

				// MAX�� �Ѿ�� ����ϴ�.
				HP_t newHP   = min((int)(oldHP + regenHP), (int)maxHP); 
				MP_t newMP   = min((int)(oldMP + regenMP), (int)maxMP);

				pOusters->setHP(newHP, ATTR_CURRENT);

				if ( oldMP < newMP ) pOusters->setMP(newMP, ATTR_CURRENT);
				newMP = pOusters->getMP(ATTR_CURRENT);

				GCModifyInformation GCMI;

				// HP�� ����Ǿ����� ��ε�ĳ�������ش�.
				if (oldHP != newHP)
				{
					GCMI.addShortData(MODIFY_CURRENT_HP, newHP); 

					GCStatusCurrentHP gcStatusCurrentHP;
					gcStatusCurrentHP.setObjectID(pOusters->getObjectID());
					gcStatusCurrentHP.setCurrentHP(newHP);
					pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &gcStatusCurrentHP, pOusters);
				}

				if (oldMP != newMP)
				{
					GCMI.addShortData(MODIFY_CURRENT_MP, newMP); 
				}

				// HP�� MP�� ����Ǿ��ٸ�, ����Ǿ��ٴ� ����� ���ο��� �˷��ش�.
				if (GCMI.getShortCount() != 0 || GCMI.getLongCount() != 0)
					m_pGamePlayer->sendPacket(&GCMI);
			}
		}

		// 10 �ʸ��� ȸ������ �ֱ� ���ؼ��� deadline �� �������� ��� �Ѵ�.
		Timeval delay;
		delay.tv_sec = 10;
		delay.tv_usec = 0;
	
		m_Deadline = m_Deadline + delay;
	}
	else
	{
		Timeval delay;
		delay.tv_sec = 10;
		delay.tv_usec = 0;
	
		m_Deadline = m_Deadline + delay;
	}
	
	__END_CATCH
}
