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
	EffectScheduleWork() throw();
	~EffectScheduleWork() throw();

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
	EffectSchedule() throw();
	~EffectSchedule() throw();

public:
	// �۾� ����� ����Ʈ�� ���Ѵ�.
	Effect* getEffect(void) const { return m_pEffect; }
	void setEffect(Effect* pEffect) { m_pEffect = pEffect; }

	// �۾��� ���Ѵ�.
	void addWork(int WorkCode, void* pData) throw();

	// �۾� �߿� ���� �տ� �ִ� �۾��� �����͸� �����Ѵ�.
	EffectScheduleWork* getFrontWork(void) throw();

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
	EffectScheduleManager() throw();
	~EffectScheduleManager() throw();

public:
	// ����Ʈ �������� ���Ѵ�.
	void addEffectSchedule(EffectSchedule* pEffectSchedule) throw();

	// ����Ʈ �������� �����Ѵ�.
	void heartbeat(void) throw();

protected:
	list<EffectSchedule*> m_EffectScheduleList;
	mutable Mutex        m_Mutex;
};


#endif
