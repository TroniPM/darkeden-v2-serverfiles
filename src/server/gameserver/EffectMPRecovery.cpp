//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectMPRecovery.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Assert.h"
#include "EffectMPRecovery.h"
#include "Gpackets/GCMPRecoveryEnd.h"
#include "Zone.h"
#include "Slayer.h"
#include "Ousters.h"
#include "Creature.h"
#include "Player.h"

EffectMPRecovery::EffectMPRecovery () 
	
{
	__BEGIN_TRY

	// ���� ���� Effect�̴�. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}

EffectMPRecovery::EffectMPRecovery (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Creature* pCreature , Turn_t delay) 
	
: Effect(pZone,x,y,pCreature,delay) 
{
	__BEGIN_TRY

	Assert(getZone() != NULL);
	Assert(getTarget() != NULL);

	// ���� ���� Effect�̴�. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}

EffectMPRecovery::~EffectMPRecovery () 
	
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectMPRecovery::affect()
	
{
	__BEGIN_TRY

	// Delay�� ���� ü�� ȸ��.
	setNextTime(m_Delay);

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);

	affect(pCreature);

	__END_CATCH
}

void EffectMPRecovery::affect(Creature* pCreature)
	
{
	__BEGIN_TRY

	if ( pCreature->isFlag( Effect::EFFECT_CLASS_PLEASURE_EXPLOSION ) )
	{
		cout << "Pleasure Explosion ���� �� ����." << endl;
		return;
	}

	Timeval CurrentTime;

	getCurrentTime(CurrentTime);

	if ( pCreature->isSlayer() )
	{
		Turn_t timegapSec =  m_Deadline.tv_sec - CurrentTime.tv_sec;
		Turn_t timegapUSec = m_Deadline.tv_usec - CurrentTime.tv_usec;

		Turn_t timegap = timegapSec* 1000000 + timegapUSec;

		int RecoveryPeriod = (timegap / (m_Delay* 100000));

		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

		if (pSlayer->getMP(ATTR_CURRENT) != pSlayer->getMP(ATTR_MAX) && m_Period != 0) 
		{
			// �÷��� �ɱ�
			pSlayer->setFlag(Effect::EFFECT_CLASS_MP_RECOVERY);

			// �� �Ͽ� �󸶳� ȸ�� ��ų ���ΰ�.
			MP_t CurrentMP = pSlayer->getMP(ATTR_CURRENT);
			MP_t NewMP     = min((int)(pSlayer->getMP(ATTR_MAX)), (int)(CurrentMP + m_MPQuantity* (m_Period - RecoveryPeriod)));

			pSlayer->setMP(NewMP, ATTR_CURRENT);
		} 
		else 
		{
			setDeadline(0);
		}

		m_Period = RecoveryPeriod;
	}
	else if ( pCreature->isOusters() )
	{
		Turn_t timegapSec =  m_Deadline.tv_sec - CurrentTime.tv_sec;
		Turn_t timegapUSec = m_Deadline.tv_usec - CurrentTime.tv_usec;

		Turn_t timegap = timegapSec* 1000000 + timegapUSec;

		int RecoveryPeriod = (timegap / (m_Delay* 100000));

		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

		if (pOusters->getMP(ATTR_CURRENT) <= pOusters->getMP(ATTR_MAX) && m_Period != 0) 
		{
			// �÷��� �ɱ�
			pOusters->setFlag(Effect::EFFECT_CLASS_MP_RECOVERY);

			// �� �Ͽ� �󸶳� ȸ�� ��ų ���ΰ�.
			MP_t CurrentMP = pOusters->getMP(ATTR_CURRENT);
			MP_t NewMP     = min((int)(pOusters->getMP(ATTR_MAX)), (int)(CurrentMP + m_MPQuantity* (m_Period - RecoveryPeriod)));

			pOusters->setMP(NewMP, ATTR_CURRENT);
		} 
		else 
		{
			setDeadline(0);
		}

		m_Period = RecoveryPeriod;
	}

	__END_CATCH
}

void EffectMPRecovery::affect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

	throw UnsupportedError(__PRETTY_FUNCTION__);
	
	__END_CATCH
}

void EffectMPRecovery::unaffect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);

	unaffect(pCreature);

	__END_CATCH
}

void EffectMPRecovery::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	
	if ( pCreature->isSlayer() )
	{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

		if (m_Period != 0)
		{
			MP_t CurrentMP = pSlayer->getMP(ATTR_CURRENT);
			MP_t NewMP     = min((int)(pSlayer->getMP(ATTR_MAX)), (int)(CurrentMP + m_MPQuantity* m_Period));

			pSlayer->setMP(NewMP, ATTR_CURRENT);
		}

		// ���� MP�� ��ε�ĳ�����Ѵ�.
		// ���� ȸ���� �������� ���� �˸����� �Ѵ�.
		// �ڽſ��� ����
		GCMPRecoveryEnd gcEffectMPRecoveryEnd;
		gcEffectMPRecoveryEnd.setCurrentMP(pSlayer->getMP(ATTR_CURRENT));
		pSlayer->getPlayer()->sendPacket(&gcEffectMPRecoveryEnd);

		pSlayer->removeFlag(Effect::EFFECT_CLASS_MP_RECOVERY);
	}
	else if ( pCreature->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

		if (pOusters->getMP(ATTR_CURRENT) <= pOusters->getMP(ATTR_MAX) && m_Period != 0)
		{
			MP_t CurrentMP = pOusters->getMP(ATTR_CURRENT);
			MP_t NewMP     = min((int)(pOusters->getMP(ATTR_MAX)), (int)(CurrentMP + m_MPQuantity* m_Period));

			pOusters->setMP(NewMP, ATTR_CURRENT);
		}

		// ���� MP�� ��ε�ĳ�����Ѵ�.
		// ���� ȸ���� �������� ���� �˸����� �Ѵ�.
		// �ڽſ��� ����
		GCMPRecoveryEnd gcEffectMPRecoveryEnd;
		gcEffectMPRecoveryEnd.setCurrentMP(pOusters->getMP(ATTR_CURRENT));
		pOusters->getPlayer()->sendPacket(&gcEffectMPRecoveryEnd);

		pOusters->removeFlag(Effect::EFFECT_CLASS_MP_RECOVERY);
	}

	__END_CATCH
}

void EffectMPRecovery::unaffect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

	__END_CATCH
}

string EffectMPRecovery::toString () const 
	throw ()
{
	StringStream msg;

	if (m_pZone) 
	{
		msg << "EffectMPRecovery("
				<< "ZoneID:" << (int)m_pZone->getZoneID()
				<< ",X:"     << (int)getX()
				<< ",Y:"     << (int)getY();
	}

	if (m_pTarget)
	{
		msg << ",Target:" << m_pTarget->toString();
	}
	else
	{
		msg << ",Target:NULL";
	}

	msg << ",Deadline:" << (int)m_Deadline.tv_sec 
			<< "." << (int)m_Deadline.tv_usec
			<< ")";

	return msg.toString();
}
