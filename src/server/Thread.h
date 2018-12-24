//////////////////////////////////////////////////////////////////////
//
// Thread.h
//
// by Reiot
//
//////////////////////////////////////////////////////////////////////
//
// POSIX Thread Class 
//
// ���� � ��ƾ�� ������� ��������, �ϴ� Thread Ŭ������ ���
// �޾� derived Ŭ������ ����, run() ����Լ��� �������� ��, 
// derived Ŭ������ ��ü�� �����ؼ� Start() �Լ��� �����ϸ� �ȴ�.
//
// ������� ������ ����.
//
// MDerivedThread * dt = new DerivedThread (...);
// dt->Start();
// delete dt;
//
// virtual destructor �� ���ǵ� ������, ������ ���� ��Ȳ���� �����
// �����ϰ� �ϱ� ���ؼ��̴�. ( ���� �������� ������ ���� Ŭ������
// destructor �� ȣ����� �ʴ´�. )
//
// Thread * t = new DerivedThread (...);
// t->Start();
// delete t;
//
// �� ������ ��ü�� �����ϴ� �Ͱ� �����带 �����Ű�� ���� �����ϴ�.
//
//////////////////////////////////////////////////////////////////////


#ifndef __THREAD_H__
#define __THREAD_H__


//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////

#include "Types.h"
#include "Exception.h"
#include "pthreadAPI.h"


//////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////
class ThreadAttr;
class ThreadException;


//////////////////////////////////////////////////////////////////////
//
// class Thread
//
// POSIX Thread Class
//
//////////////////////////////////////////////////////////////////////

class Thread {

//////////////////////////////////////////////////
// constants
//////////////////////////////////////////////////
public :
	
	enum ThreadStatus {
		READY ,		// run �� �غ� �Ǿ� �ִ� ����
		RUNNING ,	// ������ running ���� ����
		EXITING ,	// ���� ���� ���� (������ ó���� �ϰ� �ִ� ����)
		EXIT		// ������ ������ ���� 
	};
	

//////////////////////////////////////////////////
// constructor and destructor
//////////////////////////////////////////////////

public :

	// constructor
	Thread ( ThreadAttr * attr = NULL ) throw ();

	// destructor
	virtual ~Thread () throw ();


//////////////////////////////////////////////////
// public methods
//////////////////////////////////////////////////

public :

	// �����尡 ���ʷ� �����ϵ��� ���ִ� trigger �� ������ �ϴ� �Լ�. ������ 
	// ��ü�� ������ �Ŀ�, �� �Լ��� ȣ���ϸ� ���������� derived Ŭ������ 
	// run() ����Լ��� ȣ���ϰ� �ȴ�. 
	void start () throw ( ThreadException , Error );
	
	// �������� �����带 �ߴܽ�Ų��.
	// ���ο� ���ؽ��� ����ϴ� ���� ������ Ŭ���������� �����ϴ�.
	virtual void stop () throw ( Error );

	// �����尡 ������ ������ ��ٸ���. ���� �����尣�� ���ȴ�. ������ 
	// �����带 ���� �������� Ư�� �۾��� ��Ų �� �� ó���� �Ϸ�� ������
	// ������Ų �����带 ������ �������� ���ȴ�. ��Ƽ���μ��� ȯ��
	// ������ join �� ���� ������ �Ѵ�.
	// 
	// ������ ���� pthread_join() �� ���� �� �ڵ带 �����ϴ� �����尡 
	// �Ķ���ͷ� �������� �����带 ��ٸ��ٴ� ���̴�. ��, Ư�� �����尡
	// �Ǵٸ� Ư�� �����带 ��ٸ��� �� ���� ����.
	//
	// ex> Thread t;
	//     Thread::Join ( t );
	static void join ( const Thread & t ) throw ( ThreadException , Error );
	static void join ( const Thread * t ) throw ( ThreadException , Error );
	static void join ( const Thread & t , void * retval ) throw ( ThreadException , Error );
	static void join ( const Thread * t , void * retval ) throw ( ThreadException , Error );

	// �����带 Detached ���� �ٲ۴�.
	void detach () throw ( Error );

	// ���� ������� �����Ѵ�. �� Ư�� �����带 �����Ų�ٴ� ���� �ƴ϶�,
	// �� �޽�带 �����ϴ� �����带 �����Ų�ٴ� ���̴�. �̶�, Ư��
	// ��ü�� �Ķ���ͷ� �Ѱ������ν� JOIN �ϴ� �����尡 �� ���� �޾Ƴ�
	// ���� �ִ�.
	//
	// ex> Thread::Exit();
	//     or
	//     Thread::Exit(retval);
	static void exit ( void * retval = NULL ) throw ();

	// �����忡�� ���������� ����Ǵ� �ڵ尡 ���� �κ��̴�. Thread 
	// Ŭ������ ��ӹ��� ���� Ŭ������ �׻� �� �Լ��� ����������� �Ѵ�.
	virtual void run () throw () {};


//////////////////////////////////////////////////
// 
//////////////////////////////////////////////////
public :

	// get current thread's tid
	static TID self () throw ();

	// �������̴�. �����忡 ���� ������ string �� ���·� ��ȯ�Ѵ�.
	virtual string toString () const throw ();

	// get thread identifier
	TID getTID () const throw () { return m_TID; }
	
	// get/set thread's status
	ThreadStatus getStatus () const throw () { return m_Status; }
	void setStatus ( ThreadStatus status ) throw () { m_Status = status; }
	
	// get thread name
	virtual string getName () const throw () { return "Thread"; }
	

//////////////////////////////////////////////////
// data members
//////////////////////////////////////////////////

private :

	// thread identifier variable
	TID m_TID;
	
	// thread-attribute object
	ThreadAttr * m_ThreadAttr;
	
	// thread status
	ThreadStatus m_Status;

};


//////////////////////////////////////////////////
// thread function used at pthread_create()
//////////////////////////////////////////////////
void * start_routine ( void * derivedThread ) throw ();

#endif
