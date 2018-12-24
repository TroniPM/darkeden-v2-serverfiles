//--------------------------------------------------------------------------------
// 
// Filename    : ThreadManager.h 
// Written By  : Reiot
// Description :
// 
//--------------------------------------------------------------------------------

#ifndef __THREAD_MANAGER_H__
#define __THREAD_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"

// forward declaration
class ThreadPool;


//////////////////////////////////////////////////////////////////////
//
// class ThreadManager
//
// ���� �������� ���(!) ������Ǯ�� �����Ѵ�. ���Ӽ����κ��� init, start,
// stop ����� �������� ���� ������Ǯ�� ���� �޽�带 ȣ���Ѵ�.
//
// init  : �� ������Ǯ�� �ɼǿ��� ������ ������ �����带 ����, ����Ѵ�.
// start : �� ������Ǯ�� ��ϵ� ��������� Ȱ��ȭ(start)��Ų��.
// stop  : �� ������Ǯ�� ��ϵ� ��������� ��Ȱ��ȭ(stop)��Ų��.
//
//////////////////////////////////////////////////////////////////////

class ThreadManager {

public:
	
	// constructor
	ThreadManager() throw(Error);
	
	// destructor
	~ThreadManager() throw(Error);

	
public:
	
	// ������ �Ŵ����� �ʱ�ȭ�Ѵ�.
	void init() throw(Error);
	
	// activate sub thread pools
	// ���� ������ Ǯ�� Ȱ��ȭ��Ų��.
	void start() throw(Error);
	
	// deactivate sub thread pools
	// ���� ������ Ǯ�� �����Ų��.
	void stop() throw(Error);

//#ifdef __NO_COMBAT__
	ThreadPool* getThreadPool(){ return m_pZoneGroupThreadPool; } // ��漮
//#endif

private:
	
	// ������Ǯ
	ThreadPool* m_pZoneGroupThreadPool;
	
};


// global variable declaration
extern ThreadManager* g_pThreadManager;

#endif
