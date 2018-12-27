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
	ThreadAttr ();

	// destructor
	~ThreadAttr ();
	

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
	pthread_attr_t * getAttr ()  { return &attr; }

	// is thread attribute detached state?
	bool isDetached ()  { return getDetachState() == PTHREAD_CREATE_DETACHED; }
	
	// set thread attribute detached state
	void setDetached ()  { setDetachState(PTHREAD_CREATE_DETACHED); }

	// is thread attribute joinable state?
	bool isJoinable ()  { return getDetachState() == PTHREAD_CREATE_JOINABLE; }
	
	// set thread attribute joinable state
	void setJoinable ()  { setDetachState(PTHREAD_CREATE_JOINABLE); }


//////////////////////////////////////////////////
// protected methods
//////////////////////////////////////////////////

protected :

	// get thread attribute's state
	int getDetachState () ;

	// set thread attribute's state
	void setDetachState ( int state );


//////////////////////////////////////////////////
// attributes
//////////////////////////////////////////////////

private :
	
	// thread attribute
	pthread_attr_t attr;

};

#endif
