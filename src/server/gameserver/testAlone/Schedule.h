///////////////////////////////////////////////////////////////////
// �����ٸ��� �۾��� ���� Schedule Ŭ����
///////////////////////////////////////////////////////////////////

#ifndef __SCHEDULE_H__
#define __SCHEDULE_H__

#include "Types.h"
#include "VSDateTime.h"

class Work;
class Scheduler;

class Schedule 
{
public:
	enum ScheduleType {
		SCHEDULE_TYPE_ONCE,			// 0
		SCHEDULE_TYPE_PERIODIC,		// 1
	};

public:
	Schedule( Work* pWork, const VSDateTime& Time, ScheduleType type = SCHEDULE_TYPE_ONCE ) throw();
	virtual ~Schedule() throw();

public:
	virtual bool 		heartbeat();

	const VSDateTime& 	getScheduledTime() const 	{ return m_ScheduledTime; }
	ScheduleType 		getType() const 			{ return m_ScheduleType; }

	Work* 				getWork()					{ return m_pWork; }
	const Work* 		getWork() const		{ return m_pWork; }
	Work* 				popWork();

	void				setScheduledTime(const VSDateTime& dt) { m_ScheduledTime = dt; }

	friend class Scheduler;

public:
	virtual string		toString() ;

protected:
	ScheduleType 	m_ScheduleType;
	Work* 			m_pWork;
	VSDateTime 		m_ScheduledTime;
//	VSDateTime		m_LimitCheckDateTime;
//	VSTime			m_LimitCheckTime;
//	int				m_WrongCount;

	Scheduler*		m_pScheduler;
};

#endif // __SCHEDULE_H__
