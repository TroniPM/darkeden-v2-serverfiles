////////////////////////////////////////////////////////////////////////////////
//
// Thread.cpp
//
// by Reiot, the Lord of MUDMANIA(TM)
//
// Last Updated : 1999. 07. 02.
//
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////
#include "Thread.h"
#include "ThreadAttr.h"
#include "pthreadAPI.h"

using namespace pthreadAPI;


////////////////////////////////////////////////////////////////////////////////
//
// constructor
//
////////////////////////////////////////////////////////////////////////////////
//
// Thread Ŭ������ ��ӹ��� DerivedThread �� �ּ��� ThreadAttr �� �����ϰ� �ȴ�. 
// ���� DerivedThread �� ���� �� ���� �ʿ䰡 �ִٸ�, �� �޽�� ������ ������ 
// ThreadAttr �� ������ �Ŀ�, �̸� ���� �������� �����ڿ� �Ѱ��ְ� ��� ���� 
// �����带 ������ �Ŀ�, Thread-Attribute ��ü�� �����ϸ� �� ���̴�.
//
// ������ ����, ��ü ������ ���� �������� ������ ���ÿ� �̷������ �ʴ´ٴ�
// ���̴�. �� ��� �������� Start() �� ������ �Ŀ� ThreadAttr ��ü�� �����ؾ�
// �Ѵ�. �׷��� ������ ������ �� ���̴�.
//
// ���� ��� ������� new �� �����ؾ� �Ѵ�. ���� pthread_create() �� ������ 
// �Ķ���ͷ� ������ ��ü�� �ּҸ� �Ѱ��ְ� �Ǵµ�, �̶� �Լ� ���ÿ� ������ 
// ��ü�� ������ ��� Scope Rule�� ���� ������ ���� �ȴ�. ������ ������ ��ü�� 
// ��(Heap)�� �����ؾ߸� �Ѵ�!!!
//
////////////////////////////////////////////////////////////////////////////////
Thread::Thread ( ThreadAttr * attr ) 
	 
: m_TID(0) , m_ThreadAttr(attr), m_Status(Thread::READY)
{
}


////////////////////////////////////////////////////////////////////////////////
//
// destructor (virtual)
//
////////////////////////////////////////////////////////////////////////////////
//
// DerivedThread Ŭ�������� �߰��� attribute �� ������� �ϱ� ���ؼ� virtual ��
// ���ǵǾ� �ִ�. �����δ� �ƹ��� �ϵ� ���� �ʴ´�.
//
////////////////////////////////////////////////////////////////////////////////
Thread::~Thread () 
	 
{
}


////////////////////////////////////////////////////////////////////////////////
//
// �����带 �����Ѵ�.
//
////////////////////////////////////////////////////////////////////////////////
//
// pthread_create() �� ���ؼ� ���캸���� ����.
//
// int pthread_create ( pthread_t * tid , 
//                      pthread_attr_t * atttr , 
//                      void * (*start_routine)(void*) , 
//                      void * arg 
//                    );
//
// ������ �����ϸ� 0 �� �����ϸ�, ������ ��� ���� �ڵ带 �����Ѵ�.
// ���� �ڵ�� EAGAIN �� �����ϸ�, �ý��� ���ҽ��� �����ϰų� ������ ���ڰ�
// �ʹ� ������ �ǹ��Ѵ�.
//
// tid �� �����͸� ù��° �Ķ���ͷ� �ָ�, �� �ȿ� thread identifier �� ����ȴ�.
//
// attr �� NULL �� ��� Default Attribute �� ���� �����尡 �����ȴ�. Ư����
// � �Ӽ��� �����Ϸ��� ������ pthread_attr_t �� �����ϸ� �� ���̴�.
//
// start_routine ���δ� Thread Ŭ������ friend method �� ����ϴµ�, �̶� arg ��
// this - Thread Object - �� �����ϰ� �ȴ�. �׷���, start_routine �ȿ����� 
// polymorphism �� ����ؼ� ���� Ŭ������ run() �޽�带 �ڵ����� ȣ���ϰ� 
// �ǹǷ�.. ��� ���� ����������. -_-;
//
////////////////////////////////////////////////////////////////////////////////
void Thread::start () 
     throw ( ThreadException , Error )
{ 
	__BEGIN_TRY
		
	if ( m_Status != Thread::READY )
		throw ThreadException("invalid thread's status");

	pthread_create_ex( &m_TID, ( m_ThreadAttr == NULL ? NULL : m_ThreadAttr->getAttr() ) , start_routine , this );
	
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
//
// ���� Ŭ�������� ���ؽ��� �����ϸ鼭 �������ؾ� �Ѵ�.
//
////////////////////////////////////////////////////////////////////////////////
void Thread::stop ()
	 
{
	__BEGIN_TRY
		
	throw UnsupportedError();
		
	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//
// Ư�� �����尡 ������ ������ ���� �����带 �����.
//
// ���⼭ *����* �������µ� �����϶�. ������ A �� ������ B �� ��ٸ��� ����
// �ƴϹǷ�, �� �޽��� static �̾�� �Ѵ�. 
//
// �̶� status �� � ����Ÿ������ �����ϴ�. (structure, class...)
//
////////////////////////////////////////////////////////////////////////////////
void Thread::join ( const Thread & t )
     throw ( ThreadException , Error )
{ 
	__BEGIN_TRY

	pthread_join_ex ( t.getTID() , NULL );
	
	__END_CATCH
}

void Thread::join ( const Thread & t, void * status )
     throw ( ThreadException , Error )
{ 
	__BEGIN_TRY

	pthread_join_ex ( t.getTID() , &status );
	
	__END_CATCH
}

void Thread::join ( const Thread * t )
     throw ( ThreadException , Error )
{ 
	__BEGIN_TRY

	pthread_join_ex ( t->getTID() , NULL );
	
	__END_CATCH
}

void Thread::join ( const Thread * t, void * status )
     throw ( ThreadException , Error )
{ 
	__BEGIN_TRY

	pthread_join_ex ( t->getTID() , &status );
	
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
//
// �����带 Detached ���� �ٲ۴�.
//
// � �����尡 detached ����� ���, ������ �� �ڵ������� ���� ���� ���ҽ���
// �ݳ��ϰ� �ȴ�. ���� �ƴ϶�� join()�� ���ؼ� ������ ������ ��ٷȴٰ� ���ҽ���
// �ݳ��ϰ� �ؾ� �Ѵ�. �̷��� �� ��� �ý����� �����ս��� �������� �ǹǷ�, ��κ�
// �� ������鿡 �־ �� �޽�带 ȣ�����ִ� ���� ���� ���̴�.
//
////////////////////////////////////////////////////////////////////////////////
void Thread::detach () 
     
{
	__BEGIN_TRY

	pthread_detach_ex(m_TID);
	
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
//
// ���� �����带 �����Ų��.
//
// void pthread_exit ( void * retval );
//
// �ʿ��ϴٸ� � ����Ÿ������ �����ؼ� join �ϴ� ������� �ѱ� �� �ִ�.
// (�׷���, ��κ��� ��������� detached �� ���ư��ٸ� NULL �� �����ϴ� ����
// ���� ���̴�.)
//
////////////////////////////////////////////////////////////////////////////////
void Thread::exit ( void * retval )
	 
{
	pthread_exit_ex( retval );
}


////////////////////////////////////////////////////////////////////////////////
//
// thread's start routine
//
// Thread Ŭ������ friend method �̴�.
//
// REENTRANT function �̸� ���� ���⿣ ������ �� �ѵ�.. �¼��� thread ��ü��
// thread specific data �� ������� �����̾�. ȣȪ. ������ ���� �ȿ��� ����Ǹ� 
// �Ϻ��ϰ� �ٸ� �� ���� �ʳ�? 
//
// ���� Ŭ������ run()�� virtual�� ȣ���ϱ� ���Ŀ�, �������� ���¸� RUNNING,
// EXIT�� �ٲٴµ� �����϶�. �ϴ� EXIT�� �ٲ��, ������� ���̻� ����۵� �� ����.
//
////////////////////////////////////////////////////////////////////////////////
void * start_routine ( void * derivedThread )
	   
{
	Thread * thread = (Thread *)derivedThread;
	
	// set thread's status to "RUNNING"
	thread->setStatus(Thread::RUNNING);

	// here - polymorphism used. (derived::run() called.)
	thread->run();
	
	// set thread's status to "EXIT"
	thread->setStatus(Thread::EXIT);

	Thread::exit(NULL);

	return NULL;	// avoid compiler's warning
}


////////////////////////////////////////////////////////////////////////////////
//
// ���� �������� TID �� �˾Ƴ���. static ����Լ��̴�.
//
////////////////////////////////////////////////////////////////////////////////
TID Thread::self ()
	 
{
	return pthread_self_ex();
}


////////////////////////////////////////////////////////////////////////////////
//
// return thread information string
//
////////////////////////////////////////////////////////////////////////////////
string Thread::toString () const
       
{
	__BEGIN_TRY

	StringStream msg;
	msg << "Thread[" << (uint)m_TID<< "]" ;
	return msg.toString();
	
	__END_CATCH
}
