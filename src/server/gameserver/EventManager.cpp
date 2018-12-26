//////////////////////////////////////////////////////////////////////////////
// Filename    : EventManager.cpp
// Written by  : Reiot
//////////////////////////////////////////////////////////////////////////////

#include "EventManager.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
EventManager::EventManager () 
    
{
	__BEGIN_TRY

	Assert(m_Events.empty());

	__END_CATCH
}
	
//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
EventManager::~EventManager () 
    throw ()
{
	__BEGIN_TRY
		
	while (!m_Events.empty()) 
	{
		SAFE_DELETE(m_Events.front());
		m_Events.pop_front();
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// add effect and affect it to its target
// priority_queue�� ����ϰ�, affect�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void EventManager::addEvent (Event* pEvent) 
     throw ()
{
	__BEGIN_TRY
	__END_DEBUG

	Assert(pEvent != NULL);
	
	Event* pPrevEvent = getEvent(pEvent->getEventClass());

	if (pPrevEvent == NULL)
	{
		// push to priority queue
		m_Events.push_back(pEvent);
	}
	else 
	{
		//cerr << "EventManager::addEvent() : Duplicated event class" << endl;
		throw ("EventManager::addEvent() : Duplicated event class");
	}

	__BEGIN_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
Event* EventManager::getEvent(Event::EventClass EClass) 
	throw()
{
	__BEGIN_TRY

	list<Event*>::iterator itr = m_Events.begin();

	for (; itr != m_Events.end(); itr++)
	{
		Event* pEvent = *itr;
		if (pEvent->getEventClass() == EClass) return pEvent;
	}

	return NULL;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EventManager::deleteEvent (Event::EventClass EClass) 
     throw ()
{
	__BEGIN_TRY

	list<Event*>::iterator current = m_Events.begin();

	while (current != m_Events.end()) 
	{
		Assert(*current != NULL);
		Event* pEvent = *current;

		if (pEvent->getEventClass() == EClass) 
		{
			m_Events.erase(current);
			SAFE_DELETE(pEvent);
			break;
		}

		current++;
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EventManager::heartbeat () 
     
{
	__BEGIN_TRY
		
	// ���� �ð��� �����Ѵ�.
	Timeval currentTime;
	getCurrentTime(currentTime);

	list<Event*>::iterator before  = m_Events.end();
	list<Event*>::iterator current = m_Events.begin();

	while (current != m_Events.end()) 
	{
		Assert(*current != NULL);

		Event* pEvent = *current;
		
		//--------------------------------------------------------------------------------
		// *WARNING*
		//
		// EventResurrect Event �� ���, GamePlayer ��ü�� ZPM ���� IPM ���� 
		// �Ҽ��� �ٲ�� �ȴ�.  ������ ZPM �� IPM �� ���� �ٸ� �������̱� 
		// ������, IPM ���� �Ǵٽ� EventResurrect �� activate �� ���ɼ��� �ִٴ�
		// ���̴�. (������ GamePlayer ��ü���� EventResurrect �� ������ ��������
		// ���� ���¿��� IPM ���� �Ű����� �����̴�.) ����, �̷� ������
		// ���ϱ� ���ؼ��� ��ȸ�� �̺�Ʈ�� ���, �켱 �̺�Ʈ�� 
		// �̺�Ʈ�Ŵ������� �����ϰ� ���� IPM ���� �ű���� �ؾ� �Ѵ�. 
		// �̶�, �������� �̺�Ʈ�� ��� PM ���̸� �Ű� �ٴϴ� ���� ������
		// �ؾ� �� ���̴�!!!! - ���� �浵�� ���� -
		//--------------------------------------------------------------------------------
		if (currentTime > pEvent->getDeadline())
		{
			// ��ȸ�� �̺�Ʈ�� ���
			if (pEvent->isTemporary())
			{
				// �̺�Ʈ�� �����Ѵ�.
				m_Events.erase(current);

				if (before == m_Events.end()) { // first effect
					current = m_Events.begin();
				} else { // !first effect
					current = before;
					current ++;
				}
			}

			// �̺�Ʈ�� �����Ѵ�.
			pEvent->activate();

			// ��ȸ�� �̺�Ʈ�� ���
			if (pEvent->isTemporary())
			{
				// �̺�Ʈ ��ü�� �����Ѵ�.
				SAFE_DELETE(pEvent);
			}
		} 
		else 
		{
			before = current ++;
		}
	}

	__END_CATCH
}
