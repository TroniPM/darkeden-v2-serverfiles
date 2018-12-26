//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSchedule.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SCHEDULE_H__
#define __EFFECT_SCHEDULE_H__

#include "Types.h"
#include "Exception.h"
#include "Mutex.h"
#include <list>

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

enum EffectScheduleWorkCode
{
	WORKCODE_ADD_VAMPIRE_PORTAL = 0,
	WORKCODE_DELETE,

	WORKCODE_MAX
};


//////////////////////////////////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////////////////////////////////
class Effect;


//////////////////////////////////////////////////////////////////////////////
// class EffectScheduleWork
//////////////////////////////////////////////////////////////////////////////

class EffectScheduleWork
{
public:
	EffectScheduleWork() ;
	~EffectScheduleWork() ;

public:
	int getCode(void) const { return m_Code; }
	void setCode(int code) { m_Code = code; }

	void* getData(void) const { return m_pData; }
	void setData(void* pData) { m_pData = pData; }

private:
	int   m_Code;     // ����Ʈ�� ���� �۾� �ڵ�
	void* m_pData;    // ����Ʈ �۾� �ڵ忡 �ʿ��� ������
};


//////////////////////////////////////////////////////////////////////////////
// class EffectSchedule
//////////////////////////////////////////////////////////////////////////////

class EffectSchedule
{
public:
	EffectSchedule() ;
	~EffectSchedule() ;

public:
	// �۾� ����� ����Ʈ�� ���Ѵ�.
	Effect* getEffect(void) const { return m_pEffect; }
	void setEffect(Effect* pEffect) { m_pEffect = pEffect; }

	// �۾��� ���Ѵ�.
	void addWork(int WorkCode, void* pData) ;

	// �۾� �߿� ���� �տ� �ִ� �۾��� �����͸� �����Ѵ�.
	EffectScheduleWork* getFrontWork(void) ;

private:
	Effect* m_pEffect;
	list<EffectScheduleWork*> m_WorkList;
};


//////////////////////////////////////////////////////////////////////////////
// class EffectScheduleManager
//////////////////////////////////////////////////////////////////////////////

class EffectScheduleManager
{
public:
	EffectScheduleManager() ;
	~EffectScheduleManager() ;

public:
	// ����Ʈ �������� ���Ѵ�.
	void addEffectSchedule(EffectSchedule* pEffectSchedule) ;

	// ����Ʈ �������� �����Ѵ�.
	void heartbeat(void) ;

protected:
	list<EffectSchedule*> m_EffectScheduleList;
	mutable Mutex        m_Mutex;
};


#endif
