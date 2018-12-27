//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSchedule.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectSchedule.h"
#include "Effect.h"
#include "EffectManager.h"
#include "Assert.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "Tile.h"
#include "ObjectRegistry.h"

#include "skill/EffectVampirePortal.h"

#include "Gpackets/GCAddVampirePortal.h"


//////////////////////////////////////////////////////////////////////////////
// class EffectScheduleWork member methods
//////////////////////////////////////////////////////////////////////////////

EffectScheduleWork::EffectScheduleWork()
	
{
	__BEGIN_TRY

	m_Code = WORKCODE_MAX;

	__END_CATCH
}

EffectScheduleWork::~EffectScheduleWork()
	
{
	__BEGIN_TRY

	//SAFE_DELETE(m_pData);
	
	// �ڵ忡 ����, void* m_pData�� ĳ�����ؼ�, 
	// �˸°� ������� �Ѵ�.
	if (m_Code == WORKCODE_ADD_VAMPIRE_PORTAL)
	{
		Assert(m_pData == NULL);
	}
	else if (m_Code == WORKCODE_DELETE)
	{
		Assert(m_pData == NULL);
	}
	else
	{
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// class EffectSchedule member methods
//////////////////////////////////////////////////////////////////////////////

EffectSchedule::EffectSchedule()
	
{
	__BEGIN_TRY

	m_pEffect = NULL;

	__END_CATCH
}

EffectSchedule::~EffectSchedule()
	
{
	__BEGIN_TRY

	while (!m_WorkList.empty())
	{
		EffectScheduleWork* pWork = getFrontWork();
		SAFE_DELETE(pWork);
	}

	__END_CATCH
}

void EffectSchedule::addWork(int WorkCode, void* pData) 
	
{
	__BEGIN_TRY

	Assert(WorkCode < WORKCODE_MAX);

	EffectScheduleWork* pWork = new EffectScheduleWork();
	pWork->setCode(WorkCode);
	pWork->setData(pData);
	m_WorkList.push_back(pWork);

	__END_CATCH
}

EffectScheduleWork* EffectSchedule::getFrontWork(void) 
	
{
	__BEGIN_TRY

	if (!m_WorkList.empty())
	{
		EffectScheduleWork* pWork = m_WorkList.front();
		m_WorkList.pop_front();
		return pWork;
	}

	return NULL;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// class EffectScheduleManager member methods
//////////////////////////////////////////////////////////////////////////////

EffectScheduleManager::EffectScheduleManager()
	
{
	__BEGIN_TRY
	__END_CATCH
}

EffectScheduleManager::~EffectScheduleManager()
	
{
	__BEGIN_TRY

	while (!m_EffectScheduleList.empty())
	{
		EffectSchedule* pSchedule = m_EffectScheduleList.front();
		m_EffectScheduleList.pop_front();
		SAFE_DELETE(pSchedule);
	}

	__END_CATCH
}

void EffectScheduleManager::addEffectSchedule(EffectSchedule* pEffectSchedule) 
	
{
	__BEGIN_TRY

	Assert(pEffectSchedule != NULL);

	__ENTER_CRITICAL_SECTION(m_Mutex)

	m_EffectScheduleList.push_back(pEffectSchedule);

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

void EffectScheduleManager::heartbeat(void)
	
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// ��� �������� ó���� ������...
	while (!m_EffectScheduleList.empty())
	{
		EffectSchedule* pEffectSchedule = m_EffectScheduleList.front();
		Assert(pEffectSchedule != NULL);

		Effect* pEffect = pEffectSchedule->getEffect();

		// �۾� ����� �Ǵ� ����Ʈ�� ���� �����Ѵٸ�, �۾��� ����.
		if (pEffect != NULL)
		{
			// ��� ���� ó���� ������...
			while (true)
			{
				EffectScheduleWork* pWork = pEffectSchedule->getFrontWork();

				// ��� ���� ���´ٸ� �극��ũ
				if (pWork == NULL) break;

				int   WorkCode = pWork->getCode();
				//void* pData    = pWork->getData();

				// �� �۾� �ڵ忡 ���� ���� ó���Ѵ�.
				if (WorkCode == WORKCODE_ADD_VAMPIRE_PORTAL)
				{
					Assert(pEffect->getEffectClass() == Effect::EFFECT_CLASS_VAMPIRE_PORTAL);

					EffectVampirePortal* pEffectVampirePortal = dynamic_cast<EffectVampirePortal*>(pEffect);
					Assert(pEffectVampirePortal != NULL);

					// ���� ����Ʈ ���ο� �ִ� ��ǥ�� ���� ó���� ������ �ߴ� ��ǥ��.
					// �� Ÿ�Ͽ� ���� ����Ʈ�� �ְų� �ϴ� ������ ��ǥ�� ������ �� �ִ�.
					Zone* pZone = pEffectVampirePortal->getZone();
					ZoneCoord_t cx = pEffectVampirePortal->getX();
					ZoneCoord_t cy = pEffectVampirePortal->getY();
					ZONE_COORD ZoneCoord = pEffectVampirePortal->getZoneCoord();

					TPOINT pt = findSuitablePositionForEffect(pZone, cx, cy, Effect::EFFECT_CLASS_VAMPIRE_PORTAL);

					if (pt.x != -1)
					{
						// ��ǥ�� �����Ǿ��� ���� �𸣴�, ��ǥ�� �������ش�.
						pEffectVampirePortal->setX(pt.x);
						pEffectVampirePortal->setY(pt.y);

						// OID�� ��Ϲ޾ƾ� find����� �ϴ� �۾��� ������ �� �ִ�.
						ObjectRegistry& OR = pZone->getObjectRegistry();
						OR.registerObject(pEffectVampirePortal);

						// Ÿ�� �� �����̾� ��Ż �Ŵ����� ����Ѵ�.
						Tile& rTile = pZone->getTile(pt.x, pt.y);
						rTile.addEffect(pEffectVampirePortal);

						EffectManager* pVampirePortalManager = pZone->getVampirePortalManager();
						pVampirePortalManager->addEffect(pEffectVampirePortal);

						// Ÿ�Ͽ� ����Ʈ�� �پ�����, ��ε�ĳ������ ���ش�.
						GCAddVampirePortal gcAddVampirePortal;
						gcAddVampirePortal.setObjectID(pEffectVampirePortal->getObjectID());
						gcAddVampirePortal.setOwnerID(pEffectVampirePortal->getOwnerID());
						gcAddVampirePortal.setX(pt.x);
						gcAddVampirePortal.setY(pt.y);
						gcAddVampirePortal.setTargetZoneID(ZoneCoord.id);
						gcAddVampirePortal.setTargetX(ZoneCoord.x);
						gcAddVampirePortal.setTargetY(ZoneCoord.y);
						gcAddVampirePortal.setDuration(pEffectVampirePortal->getRemainDuration());
						gcAddVampirePortal.setCreateFlag(1);

						pZone->broadcastPacket(pt.x, pt.y, &gcAddVampirePortal);
					}
					else
					{
						SAFE_DELETE(pEffectVampirePortal);
					}
				}
				else if (WorkCode == WORKCODE_DELETE)
				{
					pEffect->setDeadline(0);
				}
				else
				{
					Assert(false);
				}
			}
		}

		m_EffectScheduleList.pop_front();
		SAFE_DELETE(pEffectSchedule);
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


