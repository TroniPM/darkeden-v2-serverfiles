//////////////////////////////////////////////////////////////////////
//
// ThreadAttr.h
//
// by Reiot
//
//////////////////////////////////////////////////////////////////////

#ifndef __THREAD_ATTR_H__
#define __THREAD_ATTR_H__

//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////
#include <pthread.h>
#include "Types.h"
#include "Exception.h"


//////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////
class ThreadAttrException;


//////////////////////////////////////////////////////////////////////
//
// class ThreadAttr;
//
// Thread-Attribute Ŭ������ ������ �Ӽ�(attribute)�� Thread Ŭ������ 
// ���� �� ������ �ʿ䰡 ���� �� pthread_create()�� �Ķ���ͷ� ���ȴ�. 
// �� �ϳ��� Thread-Attribute ��ü�� �����س����� �ȴٴ� ���̴�.
// (�ֶ󸮽� �����忡 �־ �����Ҷ����� thread-flag �� �����ߴ�
// ����� �ǻ�� ����~)
//
// �׷���, �����δ� �� ������ ���� �� �ϴ�. �ֳ��ϸ� ���� �����ϰ�
// ���� setstacksize()�� �������� ������, detach �� pthread_detach()
// �ε� ����ϱ� �����̴�.
//
//////////////////////////////////////////////////////////////////////

class ThreadAttr {

//////////////////////////////////////////////////
// constructor / destructor
//////////////////////////////////////////////////
public :
	
	// constructor
	ThreadAttr () throw ( Error );

	// destructor
	~ThreadAttr () throw ( Error );
	

//////////////////////////////////////////////////
// public methods
//////////////////////////////////////////////////
public :
	
	//
	// return thread-attribute object
	//
	// *CAUTION* 
	//
	// do not return pthread_attr_t value !!
	// use pthread_attr_t pointer instead.
	// (pthread_attr_t �� ���� assignment �� �������� ���� ���ɼ� ����)
	//
	pthread_attr_t * getAttr () throw () { return &attr; }

	// is thread attribute detached state?
	bool isDetached () const throw ( Error ) { return getDetachState() == PTHREAD_CREATE_DETACHED; }
	
	// set thread attribute detached state
	void setDetached () throw ( Error ) { setDetachState(PTHREAD_CREATE_DETACHED); }

	// is thread attribute joinable state?
	bool isJoinable () const throw ( Error ) { return getDetachState() == PTHREAD_CREATE_JOINABLE; }
	
	// set thread attribute joinable state
	void setJoinable () throw ( Error ) { setDetachState(PTHREAD_CREATE_JOINABLE); }


//////////////////////////////////////////////////
// protected methods
//////////////////////////////////////////////////

protected :

	// get thread attribute's state
	int getDetachState () const throw ( Error );

	// set thread attribute's state
	void setDetachState ( int state ) throw ( Error );


//////////////////////////////////////////////////
// attributes
//////////////////////////////////////////////////

private :
	
	// thread attribute
	pthread_attr_t attr;

};

#endif
