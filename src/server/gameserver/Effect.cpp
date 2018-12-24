//////////////////////////////////////////////////////////////////////////////
// Filename    : Effect.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
Effect::Effect () 
	throw ()
{
	__BEGIN_TRY

	m_pZone   = NULL;
	m_X       = 0;
	m_Y       = 0;
	m_pTarget = NULL;
	m_bBroadcastingEffect = true;

	setNextTime(99999999);
	setDeadline(99999999);
	setCustormEffect(0);
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
Effect::Effect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget , Turn_t delay) 
	throw ()
{
	__BEGIN_TRY

	m_pZone   = pZone;
	m_X       = x;
	m_Y       = y;
	m_pTarget = pTarget;

	setNextTime(99999999);
	setDeadline(delay);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
Effect::~Effect () 
	throw ()	
{
}

void Effect::setNextTime(Turn_t delay) 
	throw ()
{
	__BEGIN_TRY

	// ���� �ð��� �����Ѵ�.
	getCurrentTime(m_NextTime);
	
	// �̶�, delay �� 0.1 �ʰ� 1 �̴�.
	m_NextTime.tv_sec += delay / 10;
	m_NextTime.tv_usec += (delay % 10)* 100000;

	__END_CATCH
}

void Effect::setDeadline (Turn_t delay) throw ()
{
	__BEGIN_TRY

	// ���� �ð��� �����Ѵ�.
	getCurrentTime(m_Deadline);
	
	// ��������� �����Ѵ�. 
	// �̶�, delay �� 0.1 �ʰ� 1 �̴�.
	m_Deadline.tv_sec += delay / 10;
	m_Deadline.tv_usec += (delay % 10)* 100000;

	__END_CATCH
}

void Effect::setCustormEffect(int Effect) throw ()
{
	__BEGIN_TRY

	// ���� �ð��� �����Ѵ�.
		m_CustormEffect = Effect;
	__END_CATCH
}

// ���� duration(1/10�� ����)
Duration_t Effect::getRemainDuration() throw()
{
	__BEGIN_TRY

	Timeval currentTime;
	getCurrentTime(currentTime);
	return (m_Deadline.tv_sec  - currentTime.tv_sec)* 10 + 
	       (m_Deadline.tv_usec - currentTime.tv_usec) / 100000;

	__END_CATCH
}

