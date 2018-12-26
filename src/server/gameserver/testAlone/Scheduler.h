///////////////////////////////////////////////////////////////////
// �����ٸ��� �۾��� ���� Scheduler Ŭ����.
///////////////////////////////////////////////////////////////////

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <vector>
#include <queue>
#include <hash_map>
#include "Exception.h"
#include "Work.h"
#include "Schedule.h"

class Latter {
public :
	bool operator () ( const Schedule* pt1, const Schedule* pt2 ) const
	{
		return pt1->getScheduledTime() > pt2->getScheduledTime();
	}
};

class RecentSchedules : public priority_queue< Schedule*, vector< Schedule* >, Latter > {
public :
	typedef container_type::iterator 		iterator;
	typedef container_type::const_iterator 	const_iterator;

public :
	const container_type& 	getSchedules() const	{ return c; }
	void					arrange() 				{ make_heap(c.begin(), c.end(), comp); }
};

class Scheduler 
{
public:
	Scheduler() ;
	virtual ~Scheduler() ;

	void			clear();

	int 			getSize() const						{ return m_RecentSchedules.size(); }
	bool 			isEmpty() const						{ return m_RecentSchedules.empty(); }

public:
	void 			addSchedule( Schedule* pSchedule );

	virtual Work* 	heartbeat();

protected :
	Work* 			popRecentWork();

protected:
	RecentSchedules m_RecentSchedules;
};

#endif // __SCHEDULER_H__
