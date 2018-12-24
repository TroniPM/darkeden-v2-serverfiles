//////////////////////////////////////////////////////////////////////
//
// Filename    : ZoneGroupThread.h
// Written by  : reiot@ewestsoft.com
// Description : 
//
//////////////////////////////////////////////////////////////////////

#ifndef __ZONE_THREAD_H__
#define __ZONE_THREAD_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Thread.h"
#include "ZoneGroup.h"

//////////////////////////////////////////////////////////////////////
//
// class ZoneGroupThread;
//
// �ϳ��� ���׷�(ZoneGroup)�� �þƼ� �����ϴ� ������μ�, ���׷쿡 
// ���ӵ� PC, ���� �Ҽӵ� NPC�� MOB, ���� ���� ó��.. ���� �����Ѵ�.
// �� ���׷쿡���� ���� ó���� �̷������ �ȴ�.
//
//////////////////////////////////////////////////////////////////////

class ZoneGroupThread : public Thread {

public:

	// constructor
	ZoneGroupThread(ZoneGroup* pZoneGroup) throw();

	// destructor
	~ZoneGroupThread() throw();

	// main method
	void run() throw();

	// get debug string
	string toString() const throw();

	// get thread's name
	string getName() const throw() { return "ZoneGroupThread"; }

	ZoneGroup* getZoneGroup(){ return m_pZoneGroup; }

private:

	ZoneGroup* m_pZoneGroup;
};

#endif
