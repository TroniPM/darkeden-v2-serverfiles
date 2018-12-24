///////////////////////////////////////////////////////////////////
// �����ٸ��� �۾��� ���� Scheduler Ŭ���� ����
///////////////////////////////////////////////////////////////////

#include "Scheduler.h"
#include "Assert.h"

Scheduler::Scheduler()
	throw()
{
}
Scheduler::~Scheduler()
	throw()
{
	clear();
}

void Scheduler::clear()
	throw (Error)
{
	__BEGIN_TRY

	while ( !m_RecentSchedules.empty() )
	{
		Schedule* pSchedule = m_RecentSchedules.top();
		m_RecentSchedules.pop();

		SAFE_DELETE(pSchedule);
	}

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
// addSchedule( Schedule* )
//
//--------------------------------------------------------------------------------
// Schedule�� RecentSchedules�� Schedules�� ���ÿ� ��ϵǾ� �ִ�.
//--------------------------------------------------------------------------------
void Scheduler::addSchedule( Schedule* pSchedule )  
	throw (Error)
{ 
	__BEGIN_TRY

	m_RecentSchedules.push( pSchedule ); 
	pSchedule->m_pScheduler = this;

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
// popRecentWork( Schedule* pSchedule )
//
//--------------------------------------------------------------------------------
// m_RecentSchedules, m_Schedules���� ����
// pRecentSchedule�� Work�� return�ϰ� pRecentSchedule�� �����
//--------------------------------------------------------------------------------
Work* Scheduler::popRecentWork()
	throw (Error)
{
	__BEGIN_TRY

	Schedule* pRecentSchedule = m_RecentSchedules.top();

	m_RecentSchedules.pop();

	Work* pWork = pRecentSchedule->popWork();
	SAFE_DELETE( pRecentSchedule );

	return pWork;

	__END_CATCH	
}

//--------------------------------------------------------------------------------
//
// Work* heartbeat()
//
//--------------------------------------------------------------------------------
// ���� �ٷ�?�� ����� �� �ִ� Schedule�� üũ�غ��� ����ƴٸ�,
// Schedule�� Work�� return�Ѵ�. �� ��, Schedule�� �����.
//--------------------------------------------------------------------------------
Work* Scheduler::heartbeat()
	throw (Error)
{
	__BEGIN_TRY

	if( m_RecentSchedules.empty() ) return NULL;
	
	// priority queue �� top()�� ���� ���� (���� Former �� ���ؼ�) ���Ҹ� �����Ѵ�.
	// ��Ÿ���Ե� ������ ���� ���� �� ������ ������ ������ �𸣰ڴ�. -.-;;;
	// 2003. 1.23. by Sequoia
	// Former Ŭ������ Latter Ŭ������ �ٲ㼭 ������ ���� ���� �� ���´�.
	Schedule* pRecentSchedule = m_RecentSchedules.top();

	if( pRecentSchedule->heartbeat() ) 
	{
		return popRecentWork();
	}

	return NULL;

	__END_CATCH
}

