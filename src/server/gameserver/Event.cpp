//////////////////////////////////////////////////////////////////////////////
// Filename    : Event.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Event.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
// class Event member methods
//////////////////////////////////////////////////////////////////////////////

Event::Event(GamePlayer* pGamePlayer)
	
{
	__BEGIN_TRY

	m_pGamePlayer = pGamePlayer;

	// EventReloadInfo������ assert�����ߴ�. NULL�� �� �ֱ� ������
	// ��� EventReloadInfo�� Event�� ���� ������ ��������(GamePlayer�� ������� -_-;)
	// ���� �ð���.. EventManager�� �� �� �ۿ� �����.. -_-
	// by sigi. 2002.9.26
//	Assert(m_pGamePlayer != NULL);

	m_Deadline.tv_sec  = 0;
	m_Deadline.tv_usec = 0;

	__END_CATCH
}

Event::~Event()
	
{
	__BEGIN_TRY
	__END_CATCH
}

void Event::setDeadline(Turn_t delay)
	
{
	__BEGIN_TRY

	// ���� �ð��� �����Ѵ�.
	getCurrentTime(m_Deadline);

	// ��������� �����Ѵ�. 
	// �̶�, delay �� 0.1 �ʰ� 1 �̴�.
	m_Deadline.tv_sec += delay / 10;
	m_Deadline.tv_usec +=(delay % 10)* 100000;

	__END_CATCH
}


