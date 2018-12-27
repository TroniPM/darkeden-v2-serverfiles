//////////////////////////////////////////////////////////////////////
//
// MutexAttr.h
//
// by Reiot
//
//////////////////////////////////////////////////////////////////////
//
// Mutex-Attribute Class
//
// Mutex-Attribute Ŭ������ ������ �Ӽ�(attribute)�� Mutex Ŭ������ 
// ���� �� ������ �ʿ䰡 ���� �� pthread_mutex_init()�� �Ķ���ͷ� 
// ���ȴ�. �� �ϳ��� Mutex-Attribute ��ü�� �����س����� �ȴٴ� 
// ���̴�.
//
//////////////////////////////////////////////////////////////////////


#ifndef __MUTEX_ATTR_H__
#define __MUTEX_ATTR_H__

//////////////////////////////////////////////////
// include
//////////////////////////////////////////////////
#include <pthread.h>
#include "Types.h"
#include "pthreadAPI.h"
#include "Exception.h"


//////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
//
// class MutexAttr;
//
//////////////////////////////////////////////////////////////////////

class MutexAttr {

//////////////////////////////////////////////////
// constructor / destructor
//////////////////////////////////////////////////

public :
	
	// constructor
	MutexAttr ()  { pthread_mutexattr_init( &m_Attr ); }

	// destructor
	~MutexAttr ()  { pthread_mutexattr_destroy( &m_Attr ); }
	

//////////////////////////////////////////////////
// public methods
//////////////////////////////////////////////////

public :

	//
	// return mutex-attribute object
	//
	// *CAUTION* 
	//
	// do not return pthread_mutexattr_t value !!
	// use pthread_mutexattr_t pointer instead.
	// (pthread_mutexattr_t �� ���� assignment �� �������� ���� 
	// ���ɼ� ����)
	//
	pthread_mutexattr_t * getAttr ()  { return &m_Attr; }
	
	/*
	bool isFastMutex ()  { return getMutexKind() == PTHREAD_MUTEX_FAST_NP; }
	bool isRecursiveMutex ()  { return getMutexKind() == PTHREAD_MUTEX_RECURSIVE_NP; }
	bool isErrorCheckMutex ()  { return getMutexKind() == PTHREAD_MUTEX_ERRORCHECK_NP; }
	
	void setFastMutex () throw ( MutexAttrException ) { setMutexKind( PTHREAD_MUTEX_FAST_NP ); }
	void setRecursiveMutex () throw ( MutexAttrException ) { setMutexKind( PTHREAD_MUTEX_RECURSIVE_NP ); }
	void setErrorCheckMutex () throw ( MutexAttrException ) { setMutexKind( PTHREAD_MUTEX_ERRORCHECK_NP ); }

	// get mutex kind
	int getMutexKind () ;

	// set mutex kind
	void setMutexKind ( int Kind ) throw ( MutexAttrException );
	*/


//////////////////////////////////////////////////
// attributes
//////////////////////////////////////////////////

private :
	
	// mutex attribute
	pthread_mutexattr_t m_Attr;

};

#endif
