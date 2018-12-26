//////////////////////////////////////////////////////////////////////
// 
// ThreadPool.cpp 
// 
// by Reiot
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////
#include <algorithm>
#include "ThreadPool.h"
#include "Assert.h"
#include "Thread.h"
#include "LogClient.h"

//////////////////////////////////////////////////
// function object for find_if ()
//////////////////////////////////////////////////

//
// �����̳ʼ��� ������ ��ü�� Ư�� TID�� ���� ���� ��� true�� �����Ѵ�.
//
class isSameTID {
public :

	// constructor
	isSameTID (TID tid) : m_TID(tid) {}

	//
	bool operator () (Thread* pThread) throw ()
	{
		return pThread->getTID() == m_TID;
	}

private :
	
	// thread identifier
	TID m_TID;

};

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
ThreadPool::ThreadPool () 
	throw ()
{
	__BEGIN_TRY

	m_Mutex.setName("ThreadPool");
		
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
// �����ϰ� �ִ� ��� ������ ��ü�� �����ؾ� �Ѵ�.
//////////////////////////////////////////////////////////////////////
ThreadPool::~ThreadPool () 
	throw ()
{
	__BEGIN_TRY
		
	//////////////////////////////////////////////////
	// enter critical section
	//////////////////////////////////////////////////
	m_Mutex.lock();
		
	/*
	list<Thread*>::iterator itr = m_Threads.begin();
	for (; itr != m_Threads.end() ; itr ++) 
	{
		Thread* temp = *itr;
		
		// ������� ������ ���¿��� �Ѵ�.
		Assert(temp != NULL && temp->getStatus() == Thread::EXIT);
		
		SAFE_DELETE(temp);
	}

	m_Threads.erase(m_Threads.begin() , m_Threads.end());
	
	g_pLogManager->Log5("after erase(begin , end) , list's size == %d\n" , m_Threads.size());
	
	*/
	
	list<Thread*>::iterator itr;
	
	while ((itr = m_Threads.begin()) != m_Threads.end()) 
	{
		// ������ ����Ʈ�� ��尡 �����ִٴ� ���̴�.
		
		// ������� ������ ���¿��� �Ѵ�.
		Assert(*itr != NULL && (*itr)->getStatus() == Thread::EXIT);
		
		SAFE_DELETE(*itr);
		
		m_Threads.pop_front();
	}

	//////////////////////////////////////////////////
	// leave critical section
	//////////////////////////////////////////////////
	m_Mutex.unlock();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// ������Ǯ�ȿ� ��ϵ� ��������� RUNNING ���·� �����. 
//////////////////////////////////////////////////////////////////////
void ThreadPool::start () 
	
{
	__BEGIN_TRY
		
	log(LOG_DEBUG_MSG, "", "", "== ThreadPool has started ==");

	//////////////////////////////////////////////////
	// enter critical section
	//////////////////////////////////////////////////
	m_Mutex.lock();
		
	for (list<Thread*>::iterator itr = m_Threads.begin() ;
		  itr != m_Threads.end() ;
		  itr ++) {
		// start threads
		Assert(*itr != NULL);
		(*itr)->start();

		string msg = "== " + (*itr)->getName() + " has been started == ";
		log(LOG_DEBUG_MSG, "", "", msg);
	}

	//////////////////////////////////////////////////
	// leave critical section
	//////////////////////////////////////////////////
	m_Mutex.unlock();

	__END_CATCH
}
	

//////////////////////////////////////////////////////////////////////
// ������Ǯ�ȿ� ��ϵ� ��� �������� ������ �ߴܽ�Ų��.
// (�̴� singal Ȥ�� cancellation ���� �����ؾ� �ϰڴ�.)
//////////////////////////////////////////////////////////////////////
void ThreadPool::stop () 
	
{
	__BEGIN_TRY
		
	throw UnsupportedError("do not use this method now...");

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// ������Ǯ�� ������ ��ü�� ����Ѵ�.
//////////////////////////////////////////////////////////////////////
void ThreadPool::addThread (Thread* thread) 
	
{
	__BEGIN_TRY
		
	//////////////////////////////////////////////////
	// enter critical section
	//////////////////////////////////////////////////
	m_Mutex.lock();

	// ������� ���� �ƴϾ�� �Ѵ�.
	Assert(thread != NULL);

	// ����Ʈ�� �� �������� ������ ��ü�� �����Ѵ�.
	m_Threads.push_back(thread);
	
	string msg = "== " + thread->getName() + " added to thread pool";
	log(LOG_DEBUG_MSG, "", "", msg);

	//////////////////////////////////////////////////
	// leave critical section
	//////////////////////////////////////////////////
	m_Mutex.unlock();

	__END_CATCH
}
	

//////////////////////////////////////////////////////////////////////
// ������Ǯ���� Ư�� ������ ��ü�� �����Ѵ�.
//////////////////////////////////////////////////////////////////////
void ThreadPool::deleteThread (TID tid) 
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY
	
	//////////////////////////////////////////////////
	// enter critical section
	//////////////////////////////////////////////////
	m_Mutex.lock();

	// function object�� Ư�� TID�� ���� ������ ��ü�� ��� ��带 ����
	// iterator�� ã�Ƴ���.
	list<Thread*>::iterator itr = find_if (m_Threads.begin() , m_Threads.end() , isSameTID(tid));
	
	if (itr != m_Threads.end()) // found!
	{ 
		// ������ ��ü�� �ӽ÷� �����صд�.
		Thread* temp = *itr;
		
		// ������� ������ ���¿��� �Ѵ�.
		// ���� Ŭ������ Mutex�� ������ ���, getStatus(), setStatus()�� Mutex�� ��ȣ�Ǿ�� �Ѵ�.
		Assert(temp != NULL && temp->getStatus() == Thread::EXIT);
		
		StringStream msg;
		msg << "== Thread[" << temp->getTID()
			<< "] has been removed from ThreadPool ==";
		log(LOG_DEBUG_MSG, "", "", msg.toString());

		// ������ ��ü�� �����Ѵ�.
		SAFE_DELETE(temp);
		
		// ��带 �����Ѵ�.
		m_Threads.erase(itr);
	} 
	else // not found
	{						
		StringStream buf;
		buf << "TID(" << tid << ")" ;

		//////////////////////////////////////////////////
		// leave critical section
		//////////////////////////////////////////////////
		m_Mutex.unlock();

		throw NoSuchElementException(buf.toString());
	}
	
	//////////////////////////////////////////////////
	// leave critical section
	//////////////////////////////////////////////////
	m_Mutex.unlock();

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// ������Ǯ���� Ư�� ������ ��ü�� ã�Ƽ� �����Ѵ�.
//////////////////////////////////////////////////////////////////////
Thread* ThreadPool::getThread (TID tid) 
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY
		
	Thread* thread = NULL;
	
	//////////////////////////////////////////////////
	// enter critical section
	//////////////////////////////////////////////////
	m_Mutex.lock();
		
	list<Thread*>::iterator itr = find_if (m_Threads.begin() , m_Threads.end() , isSameTID(tid));
	
	if (itr != m_Threads.end()) {	// found
		
		Assert(*itr != NULL);
		
		thread = *itr;

	} else {						// not found

		StringStream buf;
		buf << "TID(" << tid << ")" ;

		//////////////////////////////////////////////////
		// leave critical section
		//////////////////////////////////////////////////
		m_Mutex.unlock();

		throw NoSuchElementException(buf.toString());

	}

	//////////////////////////////////////////////////
	// leave critical section
	//////////////////////////////////////////////////
	m_Mutex.unlock();
	
	return thread;

	__END_CATCH
}
