//////////////////////////////////////////////////////////////////////
// 
// ThreadPool.h 
// 
// by Reiot
// 
//////////////////////////////////////////////////////////////////////

#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////
#include <list>
#include "Types.h"
#include "Exception.h"
#include "Thread.h"
#include "Mutex.h"


//////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
//
// class ThreadPool
//
// ������ ��ü���� �÷��� Ŭ�����̴�. ���� ����� Ȱ������ ��� ���������
// �ߴܽ�ų ��, ������Ǯ ��ü�� Stop�޽�带 ����ϸ� �ȴ�. ����������
// �ñ׳��̳� ĵ�����̼��� ���� �����̴�. �׷���, ������ �ڷᰡ ���
// ������ ���ϰ� �ִ�. ^^;
//
//////////////////////////////////////////////////////////////////////

class ThreadPool {

//////////////////////////////////////////////////
// constructor/destructor
//////////////////////////////////////////////////
public:
	
	// constructor
	ThreadPool() ;
	
	// destructor
	// �����ϰ� �ִ� ��� ������ ��ü�� �����ؾ� �Ѵ�.
	virtual ~ThreadPool() ;

	
//////////////////////////////////////////////////
// methods
//////////////////////////////////////////////////
public:
	
	// ������Ǯ�ȿ� ��ϵ� ��������� RUNNING ���·� �����. 
	void start();
	
	// ������Ǯ�ȿ� ��ϵ� ��� �������� ������ �ߴܽ�Ų��.
	//(�̴� singal Ȥ�� cancellation ���� �����ؾ� �ϰڴ�.)
	void stop();
	
	// ������Ǯ�� ������ ��ü�� ����Ѵ�.
	void addThread(Thread* thread);
	
	// ������Ǯ���� Ư�� ������ ��ü�� �����Ѵ�.
	void deleteThread(TID tid) throw(NoSuchElementException, Error);
	
	// ������Ǯ���� Ư�� ������ ��ü�� ã�Ƽ� �����Ѵ�.
	Thread* getThread(TID tid) throw(NoSuchElementException, Error);

//#ifdef __NO_COMBAT__
	list<Thread*> getThreads(){ return m_Threads; } // ��漮
//#endif

//////////////////////////////////////////////////
// attributes
//////////////////////////////////////////////////
private:
	
	//
	// ������ ��ü�� �����Ϳ� ���� ����Ʈ
	// �����δ� ������ Ŭ������ ���� Ŭ������ ���� �ȴ�.
	// �Ϲ������� ���� ������ ��������� ��ϵȴ�.
	//
	// ex> PlayerThreadPool - PlayerThread
	//     NPCThreadPool    - NPCThread
	//     MobThreadPool    - MobThread
	//
	list<Thread*> m_Threads;

	// mutex for list operation(add, delete, get ...)	
	mutable Mutex m_Mutex;
};

#endif
